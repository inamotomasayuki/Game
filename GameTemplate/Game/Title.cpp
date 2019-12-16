#include "stdafx.h"
#include "Title.h"
#include "Game.h"

const CVector3 CAMERA_POSITION = { 0, 0, -1 };		//カメラの位置
const CVector3 CAMERA_TARGET = { 0, 0, 0 };			//カメラの注視点
const CVector3 CAMERA_UP = { 0,1,0 };				//カメラの上方向

Title::Title()
{
	m_sprite.Init(L"Assets/sprite/kaburon.dds", 1280, 720);
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
	mProj.MakeOrthoProjectionMatrix(1280.0f, 720.0f, 0.1f, 100.0f);
	//描画
	m_sprite.Draw(mView, mProj);
	
}

