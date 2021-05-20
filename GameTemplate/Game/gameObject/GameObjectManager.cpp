#include "stdafx.h"
#include "GameObjectManager.h"
#include "../time/GameTime.h"

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

void GameObjectManager::DrawFade()
{
	for (auto go : m_goList) {
		go->DrawFade();
	}
}

void GameObjectManager::DrawEffect()
{
	for (auto go : m_goList) {
		go->DrawEffect();
	}
}

void GameObjectManager::DrawFont()
{
	for (auto go : m_goList) {
		go->DrawFont();
	}
}
void GameObjectManager::Update()
{
	//登録されているゲームオブジェクトの更新処理を呼ぶ。
	const float GAME_BASE_DELTA_TIME = 1.0f / 60.0f;
	int updateCount = (int)( GameTime().GetFrameDeltaTime() / GAME_BASE_DELTA_TIME);
	//更新回数は最大２回。
	updateCount = 1;// min(2, updateCount);

	for (int i = 0; i < updateCount; i++){
		for (auto go : m_goList) {
			if (go->IsRequestDelete() == false) {
				go->Update();
			}
		}
	}
	for (auto go : m_goList) {
		if (go->IsRequestDelete() == false) {
			go->NewUpdate();
		}
	}
}
void GameObjectManager::PauseUpdate()
{
	for (auto go : m_goList) {
		if (go->IsRequestDelete() == false) {
			go->PauseUpdate();
		}
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