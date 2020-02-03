#pragma once
#include "EffekseerRuntime130/src/Effekseer/Effekseer.h"
#include "EffekseerRuntime130/src/EffekseerRendererCommon/EffekseerRenderer.Renderer.h"


class Effect
{
public:
	Effect();
	~Effect();
	void Update();
	void Draw();
	/// <summary>
	/// Effekseerの初期化。
	/// </summary>
	void InitEffekseer();	
	/// <summary>
	/// EffekseerManagerの取得
	/// </summary>
	/// <returns>EffekseerManager</returns>
	Effekseer::Manager* GetEffekseerManager()
	{
		return m_effekseerManager;
	}
	/*!
	 *@brief　エフェクトのロードと取得
	*@param[in] filePath ファイルパス
	*/
	Effekseer::Effect* GetAndCreateEffect( const wchar_t* filePath);
	/*!
	 *@brief　エフェクトの再生とハンドルの取得
	*@param[in] effect エフェクト
	*@param[in] pos エフェクトの位置
	*/
	Effekseer::Handle GetAndEffectPlay( Effekseer::Effect* effect, CVector3 pos);
private:
	//Effekseerマネージャ管理。
	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;
};

extern Effect* g_effect;