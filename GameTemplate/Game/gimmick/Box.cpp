#include "stdafx.h"
#include "Box.h"
#include "../item/Coin.h"
#include "../item/Item.h"

namespace {
	const float COIN_POS = 70.0f;		//�R�C���ʒu
	const float COIN_SCALE = 0.8f;		//�R�C���傫��
	const float ITEM_POS = 30.0f;		//�A�C�e���ʒu
}

Box::Box()
{
	m_skinModel.Init(L"Assets/modelData/Boxmae.cmo");
	m_ghostObject.CreateBox(m_ghostPos, m_rotation, m_ghostScale);
	m_meshGhostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
	m_staticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
	m_se = g_goMgr.NewGameObject<CSoundSource>(0);	//SE
	m_se->Init(L"Assets/sound/boxPoko.wav");		//���A�C�e��
}


Box::~Box()
{
}
void Box::Update()
{
	//������@���ꂽ
	if (m_isContact) {
		if (!m_isInitModel) {
			m_skinModel.Init(L"Assets/modelData/Boxato.cmo");
			m_isInitModel = true;
			//�݂���
			if (m_itemState == enItem_mikan) {
				m_se->Play(false);
				const auto& m_item = g_goMgr.NewGameObject<Item>("item");
				m_item->SetPosition(m_position);
			}
			//�R�C��
			if (m_itemState == enItem_coin) {
				const auto& m_coin = g_goMgr.NewGameObject<Coin>("coin");
				m_coin->SetCoinGet();
				//�傫������̂ŏ���������
				m_coin->SetScale(m_scale * COIN_SCALE);
				//�ʒu�������グ��
				CVector3 itemPos = m_position;
				itemPos.y += COIN_POS;
				m_coin->SetPosition(itemPos);
			}
		}
	}
	//�q�b�v�h���b�v���ꂽ
	if (m_isHipDrop) {
		if (!m_isInitModel) {
			m_skinModel.Init(L"Assets/modelData/Boxato.cmo");
			m_isInitModel = true;
			//�݂���
			if (m_itemState == enItem_mikan) {
				m_se->Play(false);
				const auto& m_item = g_goMgr.NewGameObject<Item>("item");	
				m_item->IsHipDrop();
				auto pos = m_position;
				pos.y -= ITEM_POS;
				m_item->SetPosition(pos);
			}
			//�R�C��
			if (m_itemState == enItem_coin) {
				const auto& m_coin = g_goMgr.NewGameObject<Coin>("coin");
				m_coin->SetCoinGet();
				//�傫������̂ŏ���������
				m_coin->SetScale(m_scale * COIN_SCALE);
				//�ʒu������������
				CVector3 itemPos = m_position;
				itemPos.y -= COIN_POS;
				m_coin->SetPosition(itemPos);
			}
		}
	}
	//���[���h�s��̍X�V�B
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//�S�[�X�g�̍X�V
	m_ghostObject.SetPosition(m_ghostPos);
	m_meshGhostObject.SetPosition(m_position);
	//�ÓI�����I�u�W�F�N�g�̍X�V
	m_staticObject.SetPositionAndRotation(m_position, m_rotation);
}
void Box::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	//�������C�g�I�t
	m_skinModel.RimLightOff();
	m_skinModel.ToonOff();
}
