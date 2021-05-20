#include "stdafx.h"
#include "Box.h"
#include "../item/Coin.h"
#include "../item/Item.h"

namespace {
	const float COIN_POS = 70.0f;		//コイン位置
	const float COIN_SCALE = 0.8f;		//コイン大きさ
	const float ITEM_POS = 30.0f;		//アイテム位置
}

Box::Box()
{
	m_skinModel.Init(L"Assets/modelData/Boxmae.cmo");
	m_ghostObject.CreateBox(m_ghostPos, m_rotation, m_ghostScale);
	m_meshGhostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
	m_staticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
	m_se = g_goMgr.NewGameObject<CSoundSource>(0);	//SE
	m_se->Init(L"Assets/sound/boxPoko.wav");		//箱アイテム
}


Box::~Box()
{
}
void Box::Update()
{
	//下から叩かれた
	if (m_isContact) {
		if (!m_isInitModel) {
			m_skinModel.Init(L"Assets/modelData/Boxato.cmo");
			m_isInitModel = true;
			//みかん
			if (m_itemState == enItem_mikan) {
				m_se->Play(false);
				const auto& m_item = g_goMgr.NewGameObject<Item>("item");
				m_item->SetPosition(m_position);
			}
			//コイン
			if (m_itemState == enItem_coin) {
				const auto& m_coin = g_goMgr.NewGameObject<Coin>("coin");
				m_coin->SetCoinGet();
				//大きすぎるので少し小さく
				m_coin->SetScale(m_scale * COIN_SCALE);
				//位置を少し上げる
				CVector3 itemPos = m_position;
				itemPos.y += COIN_POS;
				m_coin->SetPosition(itemPos);
			}
		}
	}
	//ヒップドロップされた
	if (m_isHipDrop) {
		if (!m_isInitModel) {
			m_skinModel.Init(L"Assets/modelData/Boxato.cmo");
			m_isInitModel = true;
			//みかん
			if (m_itemState == enItem_mikan) {
				m_se->Play(false);
				const auto& m_item = g_goMgr.NewGameObject<Item>("item");	
				m_item->IsHipDrop();
				auto pos = m_position;
				pos.y -= ITEM_POS;
				m_item->SetPosition(pos);
			}
			//コイン
			if (m_itemState == enItem_coin) {
				const auto& m_coin = g_goMgr.NewGameObject<Coin>("coin");
				m_coin->SetCoinGet();
				//大きすぎるので少し小さく
				m_coin->SetScale(m_scale * COIN_SCALE);
				//位置を少し下げる
				CVector3 itemPos = m_position;
				itemPos.y -= COIN_POS;
				m_coin->SetPosition(itemPos);
			}
		}
	}
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//ゴーストの更新
	m_ghostObject.SetPosition(m_ghostPos);
	m_meshGhostObject.SetPosition(m_position);
	//静的物理オブジェクトの更新
	m_staticObject.SetPositionAndRotation(m_position, m_rotation);
}
void Box::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	//リムライトオフ
	m_skinModel.RimLightOff();
	m_skinModel.ToonOff();
}
