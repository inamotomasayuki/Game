#include "stdafx.h"
#include "GameCamera.h"
#include "player/Player.h"
#include "Game.h"
#include "GameData.h"
namespace {
	const float CAMERA_POS_Y_UNDER = -0.2f;						//�J�����ʒu�Ⴓ
	const float CAMERA_POS_Y_UPPER = 0.8f;						//�J�����ʒu����
	const float CAMERA_TARGET_Y = 100.0f;						//�J�����^�[�Q�b�gY�ʒu
	const float CAMERA_LENGTH_MIN = 100.0f;						//�J�����ŏ�����
	const float CAMERA_LENGTH_MAX = 1000.0f;					//�J�����ő勗��
	const CVector3 CAMERA_POS = { 0.0f, 300.0f, -500.0f };		//�J�����ʒu
	const CVector3 CAMERA_UP_POS = { 1000.0f, 0.0f, 0.0f };		//�J�����ʒu
	const CVector3 CAMERA_TARGET = { 0.0f, 100.0f, 0.0f };		//�J�����^�[�Q�b�g
	const float CAMERA_FAR = 100000.0f;							//�J����������

	const CVector3 CAMERA_POS_STAGE_ONE = { 0.0f, 10.0f, 1000.0f };	//�X�e�[�W�P�̃J�����ʒu
	const float GAMECLEAR_CAMERA_POS_Y = 200.0f;			//�Q�[���N���A�J�����̍���
	const float GAMEOVER_CAMERA_POS_Y = 2000.0f;			//�Q�[���I�[�o�[�J�����̍���
	const float ZOOM_SPEED = 15.0f;							//�Y�[�����x
	const float CLEAR_CAMERA_ZOOM_SPEED = 0.97f;			//�N���A���̃J�����̃Y�[�����x
	const float CLEAR_CAMERA_START_LENGTH = 1000.0f;		//�N���A�������̃J�����̋���
	const float CLEAR_CAMERA_END_LENGTH = 300.0f;			//�Y�[��������̃J�����̋���

}

GameCamera::GameCamera()
{
	//�X�e�[�W�P
	if (g_gameData.GetStageNo() == g_gameData.enStage_Zero) {
		g_camera3D.SetPosition(CAMERA_POS);
		g_camera3D.SetTarget(CAMERA_TARGET);
		g_camera3D.SetFar(CAMERA_FAR);
	}
	//�X�e�[�W�Q
	if (g_gameData.GetStageNo() == g_gameData.enStage_One) {
		g_camera3D.SetPosition(CAMERA_POS_STAGE_ONE);
		g_camera3D.SetTarget(CAMERA_TARGET);
		g_camera3D.SetFar(CAMERA_FAR);
	}
}

GameCamera::~GameCamera()
{

}

void GameCamera::Update()
{
	m_player = g_goMgr.FindGameObject<Player>("player");
	m_game = g_goMgr.FindGameObject<Game>("game");
	if (m_player != nullptr
		&& m_game != nullptr) {
		m_cameraTarget = m_player->GetPositon();	//�����_���v�Z����
		m_cameraTarget.y += CAMERA_TARGET_Y;		//�v���C���[�̑������炿����Ə�𒍎��_�Ƃ���
		//�X�e�[�W�P�J����
		StageOneCamera();
		//�Q�[���I�[�o�[���A���_��߂�
		if (m_game->GetIsStop() && !m_player->IsOnGround()) {
			if (!m_isStop) {
				auto pos = m_player->GetPositon();
				pos += CAMERA_POS;
				g_camera3D.SetPosition(pos);
				m_isStop = true;
			}
		}
		m_cameraPos = g_camera3D.GetPosition();					//���_
		m_toCameraPos = m_cameraPos - g_camera3D.GetTarget();	//�����_
		//��]
		Rotation();
		//���_���v�Z����
		m_cameraPos = m_cameraTarget + m_toCameraPos;
		//�Q�[���N���A�J����
		GameClearCamera();
		//�Q�[���I�[�o�[�J����
		GameOverCamera();
		if (!m_game->GetIsStar()) {
			//�Y�[���C���E�A�E�g
			ZoomInAndOut();
		}
		g_camera3D.SetTarget(m_cameraTarget);
		g_camera3D.SetPosition(m_cameraPos);
		g_camera3D.Update();
	}
}

void GameCamera::Rotation()
{
	CVector3 toCameraPosOld = m_toCameraPos;
	//Y������̉�]
	if (g_gameData.GetStageNo() != g_gameData.enStage_One) {
		if (!m_game->GetStar()) {
			m_rotation.SetRotationDeg(CVector3::AxisY(), g_pad[0].GetRStickXF() * 6.0f);
		}
		m_rotation.Multiply(m_toCameraPos);
	}
	//X������̉�]
	const CVector3& vUP = CVector3::Up();
	CVector3 vRotAxis;
	vRotAxis.Cross(m_toCameraPos, vUP);
	vRotAxis.Normalize();
	if (g_gameData.GetStageNo() != g_gameData.enStage_One) {
		if (!m_game->GetStar()) {
			if (!g_pad[0].IsPress(enButtonLB1)) {
				m_rotation.SetRotationDeg(vRotAxis, g_pad[0].GetRStickYF() * -6.0f);
			}
		}
		m_rotation.Multiply(m_toCameraPos);
	}
	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	auto toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (g_gameData.GetStageNo() != g_gameData.enStage_One) {
		if (toPosDir.y < CAMERA_POS_Y_UNDER) {
			//�J�����������������B
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > CAMERA_POS_Y_UPPER) {
			//�J����������������B
			m_toCameraPos = toCameraPosOld;
		}
	}
}

void GameCamera::ZoomInAndOut()
{
	//����O�̈ʒu
	auto cameraPosOld = m_cameraPos;
	//�J��������J�����^�[�Q�b�g�ւ̕���
	auto v = g_camera3D.GetTarget() - g_camera3D.GetPosition();
	v.Normalize();
	if (g_gameData.GetStageNo() != g_gameData.enStage_One) {
		//LB�P�{�^���������Ȃ���E�X�e�B�b�N�Ŏ��_���Y�[�����삷��
		if (g_pad[0].IsPress(enButtonLB1)) {
			m_moveSpeed = v * g_pad[0].GetRStickYF() * ZOOM_SPEED;
			m_cameraPos += m_moveSpeed;
		}
	}
	//�����̈ʒu�Ƃ̋���
	//�߂�or�����Ȃ����瑀��O�̈ʒu�ɖ߂��B
	auto vec = g_camera3D.GetTarget() - m_cameraPos;
	auto len = vec.Length();
	if (len < CAMERA_LENGTH_MIN) {
		m_cameraPos = cameraPosOld;
	}
	else if (len > CAMERA_LENGTH_MAX) {
		m_cameraPos = cameraPosOld;
	}
}

void GameCamera::StageOneCamera()
{
	if (g_gameData.GetStageNo() == g_gameData.enStage_One) {
		if (m_player->GetButtonState() == 1) {
			m_isButtonYoko = true;
		}
		else {
			m_isButtonMae = true;
		}
		//������
		if (m_isButtonYoko) {
			auto pos = m_player->GetPositon();
			pos += CAMERA_UP_POS;
			pos.y += CAMERA_TARGET_Y;
			g_camera3D.SetPosition(pos);
			m_isButtonYoko = false;
		}
		//�O����
		if (m_isButtonMae) {
			auto pos = m_player->GetPositon();
			pos += CAMERA_POS_STAGE_ONE;
			pos.y += CAMERA_TARGET_Y;
			g_camera3D.SetPosition(pos);
			m_isButtonMae = false;
		}
	}
}

void GameCamera::GameClearCamera()
{
	if (m_game->GetIsStar()) {
		if (!m_isClearCameraInit) {
			//�J�����̈ʒu�𐳖ʌ����ŗ���
			m_clearPos = m_player->GetPositon() - m_cameraPos;
			m_clearPos.y = GAMECLEAR_CAMERA_POS_Y;
			m_clearPos.Normalize();
			m_nextCameraPos = m_clearPos;
			m_nextCameraPos *= CLEAR_CAMERA_END_LENGTH;
			m_clearPos *= CLEAR_CAMERA_START_LENGTH;
			m_isClearCameraInit = true;
		}
		//�Y�[������
		if (m_nextCameraPos.Length() < m_clearPos.Length()) {
			m_clearPos *= CLEAR_CAMERA_ZOOM_SPEED;
		}
		m_cameraPos = m_cameraTarget + m_clearPos;
	}
}

void GameCamera::GameOverCamera()
{
	if (!m_game->GetGameOverFlag()) {
		m_oldPos = m_cameraPos;
		m_oldPos.y += GAMEOVER_CAMERA_POS_Y;
	}
	else if (m_game->GetGameOverFlag()
		&& !m_game->GetIsHp0GameOver()
		&& !m_player->IsOnGround()) {
		if (m_game->GetIsStop()) {
			m_cameraPos = m_cameraTarget + m_toCameraPos;
		}
		else {
			//���_���ォ��ɂ���
			m_cameraPos = m_oldPos;
		}
	}
}