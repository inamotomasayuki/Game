#pragma once

#include "../RenderTarget.h"
#include "graphics/Shader.h"
#include "../ConstantBufferGPU.h"

class PostEffect;
/// <summary>
/// ガウシアンブラー
/// </summary>
class GaussianBlur
{
public:
	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="srcTexture">ブラーをかけるテクスチャのSRV</param>
	/// <param name="blurIntensity">ブラーの強さ。値が大きいほど強くブラーがかかる。</param>
	void Init(ID3D11ShaderResourceView* srcTextureSRV, float blurIntensity);
	/// <summary>
	/// ブラーの実行
	/// </summary>
	/// <param name="postEffect">
	/// ポストエフェクトのインスタンス。
	/// 全画面描画の機能を使いたいだけです。。。
	/// </param>
	/// <remarks>
	/// Init関数を呼び出した後で実行するようにしてください。
	/// </remarks>
	void Execute(PostEffect& postEffect);
	/// <summary>
	/// ブラーをかけた結果のテクスチャSRVを取得。
	/// </summary>
	/// <returns></returns>
	ID3D11ShaderResourceView* GetResultTextureSRV()
	{
		return m_renderTarget[enRenderTarget_YBlur].GetRenderTargetSRV();
	}
	/// <summary>
	/// ブラーをかけた結果のテクスチャの幅を取得。
	/// </summary>
	float GetResultTextureWidth() const
	{
		return m_renderTarget[enRenderTarget_YBlur].GetWidth();
	}
	/// <summary>
	/// ブラーをかけた結果のテクスチャの高さを取得。
	/// </summary>
	/// <returns></returns>
	float GetResultTextureHeight() const
	{
		return m_renderTarget[enRenderTarget_YBlur].GetHeight();
	}
	/// <summary>
	/// ブラーをかけた結果のテクスチャのフォーマットを取得。
	/// </summary>
	/// <returns></returns>
	DXGI_FORMAT GetResultTextureFormat() const
	{
		return m_renderTarget[enRenderTarget_YBlur].GetTextureFormat();
	}
private:
	/// <summary>
	/// ブラーの重みの更新。
	/// </summary>
	void UpdateWeights();
private:
	/// <summary>
	/// レンダリングターゲット。
	/// </summary>
	enum EnRenderTarget {
		enRenderTarget_XBlur,		//Xブラーの書き込み先となるレンダリングターゲット。
		enRenderTarget_YBlur,		//Yブラーの書き込み先となるレンダリングターゲット。
		enRenderTarget_Num,			//レンダリングターゲットの枚数。
	};
	static const int NUM_WEIGHTS = 8;	//カウスフィルタの重みの数。
	/// <summary>
	/// ブラー用のパラメータバッファ。
	/// </summary>
	/// <remarks>
	/// これを変更したら、Assets/shader/GaussianBlur.fxのCBBlurの中身も変更するように。
	/// </remarks>
	struct SBlurParam {
		float weights[NUM_WEIGHTS];
	};
	bool m_isInited = false;		//初期化済みフラグ。
	float m_blurIntensity = 25.0f;							//ブラーの強さ。ブラーのウェイトの計算で使用されます。
	RenderTarget m_renderTarget[enRenderTarget_Num];		//レンダリングターゲット。
	ID3D11ShaderResourceView* m_srcTextureSRV = nullptr;	//ソーステクスチャのSRV
	unsigned int m_srcTextureWidth = 0;						//ソーステクスチャの幅。
	unsigned int m_srcTextureHeight = 0;					//ソーステクスチャの高さ。
	Shader m_vsXBlur;						//Xブラー用の頂点シェーダー。
	Shader m_vsYBlur;						//Yブラー用の頂点シェーダー。
	Shader m_psBlur;						//ブラー用のピクセルシェーダー。
	SBlurParam m_blurParam;						//ブラー用のパラメータ。
	ConstantBufferGPU m_blurCbGpu;				//ブラー用の定数バッファ(GPU側)
};


