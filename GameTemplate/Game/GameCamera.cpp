#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{
	g_camera3D.SetPosition({ 0.0f, 100.0f, -500.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(100000.0f);
}


GameCamera::~GameCamera()
{

}

void GameCamera::Update()
{		
	m_player = g_goMgr.FindGameObject<Player>("player");
	if (m_player != nullptr) {
		m_cameraTarget = m_player->GetPositon(); //注視点を計算する
		m_cameraTarget.y += 100.0f;		//プレイヤーの足元からちょっと上を注視点とする

		m_cameraPos = g_camera3D.GetPosition();
		m_toCameraPos = m_cameraPos - g_camera3D.GetTarget(); //注視点

		auto toCameraPosOld = m_toCameraPos;
		//Y軸周りの回転
		m_rotation.SetRotationDeg(CVector3::AxisY(), g_pad[0].GetRStickXF()*6.0f);
		m_rotation.Multiply(m_toCameraPos);
		//X軸周りの回転
		CVector3 vUP = CVector3::Up();
		CVector3 vRotAxis;
		vRotAxis.Cross(m_toCameraPos, vUP);
		vRotAxis.Normalize();
		m_rotation.SetRotationDeg(vRotAxis, g_pad[0].GetRStickYF()*-6.0f);
		m_rotation.Multiply(m_toCameraPos);
		//カメラの回転の上限をチェックする。
		//注視点から視点までのベクトルを正規化する。
		//正規化すると、ベクトルの大きさが１になる。
		//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
		auto toPosDir = m_toCameraPos;
		toPosDir.Normalize();
		if (toPosDir.y < -0.2f) {
			//カメラが下向きすぎ。
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.8) {
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