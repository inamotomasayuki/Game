#include "stdafx.h"
#include "Title.h"
#include "Game.h"

const float VIEW_BOLUME_WIDTH = 1280.0f;		//ビューボリュームの幅
const float VIEW_BOLUME_HIGHT = 720.0f;			//ビューボリュームの高さ
const float F_NEAR = 0.1f;						//近平面
const float F_FAR = 100.0f;						//遠平面

const CVector3 CAMERA_POSITION = { 0, 0, -1 };		//カメラの位置
const CVector3 CAMERA_TARGET = { 0, 0, 0 };			//カメラの注視点
const CVector3 CAMERA_UP = { 0,1,0 };				//カメラの上方向

const float SPRITE_WIDTH = 1280.0f;		//スプライトの幅
const float SPRITE_HIGHT = 720.0f;			//スプライトの高さ

Title::Title()
{
	m_sprite.Init(L"Assets/sprite/kaburon.dds", SPRITE_WIDTH, SPRITE_HIGHT);
}


Title::~Title()
{
}

void Title::Update()
{
	m_sprite.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	//ゲームに遷移
	if (g_pad[0].IsTrigger(enButtonA)){
		g_goMgr.NewGameObject<Game>("game");
		g_goMgr.DeleteGameObject(this);
	}
}

void Title::Draw()
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

