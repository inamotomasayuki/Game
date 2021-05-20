#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"
#include "../Game.h"
void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	//シェーダーを適用する。
	deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
	switch (m_renderMode) {
	case enRenderMode_Normal:{
		//通常描画。
		//deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
		//todo シェーダーリソースビューを一気に設定する。
		ID3D11ShaderResourceView* srvArray[] = {
			m_albedoTex,							//アルベドテクスチャ。
			g_shadowMap->GetShadowMapSRV()	//シャドウマップ。
		};
		ID3D11ShaderResourceView* srvarray[] = {
			m_toonMapTex
		};
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 2, srvArray);
		deviceContext->PSSetShaderResources(3, 1, srvarray);
	}break;
	case enRenderMode_Sky: {
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psSky.GetBody(), NULL, 0);
		//todo シェーダーリソースビューを一気に設定する。
		ID3D11ShaderResourceView* srvArray[] = {
			m_albedoTex,							//アルベドテクスチャ
		};
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, srvArray);
	}break;
	case enRenderMode_Silhouette:
		//シルエット描画。
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psSilhouette.GetBody(), NULL, 0);
		//デプスステンシルステートを切り替える。
		deviceContext->OMSetDepthStencilState(m_silhouettoDepthStepsilState, 0);
		break;
	case enRenderMode_CreateShadowMap:
		//シャドウマップ生成。
		deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShadowMap->GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		break;
	}
}

void ModelEffect::InitSilhouettoDepthStepsilState()
{
	//D3Dデバイスを取得。
	auto pd3d = g_graphicsEngine->GetD3DDevice();
	//作成する深度ステンシルステートの定義を設定していく。
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;						   //Zテストが有効。
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; //ZバッファにZ値を描き込まない。
	desc.DepthFunc = D3D11_COMPARISON_GREATER;		   //Z値が大きければフレームバッファに描き込む。

	pd3d->CreateDepthStencilState(&desc, &m_silhouettoDepthStepsilState);
}

void ModelEffect::InitToonMap()
{
	//テクスチャを読み込みます
	DirectX::CreateDDSTextureFromFile(
		g_graphicsEngine->GetD3DDevice(), // D3Dデバイス
		L"Assets/shader/toonmap.dds",  //テクスチャのファイルパス
		nullptr,   //nullptrでいい
		&m_toonMapTex  //シェーダーリソースビュー
	);
}