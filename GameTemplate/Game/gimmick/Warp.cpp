#include "stdafx.h"
#include "Warp.h"
#include "../player/Player.h"
namespace {
	const float ROTATION_SPEED = 2.0f;					//��]���x
	const float LENGTH_NEAR = 50.0f;				//�߂�	
	const float LENGTH_LEAVE = 100.0f;				//���ꂽ
	const float EFFECT_SCALE = 10.0f;				//�G�t�F�N�g�̑傫��
}

Warp::Warp()
{
	m_skinModel[enState_00].Init(L"Assets/modelData/warp.cmo");
	m_skinModel[enState_01].Init(L"Assets/modelData/warp.cmo");
	//�������C�g�I�t
	for (int i = 0; i < enState_Num; i++) {
		m_skinModel[i].RimLightOff();
		//�G�t�F�N�g
		m_effect[i] = g_goMgr.NewGameObject<EffectEngine>(0);
		//�G�t�F�N�g�����[�h����B
		m_effect[i]->SetFilePath(L"Assets/effect/uzu.efk");
	}
}


Warp::~Warp()
{
	for (int i = 0; i < enState_Num; i++) {
		g_goMgr.DeleteGameObject(m_effect[i]);
	}
}

void Warp::Update()
{
	//��]
	Rotation();
	//���[�v
	m_player = g_goMgr.FindGameObject<Player>("player");
	if (m_player != nullptr) {
		for (int i = 0; i < enState_Num; i++) {
			const auto& v = m_position[i] - m_player->GetPositon();
			auto len = v.Length();
			if (!m_isWarp && m_isPossible) {
				//�v���C���[���߂��ɗ�����t���O�𑗂�
				if (len < LENGTH_NEAR) {
					m_stateNum = i + 1;
					if (m_stateNum == enState_Num) {
						m_stateNum = 0;
					}
					m_isWarp = true;
					m_isPossible = false;
				}
			}
		}
		if (!m_isWarp && !m_isPossible) {
			//����Ă�����ēx���[�v���\�ɂ���t���O�𑗂�
			const auto& v = m_position[m_stateNum] - m_player->GetPositon();
			auto len = v.Length();
			if (len > LENGTH_LEAVE) {
				m_isPossible = true;
			}
		}
	}
	//�G�t�F�N�g���Đ�����B
	for (int i = 0; i < enState_Num; i++) {
		m_effect[i]->PlayAndSetPos(m_position[i]);
		m_effect[i]->SetScale(m_scale[i] * EFFECT_SCALE);
	}
	//���[���h�s��̍X�V�B
	for (int i = 0; i < enState_Num; i++) {
		m_skinModel[i].UpdateWorldMatrix(m_position[i], m_rotation[i], m_scale[i]);
	}

}
void Warp::Draw()
{
	for (int i = 0; i < enState_Num; i++) {
		m_skinModel[i].Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			enRenderMode_Normal
		);
	}
}
void Warp::Rotation()
{
	//��葬�x�ŉ�]������
	float rotSpeed = 0.0f;;
	rotSpeed += ROTATION_SPEED;
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
	for (int i = 0; i < enState_Num; i++) {
		m_rotation[i].Multiply(addRot);
	}
}