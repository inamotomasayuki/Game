#pragma once

#include "GaussianBlur.h"
#include "HexaBlur.h"

class PostEffect;

/// <summary>
/// �ǂ��ӁA�ǂ�
/// </summary>
/// <remarks>
/// Dof�̃C���X�^���X��PostEffect�N���X���ێ����Ă���̂�
/// �N���������K�v�͂Ȃ��IDraw�֐���K�؂Ɏ�������̂��I
/// </remarks>
class Dof
{
public:
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Dof();
	/// <summary>
	/// �������B
	/// </summary>
	void Init();
	/// <summary>
	/// �`��B
	/// </summary>
	/// <param name="postEffect"></param>
	void Draw(PostEffect& postEffect);
private:
	GaussianBlur m_bokeBlur;	//�{�P�e�N�X�`�����ڂ������߂̃K�E�V�A���u���[�B
	HexaBlur m_hexaBlur;	//�{�P�e�N�X�`�����ڂ������߂̘Z�p�`�u���[
	ID3D11BlendState* m_finalBlendState = nullptr;		//�ŏI�����p�̃u�����f�B���O�X�e�[�g�B

	Shader m_vs;				//���_�V�F�[�_�[�B
	Shader m_psFinal;			//�ŏI�s�N�Z���V�F�[�_�[�B
};

