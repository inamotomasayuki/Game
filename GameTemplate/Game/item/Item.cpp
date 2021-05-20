#include "stdafx.h"
#include "Item.h"
#include "../gimmick/Box.h"
#include "../player/Player.h"

namespace {
	const float MOVE_SPEED = 2.0f;				//�オ�鑬�x
	const float DOWN_SPEED = 5.0f;				//�����鑬�x
	const float ROTATION_SPEED = 3.0f;			//��]���x
	const float DLIG_COLOR = 1.5f;				//�f�B���N�V�������C�g�̖��邳
}

Item::Item()
{
	m_skinModel.Init(L"Assets/modelData/mikan.cmo");
	m_se = g_goMgr.NewGameObject<CSoundSource>(0);
	m_se->Init(L"Assets/sound/kyodaika.wav");		//���剻
}


Item::~Item()
{
}

void Item::Update()
{
	const auto& player = g_goMgr.FindGameObject<Player>("player");
	if (m_isHipDrop) {
		if (m_posDown < m_position.y) {
			m_position.y -= DOWN_SPEED;
		}
		else {
			//�S�[�X�g�쐬
			if (!m_isInit) {
				m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
				m_isInit = true;
			}
		}
	}
	else{
		if (!m_isInit) {
			m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
			m_isInit = true;
		}
		if (player != nullptr) {
			//�オ���Ă���
			if (m_posUp > m_position.y) {
				m_position.y += MOVE_SPEED;
			}
		}
	}
	//�폜
	if (m_isGet) {
		if (player != nullptr) {
			if (!player->GetisItem()) {
				m_se->Play(false);
			}
		}
		g_goMgr.DeleteGameObject(this);
	}
	//��]
	Rotation();
	//���[���h�s��̍X�V�B
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_ghostObject.SetPosition(m_position);
}
void Item::Rotation()
{
	//��葬�x�ŉ�]������
	float rotSpeed = 0.0f;;
	rotSpeed += ROTATION_SPEED;
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
	m_rotation.Multiply(addRot);
}
void Item::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	//�������C�g�I�t
	m_skinModel.RimLightOff();
	//�I�t
	m_skinModel.ToonOff();
	m_skinModel.ShadowReciverOff();
	//���C�g�̕����E���邳�ݒ�
	m_skinModel.SetDligColor(0, DLIG_COLOR);
	m_skinModel.SetDligColor(1, DLIG_COLOR);
}