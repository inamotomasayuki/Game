#include "stdafx.h"
#include "Coin.h"
#include "Game.h"
namespace {
	const float PYON_UP = 20.0f;			//跳ね上がるときの速度
	const float PYON_DOWN = -20.0f;			//跳ね落ちるときの速度
	const int PYON_UP_TIME = 5;				//跳ね上がる時間
	const int PYON_DOWN_TIME = 8;			//跳ね落ちる時間
	const int DELETE_TIME = 10;				//削除までの待ち時間
	const int COIN_SCORE = 1;				//コインのスコア
	const float FLAG_LENGTH = 110.0f;		//コイン取得フラグさせるプレイヤーとの距離
	const float ROTATION_SPEED = 5.0f;		//回転速度
	const float DLIG_COLOR = 2.0f;		    //ディレクションライトの明るさ
	//アンビエントライト
	const CVector4 AMBIENT[2] = {
		{ 0.5f,0.5f,0.5f,1.0f },
		{ 0.1f,0.1f,0.1f,1.0f }
	};
	const float LIG_LENGTH = 6000.0f;		//明るさ距離
}

Coin::Coin()
{
	m_skinModel.Init(L"Assets/modelData/coin.cmo");
	//ゴースト
	m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
	//効果音
	m_se = g_goMgr.NewGameObject<CSoundSource>(0);
	m_se->Init(L"Assets/sound/coin.wav");
}


Coin::~Coin()
{

}

void Coin::Update()
{	
	m_player = g_goMgr.FindGameObject<Player>("player");
	m_game = g_goMgr.FindGameObject<Game>("game");

	//回転
	Rotation();
	//コイン取得処理
	GetCoin();	
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//ゴースト更新
	m_ghostObject.SetPosition(m_position);
	m_ghostObject.SetRotation(m_rotation);

}
void Coin::Draw()
{
	//描画
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	//リムライトオフ
	m_skinModel.RimLightOff();
	m_skinModel.ToonOff();
	//シャドウレシーバーオフ
	m_skinModel.ShadowReciverOff();
	//ライトの方向・明るさ設定
	auto dir = m_position - g_camera3D.GetPosition();
	auto len = dir.Length();
	if (len > LIG_LENGTH) {
		m_skinModel.SetAmbient(AMBIENT[0]);
	}
	else{
		m_skinModel.SetAmbient(AMBIENT[1]);
	}	
	m_skinModel.SetDligColor(0, DLIG_COLOR);
	m_skinModel.SetDligColor(1, DLIG_COLOR);
}
void Coin::Rotation()
{
	auto dir = m_position - g_camera3D.GetPosition();
	auto len = dir.Length();
	//一定速度で回転させる
	float rotSpeed = 0.0f;;
	rotSpeed += ROTATION_SPEED;
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
	m_addRot.Multiply(addRot);
	if (len <= LIG_LENGTH) {
		if (!m_isInit) {
			m_rotation = CQuaternion::Identity();
			m_isInit = true;
		}
		m_rotation = m_addRot;
	}
	else {
		m_isInit = false;
		//カメラの回転行列を取得
		CMatrix mRotCamera = g_camera3D.GetViewMatrix();
		//カメラ行列の逆行列はカメラのワールド行列。
		mRotCamera.Inverse(mRotCamera);
		//平行移動成分はいらない。
		mRotCamera.m[3][0] = 0.0f;
		mRotCamera.m[3][1] = 0.0f;
		mRotCamera.m[3][2] = 0.0f;
		//カメラの回転行列から、コインの回転クォータニオンを求める。
		m_rotation.SetRotation(mRotCamera);
	}
}

void Coin::GetCoin()
{
	if (m_player != nullptr) {
		const CVector3& v = m_player->GetPositon() - m_position;
		float len = v.Length();
		//距離が一定以下なら取得フラグを立てる
		if (len < FLAG_LENGTH) {
			m_coinGetFlag = true;
		}
	}
	g_goMgr.FindGameObjects<EnemyBall>("enemyBall", [this](EnemyBall* enemyBall)->bool {
		const auto& enemy_v = enemyBall->GetPositon() - m_position;
		auto enemy_len = enemy_v.Length();
		//甲羅と一定距離ならフラグを立てる
		if (enemy_len < FLAG_LENGTH) {
			m_coinGetFlag = true;
		}
		return true;
		});
	//フラグが立ったら跳ねさせる
	if (m_coinGetFlag == true) {
		m_timer++;
		m_se->Play(false);
		if (m_timer < PYON_UP_TIME) {
			m_moveSpeed.y = PYON_UP;
			m_position += m_moveSpeed;
		}
		if (m_timer >= PYON_UP_TIME && m_timer < PYON_DOWN_TIME) {
			m_moveSpeed.y = PYON_DOWN;
			m_position += m_moveSpeed;
		}
		//削除
		if (m_timer == DELETE_TIME) {	
			m_timer = 0;
			m_game->SetScore(COIN_SCORE);
			g_goMgr.DeleteGameObject(this);
		}
	}
}