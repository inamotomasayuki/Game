#include "stdafx.h"
#include "system/system.h"
#include "ShadowMap.h"
#include "gameObject/GameObjectManager.h"
#include "Title.h"
#include "sound/SoundEngine.h"
void GameUpdate()
{
	//ゲームパッドの更新。	
	for (auto& pad : g_pad) {
		pad.Update();
	}
	//物理エンジンの更新。
	g_physics.Update();
	g_soundEngine->Update();
	//ゲームオブジェクトマネージャーの更新
	g_goMgr.Update();
}	

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//g_shadowMap = new ShadowMap;	
	g_shadowMap = g_goMgr.NewGameObject<ShadowMap>(0);

	g_soundEngine = new CSoundEngine;
	g_soundEngine->Init();
	g_goMgr.NewGameObject<Title>(0);
	
	//メインとなるレンダリングターゲットを作成する。
	g_graphicsEngine->CreateMainRenderTarget();

	//半透明合成のブレンドステートを初期化する。
	g_graphicsEngine->InitTranslucentBlendState();


	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		GameUpdate();
		g_graphicsEngine->GameDraw();
		g_goMgr.Delete();
	}
}
