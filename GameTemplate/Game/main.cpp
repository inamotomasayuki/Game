#include "stdafx.h"
#include "system/system.h"
#include "ShadowMap.h"
#include "gameObject/GameObjectManager.h"
#include "Title.h"


//RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。	
//Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
//D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
//ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
//ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。

void GameUpdate()
{
	//ゲームパッドの更新。	
	for (auto& pad : g_pad) {
		pad.Update();
	}
	//物理エンジンの更新。
	g_physics.Update();

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
	}
}
