#include "stdafx.h"
#include "Game.h"
#include "GameData.h"

Game::Game()
{
	if (g_gameData.GetStageNo() == 0) {
		m_level.Init(L"Assets/level/stage_01.tkl", [&](LevelObjectData& objData) {
			if (objData.EqualObjectName(L"unityChan")) {
				m_player = g_goMgr.NewGameObject<Player>("player");
				m_player->SetPosition(objData.position);
				m_player->SetRotation(objData.rotation);
				m_player->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"coin")) {
				m_coin = g_goMgr.NewGameObject<Coin>("coin");
				m_coin->SetPosition(objData.position);
				m_coin->SetRotation(objData.rotation);
				m_coin->SetScale(objData.scale);
			}
			if (objData.EqualObjectName(L"kuribo")) {
				m_enemy01 = g_goMgr.NewGameObject<Enemy01>("enemy01");
				m_enemy01->SetPosition(objData.position);
				m_enemy01->SetRotation(objData.rotation);
				m_enemy01->SetScale(objData.scale);
				
				//m_enemy02 = g_goMgr.NewGameObject<Enemy02>("enemy02");
				//m_enemy02->SetPosition(objData.position);
				//m_enemy02->SetRotation(objData.rotation);
				//m_enemy02->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"gameStage01")) {
				m_backGround = g_goMgr.NewGameObject<BackGround>(0);
				m_backGround->SetPosition(objData.position);
				m_backGround->SetRotation(objData.rotation);
				m_backGround->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"moveFloor")) {
				m_moveFloor = g_goMgr.NewGameObject<MoveFloor>("moveFloor");
				m_moveFloor->SetPosition(objData.position);
				m_moveFloor->SetRotation(objData.rotation);
				m_moveFloor->SetScale(objData.scale);
				return true;
			}
			return false;
		});
		
		m_gameCamera = g_goMgr.NewGameObject<GameCamera>("gameCamera");
	}
}


Game::~Game()
{
	
}

void Game::Update()
{
}
void Game::Draw()
{
}