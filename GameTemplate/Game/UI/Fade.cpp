#include "stdafx.h"
#include "Fade.h"

namespace {
	const float SPRITE_WIDTH = 1280.0f;						//スプライトの幅
	const float SPRITE_HIGHT = 720.0f;						//スプライトの高さ
	const float VIEW_BOLUME_WIDTH = 1280.0f;		//ビューボリュームの幅
	const float VIEW_BOLUME_HIGHT = 720.0f;			//ビューボリュームの高さ
	const float F_NEAR = 0.1f;						//近平面
	const float F_FAR = 100.0f;						//遠平面

	const int FADEOUT_TIMER = 15;					//フェードアウトまでの時間

	const float MINUS_ALPHA = -0.02f;				//アルファ値マイナス
	const float PLUS_ALPHA = 0.02f;					//アルファ値プラス
	const float MINUS_START_ALPHA = 1.0f;			//マイナスを開始するアルファ値
	const float INIT_ALPHA = -0.1f;					//アルファ初期値

	const float UPPER_ALPHA = 1.0f;					//アルファ値上限
	const float DELETE_ALPHA = 0.0f;				//このアルファ値で削除する

	const CVector3 CAMERA_POSITION = { 0, 0, -1 };		//カメラの位置
	const CVector3 CAMERA_TARGET = { 0, 0, 0 };			//カメラの注視点
	const CVector3 CAMERA_UP = { 0,1,0 };				//カメラの上方向
}

Fade::Fade()
{
	m_sprite.Init(L"Assets/sprite/black.dds", SPRITE_WIDTH, SPRITE_HIGHT);
	m_sprite.SetAlpha(INIT_ALPHA);
}


Fade::~Fade()
{
}

void Fade::Update()
{
	if (!m_isFade) {
		//暗くする
		m_sprite.DeltaAlpha(PLUS_ALPHA);
		if (m_sprite.GetAlpha() >= UPPER_ALPHA) {
			m_timer++;
		}
	}
	if (m_timer >= FADEOUT_TIMER) {
		m_isFade = true;
	}
	if (m_isFade) {
		//薄くする
		m_sprite.DeltaAlpha(MINUS_ALPHA);
		if (m_sprite.GetAlpha() <= DELETE_ALPHA) {
			//削除
			g_goMgr.DeleteGameObject(this);
		}
	}
	m_sprite.UpdateWorldMatrix(m_spritePos, m_spriteRot, m_spriteScale);
}

void Fade::DrawFade()
{
	CMatrix mView;
	CMatrix mProj;
	mView.MakeLookAt(
		CAMERA_POSITION,
		CAMERA_TARGET,
		CAMERA_UP
	);
	mProj.MakeOrthoProjectionMatrix(VIEW_BOLUME_WIDTH, VIEW_BOLUME_HIGHT, F_NEAR, F_FAR);

	//描画
	m_sprite.Draw(mView, mProj);

}
