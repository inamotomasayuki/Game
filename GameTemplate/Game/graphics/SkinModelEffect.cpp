#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"
#include "../Game.h"
void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	//�V�F�[�_�[��K�p����B
	deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
	switch (m_renderMode) {
	case enRenderMode_Normal:{
		//�ʏ�`��B
		//deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
		//todo �V�F�[�_�[���\�[�X�r���[����C�ɐݒ肷��B
		ID3D11ShaderResourceView* srvArray[] = {
			m_albedoTex,							//�A���x�h�e�N�X�`���B
			g_shadowMap->GetShadowMapSRV()	//�V���h�E�}�b�v�B
		};
		ID3D11ShaderResourceView* srvarray[] = {
			m_toonMapTex
		};
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 2, srvArray);
		deviceContext->PSSetShaderResources(3, 1, srvarray);
	}break;
	case enRenderMode_Sky: {
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psSky.GetBody(), NULL, 0);
		//todo �V�F�[�_�[���\�[�X�r���[����C�ɐݒ肷��B
		ID3D11ShaderResourceView* srvArray[] = {
			m_albedoTex,							//�A���x�h�e�N�X�`��
		};
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, srvArray);
	}break;
	case enRenderMode_Silhouette:
		//�V���G�b�g�`��B
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psSilhouette.GetBody(), NULL, 0);
		//�f�v�X�X�e���V���X�e�[�g��؂�ւ���B
		deviceContext->OMSetDepthStencilState(m_silhouettoDepthStepsilState, 0);
		break;
	case enRenderMode_CreateShadowMap:
		//�V���h�E�}�b�v�����B
		deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShadowMap->GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		break;
	}
}

void ModelEffect::InitSilhouettoDepthStepsilState()
{
	//D3D�f�o�C�X���擾�B
	auto pd3d = g_graphicsEngine->GetD3DDevice();
	//�쐬����[�x�X�e���V���X�e�[�g�̒�`��ݒ肵�Ă����B
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;						   //Z�e�X�g���L���B
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; //Z�o�b�t�@��Z�l��`�����܂Ȃ��B
	desc.DepthFunc = D3D11_COMPARISON_GREATER;		   //Z�l���傫����΃t���[���o�b�t�@�ɕ`�����ށB

	pd3d->CreateDepthStencilState(&desc, &m_silhouettoDepthStepsilState);
}

void ModelEffect::InitToonMap()
{
	//�e�N�X�`����ǂݍ��݂܂�
	DirectX::CreateDDSTextureFromFile(
		g_graphicsEngine->GetD3DDevice(), // D3D�f�o�C�X
		L"Assets/shader/toonmap.dds",  //�e�N�X�`���̃t�@�C���p�X
		nullptr,   //nullptr�ł���
		&m_toonMapTex  //�V�F�[�_�[���\�[�X�r���[
	);
}