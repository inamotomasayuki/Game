#pragma once
#include "../RenderTarget.h"
#include "../graphics/2D/Sprite.h"
#include "../PostEffect.h"
#include "../EffectEngine.h"

/// <summary>
/// レンダリングモード。
/// </summary>
enum EnRenderMode {
	enRenderMode_Invalid,			//不正なレンダリングモード。
	enRenderMode_CreateShadowMap,	//シャドウマップ生成。
	enRenderMode_Normal,			//通常レンダリング。
	enRenderMode_Silhouette,		//シルエット描画。
	enRenderMode_Sky,
	enRenderMode_Num,				//レンダリングモードの数。
};


/*!
 *@brief	グラフィックスエンジン。
 */
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	初期化。
	 *@param[in]	hWnd		ウィンドウハンドル。
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	解放。
	 */
	void Release();
	/*!
	 *@brief	D3D11デバイスを取得。
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11デバイスコンテキストを取得。
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}

	/*!
	 *@brief	描画開始。
	 */
	void BegineRender();
	/*!
	 *@brief	描画終了。
	 */
	void EndRender();
	/// <summary>
/// レンダリングターゲットの切り替え。
/// </summary>
/// <param name="renderTarget">レンダリングターゲット</param>
/// <param name="viewport">ビューポート</param>
	void ChangeRenderTarget(RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
	/// <summary>
	/// 描画
	/// </summary>
	void GameDraw();
	/// <summary>
	/// メインレンダリングターゲットを作成
	/// </summary>
	void CreateMainRenderTarget();
	/// <summary>
/// メインレンダリングターゲットを取得。
/// </summary>
/// <returns></returns>
	RenderTarget* GetMainRenderTarget()
	{
		return &m_mainRenderTarget;
	}
	/// <summary>
	/// 半透明合成のブレンドステートを初期化
	/// </summary>
	void InitTranslucentBlendState();
	/// <summary>
	/// 半透明合成のブレンドステートを設定
	/// </summary>
	void SetBlendState();
	DirectX::SpriteBatch* GetSpriteBatch()
	{
		return m_spriteBatch.get();
	}
	DirectX::SpriteFont* GetSpriteFont()
	{
		return m_spriteFont.get();
	}
private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11デバイス。
	IDXGISwapChain*			m_pSwapChain = NULL;		//スワップチェイン。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11デバイスコンテキスト。
	ID3D11RenderTargetView* m_backBuffer = NULL;		//バックバッファ。
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//ラスタライザステート。
	ID3D11Texture2D*		m_depthStencil = NULL;		//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//デプスステンシルビュー。

	PostEffect m_postEffect;
	RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。	
	Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
	ID3D11BlendState* m_translucentBlendState = nullptr;	//半透明合成用のブレンドステート。

	//定義。
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;     //これが肝
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;		//これも肝
};

extern GraphicsEngine* g_graphicsEngine;			//グラフィックスエンジン