#include "stdafx.h"
#include "Bridge.h"

Bridge::Bridge()
{
	m_skinModel.Init(L"Assets/modelData/bridge.cmo");
	m_skinModel.LoadNormalMap(L"Assets/modelData/vol_2_3_Normal.dds");
	m_skinModel.LoadAoMap(L"Assets/modelData/vol_2_3_Ambient_Occlusion.dds");
}


Bridge::~Bridge()
{
}

void Bridge::Update()
{
	g_goMgr.FindGameObjects<Button>("button", [&](Button* button)->bool {
		if (button->GetState() == button->enState_0) {
			if (!m_isCreatePhysics) {
				//�{�^���������ꂽ�Aphysics���
				m_physicsStaticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
				m_isCreatePhysics = true;
			}
		}
		else {
			if (m_isCreatePhysics) {
				//�ʏ펞�Aphysics�폜���Ă����B
				m_physicsStaticObject.Delete();
				m_isCreatePhysics = false;
			}
		}
		return true;
		});
	//���[���h�s��̍X�V�B
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Bridge::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	m_skinModel.RimLightOff();		//�������C�g�I�t
	m_skinModel.ToonOff();
	g_goMgr.FindGameObjects<Button>("button", [&](Button* button)->bool {
		if(button->GetState() == button->enState_0){
			//�{�^���������ꂽ��f�B�U�����O�I�t
			m_skinModel.DitheringOff();
		}
		else{
			//�ʏ펞�f�B�U�����O�I��
			m_skinModel.DitheringOn();
		}
		return true;
	});
}