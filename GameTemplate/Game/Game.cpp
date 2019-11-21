#include "stdafx.h"
#include "Game.h"
#include "GameData.h"

Game::Game()
{
	if (g_gameData.GetStageNo() == 0) {
		m_level.Init(L"Assets/level/stage_03.tkl", [&](LevelObjectData& objData) {
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
				return true;
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
			if (objData.EqualObjectName(L"jumpFloor")) {
				m_jumpFloor = g_goMgr.NewGameObject<JumpFloor>("jumpFloor");
				m_jumpFloor->SetPosition(objData.position);
				m_jumpFloor->SetRotation(objData.rotation);
				m_jumpFloor->SetScale(objData.scale);
				return true;
			}
			return false;
		});
		m_spriteUI = g_goMgr.NewGameObject<SpriteUI>(0);
		m_gameCamera = g_goMgr.NewGameObject<GameCamera>("gameCamera");
	}
}


Game::~Game()
{
	
}

void Game::Update()
{
	////シャドウキャスターを登録。
	//g_shadowMap->RegistShadowCaster(m_player->GetSkinModel());
	//g_shadowMap->RegistShadowCaster(m_backGround->GetSkinModel());
	////シャドウマップを更新。
	//g_shadowMap->UpdateFromLightTarget(
	//	{ 1000.0f, 1000.0f, 1000.0f },
	//	{ 0.0f, 0.0f, 0.0f }
	//);
}

void Game::Draw()
{
	/////////////////////////////////////////////////
	////シャドウマップにレンダリング
	/////////////////////////////////////////////////
	//auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	////現在のレンダリングターゲットをバックアップしておく。
	//ID3D11RenderTargetView* oldRenderTargetView;
	//ID3D11DepthStencilView* oldDepthStencilView;
	//d3dDeviceContext->OMGetRenderTargets(
	//	1,
	//	&oldRenderTargetView,
	//	&oldDepthStencilView
	//);
	////ビューポートもバックアップを取っておく。
	//unsigned int numViewport = 1;
	//D3D11_VIEWPORT oldViewports;
	//d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);

	////シャドウマップにレンダリング
	//g_shadowMap->RenderToShadowMap();

	////元に戻す。
	//d3dDeviceContext->OMSetRenderTargets(
	//	1,
	//	&oldRenderTargetView,
	//	oldDepthStencilView
	//);
	//d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	////レンダリングターゲットとデプスステンシルの参照カウンタを下す。
	//oldRenderTargetView->Release();
	//oldDepthStencilView->Release();
}