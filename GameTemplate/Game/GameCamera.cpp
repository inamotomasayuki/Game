#include "stdafx.h"
#include "GameCamera.h"
#include "player/Player.h"
#include "Game.h"
#include "GameData.h"
namespace {
	const float CAMERA_POS_Y_UNDER = -0.2f;						//カメラ位置低さ
	const float CAMERA_POS_Y_UPPER = 0.8f;						//カメラ位置高さ
	const float CAMERA_TARGET_Y = 100.0f;						//カメラターゲットY位置
	const float CAMERA_LENGTH_MIN = 100.0f;						//カメラ最小距離
	const float CAMERA_LENGTH_MAX = 1000.0f;					//カメラ最大距離
	const CVector3 CAMERA_POS = { 0.0f, 300.0f, -500.0f };		//カメラ位置
	const CVector3 CAMERA_UP_POS = { 1000.0f, 0.0f, 0.0f };		//カメラ位置
	const CVector3 CAMERA_TARGET = { 0.0f, 100.0f, 0.0f };		//カメラターゲット
	const float CAMERA_FAR = 100000.0f;							//カメラ遠平面

	const CVector3 CAMERA_POS_STAGE_ONE = { 0.0f, 10.0f, 1000.0f };	//ステージ１のカメラ位置
	const float GAMECLEAR_CAMERA_POS_Y = 200.0f;			//ゲームクリアカメラの高さ
	const float GAMEOVER_CAMERA_POS_Y = 2000.0f;			//ゲームオーバーカメラの高さ
	const float ZOOM_SPEED = 15.0f;							//ズーム速度
	const float CLEAR_CAMERA_ZOOM_SPEED = 0.97f;			//クリア時のカメラのズーム速度
	const float CLEAR_CAMERA_START_LENGTH = 1000.0f;		//クリアした時のカメラの距離
	const float CLEAR_CAMERA_END_LENGTH = 300.0f;			//ズームした後のカメラの距離

}

GameCamera::GameCamera()
{
	//ステージ１
	if (g_gameData.GetStageNo() == g_gameData.enStage_Zero) {
		g_camera3D.SetPosition(CAMERA_POS);
		g_camera3D.SetTarget(CAMERA_TARGET);
		g_camera3D.SetFar(CAMERA_FAR);
	}
	//ステージ２
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
		m_cameraTarget = m_player->GetPositon();	//注視点を計算する
		m_cameraTarget.y += CAMERA_TARGET_Y;		//プレイヤーの足元からちょっと上を注視点とする
		//ステージ１カメラ
		StageOneCamera();
		//ゲームオーバー時、視点を戻す
		if (m_game->GetIsStop() && !m_player->IsOnGround()) {
			if (!m_isStop) {
				auto pos = m_player->GetPositon();
				pos += CAMERA_POS;
				g_camera3D.SetPosition(pos);
				m_isStop = true;
			}
		}
		m_cameraPos = g_camera3D.GetPosition();					//視点
		m_toCameraPos = m_cameraPos - g_camera3D.GetTarget();	//注視点
		//回転
		Rotation();
		//視点を計算する
		m_cameraPos = m_cameraTarget + m_toCameraPos;
		//ゲームクリアカメラ
		GameClearCamera();
		//ゲームオーバーカメラ
		GameOverCamera();
		if (!m_game->GetIsStar()) {
			//ズームイン・アウト
			ZoomInAndOut();
		}
		g_camera3D.SetTarget(m_cameraTarget);
		g_camera3D.SetPosition(m_cameraPos);
		g_camera3D.Update();
	}
}

void GameCamera::Rotation()
{
	CVector3 toCameraPosOld = m_toCameraPos;
	//Y軸周りの回転
	if (g_gameData.GetStageNo() != g_gameData.enStage_One) {
		if (!m_game->GetStar()) {
			m_rotation.SetRotationDeg(CVector3::AxisY(), g_pad[0].GetRStickXF() * 6.0f);
		}
		m_rotation.Multiply(m_toCameraPos);
	}
	//X軸周りの回転
	const CVector3& vUP = CVector3::Up();
	CVector3 vRotAxis;
	vRotAxis.Cross(m_toCameraPos, vUP);
	vRotAxis.Normalize();
	if (g_gameData.GetStageNo() != g_gameData.enStage_One) {
		if (!m_game->GetStar()) {
			if (!g_pad[0].IsPress(enButtonLB1)) {
				m_rotation.SetRotationDeg(vRotAxis, g_pad[0].GetRStickYF() * -6.0f);
			}
		}
		m_rotation.Multiply(m_toCameraPos);
	}
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	auto toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (g_gameData.GetStageNo() != g_gameData.enStage_One) {
		if (toPosDir.y < CAMERA_POS_Y_UNDER) {
			//カメラが下向きすぎ。
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > CAMERA_POS_Y_UPPER) {
			//カメラが上向きすぎ。
			m_toCameraPos = toCameraPosOld;
		}
	}
}

void GameCamera::ZoomInAndOut()
{
	//操作前の位置
	auto cameraPosOld = m_cameraPos;
	//カメラからカメラターゲットへの方向
	auto v = g_camera3D.GetTarget() - g_camera3D.GetPosition();
	v.Normalize();
	if (g_gameData.GetStageNo() != g_gameData.enStage_One) {
		//LB１ボタンを押しながら右スティックで視点をズーム操作する
		if (g_pad[0].IsPress(enButtonLB1)) {
			m_moveSpeed = v * g_pad[0].GetRStickYF() * ZOOM_SPEED;
			m_cameraPos += m_moveSpeed;
		}
	}
	//操作後の位置との距離
	//近いor遠くなったら操作前の位置に戻す。
	auto vec = g_camera3D.GetTarget() - m_cameraPos;
	auto len = vec.Length();
	if (len < CAMERA_LENGTH_MIN) {
		m_cameraPos = cameraPosOld;
	}
	else if (len > CAMERA_LENGTH_MAX) {
		m_cameraPos = cameraPosOld;
	}
}

void GameCamera::StageOneCamera()
{
	if (g_gameData.GetStageNo() == g_gameData.enStage_One) {
		if (m_player->GetButtonState() == 1) {
			m_isButtonYoko = true;
		}
		else {
			m_isButtonMae = true;
		}
		//横向き
		if (m_isButtonYoko) {
			auto pos = m_player->GetPositon();
			pos += CAMERA_UP_POS;
			pos.y += CAMERA_TARGET_Y;
			g_camera3D.SetPosition(pos);
			m_isButtonYoko = false;
		}
		//前向き
		if (m_isButtonMae) {
			auto pos = m_player->GetPositon();
			pos += CAMERA_POS_STAGE_ONE;
			pos.y += CAMERA_TARGET_Y;
			g_camera3D.SetPosition(pos);
			m_isButtonMae = false;
		}
	}
}

void GameCamera::GameClearCamera()
{
	if (m_game->GetIsStar()) {
		if (!m_isClearCameraInit) {
			//カメラの位置を正面向きで離す
			m_clearPos = m_player->GetPositon() - m_cameraPos;
			m_clearPos.y = GAMECLEAR_CAMERA_POS_Y;
			m_clearPos.Normalize();
			m_nextCameraPos = m_clearPos;
			m_nextCameraPos *= CLEAR_CAMERA_END_LENGTH;
			m_clearPos *= CLEAR_CAMERA_START_LENGTH;
			m_isClearCameraInit = true;
		}
		//ズームする
		if (m_nextCameraPos.Length() < m_clearPos.Length()) {
			m_clearPos *= CLEAR_CAMERA_ZOOM_SPEED;
		}
		m_cameraPos = m_cameraTarget + m_clearPos;
	}
}

void GameCamera::GameOverCamera()
{
	if (!m_game->GetGameOverFlag()) {
		m_oldPos = m_cameraPos;
		m_oldPos.y += GAMEOVER_CAMERA_POS_Y;
	}
	else if (m_game->GetGameOverFlag()
		&& !m_game->GetIsHp0GameOver()
		&& !m_player->IsOnGround()) {
		if (m_game->GetIsStop()) {
			m_cameraPos = m_cameraTarget + m_toCameraPos;
		}
		else {
			//視点を上からにする
			m_cameraPos = m_oldPos;
		}
	}
}