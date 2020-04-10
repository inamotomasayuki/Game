#include "stdafx.h"
#include "Effect.h"
#include "EffekseerRuntime130/src/EffekseerRendererDX11/EffekseerRendererDX11.h"


Effect::Effect()
{
}


Effect::~Effect()
{
	//エフェクトを破棄。
	if (m_effekseer != nullptr) {
		m_effekseer->Release();
	}

}
void Effect::Update()
{
	//Effekseerカメラ行列を設定。
	//まずはEffeseerの行列型の変数に、カメラ行列とプロジェクション行列をコピー。
	Effekseer::Matrix44 efCameraMat;
	g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
	Effekseer::Matrix44 efProjMat;
	g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
	//カメラ行列とプロジェクション行列を設定。
	g_effectEngine.GetEffekseerRender()->SetCameraMatrix(efCameraMat);
	g_effectEngine.GetEffekseerRender()->SetProjectionMatrix(efProjMat);
	//Effekseerを更新。
	g_effectEngine.GetEffekseerManager()->Update();
}
void Effect::DrawEffect()
{
	//エフェクトは不透明オブジェクトを描画した後で描画する。
	g_effectEngine.GetEffekseerRender()->BeginRendering();
	g_effectEngine.GetEffekseerManager()->Draw();
	g_effectEngine.GetEffekseerRender()->EndRendering();
}
