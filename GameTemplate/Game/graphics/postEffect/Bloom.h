#pragma once
#include "../RenderTarget.h"
#include "graphics/Shader.h"
#include "GaussianBlur.h"
#include "../../option/OptionData.h"
class PostEffect;

struct Luminance {
	float lum;			//�u���[���̋P�x
};

struct Combine {
	float bloomPow;		//�u���[���̋���
};
/// <summary>
/// �u���[��
/// </summary>
class Bloom
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Bloom()=default;
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Bloom();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(PostEffect& postEffect);
private:
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �A���t�@�u�����f�B���O�̃X�e�[�g������������B
	/// </summary>
	void InitAlphaBlendState();

	/// <summary>
	/// �V�F�[�_�[���������B
	/// </summary>
	void InitShader();
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�̏������B
	/// </summary>
	void InitRenderTarget();
	/// <summary>
	/// �T���v���X�e�[�g�̏������B
	/// </summary>
	void InitSamplerState();
private:
	bool m_isInit = false;
	static const int NUM_DOWN_SAMPLE = 4;				//�_�E���T���v�����O�̉񐔁B
	ID3D11Buffer*		m_luminanceCb = nullptr;					//!<�萔�o�b�t�@�B
	ID3D11Buffer*		m_combineCb = nullptr;					//!<�萔�o�b�t�@�B
	ID3D11SamplerState* m_samplerState = nullptr;		//�T���v���X�e�[�g�B
	ID3D11BlendState* m_disableBlendState = nullptr;	//�A���t�@�u�����f�B���O�𖳌��ɂ���u�����f�B���O�X�e�[�g�B
	ID3D11BlendState* m_finalBlendState = nullptr;		//�ŏI�����p�̃u�����f�B���O�X�e�[�g�B
	RenderTarget m_luminanceRT;			//�P�x�𒊏o���郌���_�����O�^�[�Q�b�g
	RenderTarget m_blurCombineRT;		//�u���[�̉摜���������郌���_�����O�^�[�Q�b�g�B
	Shader m_vs;						//�������Ȃ����_�V�F�[�_�[�B
	Shader m_psLuminance;				//�P�x���o�p�̃s�N�Z���V�F�[�_�[�B
	Shader m_psCombine;					//�ڂ����摜�����p�̃s�N�Z���V�F�[�_�[�B
	Shader m_psFinal;					//�ŏI�����p�̃s�N�Z���V�F�[�_�[�B
	GaussianBlur m_gausianBlur[NUM_DOWN_SAMPLE];	//�P�x���ڂ������߂̃K�E�V�A���u���[�B
													//1/2��1/4��1/8��1/16�̉𑜓x�܂Ń_�E���T���v�����O����Ă����܂��B
	Luminance m_luminance;			//�P�x
	Combine m_combine;				//����
	OptionData* m_optionData = nullptr;		//�I�v�V�����f�[�^
};

