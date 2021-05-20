#include "stdafx.h"
#include "Wall.h"

Wall::Wall()
{
}


Wall::~Wall()
{
}

void Wall::Update()
{
	//������
	if (!m_isInit) {
		Init();
		m_isInit = true;
	}
	//�f�B�U�����O�ŏ��X�ɏ����Ă����A��������폜
	g_goMgr.FindGameObjects<Button>("button1", [&](Button* button)->bool {
		if (button->GetState() == button->enState_1) {
			if (m_skinModel.GetDitheringPow() == 0) {
				g_goMgr.DeleteGameObject(this);
			}
		}
		return true;
	});

	//���[���h�s��̍X�V�B
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);
}

void Wall::Draw()
{
	if (m_isInit) {
		m_skinModel.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			enRenderMode_Normal
		);
		//�������C�g�I�t
		m_skinModel.RimLightOff();
		//�g�D�[���I�t
		m_skinModel.ToonOff();
		//�{�^���������ꂽ��f�B�U�����O�̃I��
		g_goMgr.FindGameObjects<Button>("button1", [&](Button* button)->bool {
			if (button->GetState() == button->enState_1) {
				m_skinModel.DitheringOn();
				m_skinModel.DecDitheringPow();
			}
			return true;
			});
	}
}
void Wall::Init()
{
	m_skinModel.Init(L"Assets/modelData/UCW_Wall0.cmo");
	m_skinModel.LoadNormalMap(L"Assets/modelData/Stone_floor_n.dds");
	m_physicsStaticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
	//������ƕϊ�
	auto y = m_scale.z;
	m_scale.z = m_scale.y;
	m_scale.y = y;
}