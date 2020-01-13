#include "stdafx.h"
#include "GameObjectManager.h"
//GameObjectManagerクラスのインスタンス。
GameObjectManager g_goMgr;

/// <summary>
/// 3Dを描画
/// </summary>
void GameObjectManager::Draw3D()
{
	for (auto go : m_goList) {
		go->Draw();
	}
}
/// <summary>
/// 2Dを描画。
/// </summary>
void GameObjectManager::Draw2D()
{
	for (auto go : m_goList) {
		go->Draw2D();
	}
}
void GameObjectManager::Update()
{
	//登録されているゲームオブジェクトの更新処理を呼ぶ。
	for (auto go : m_goList) {
		go->Update();
	}
	
}
void GameObjectManager::Delete()
{
	//全てのゲームオブジェクトの1フレーム分の処理が終わってから、削除する。
	for (auto it = m_goList.begin(); it != m_goList.end();) {
		if ((*it)->IsRequestDelete()) {		
			//削除リクエストを受けているので削除。
			delete* it;
			it = m_goList.erase(it);
		}
		else {
			//リクエストを受けていないの。
			it++;
		}
	}
}