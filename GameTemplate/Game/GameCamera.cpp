#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Game.h"
#include "GameData.h"

const float CAMERA_POS_Y_UNDER = -0.2f;						//カメラ位置低さ
const float CAMERA_POS_Y_UPPER = 0.8f;						//カメラ位置高さ
const float CAMERA_TARGET_Y = 100.0f;						//カメラターゲットY位置
const CVector3 CAMERA_POS = { 0.0f, 100.0f, -500.0f };		//カメラ位置
const CVector3 CAMERA_TARGET = { 0.0f, 100.0f, 0.0f };		//カメラターゲット
const float CAMERA_FAR = 100000.0f;							//カメラ遠平面
const CVector3 CAMERA_POS_STAGE_ONE = { 500.0f, 200.0f, -50.0f };	//ステージ１のカメラ位置

GameCamera::GameCamera()
{
	if (g_gameData.GetStageNo() == g_gameData.enStage_Zero) {
		g_camera3D.SetPosition(CAMERA_POS);
		g_camera3D.SetTarget(CAMERA_TARGET);
		g_camera3D.SetFar(CAMERA_FAR);
	}
	if (g_gameData.GetStageNo() == g_gameData.enStage_One) {
		g_camera3D.SetPosition(CAMERA_POS_STAGE_ONE);
		g_camera3D.SetTarget(CAMERA_TARGET);
		g_camera3D.SetFar(CAMERA_FAR);
	}
}


GameCamera::~GameCamera()
{

}

void GameCamera::Update()
{
	m_player = g_goMgr.FindGameObject<Player>("player");
	m_game = g_goMgr.FindGameObject<Game>("game");
	if (m_player != nullptr
		&& m_game != nullptr) {
		m_cameraTarget = m_player->GetPositon(); //注視点を計算する
		m_cameraTarget.y += CAMERA_TARGET_Y;		//プレイヤーの足元からちょっと上を注視点とする

		m_cameraPos = g_camera3D.GetPosition();
		m_toCameraPos = m_cameraPos - g_camera3D.GetTarget(); //注視点

		auto toCameraPosOld = m_toCameraPos;
		//Y軸周りの回転
		if (!m_game->GetStar()) {
			m_rotation.SetRotationDeg(CVector3::AxisY(), g_pad[0].GetRStickXF()*6.0f);
		}
		m_rotation.Multiply(m_toCameraPos);
		//X軸周りの回転
		CVector3 vUP = CVector3::Up();
		CVector3 vRotAxis;
		vRotAxis.Cross(m_toCameraPos, vUP);
		vRotAxis.Normalize();
		if (!m_game->GetStar()) {
			m_rotation.SetRotationDeg(vRotAxis, g_pad[0].GetRStickYF()*-6.0f);
		}
		m_rotation.Multiply(m_toCameraPos);
		//カメラの回転の上限をチェックする。
		//注視点から視点までのベクトルを正規化する。
		//正規化すると、ベクトルの大きさが１になる。
		//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
		auto toPosDir = m_toCameraPos;
		toPosDir.Normalize();
		if (toPosDir.y < CAMERA_POS_Y_UNDER) {
			//カメラが下向きすぎ。
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > CAMERA_POS_Y_UPPER) {
			//カメラが上向きすぎ。
			m_toCameraPos = toCameraPosOld;
		}
		//視点を計算する
		m_cameraPos = m_cameraTarget + m_toCameraPos;

		g_camera3D.SetTarget(m_cameraTarget);
		g_camera3D.SetPosition(m_cameraPos);
		g_camera3D.Update();
	}
}
void GameCamera::Draw()
{

}