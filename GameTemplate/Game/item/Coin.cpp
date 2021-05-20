#include "stdafx.h"
#include "Coin.h"
#include "Game.h"
namespace {
	const float PYON_UP = 20.0f;			//���ˏオ��Ƃ��̑��x
	const float PYON_DOWN = -20.0f;			//���˗�����Ƃ��̑��x
	const int PYON_UP_TIME = 5;				//���ˏオ�鎞��
	const int PYON_DOWN_TIME = 8;			//���˗����鎞��
	const int DELETE_TIME = 10;				//�폜�܂ł̑҂�����
	const int COIN_SCORE = 1;				//�R�C���̃X�R�A
	const float FLAG_LENGTH = 110.0f;		//�R�C���擾�t���O������v���C���[�Ƃ̋���
	const float ROTATION_SPEED = 5.0f;		//��]���x
	const float DLIG_COLOR = 2.0f;		    //�f�B���N�V�������C�g�̖��邳
	//�A���r�G���g���C�g
	const CVector4 AMBIENT[2] = {
		{ 0.5f,0.5f,0.5f,1.0f },
		{ 0.1f,0.1f,0.1f,1.0f }
	};
	const float LIG_LENGTH = 6000.0f;		//���邳����
}

Coin::Coin()
{
	m_skinModel.Init(L"Assets/modelData/coin.cmo");
	//�S�[�X�g
	m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
	//���ʉ�
	m_se = g_goMgr.NewGameObject<CSoundSource>(0);
	m_se->Init(L"Assets/sound/coin.wav");
}


Coin::~Coin()
{

}

void Coin::Update()
{	
	m_player = g_goMgr.FindGameObject<Player>("player");
	m_game = g_goMgr.FindGameObject<Game>("game");

	//��]
	Rotation();
	//�R�C���擾����
	GetCoin();	
	//���[���h�s��̍X�V�B
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//�S�[�X�g�X�V
	m_ghostObject.SetPosition(m_position);
	m_ghostObject.SetRotation(m_rotation);

}
void Coin::Draw()
{
	//�`��
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	//�������C�g�I�t
	m_skinModel.RimLightOff();
	m_skinModel.ToonOff();
	//�V���h�E���V�[�o�[�I�t
	m_skinModel.ShadowReciverOff();
	//���C�g�̕����E���邳�ݒ�
	auto dir = m_position - g_camera3D.GetPosition();
	auto len = dir.Length();
	if (len > LIG_LENGTH) {
		m_skinModel.SetAmbient(AMBIENT[0]);
	}
	else{
		m_skinModel.SetAmbient(AMBIENT[1]);
	}	
	m_skinModel.SetDligColor(0, DLIG_COLOR);
	m_skinModel.SetDligColor(1, DLIG_COLOR);
}
void Coin::Rotation()
{
	auto dir = m_position - g_camera3D.GetPosition();
	auto len = dir.Length();
	//��葬�x�ŉ�]������
	float rotSpeed = 0.0f;;
	rotSpeed += ROTATION_SPEED;
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
	m_addRot.Multiply(addRot);
	if (len <= LIG_LENGTH) {
		if (!m_isInit) {
			m_rotation = CQuaternion::Identity();
			m_isInit = true;
		}
		m_rotation = m_addRot;
	}
	else {
		m_isInit = false;
		//�J�����̉�]�s����擾
		CMatrix mRotCamera = g_camera3D.GetViewMatrix();
		//�J�����s��̋t�s��̓J�����̃��[���h�s��B
		mRotCamera.Inverse(mRotCamera);
		//���s�ړ������͂���Ȃ��B
		mRotCamera.m[3][0] = 0.0f;
		mRotCamera.m[3][1] = 0.0f;
		mRotCamera.m[3][2] = 0.0f;
		//�J�����̉�]�s�񂩂�A�R�C���̉�]�N�H�[�^�j�I�������߂�B
		m_rotation.SetRotation(mRotCamera);
	}
}

void Coin::GetCoin()
{
	if (m_player != nullptr) {
		const CVector3& v = m_player->GetPositon() - m_position;
		float len = v.Length();
		//���������ȉ��Ȃ�擾�t���O�𗧂Ă�
		if (len < FLAG_LENGTH) {
			m_coinGetFlag = true;
		}
	}
	g_goMgr.FindGameObjects<EnemyBall>("enemyBall", [this](EnemyBall* enemyBall)->bool {
		const auto& enemy_v = enemyBall->GetPositon() - m_position;
		auto enemy_len = enemy_v.Length();
		//�b���ƈ�苗���Ȃ�t���O�𗧂Ă�
		if (enemy_len < FLAG_LENGTH) {
			m_coinGetFlag = true;
		}
		return true;
		});
	//�t���O���������璵�˂�����
	if (m_coinGetFlag == true) {
		m_timer++;
		m_se->Play(false);
		if (m_timer < PYON_UP_TIME) {
			m_moveSpeed.y = PYON_UP;
			m_position += m_moveSpeed;
		}
		if (m_timer >= PYON_UP_TIME && m_timer < PYON_DOWN_TIME) {
			m_moveSpeed.y = PYON_DOWN;
			m_position += m_moveSpeed;
		}
		//�폜
		if (m_timer == DELETE_TIME) {	
			m_timer = 0;
			m_game->SetScore(COIN_SCORE);
			g_goMgr.DeleteGameObject(this);
		}
	}
}