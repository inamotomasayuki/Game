#pragma once
#include "EffekseerRuntime130/src/Effekseer/Effekseer.h"
#include "EffekseerRuntime130/src/EffekseerRendererCommon/EffekseerRenderer.Renderer.h"
#include "gameObject/IGameObject.h"
#include "EffectEngine.h"

class Effect : public IGameObject
{
public:
	Effect();
	~Effect();
	void Update();
	void Draw() {};
	void DrawEffect();
	/// <summary>
	/// エフェクトのファイルパス設定
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	virtual void SetFilePath(const wchar_t* filePath)
	{
		m_effekseer = Effekseer::Effect::Create(g_effectEngine.GetEffekseerManager(), (const EFK_CHAR*)filePath);
	}

	void SetScale(CVector3 scale)
	{
		g_effectEngine.GetEffekseerManager()->SetScale(m_playEffectHandle, scale.x, scale.y, scale.z);
	}
	void PlayAndSetPos(CVector3 pos)
	{
		m_playEffectHandle = g_effectEngine.GetEffekseerManager()->Play(m_effekseer, pos.x, pos.y, pos.z);
	}
private:
	Effekseer::Effect* m_effekseer = nullptr;				//エフェクト
	Effekseer::Handle m_playEffectHandle = -1;		//ハンドル
};
