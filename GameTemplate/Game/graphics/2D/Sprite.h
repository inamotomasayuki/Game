#pragma once

#include "graphics/shader.h"

class Sprite {
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Sprite::Sprite();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	Sprite::~Sprite();
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="textureFilePath">�e�N�X�`���̃t�@�C���p�X�B</param>
	void Init(const wchar_t* textureFilePath, float w, float h);
	void Sprite::Init(ID3D11ShaderResourceView* srv, float w, float h)
	{
		//���ʂ̏������������Ăяo���B
		InitCommon(w, h);
		m_texture = srv;
		m_texture->AddRef();	//�Q�ƃJ�E���^�𑝂₷�B
	}
	/// <summary>
	/// ���[���h�s����X�V�B
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�g�嗦</param>
	void UpdateWorldMatrix(const CVector3& pos, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot = CVector2::Zero());
	/// <summary>
	/// �`��B
	/// </summary>
	/// <param name="mView">�J�����s��</param>
	/// /// <param name="mView">�v���W�F�N�V�����s��</param>
	void Draw(const CMatrix& mView, const CMatrix& mProj);
	/// <summary>
/// ����ψʂ�����
/// </summary>
/// <param name="delta">��Z����ψʂ������</param>
	void DeltaAlpha(float delta)
	{
		m_alpha += delta;
		//���l�̋��E�`�F�b�N�B
		if (m_alpha > 1.0f) {
			m_alpha = 1.0f;
		}
		else if (m_alpha < 0.0f) {
			m_alpha = 0.0f;
		}
	}
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
		//���l�̋��E�`�F�b�N�B
		if (m_alpha > 1.0f) {
			m_alpha = 1.0f;
		}
		else if (m_alpha < 0.0f) {
			m_alpha = 0.0f;
		}

	}
	/// <summary>
	/// �A���t�@�l�擾
	/// </summary>
	/// <returns></returns>
	float GetAlpha() const
	{
		return m_alpha;
	}
	/// <summary>
	/// ���m�N�����ݒ�
	/// </summary>
	/// <param name="monochrome"></param>
	void SetIsMonochrome(bool monochrome)
	{
		m_isMonochrome = monochrome;
	}
	/// <summary>
/// �������̋��ʏ����B
/// </summary>
	void InitCommon(float w, float h);

private:
	/// <summary>
	/// �V�F�[�_�[�����[�h�B
	/// </summary>
	void LoadShader();
	/// <summary>
	/// ���_�o�b�t�@���쐬�B
	/// </summary>
	void CreateVertexBuffer(float w, float h);
	/// <summary>
	/// �C���f�b�N�X�o�b�t�@���쐬�B
	/// </summary>
	void CreateIndexBuffer();
	/// <summary>
	/// �T���v���X�e�[�g���쐬�B
	/// </summary>
	void CreateSamplerState();
	/// <summary>
	/// �萔�o�b�t�@�̍쐬�B
	/// </summary>
	void CreateConstantBuffer();
	/// <summary>
	/// �e�N�X�`�������\�h�B
	/// </summary>
	/// <param name="textureFIlePath">���[�h����e�N�X�`���̃t�@�C���p�X�B</param>
	void LoadTexture(const wchar_t* textureFIlePath);

private:
	ID3D11DepthStencilState* m_depthStencilState = nullptr;
	Shader	m_vs;											//���_�V�F�[�_�[�B
	Shader	m_ps;											//�s�N�Z���V�F�[�_�[�B
	ID3D11Buffer*	m_vertexBuffer = nullptr;	//VRAM��̒��_�o�b�t�@�ɃA�N�Z�X���邽�߂̃C���^�[�t�F�[�X�B
	ID3D11Buffer*	m_indexBuffer = nullptr;		//VRAM��̃C���f�b�N�X�o�b�t�@�ɃA�N�Z�X���邽�߂̃C���^�[�t�F�[�X�B
	ID3D11Buffer*	m_cbGPU = nullptr;			//GPU���̒萔�o�b�t�@�ɃA�N�Z�X���邽�߂̃C���^�[�t�F�[�X�B
	ID3D11ShaderResourceView* m_texture = nullptr;	//�e�N�X�`���ɃA�N�Z�X���邽�߂̃C���^�[�t�F�[�X�B
	ID3D11SamplerState* m_samplerState = nullptr;	//�T���v���X�e�[�g�B
	CMatrix m_world = CMatrix::Identity();					//���[���h�s��B
	float						m_alpha = 1.0f;							//�X�v���C�g�̃��l�B
	CVector2					m_size = CVector2::Zero();				//�摜�̃T�C�Y�B
	bool m_isMonochrome = false;			//���m�N���H
};