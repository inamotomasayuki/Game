#include "stdafx.h"
#include "system/system.h"
#include "ShadowMap.h"
#include "gameObject/GameObjectManager.h"
#include "Title.h"

RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。	
Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。

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

void GameDraw()
{
	//描画開始。
	g_graphicsEngine->BegineRender();


	////メインとなるレンダリングターゲットを作成する。
	//m_mainRenderTarget.Create(
	//	FRAME_BUFFER_W,
	//	FRAME_BUFFER_H,
	//	DXGI_FORMAT_R8G8B8A8_UNORM
	//);

	////メインレンダリングターゲットに描かれた絵を
	////フレームバッファにコピーするためのスプライトを初期化する。
	//m_copyMainRtToFrameBufferSprite.Init(
	//	m_mainRenderTarget.GetRenderTargetSRV(),
	//	FRAME_BUFFER_W,
	//	FRAME_BUFFER_H
	//);

	//フレームバッファののレンダリングターゲットをバックアップしておく。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&m_frameBufferRenderTargetView,
		&m_frameBufferDepthStencilView
	);
	//ビューポートもバックアップを取っておく。
	unsigned int numViewport = 1;
	d3dDeviceContext->RSGetViewports(&numViewport, &m_frameBufferViewports);



	//シャドウマップを更新。
	g_shadowMap->UpdateFromLightTarget(
		{ 1000.0f, 1000.0f, 1000.0f },
		{ 0.0f, 0.0f, 0.0f }
	);

	///////////////////////////////////////////////
	//シャドウマップにレンダリング
	///////////////////////////////////////////////
	//auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//現在のレンダリングターゲットをバックアップしておく。
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);
	//ビューポートもバックアップを取っておく。
	//unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);

	//シャドウマップにレンダリング
	g_shadowMap->RenderToShadowMap();
	//元に戻す。
	d3dDeviceContext->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();

	//レンダリングターゲットをメインに変更する。
	//auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	m_copyMainRtToFrameBufferSprite.ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
	//メインレンダリングターゲットをクリアする。
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);


	g_goMgr.Draw3D();


	//レンダリングターゲットをフレームバッファに戻す。
	//auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	m_copyMainRtToFrameBufferSprite.ChangeRenderTarget(
		d3dDeviceContext,
		m_frameBufferRenderTargetView,
		m_frameBufferDepthStencilView,
		&m_frameBufferViewports
	);

	CMatrix mView;
	CMatrix mProj;
	mView.MakeLookAt(
		{ 0, 0, -1 },
		{ 0, 0, 0 },
		{ 0,1,0 }
	);
	mProj.MakeOrthoProjectionMatrix(1280.0f, 720.0f, 0.1f, 100.0f);
	////ドロドロ
	m_copyMainRtToFrameBufferSprite.Draw(mView, mProj);

	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();

	//2Dを描画
	g_goMgr.Draw2D();

	if (m_frameBufferRenderTargetView != nullptr) {
		m_frameBufferRenderTargetView->Release();
	}
	if (m_frameBufferDepthStencilView != nullptr) {
		m_frameBufferDepthStencilView->Release();
	}


	//描画終了。
	g_graphicsEngine->EndRender();
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
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R8G8B8A8_UNORM
	);

	//メインレンダリングターゲットに描かれた絵を
	//フレームバッファにコピーするためのスプライトを初期化する。
	m_copyMainRtToFrameBufferSprite.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		GameUpdate();
		GameDraw();
	}
}
