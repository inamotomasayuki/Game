#include "stdafx.h"
#include "PlayerWarpState.h"
#include "Player.h"
#include "../gimmick/Warp.h"

namespace {
	const float ROTATION_SPEED = 1.0f;				//��]���Z���x
	const int WARP_TIMER = 100;						//���[�v����
	const float SE_VOLUME = 1.0f;					//�{�����[��

}

PlayerWarpState::PlayerWarpState()
{
	//������
	Init();
}


PlayerWarpState::~PlayerWarpState()
{
	//�폜
	Delete();
}

void PlayerWarpState::Update(Player* p)
{
	//���[�v����]�ړ�����
	Rotation(p);
	//�T�E���h
	Sound();
}

void PlayerWarpState::Init()
{
	//�T�E���h
	for (int i = 0; i < enSE_Num; i++) {
		m_se[i] = g_goMgr.NewGameObject<CSoundSource>(0);
	}
	m_se[enSE_warp0]->Init(L"Assets/sound/warp0.wav");				//���[�v�O
	m_se[enSE_warp1]->Init(L"Assets/sound/warp1.wav");				//���[�v��
}

void PlayerWarpState::Delete()
{
	//�T�E���h�폜
	for (int i = 0; i < enSE_Num; i++) {
		g_goMgr.DeleteGameObject(m_se[i]);
	}
}

void PlayerWarpState::Rotation(Player* p)
{
	const auto& warp = g_goMgr.FindGameObject<Warp>("warp");
	if (!m_isRotReverse && warp->IsWarp()) {
		m_isRotStart = true;
	}
	//��]���x���グ��
	if (m_isRotStart) {
		m_warpTimer++;
		m_rotSpeed += ROTATION_SPEED;
	}
	if (m_warpTimer == WARP_TIMER) {
		//�ړ���Ɉړ�
		p->SetCharaConPos(warp->GetPosition());
		m_isRotReverse = true;
		m_warpTimer = 0;
	}
	//���[�v��ŉ�]���x���Ƃ�
	if (m_isRotReverse) {
		m_isRotStart = false;
		if (m_rotSpeed > 0) {
			m_rotSpeed -= ROTATION_SPEED;
		}
		else {
			//���[�v����
			warp->SetIsWarp(false);
			m_isRotReverse = false;
		}
	}
	//��]���v���C���[�ɑ���
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), m_rotSpeed);
	auto pRot = p->GetRotation();
	pRot.Multiply(addRot);
	p->SetRotation(pRot);
}

void PlayerWarpState::Sound()
{
	//���[�v��
	if (m_isRotStart) {
		m_se[enSE_warp0]->Play(false);
	}
	if (m_isRotReverse) {
		m_se[enSE_warp0]->Stop();
		m_se[enSE_warp1]->SetVolume(SE_VOLUME);
		m_se[enSE_warp1]->Play(false);
	}
	else {
		m_se[enSE_warp1]->Stop();
	}
}