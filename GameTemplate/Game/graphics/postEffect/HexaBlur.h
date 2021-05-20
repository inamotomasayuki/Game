/*!
 *@brief	六角形ブラー。
 */

#pragma once

#include "../Shader.h"
#include "../RenderTarget.h"
#include "../ConstantBufferGPU.h"
class PostEffect;
 /// <summary>
 /// 六角形ブラー。
 /// </summary>
class HexaBlur final {
public:
	/// <summary>
	/// 描画パス。
	/// </summary>
	enum EnRenderPass {
		enRenderPass_VerticalDiagonalBlur,			//垂直、斜めブラー
		enRenderPass_CombineVerticalDiagonalBlur,	//垂直ブラーと斜めブラーを合成する。
		enRenderPass_RhomboidBlur,					//六角形ブラーを作成する。
		enRenderPass_Num,
	};
	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="srcTexture">ソースとなるテクスチャ</param>
	void Init(ID3D11ShaderResourceView* srcTexture);
	/// <summary>
	/// ブラーを実行。
	/// </summary>
	/// <param name="postEffect">ポストエフェクト</param>
	void Execute(PostEffect& postEffect);
	/// <summary>
	/// ソーステクスチャを変更。
	/// </summary>
	/// <param name="srcTexture">ソーステクスチャ</param>
	void ChangeSrcTexture(ID3D11ShaderResourceView& srcTexture)
	{
		m_srcTextureSRV = &srcTexture;
	}
	/// <summary>
	/// ブラーの半径を設定。
	/// </summary>
	/// <param name="radius">ブラーの半径(単位：テクセル)</param>
	void SetRadius(float radius)
	{
		m_radius = radius;
	}
	/// <summary>
	/// ブラーの半径を取得。
	/// </summary>
	float GetRadius() const
	{
		return m_radius;
	}
	/// <summary>
	/// 結果を取得。
	/// </summary>
	/// <returns></returns>
	ID3D11ShaderResourceView* GetResultSRV()
	{
		return m_renderTarget[enRenderTarget_RhomboidBlur].GetRenderTargetSRV();
	}
private:
	enum EnRenderTarget {
		enRenderTarget_VerticalBlur,			//垂直ブラー。
		enRenderTarget_DiagonalBlur,			//斜めブラー。
		enRenderTarget_VerticalDiagonalBlur,	//垂直、斜めブラー。
		enRenderTarget_RhomboidBlur,			//六角形ブラー。
		enRenderTarget_Num,
	};
	struct SCBParam {
		CVector2 texSize;		//ブラーをかけるテクスチャのサイズ。
		float radius;			//ブラーの半径。
	};
	ID3D11ShaderResourceView* m_srcTextureSRV = nullptr;		//ブラー元のテクスチャ。
	RenderTarget m_renderTarget[enRenderTarget_Num];	//レンダリングターゲット。
	Shader m_vs;										//頂点シェーダ。
	Shader m_psVerticalDiagonalBlur;					//垂直、斜めブラーのピクセルシェーダー。
	Shader m_psCombineVerticalDiagonalBlur;			//垂直、斜めブラーの合成用のピクセルシェーダー。
	Shader m_psRhomboidBlur;							//六角形ブラーを作成する。
	ConstantBufferGPU m_hexaBlurCbGpu;				//定数バッファ。
	float m_radius = 8.0f;								//ブラー半径。
};