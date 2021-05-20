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
	*@brief 更新
	*/
	void Update() override;
	/*!
	*@brief 描画
	*/
	void Draw() override {};
	/*!
	*@brief エフェクト描画
	*/
	void DrawEffect() override;
	/*!
	*@brief ファイルパスの設定
	*@param filePath ファイルパス
	*/
	void SetFilePath(const wchar_t* filePath)
	{
		m_effekseer = Effekseer::Effect::Create(m_effekseerManager, (const EFK_CHAR*)filePath);
	}
	/*!
	*@brief 拡大率の設定
	*@param scale 拡大率
	*/
	void SetScale(const CVector3& scale)
	{
		m_effekseerManager->SetScale(m_playEffectHandle, scale.x, scale.y, scale.z);
	}
	/*!
	*@bried エフェクトの再生と座標設定
	*@param pos エフェクトの座標
	*/
	void PlayAndSetPos(const CVector3& pos)
	{
		m_playEffectHandle = m_effekseerManager->Play(m_effekseer, pos.x, pos.y, pos.z);
	}
	/// <summary>
	/// Effekseerの初期化。
	/// </summary>
	void InitEffekseer();
private:
	//Effekseerマネージャ管理。
	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;
	Effekseer::Effect* m_effekseer = nullptr;	//エフェクト
	Effekseer::Handle m_playEffectHandle;		//ハンドル

};
