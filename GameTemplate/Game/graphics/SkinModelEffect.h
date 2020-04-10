#pragma once

#include "graphics/Shader.h"
class Game;
/*!
*@brief	モデルエフェクト。
*/
class ModelEffect : public DirectX::IEffect {
protected:
	std::wstring m_materialName;	//!<マテリアル名。

	Shader* m_pVSShader = nullptr;
	Shader* m_pPSShader = nullptr;
	Shader* m_pPSSilhouette = nullptr;		//シルエット描画用のピクセルシェーダー。
	Shader* m_pVSShadowMap = nullptr;
	Shader* m_pPSShadowMap = nullptr;
	Shader* m_pPSSky = nullptr;

	Shader m_vsShader;
	Shader m_psShader;
	Shader m_psSilhouette;
	Shader m_vsShadowMap;
	Shader m_psShadowMap;
	Shader m_psSky;

	bool isSkining;
	ID3D11ShaderResourceView* m_albedoTex = nullptr;
	ID3D11ShaderResourceView* m_toonMapTex = nullptr;
	
	EnRenderMode m_renderMode = enRenderMode_Invalid;	//レンダリングモード。
	ID3D11DepthStencilState* m_silhouettoDepthStepsilState = nullptr;	//シルエット描画用のデプスステンシルステート。
private:
	/// <summary>
	/// シルエット描画用のデプスステンシルステートを初期化する。
	/// </summary>
	void InitSilhouettoDepthStepsilState();
	void InitToonMap();
public:
	ModelEffect()
	{
		//頂点シェーダーをロード。
		m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
		m_psSilhouette.Load("Assets/shader/model.fx", "PSMain_Silhouette", Shader::EnType::PS);
		//todo シャドウマップ用のシェーダーをロード。
		m_psShadowMap.Load("Assets/shader/model.fx", "PSMain_ShadowMap", Shader::EnType::PS);
		m_psSky.Load("Assets/shader/model.fx", "PSMain_Sky", Shader::EnType::PS);
		//m_pVSShader = &m_vsShader;
		m_pPSShader = &m_psShader;
		m_pPSSilhouette = &m_psSilhouette;
		m_pPSShadowMap = &m_psShadowMap;
		m_pPSSky = &m_psSky;
		//デプスステンシルの初期化。
		InitSilhouettoDepthStepsilState();
		InitToonMap();
	}
	virtual ~ModelEffect()
	{
		if (m_albedoTex) {
			m_albedoTex->Release();
		}
		if (m_toonMapTex) {
			m_toonMapTex->Release();
		}
		if (m_silhouettoDepthStepsilState != nullptr) {
			m_silhouettoDepthStepsilState->Release();
		}
	}
	void __cdecl Apply(ID3D11DeviceContext* deviceContext) override;

	void __cdecl GetVertexShaderBytecode(void const** pShaderByteCode, size_t* pByteCodeLength) override
	{
		*pShaderByteCode = m_vsShader.GetByteCode();
		*pByteCodeLength = m_vsShader.GetByteCodeSize();
	}
	void SetAlbedoTexture(ID3D11ShaderResourceView* tex)
	{
		m_albedoTex = tex;
	}
	void SetMatrialName(const wchar_t* matName)
	{
		m_materialName = matName;
	}
	
	bool EqualMaterialName(const wchar_t* name) const
	{
		return wcscmp(name, m_materialName.c_str()) == 0;
	}
	void SetRenderMode(EnRenderMode renderMode)
	{
		m_renderMode = renderMode;
	}
};
/*!
*@brief
*  スキンなしモデルエフェクト。
*/
class NonSkinModelEffect : public ModelEffect {
public:
	NonSkinModelEffect()
	{
		m_vsShader.Load("Assets/shader/model.fx", "VSMain", Shader::EnType::VS);
		m_vsShadowMap.Load("Assets/shader/model.fx", "VSMain_ShadowMap", Shader::EnType::VS);
		m_pVSShadowMap = &m_vsShadowMap;
		m_pVSShader = &m_vsShader;
		isSkining = false;
	}
};
/*!
*@brief
*  スキンモデルエフェクト。
*/
class SkinModelEffect : public ModelEffect {
public:
	SkinModelEffect()
	{
		wchar_t hoge[256];
		GetCurrentDirectoryW(256, hoge);
		m_vsShader.Load("Assets/shader/model.fx", "VSMainSkin", Shader::EnType::VS);
		
		m_pVSShader = &m_vsShader;
		isSkining = true;
	}
};

/*!
*@brief
*  エフェクトファクトリ。
*/
class SkinModelEffectFactory : public DirectX::EffectFactory {
public:
	SkinModelEffectFactory(ID3D11Device* device) :
		EffectFactory(device) {}
	std::shared_ptr<DirectX::IEffect> __cdecl CreateEffect(const EffectInfo& info, ID3D11DeviceContext* deviceContext)override
	{
		std::shared_ptr<ModelEffect> effect;
		if (info.enableSkinning) {
			//スキニングあり。
			effect = std::make_shared<SkinModelEffect>();
		}
		else {
			//スキニングなし。
			effect = std::make_shared<NonSkinModelEffect>();
		}
		effect->SetMatrialName(info.name);
		if (info.diffuseTexture && *info.diffuseTexture)
		{
			ID3D11ShaderResourceView* texSRV;
			DirectX::EffectFactory::CreateTexture(info.diffuseTexture, deviceContext, &texSRV);
			effect->SetAlbedoTexture(texSRV);
		}
		return effect;
	}

	void __cdecl CreateTexture(const wchar_t* name, ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView** textureView) override
	{
		return DirectX::EffectFactory::CreateTexture(name, deviceContext, textureView);
	}
};
