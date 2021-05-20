#pragma once
#include "Bloom.h"
#include "Dof.h"

/// <summary>
/// �|�X�g�G�t�F�N�g�N���X�B
/// </summary>
class PostEffect
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	PostEffect()=default;
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~PostEffect();

	void Init();
	void InitDof();
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
	/// �h���[�B
	/// </summary>
	void Draw();
	/// <summary>
	/// �t���X�N���[���`��B
	/// </summary>
	void DrawFullScreenQuadPrimitive(ID3D11DeviceContext* deviceContext, Shader& vsShader, Shader& psShader);
	/// <summary>
	/// �u���[���̎擾
	/// </summary>
	/// <returns>�u���[��</returns>
	const Bloom& GetBloom() const
	{
		return m_bloom;
	}
private:
	/// <summary>
	/// �t���X�N���[���`��p�̎l�p�`�v���~�e�B�u�̏������B
	/// </summary>
	void InitFullScreenQuadPrimitive();
private:
	Bloom	m_bloom;	//�u���[���B
	Dof m_dof;			//DoF
	//�t���X�N���[���`��p�̃����o�ϐ��B
	ID3D11Buffer*	m_vertexBuffer = nullptr;		//���_�o�b�t�@�B
	ID3D11InputLayout* m_inputLayout = nullptr;		//���̓��C�A�E�g�B
};

