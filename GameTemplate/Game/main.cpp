#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "gameObject/GameObjectManager.h"
#include "Title.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");


	////シャドウマップを更新。
	//g_shadowMap->UpdateFromLightTarget(
	//	{ 1000.0f, 1000.0f, 1000.0f },
	//	{ 0.0f, 0.0f, 0.0f }
	//);
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

	g_goMgr.NewGameObject<Title>(0);

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		//ゲームオブジェクトマネージャーの更新
		g_goMgr.Update();
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}
