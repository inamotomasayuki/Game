#include "stdafx.h"
#include "PlayerWarpState.h"
#include "Player.h"
#include "../gimmick/Warp.h"

namespace {
	const float ROTATION_SPEED = 1.0f;				//回転加算速度
	const int WARP_TIMER = 100;						//ワープ時間
	const float SE_VOLUME = 1.0f;					//ボリューム

}

PlayerWarpState::PlayerWarpState()
{
	//初期化
	Init();
}


PlayerWarpState::~PlayerWarpState()
{
	//削除
	Delete();
}

void PlayerWarpState::Update(Player* p)
{
	//ワープ中回転移動処理
	Rotation(p);
	//サウンド
	Sound();
}

void PlayerWarpState::Init()
{
	//サウンド
	for (int i = 0; i < enSE_Num; i++) {
		m_se[i] = g_goMgr.NewGameObject<CSoundSource>(0);
	}
	m_se[enSE_warp0]->Init(L"Assets/sound/warp0.wav");				//ワープ前
	m_se[enSE_warp1]->Init(L"Assets/sound/warp1.wav");				//ワープ後
}

void PlayerWarpState::Delete()
{
	//サウンド削除
	for (int i = 0; i < enSE_Num; i++) {
		g_goMgr.DeleteGameObject(m_se[i]);
	}
}

void PlayerWarpState::Rotation(Player* p)
{
	const auto& warp = g_goMgr.FindGameObject<Warp>("warp");
	if (!m_isRotReverse && warp->IsWarp()) {
		m_isRotStart = true;
	}
	//回転速度を上げる
	if (m_isRotStart) {
		m_warpTimer++;
		m_rotSpeed += ROTATION_SPEED;
	}
	if (m_warpTimer == WARP_TIMER) {
		//移動先に移動
		p->SetCharaConPos(warp->GetPosition());
		m_isRotReverse = true;
		m_warpTimer = 0;
	}
	//ワープ先で回転速度落とす
	if (m_isRotReverse) {
		m_isRotStart = false;
		if (m_rotSpeed > 0) {
			m_rotSpeed -= ROTATION_SPEED;
		}
		else {
			//ワープ完了
			warp->SetIsWarp(false);
			m_isRotReverse = false;
		}
	}
	//回転をプレイヤーに送る
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), m_rotSpeed);
	auto pRot = p->GetRotation();
	pRot.Multiply(addRot);
	p->SetRotation(pRot);
}

void PlayerWarpState::Sound()
{
	//ワープ音
	if (m_isRotStart) {
		m_se[enSE_warp0]->Play(false);
	}
	if (m_isRotReverse) {
		m_se[enSE_warp0]->Stop();
		m_se[enSE_warp1]->SetVolume(SE_VOLUME);
		m_se[enSE_warp1]->Play(false);
	}
	else {
		m_se[enSE_warp1]->Stop();
	}
}