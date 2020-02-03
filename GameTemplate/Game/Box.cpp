#include "stdafx.h"
#include "Box.h"
#include "Coin.h"

const float ITEM_UNDER_POS = 100.0f;		//アイテムの出現位置
const float COIN_UP_POS = 40.0f;		//コイン上位置
const float COIN_UNDER_POS = 180.0f;		//コイン下位置
const float COIN_SCALE = 0.5f;		//コイン大きさ
Box::Box()
{
	m_skinModel.Init(L"Assets/modelData/Boxmae.cmo");
	m_ghostObject.CreateBox(m_ghostPos, m_rotation, m_ghostScale);
	m_ghostMesh.CreateMesh(m_ghostMeshPos, m_rotation, m_ghostScale, m_skinModel);
	m_staticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
	m_se.Init(L"Assets/sound/boxPoko.wav");		//箱アイテム
}


Box::~Box()
{
}
void Box::Update()
{
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_ghostObject.SetPosition(m_ghostPos);
	m_ghostMesh.SetPosition(m_ghostMeshPos);
	m_staticObject.SetPositionAndRotation(m_position, m_rotation);

	if (m_isContact) {
		if (!m_isInitModel) {
			m_skinModel.Init(L"Assets/modelData/Boxato.cmo");
			m_isInitModel = true;
			if (m_itemState == enItem_mikan) {
				m_se.Play(false);
				m_item = g_goMgr.NewGameObject<Item>("item");
				CVector3 itemPos = m_position;
				itemPos.y -= ITEM_UNDER_POS;
				if (!m_isHipDrop) {
					m_item->SetPosition(m_position);
				}
				else {
					m_item->SetPosition(itemPos);
				}	
			}
			if (m_itemState == enItem_coin) {
				m_coin = g_goMgr.NewGameObject<Coin>("coin");
				m_coin->SetCoinGet();
				CVector3 itemPos = m_position;
				m_coin->SetScale(m_scale * COIN_SCALE);
				if (!m_isHipDrop) {			
					itemPos.y += COIN_UP_POS;
					m_coin->SetPosition(itemPos);
				}
				else {
					itemPos.y -= COIN_UNDER_POS;
					m_coin->SetPosition(itemPos);
				}
			}
		}
	}
}
void Box::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	m_skinModel.RimLightOff();
}