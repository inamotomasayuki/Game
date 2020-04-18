#include "stdafx.h"
#include "system/system.h"
#include "ShadowMap.h"
#include "gameObject/GameObjectManager.h"
#include "Title.h"
#include "sound/SoundEngine.h"
#include "Stopwatch.h"
#include "GameTime.h"
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
	g_soundEngine = new CSoundEngine;
	g_soundEngine->Init();

	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	g_shadowMap = new ShadowMap;	

	g_goMgr.NewGameObject<Title>(0);

	CStopwatch sw;

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		sw.Start();
		GameUpdate();
		g_graphicsEngine->GameDraw();
		g_goMgr.Delete();
		sw.Stop();
		GameTime().PushFrameDeltaTime((float)sw.GetElapsed());
	}
}
