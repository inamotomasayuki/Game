#include "stdafx.h"
#include "Player.h"

Player::Player()
{	

	//cmoファイルの読み込み。
	m_skinModel.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);

	//アニメーションクリップのロード。
	m_animClips[enAnimationClip_idle].Load(L"Assets/animData/idle.tka");
	m_animClips[enAnimationClip_run].Load(L"Assets/animData/run.tka");
	m_animClips[enAnimationClip_jump].Load(L"Assets/animData/jump.tka");
	m_animClips[enAnimationClip_damage].Load(L"Assets/animData/damage.tka");

	//ループフラグを設定する
	//走りアニメーションはループフラグを設定していないのでワンショット再生で停止。
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_run].SetLoopFlag(true);
	m_animClips[enAnimationClip_jump].SetLoopFlag(false);
	m_animClips[enAnimationClip_damage].SetLoopFlag(false);
	m_animation.Init(m_skinModel, m_animClips, enAnimationClip_Num);
}


Player::~Player()
{
}

void Player::Update()
{
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_animation.Update(1.0f / 60.0f);
	//パッド操作
	PadMove();
	//プレイヤーの回転
	Rotation();
	m_moveFloor = g_goMgr.FindGameObject<MoveFloor>("moveFloor");
	g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
		if (m_moveFloor->GetGhost()->IsSelf(contactObject) == true) {
			//m_ghostObjectとぶつかった	
			m_addSpeed = m_floorSpeed;	
			m_contactFloor = true;
		}
	});
	if (m_contactFloor) {
		m_moveSpeed += m_addSpeed;
		m_contactFloor = false;
	}
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);

}

void Player::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		1
	);
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix(),
		0
	);
}

void Player::PadMove()
{
	if (m_isAttacked == false) {
		//カメラを考慮したスティックでのプレイヤー移動
		//前方向の移動
		auto v = g_camera3D.GetTarget() - g_camera3D.GetPosition();
		v.Normalize();
		v.y = 0.0f;
		m_moveSpeed = v * g_pad[0].GetLStickYF() * 1000.0f;
		//横方向の移動
		CVector3 cameraSide;
		cameraSide.Cross(v, CVector3::AxisY());
		cameraSide.Normalize();
		m_moveSpeed -= cameraSide * g_pad[0].GetLStickXF() * 1000.0f;
	}
	//ダッシュ（仮）
	if (g_pad[0].IsPress(enButtonB)) {
		m_moveSpeed *= 2.0f;
	}
	////３段目のジャンプなら回転を求める
	if (m_jumpFlag == true && m_threeStep == 3) {
		CVector3 side;
		CVector3 v;
		CVector3 moveSpeedXZ;
		//if (m_moveSpeed.x || m_moveSpeed.z > 0) {
		//	v = m_moveSpeed;
			moveSpeedXZ = m_moveSpeed;
		/*}
		else if(m_moveSpeed.x && m_moveSpeed.z == 0) {
			moveSpeedXZ = moveSpeedXZ;
		}*/
		moveSpeedXZ.Normalize();
		side.Cross(moveSpeedXZ, CVector3::AxisY());
		side.Normalize();
		m_rotation.SetRotation(side, angle-=0.5f);
	}
	//デバッグ用上下移動
	//if (g_pad[0].IsPress(enButtonA)) {
	//	m_moveSpeed.y = 2000.0f;
	//}
	//if (g_pad[0].IsPress(enButtonB))
	//{
	//	m_moveSpeed.y = -2000.0f;
	//}

	//３段ジャンプ
	if (m_charaCon.IsOnGround() && g_pad[0].IsTrigger(enButtonA)) {
		//移動しながらジャンプしてたら段を進める
		if (m_moveSpeed.x || m_moveSpeed.z != 0) {
			m_threeStep++;
		}
		else {
			m_threeStep = 0;
			m_isMoveJump = false;
		}
		if (m_threeStep <= 1) {
			m_jumpSpeed = 4000.0f;
		}
		if (m_threeStep == 2) {
			m_jumpSpeed = 5000.0f;
		}
		if (m_threeStep == 3) {
			m_jumpSpeed = 8000.0f;
		}
		m_jumpFlag = true;
	}
	//移動せずにジャンプしてから移動しようとしたら空中では半分の速度
	if (m_isMoveJump == false) {
		m_moveSpeed.x /= 2;
		m_moveSpeed.z /= 2;
	}
	//ジャンプ
	if (m_jumpFlag == true) {
		m_moveSpeed.y = m_jumpSpeed;
		m_jumpSpeed *= 0.85f;
		if (m_jumpSpeed < 700.0f) {
			m_jumpSpeed = 0.0f;
			m_isMoveJump = true;
			m_jumpFlag = false;
			if (m_threeStep == 3) {
				m_threeStep = 0;
			}
		}
	}
	//地面に一定時間いたら3段ジャンプをリセットする
	if (m_charaCon.IsOnGround()) {
		m_timer++;
		if (m_timer == 7) {
			m_threeStep = 0;
			m_timer = 0;
		}
	}
	//重力
	if (m_charaCon.IsOnGround() == false) {
		m_timer = 0;
		m_animation.Play(enAnimationClip_jump, 0.1f);
		m_moveSpeed.y -= 1200.0f;
	}

	//攻撃されたらノックバックする。
	if (m_isAttacked == true) {
		m_animation.Play(enAnimationClip_damage, 0.1f);
		m_moveSpeed = m_addSpeed;
		m_moveSpeed.y -= 800.0f;
		m_addSpeed *= 0.75f;
		if (m_addSpeed.Length() < 0.01f) {
			m_addSpeed = CVector3::Zero();
		}
	}
	//m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
}
void Player::Rotation()
{
	//プレイヤーの回転
	//ｘとｚのベクトルから角度を求めて回転させる。
	auto moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	if (m_isAttacked == false) {
		if (moveSpeedXZ.LengthSq() < 0.8f) {
			if (m_charaCon.IsOnGround()) {
				m_animation.Play(enAnimationClip_idle, 0.1f);
			}
				return;		//入力量が小さいときは回転しない
		}
		else {
			if (m_charaCon.IsOnGround()) {
				m_animation.Play(enAnimationClip_run, 0.1f);
			}
		}
		//３段目のジャンプなら回転
		if (m_jumpFlag == true && m_threeStep == 3) {
			CQuaternion rot;
			rot.SetRotation(CVector3::AxisY(), atan2f(moveSpeedXZ.x, moveSpeedXZ.z));  //角度を求める関数
			m_rotation.Multiply(rot);
		} 
		if (m_threeStep < 3) {
			m_rotation.SetRotation(CVector3::AxisY(), atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
		}
	}
	else {
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(-moveSpeedXZ.x, -moveSpeedXZ.z));
	}
}