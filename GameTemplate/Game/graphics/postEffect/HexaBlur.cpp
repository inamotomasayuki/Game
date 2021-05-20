/*!
 *@brief	六角形ブラー。
 */
#include "stdafx.h"
#include "HexaBlur.h"
#include "PostEffect.h"

void HexaBlur::Init(ID3D11ShaderResourceView* srcTextureSRV)
{
	//ソーステクスチャのSRVをコピー。
	m_srcTextureSRV = srcTextureSRV;
	//ソーステクスチャの情報を取得。
	ID3D11Texture2D* tex;
	//まず、SRVに関連付けされているテクスチャを取得する。
	srcTextureSRV->GetResource((ID3D11Resource**)&tex);
	//取得したテクスチャから、テクスチャ情報を取得する。
	D3D11_TEXTURE2D_DESC texDesc;
	tex->GetDesc(&texDesc);
	//テクスチャ情報を取得できたので、テクスチャの参照カウンタをおろす。
	tex->Release();
	for (auto& rt : m_renderTarget) {
		//レンダリングターゲットを作成。
		rt.Create(
			texDesc.Width,		
			texDesc.Height,	
			texDesc.Format
		);
	}
	//シェーダーを初期化。
	m_vs.Load("Assets/shader/hexaBlur.fx", "VSMain", Shader::EnType::VS);
	m_psVerticalDiagonalBlur.Load("Assets/shader/hexaBlur.fx", "PSVerticalDiagonalBlur", Shader::EnType::PS);
	m_psCombineVerticalDiagonalBlur.Load("Assets/shader/hexaBlur.fx", "PSCombineVerticalDiagonalBlur", Shader::EnType::PS);
	m_psRhomboidBlur.Load("Assets/shader/hexaBlur.fx", "PSRhomboidBlur", Shader::EnType::PS);
	//定数バッファを初期化。
	m_hexaBlurCbGpu.Create(nullptr, sizeof(SCBParam));
}
void HexaBlur::Execute(PostEffect& postEffect)
{
	if (m_srcTextureSRV == nullptr) {
		//ソーステクスチャが指定されていないぞゴルァ。
		return;
	}

	//ソーステクスチャの情報を取得。
	ID3D11Texture2D* tex;
	//まず、SRVに関連付けされているテクスチャを取得する。
	m_srcTextureSRV->GetResource((ID3D11Resource**)&tex);
	//取得したテクスチャから、テクスチャ情報を取得する。
	D3D11_TEXTURE2D_DESC texDesc;
	tex->GetDesc(&texDesc);
	//テクスチャ情報を取得できたので、テクスチャの参照カウンタをおろす。
	tex->Release();

	SCBParam cbParam;
	cbParam.texSize.x = texDesc.Width;
	cbParam.texSize.y = texDesc.Height;
	cbParam.radius = m_radius;

	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	auto d3d11CbGpu = m_hexaBlurCbGpu.GetD3D11Buffer();
	//VRAM上の定数バッファを更新。
	deviceContext->UpdateSubresource(d3d11CbGpu, 0, nullptr, &cbParam, 0, 0);
	//b0レジスタに定数バッファのアドレスを設定。
	deviceContext->PSSetConstantBuffers(0, 1, &d3d11CbGpu);

	//垂直、斜めブラー
	ID3D11RenderTargetView* rts[] = {
		m_renderTarget[enRenderTarget_VerticalBlur].GetRenderTargetView(),
		m_renderTarget[enRenderTarget_DiagonalBlur].GetRenderTargetView()
	};
	const auto& dsv = m_renderTarget[0].GetDepthStensilView();
	deviceContext->OMSetRenderTargets(2, rts, dsv);
	if (rts[0] != nullptr) {
		deviceContext->RSSetViewports(1, &g_graphicsEngine->GetFrameBufferViewport());
	}
	deviceContext->PSSetShaderResources(0, 1, &m_srcTextureSRV);
	float color[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	deviceContext->ClearRenderTargetView(m_renderTarget[enRenderTarget_VerticalBlur].GetRenderTargetView(), color);
	deviceContext->ClearRenderTargetView(m_renderTarget[enRenderTarget_DiagonalBlur].GetRenderTargetView(), color);
	postEffect.DrawFullScreenQuadPrimitive(
		deviceContext, m_vs, m_psVerticalDiagonalBlur
	);

	//六角形ブラーを作成する。
	g_graphicsEngine->ChangeRenderTarget(
		&m_renderTarget[enRenderTarget_RhomboidBlur],
		m_renderTarget[enRenderTarget_RhomboidBlur].GetViewport());

	ID3D11ShaderResourceView* srv[] = {
		m_renderTarget[enRenderTarget_VerticalBlur].GetRenderTargetSRV(),
		m_renderTarget[enRenderTarget_DiagonalBlur].GetRenderTargetSRV()
	};
	for (int i = 0; i < 2; i++) {
		deviceContext->PSSetShaderResources(i, 1, &srv[i]);
	}
	postEffect.DrawFullScreenQuadPrimitive(
		deviceContext, m_vs, m_psRhomboidBlur
	);

}