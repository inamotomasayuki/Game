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
	m_animClips[enAnimationClip_walk].Load(L"Assets/animData/walk.tka");

	//ループフラグを設定する
	//走りアニメーションはループフラグを設定していないのでワンショット再生で停止。
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_run].SetLoopFlag(true);
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_jump].SetLoopFlag(false);
	m_animClips[enAnimationClip_damage].SetLoopFlag(false);
	m_animation.Init(m_skinModel, m_animClips, enAnimationClip_Num);
}


Player::~Player()
{
}

void Player::Update()
{
	
	float DELTA_TIME = 1.0f / 60.0f;
	bool isJump = m_jumpFlag;
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_animation.Update(DELTA_TIME);
	//パッド操作
	PadMove();
	//プレイヤーの回転
	Rotation();
	m_backGround = g_goMgr.FindGameObject<BackGround>("backGround");
	m_moveFloor = g_goMgr.FindGameObject<MoveFloor>("moveFloor");
	m_jumpFloor = g_goMgr.FindGameObject<JumpFloor>("jumpFloor");
	if (g_pad[0].IsTrigger(enButtonX)) {
		m_charaCon.SetPosition(m_jumpFloor->GetPosition());
	}
	bool isContact = false;
	g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
		if (m_moveFloor->GetGhost()->IsSelf(contactObject) == true) {
			//m_ghostObjectとぶつかった	
			m_addSpeed = m_floorSpeed;
		
			m_contactFloor = true;
			isContact = true;
		}

		if (m_jumpFloor->GetGhost()->IsSelf(contactObject) == true) {
			m_jumpSpeed = 23000.0f;
			m_contactJumpFloor = true;
		}
	});
	if (m_contactJumpFloor) {
		m_jumpSpeed *= 0.90f;
		m_moveSpeed.y = m_jumpSpeed;
		if (m_moveSpeed.Length() < 1000.0f) {
			m_contactJumpFloor = false;
		}
	}
	if (isContact == false) {
		m_contactFloor = false;
	}
	if (!isJump && m_jumpFlag) {
		m_moveSpeed += m_addSpeed;
	}
	if (m_contactFloor) {
		CVector3 movespeed = m_moveSpeed + m_addSpeed;
		m_position = m_charaCon.Execute(DELTA_TIME, movespeed);
	}
	else {
	
		m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);
	}
	m_moveSpeed *= 0.95f;
	if (m_moveSpeed.Length() < 40.0f) {
		m_moveSpeed = CVector3::Zero();
	}
	AnimationController();
}

void Player::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Silhouette
	);	
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);

	
}

void Player::PadMove()
{
	const float MOVE_SPEED = 50.0f;
	float DASH_SPEED = 1.0f;
	if (g_pad[0].IsPress(enButtonB)) {
		DASH_SPEED = 2.0f;
		if (m_moveSpeed.Length() < 2000.0f) {
			m_contactJumpFloor = false;
		}
	}
	else {
		DASH_SPEED = 1.0f;
	}
	if (m_isAttacked == false) {
		//カメラを考慮したスティックでのプレイヤー移動
		//前方向の移動
		auto v = g_camera3D.GetTarget() - g_camera3D.GetPosition();
		v.Normalize();
		v.y = 0.0f;
		m_moveSpeed += v * g_pad[0].GetLStickYF() * MOVE_SPEED * DASH_SPEED;
		
		//横方向の移動
		CVector3 cameraSide;
		cameraSide.Cross(v, CVector3::AxisY());
		cameraSide.Normalize();
		m_moveSpeed -= cameraSide * g_pad[0].GetLStickXF() * MOVE_SPEED * DASH_SPEED;

		//m_moveSpeed *= 0.90f;
		/*if (m_moveSpeed.Length() < 10.0f)
		{
			m_moveSpeed = CVector3::Zero();
		}*/
	}
	
	//ダッシュ（仮）
	
	
	//３段目のジャンプなら回転を求める
	//if (m_jumpFlag == true && m_threeStep == 3) {
	//	CVector3 side;
	//	CVector3 v;
	//	CVector3 moveSpeedXZ;
	//	//if (m_moveSpeed.x || m_moveSpeed.z > 0) {
	//	//	v = m_moveSpeed;
	//		moveSpeedXZ = m_moveSpeed;
	//	/*}
	//	else if(m_moveSpeed.x && m_moveSpeed.z == 0) {
	//		moveSpeedXZ = moveSpeedXZ;
	//	}*/
	//	moveSpeedXZ.Normalize();
	//	side.Cross(moveSpeedXZ, CVector3::AxisY());
	//	side.Normalize();
	//	m_rotation.SetRotation(side, angle-=0.5f);
	//}

	//３段ジャンプ
	if (m_charaCon.IsOnGround()){
		m_jumpFlag = false;
			if (g_pad[0].IsTrigger(enButtonA)) {
				//移動しながらジャンプしてたら段を進める
				if (m_moveSpeed.x || m_moveSpeed.z != 0) {
					m_threeStep++;
				}
				else {
					m_threeStep = 0;
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
	}
	
	//ジャンプ
	if (m_jumpFlag == true) {
		m_moveSpeed.y = m_jumpSpeed;
		m_jumpSpeed *= 0.85f;
		//if (m_jumpSpeed < 700.0f) {
		//	m_jumpSpeed = 0.0f;
		//}
		//	//m_jumpFlag = false;
			if (m_threeStep == 3) {
				m_threeStep = 0;
			}
		//}
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
		float gravity = 400.0f;
		gravity *= 2.0f;
		m_moveSpeed.y -= gravity;
	}

	//攻撃されたらノックバックする。
	if (m_isAttacked == true) {
		m_moveSpeed = m_addSpeed;
		m_moveSpeed.y -= 800.0f;
		m_addSpeed *= 0.75f;
		if (m_addSpeed.Length() < 0.01f) {
			m_addSpeed = CVector3::Zero();
		}
	}
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
				return;		//入力量が小さいときは回転しない
		}
		//３段目のジャンプなら回転
		//if (m_jumpFlag == true && m_threeStep == 3) {
		//	CQuaternion rot;
		//	rot.SetRotation(CVector3::AxisY(), atan2f(moveSpeedXZ.x, moveSpeedXZ.z));  //角度を求める関数
		//	m_rotation.Multiply(rot);
		//} 
		if (m_threeStep < 3) {
			m_rotation.SetRotation(CVector3::AxisY(), atan2f(moveSpeedXZ.x, moveSpeedXZ.z));
		}
	}
	else {
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(-moveSpeedXZ.x, -moveSpeedXZ.z));
	}
}
void Player::AnimationController()
{
	if (m_charaCon.IsOnGround() && !m_isAttacked) {
		if (m_moveSpeed.LengthSq() >= 1000000.0f) {
			m_animation.Play(enAnimationClip_run, 0.1f);
		}
		else if (m_moveSpeed.LengthSq() >= 10.0f) {
			m_animation.Play(enAnimationClip_walk, 0.1f);
		}
		else {
			m_animation.Play(enAnimationClip_idle, 0.1f);
		}
	}
	if (m_charaCon.IsOnGround() == false) {
		m_animation.Play(enAnimationClip_jump, 0.1f);
	}
	if (m_isAttacked == true) {
		m_animation.Play(enAnimationClip_damage, 0.1f);
	}
}