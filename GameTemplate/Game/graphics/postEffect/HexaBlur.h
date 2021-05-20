/*!
 *@brief	�Z�p�`�u���[�B
 */

#pragma once

#include "../Shader.h"
#include "../RenderTarget.h"
#include "../ConstantBufferGPU.h"
class PostEffect;
 /// <summary>
 /// �Z�p�`�u���[�B
 /// </summary>
class HexaBlur final {
public:
	/// <summary>
	/// �`��p�X�B
	/// </summary>
	enum EnRenderPass {
		enRenderPass_VerticalDiagonalBlur,			//�����A�΂߃u���[
		enRenderPass_CombineVerticalDiagonalBlur,	//�����u���[�Ǝ΂߃u���[����������B
		enRenderPass_RhomboidBlur,					//�Z�p�`�u���[���쐬����B
		enRenderPass_Num,
	};
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="srcTexture">�\�[�X�ƂȂ�e�N�X�`��</param>
	void Init(ID3D11ShaderResourceView* srcTexture);
	/// <summary>
	/// �u���[�����s�B
	/// </summary>
	/// <param name="postEffect">�|�X�g�G�t�F�N�g</param>
	void Execute(PostEffect& postEffect);
	/// <summary>
	/// �\�[�X�e�N�X�`����ύX�B
	/// </summary>
	/// <param name="srcTexture">�\�[�X�e�N�X�`��</param>
	void ChangeSrcTexture(ID3D11ShaderResourceView& srcTexture)
	{
		m_srcTextureSRV = &srcTexture;
	}
	/// <summary>
	/// �u���[�̔��a��ݒ�B
	/// </summary>
	/// <param name="radius">�u���[�̔��a(�P�ʁF�e�N�Z��)</param>
	void SetRadius(float radius)
	{
		m_radius = radius;
	}
	/// <summary>
	/// �u���[�̔��a���擾�B
	/// </summary>
	float GetRadius() const
	{
		return m_radius;
	}
	/// <summary>
	/// ���ʂ��擾�B
	/// </summary>
	/// <returns></returns>
	ID3D11ShaderResourceView* GetResultSRV()
	{
		return m_renderTarget[enRenderTarget_RhomboidBlur].GetRenderTargetSRV();
	}
private:
	enum EnRenderTarget {
		enRenderTarget_VerticalBlur,			//�����u���[�B
		enRenderTarget_DiagonalBlur,			//�΂߃u���[�B
		enRenderTarget_VerticalDiagonalBlur,	//�����A�΂߃u���[�B
		enRenderTarget_RhomboidBlur,			//�Z�p�`�u���[�B
		enRenderTarget_Num,
	};
	struct SCBParam {
		CVector2 texSize;		//�u���[��������e�N�X�`���̃T�C�Y�B
		float radius;			//�u���[�̔��a�B
	};
	ID3D11ShaderResourceView* m_srcTextureSRV = nullptr;		//�u���[���̃e�N�X�`���B
	RenderTarget m_renderTarget[enRenderTarget_Num];	//�����_�����O�^�[�Q�b�g�B
	Shader m_vs;										//���_�V�F�[�_�B
	Shader m_psVerticalDiagonalBlur;					//�����A�΂߃u���[�̃s�N�Z���V�F�[�_�[�B
	Shader m_psCombineVerticalDiagonalBlur;			//�����A�΂߃u���[�̍����p�̃s�N�Z���V�F�[�_�[�B
	Shader m_psRhomboidBlur;							//�Z�p�`�u���[���쐬����B
	ConstantBufferGPU m_hexaBlurCbGpu;				//�萔�o�b�t�@�B
	float m_radius = 8.0f;								//�u���[���a�B
};