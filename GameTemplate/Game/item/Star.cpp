#include "stdafx.h"
#include "Star.h"
#include "../player/Player.h"
#include "Game.h"

namespace {
	const int CLEAR_TIME = 25;							//�N���A�܂ł̎���
	const float ROTATION_SPEED = 5.0f;					//��]���x
	const float GET_STAR_POSITION_Y = 100.0f;			//�����������Y�̈ʒu
	const float DLIG_COLOR = 1.8f;						//�f�B���N�V�������C�g�̖��邳	
	const float POS_Y = 150.0f;							//���̍���
}
Star::Star()
{
	m_skinModel.Init(L"Assets/modelData/star.cmo");
	m_ghost.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
}


Star::~Star()
{
}

void Star::Update()
{
	//���[���h�s��̍X�V�B
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//��]
	Rotation();
	m_player = g_goMgr.FindGameObject<Player>("player");
	m_game = g_goMgr.FindGameObject<Game>("game");
	if (m_player != nullptr
		&& m_game != nullptr) {
		//�����������v���C���[�̓����
		if (m_game->GetStar()) {
			m_timer++;
			auto pos = m_player->GetPositon();
			if (m_player->GetisItem()) {
				//�ʏ펞
				pos.y += POS_Y;
			}
			else {
				//�A�C�e���ő傫���Ȃ��Ă鎞
				pos.y += GET_STAR_POSITION_Y;
			}
			m_position = pos;
			if (m_timer == CLEAR_TIME) {
				m_getStar = true;
			}
		}
	}
	//�S�[�X�g�X�V
	m_ghost.SetPosition(m_position);
	m_ghost.SetRotation(m_rotation);
}

void Star::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	//�������C�g�I�t
	m_skinModel.RimLightOff();
	m_skinModel.ToonOff();
	m_skinModel.ShadowReciverOff();
	//���C�g�̕����E���邳
	m_skinModel.SetDligColor(0, DLIG_COLOR);
	m_skinModel.SetDligColor(1, DLIG_COLOR);
}

void Star::Rotation()
{
	//��葬�x�ŉ�]������
	float rotSpeed = 0.0f;;
	rotSpeed += ROTATION_SPEED;
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
	m_rotation.Multiply(addRot);
}
