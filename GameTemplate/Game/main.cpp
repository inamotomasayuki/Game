#include "stdafx.h"
#include "system/system.h"
#include "graphics/ShadowMap.h"
#include "gameObject/GameObjectManager.h"
#include "title/Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "time/Stopwatch.h"
#include "time/GameTime.h"
#include "GameData.h"
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
	if (!g_gameData.GetIsPause()) {
		//通常時
		g_goMgr.Update();
	}
	else {
		//ポーズ中
		g_goMgr.PauseUpdate();
	}
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
	//g_goMgr.NewGameObject<Game>("game");

	CStopwatch sw;

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		sw.Start();
		//更新
		GameUpdate();
		//描画
		g_graphicsEngine->GameDraw();
		//削除
		g_goMgr.Delete();
		sw.Stop();
		GameTime().PushFrameDeltaTime((float)sw.GetElapsed());
	}
}
