/*!
 *@brief	�Z�p�`�u���[�B
 */
#include "stdafx.h"
#include "HexaBlur.h"
#include "PostEffect.h"

void HexaBlur::Init(ID3D11ShaderResourceView* srcTextureSRV)
{
	//�\�[�X�e�N�X�`����SRV���R�s�[�B
	m_srcTextureSRV = srcTextureSRV;
	//�\�[�X�e�N�X�`���̏����擾�B
	ID3D11Texture2D* tex;
	//�܂��ASRV�Ɋ֘A�t������Ă���e�N�X�`�����擾����B
	srcTextureSRV->GetResource((ID3D11Resource**)&tex);
	//�擾�����e�N�X�`������A�e�N�X�`�������擾����B
	D3D11_TEXTURE2D_DESC texDesc;
	tex->GetDesc(&texDesc);
	//�e�N�X�`�������擾�ł����̂ŁA�e�N�X�`���̎Q�ƃJ�E���^�����낷�B
	tex->Release();
	for (auto& rt : m_renderTarget) {
		//�����_�����O�^�[�Q�b�g���쐬�B
		rt.Create(
			texDesc.Width,		
			texDesc.Height,	
			texDesc.Format
		);
	}
	//�V�F�[�_�[���������B
	m_vs.Load("Assets/shader/hexaBlur.fx", "VSMain", Shader::EnType::VS);
	m_psVerticalDiagonalBlur.Load("Assets/shader/hexaBlur.fx", "PSVerticalDiagonalBlur", Shader::EnType::PS);
	m_psCombineVerticalDiagonalBlur.Load("Assets/shader/hexaBlur.fx", "PSCombineVerticalDiagonalBlur", Shader::EnType::PS);
	m_psRhomboidBlur.Load("Assets/shader/hexaBlur.fx", "PSRhomboidBlur", Shader::EnType::PS);
	//�萔�o�b�t�@���������B
	m_hexaBlurCbGpu.Create(nullptr, sizeof(SCBParam));
}
void HexaBlur::Execute(PostEffect& postEffect)
{
	if (m_srcTextureSRV == nullptr) {
		//�\�[�X�e�N�X�`�����w�肳��Ă��Ȃ����S���@�B
		return;
	}

	//�\�[�X�e�N�X�`���̏����擾�B
	ID3D11Texture2D* tex;
	//�܂��ASRV�Ɋ֘A�t������Ă���e�N�X�`�����擾����B
	m_srcTextureSRV->GetResource((ID3D11Resource**)&tex);
	//�擾�����e�N�X�`������A�e�N�X�`�������擾����B
	D3D11_TEXTURE2D_DESC texDesc;
	tex->GetDesc(&texDesc);
	//�e�N�X�`�������擾�ł����̂ŁA�e�N�X�`���̎Q�ƃJ�E���^�����낷�B
	tex->Release();

	SCBParam cbParam;
	cbParam.texSize.x = texDesc.Width;
	cbParam.texSize.y = texDesc.Height;
	cbParam.radius = m_radius;

	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	auto d3d11CbGpu = m_hexaBlurCbGpu.GetD3D11Buffer();
	//VRAM��̒萔�o�b�t�@���X�V�B
	deviceContext->UpdateSubresource(d3d11CbGpu, 0, nullptr, &cbParam, 0, 0);
	//b0���W�X�^�ɒ萔�o�b�t�@�̃A�h���X��ݒ�B
	deviceContext->PSSetConstantBuffers(0, 1, &d3d11CbGpu);

	//�����A�΂߃u���[
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

	//�Z�p�`�u���[���쐬����B
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