#pragma once
#include "EffekseerRuntime130/src/Effekseer/Effekseer.h"
#include "EffekseerRuntime130/src/EffekseerRendererCommon/EffekseerRenderer.Renderer.h"
#include "gameObject/IGameObject.h"
class EffectEngine : public IGameObject
{
public:
	EffectEngine();
	~EffectEngine();
	/*!
	*@brief �X�V
	*/
	void Update() override;
	/*!
	*@brief �`��
	*/
	void Draw() override {};
	/*!
	*@brief �G�t�F�N�g�`��
	*/
	void DrawEffect() override;
	/*!
	*@brief �t�@�C���p�X�̐ݒ�
	*@param filePath �t�@�C���p�X
	*/
	void SetFilePath(const wchar_t* filePath)
	{
		m_effekseer = Effekseer::Effect::Create(m_effekseerManager, (const EFK_CHAR*)filePath);
	}
	/*!
	*@brief �g�嗦�̐ݒ�
	*@param scale �g�嗦
	*/
	void SetScale(const CVector3& scale)
	{
		m_effekseerManager->SetScale(m_playEffectHandle, scale.x, scale.y, scale.z);
	}
	/*!
	*@bried �G�t�F�N�g�̍Đ��ƍ��W�ݒ�
	*@param pos �G�t�F�N�g�̍��W
	*/
	void PlayAndSetPos(const CVector3& pos)
	{
		m_playEffectHandle = m_effekseerManager->Play(m_effekseer, pos.x, pos.y, pos.z);
	}
	/// <summary>
	/// Effekseer�̏������B
	/// </summary>
	void InitEffekseer();
private:
	//Effekseer�}�l�[�W���Ǘ��B
	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;
	Effekseer::Effect* m_effekseer = nullptr;	//�G�t�F�N�g
	Effekseer::Handle m_playEffectHandle;		//�n���h��

};
