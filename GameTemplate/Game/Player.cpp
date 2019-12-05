#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "JumpFloor.h"
const float DELTA_TIME = 1.0f / 60.0f;			//経過時間　単位：秒
const float INTERPOLATE_TIME = 0.1f;			//補完時間　単位：秒

const float MOVE_SPEED = 50.0f;					//移動速度
float DASH_SPEED = 1.0f;						//ダッシュ速度
const float KNOCK_BACK_SPEED = 800.0f;			//ノックバック速度

const float MOVE_SPEED_DECAY = 0.95f;			//移動速度減衰
const float JUMP_SPEED_DECAY = 0.85f;			//ジャンプ速度減衰
const float JUMP_FLOOR_SPEED_DECAY = 0.90f;		//ジャンプ床時の速度減衰
const float ADD_SPEED_DECAY = 0.75f;			//加算速度減衰

const float GRAVITY_ACCELERATION = 1.05f;		//重力加速度

//条件式用の速度の大きさの数値
const float MOVE_SPEED_LENGTH = 40.0f;			//移動中
const float DASH_SPEED_LENGTH = 2000.0f;		//ダッシュ中
const float JUMP_FLOOR_SPEED_LENGTH = 1000.0f;	//ジャンプ床のジャンプ中
const float ADD_SPEED_LENGTH = 0.01f;			//加速度加算中
const float INPUT_AMOUNT_LENGTH = 0.8f;			//角度を求めるときの入力量
const float INPUT_AMOUNT_DASH_LENGTH = 1000000.0f;	//走りアニメーションさせる
const float INPUT_AMOUNT_WALK_LENGTH = 10.0f;		//歩きアニメーションさせる
const int TIMER = 7;

const float ANIMATION_DOWN_SPEED = 3.0f;		//ダウンアニメーションスピード
const float ANIMATION_CLEAR_SPEED = 2.0f;		//クリアアニメーションスピード

Player::Player()
{
	//cmoファイルの読み込み。
	m_skinModel.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);

	//アニメーションクリップの
	//ロードとループフラグ設定
	InitAnimationClip();

	m_animation.Init(m_skinModel, m_animClips, enAnimationClip_Num);
}


Player::~Player()
{
}

void Player::Update()
{


	bool isJump = m_jumpFlag;
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//パッド操作
	PadMove();
	//プレイヤーの回転
	Rotation();

	m_moveFloor = g_goMgr.FindGameObject<MoveFloor>("moveFloor");
	m_jumpFloor = g_goMgr.FindGameObject<JumpFloor>("jumpFloor");
	m_star = g_goMgr.FindGameObject<Star>("star");
	if (g_pad[0].IsTrigger(enButtonX)) {
		m_charaCon.SetPosition(m_jumpFloor->GetPosition());
	}
	if (g_pad[0].IsTrigger(enButtonY)) {
		m_charaCon.SetPosition(m_moveFloor->GetPosition());
	}

	bool isContact = false;

	g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
		//星とぶつかった
		if (m_star->GetGhost()->IsSelf(contactObject) == true) {
			m_game->SetGetStarFlag();
		}
		//動く床とぶつかった
		if (m_moveFloor->GetGhost()->IsSelf(contactObject) == true) {
			m_addSpeed = m_floorSpeed;
			m_contactFloor = true;
			isContact = true;
		}
		//ジャンプ床とぶつかった
		if (m_jumpFloor->GetGhost()->IsSelf(contactObject) == true) {
			m_jumpSpeed = 23000.0f;
			m_contactJumpFloor = true;
		}
	});

	if (m_contactJumpFloor) {
		m_jumpSpeed *= JUMP_FLOOR_SPEED_DECAY;
		m_moveSpeed.y = m_jumpSpeed;
		m_gravity = GRAVITY;
		if (m_moveSpeed.Length() < JUMP_FLOOR_SPEED_LENGTH) {
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
		if (!m_isAttacked) {
			m_addSpeed = CVector3::Zero();
		}
		m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);
	}
	m_moveSpeed *= MOVE_SPEED_DECAY;
	if (m_moveSpeed.Length() < MOVE_SPEED_LENGTH) {
		m_moveSpeed = CVector3::Zero();
	}
	if (m_game != nullptr) {
		//アニメーション
		AnimationController();
	}
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

	//Bダッシュ
	if (g_pad[0].IsPress(enButtonB)) {
		DASH_SPEED = 2.0f;
		if (m_moveSpeed.Length() < DASH_SPEED_LENGTH) {
			m_contactJumpFloor = false;
		}
	}
	else {
		DASH_SPEED = 1.0f;
	}
	
	m_game = g_goMgr.FindGameObject<Game>("game");
	if (m_game != nullptr) {
		if (m_isAttacked == false 
			&& !m_game->GetGameOverFlag()
			&& !m_game->GetStar()) {
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

			//３段ジャンプ
			if (m_charaCon.IsOnGround()) {
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
		}
		if (m_game->GetGameClearFlag()) {
			m_moveSpeed *= 0.0f;
		}
	}

	//ジャンプ
	if (m_jumpFlag == true) {
		m_moveSpeed.y = m_jumpSpeed;
		m_jumpSpeed *= JUMP_SPEED_DECAY;
		if (m_threeStep == 3) {
			m_threeStep = 0;
		}
	}

	//地面に一定時間いたら3段ジャンプをリセットする
	if (m_charaCon.IsOnGround()) {
		m_timer++;
		if (m_timer == TIMER) {
			m_threeStep = 0;
			m_timer = 0;
		}
	}

	//重力
	if (m_charaCon.IsOnGround() == false) {
		m_gravity *= GRAVITY_ACCELERATION;
		m_moveSpeed.y -= m_gravity;
	}
	else {
		m_gravity = GRAVITY;
	}

	//攻撃されたらノックバックする。
	if (m_isAttacked == true) {
		m_moveSpeed = m_addSpeed;
		m_moveSpeed.y -= KNOCK_BACK_SPEED;
		m_addSpeed *= ADD_SPEED_DECAY;
		if (m_addSpeed.Length() < ADD_SPEED_LENGTH) {
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
		if (moveSpeedXZ.LengthSq() < INPUT_AMOUNT_LENGTH) {
			return;		//入力量が小さいときは回転しない
		}
		if (m_threeStep < 3) {
			m_rotation.SetRotation(
				CVector3::AxisY(),
				atan2f(moveSpeedXZ.x, moveSpeedXZ.z)
			);
		}
	}
	else {
		m_rotation.SetRotation(
			CVector3::AxisY(), 
			atan2f(-moveSpeedXZ.x, -moveSpeedXZ.z)
		);
	}
}

void Player::AnimationController()
{
	if (!m_game->GetGameOverFlag()
		&& !m_game->GetStar()) {
		if (m_charaCon.IsOnGround() && !m_isAttacked) {
			//ダッシュ中
			if (m_moveSpeed.LengthSq() >= INPUT_AMOUNT_DASH_LENGTH) {
				//走りアニメーション
				m_animation.Play(enAnimationClip_run, INTERPOLATE_TIME);
				m_animation.Update(DELTA_TIME);
			}
			//通常移動中
			else if (m_moveSpeed.LengthSq() >= INPUT_AMOUNT_WALK_LENGTH) {
				//歩きアニメーション
				m_animation.Play(enAnimationClip_walk, INTERPOLATE_TIME);
				m_animation.Update(DELTA_TIME);
			}
			//何も操作されてない
			else {
				//立ちアニメーション
				m_animation.Play(enAnimationClip_idle, INTERPOLATE_TIME);
				m_animation.Update(DELTA_TIME);
			}
		}
		//床から離れている
		if (m_charaCon.IsOnGround() == false) {
			//ジャンプアニメーション
			m_animation.Play(enAnimationClip_jump, INTERPOLATE_TIME);
			m_animation.Update(DELTA_TIME);
		}
		//攻撃されたら
		if (m_isAttacked == true) {
			//ダメージアニメーション
			m_animation.Play(enAnimationClip_damage, INTERPOLATE_TIME);
			m_animation.Update(DELTA_TIME);
		}
	}
	//ゲームオーバーなら
	if(m_game->GetGameOverFlag()) {
		//ダウンアニメーション
		m_animation.Play(enAnimationClip_down, INTERPOLATE_TIME);
		m_animation.Update(DELTA_TIME * ANIMATION_DOWN_SPEED);
	}

	//ゲームクリアなら
	if (m_game->GetGameClearFlag()) {
		//クリアアニメーション
		m_animation.Play(enAnimationClip_clear, INTERPOLATE_TIME);
		m_animation.Update(DELTA_TIME * ANIMATION_CLEAR_SPEED);
	}	
	else if (m_game->GetStar()) {
		//ダッシュ中
		if (m_moveSpeed.LengthSq() >= INPUT_AMOUNT_DASH_LENGTH) {
			//走りアニメーション
			m_animation.Play(enAnimationClip_run, INTERPOLATE_TIME);
			m_animation.Update(DELTA_TIME);
		}
		//通常移動中
		else if (m_moveSpeed.LengthSq() >= INPUT_AMOUNT_WALK_LENGTH) {
			//歩きアニメーション
			m_animation.Play(enAnimationClip_walk, INTERPOLATE_TIME);
			m_animation.Update(DELTA_TIME);
		}
		//何も操作されてない
		else {
			//立ちアニメーション
			m_animation.Play(enAnimationClip_idle, INTERPOLATE_TIME);
			m_animation.Update(DELTA_TIME);
		}
	}
}

void Player::InitAnimationClip()
{
	//アニメーションクリップのロード。
	m_animClips[enAnimationClip_idle].Load(L"Assets/animData/idle.tka");
	m_animClips[enAnimationClip_run].Load(L"Assets/animData/run.tka");
	m_animClips[enAnimationClip_jump].Load(L"Assets/animData/jump.tka");
	m_animClips[enAnimationClip_damage].Load(L"Assets/animData/damage.tka");
	m_animClips[enAnimationClip_walk].Load(L"Assets/animData/walk.tka");
	m_animClips[enAnimationClip_down].Load(L"Assets/animData/KneelDown.tka");
	m_animClips[enAnimationClip_clear].Load(L"Assets/animData/clear.tka");
	//ループフラグを設定する
	//走りアニメーションはループフラグを設定していないのでワンショット再生で停止。
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_run].SetLoopFlag(true);
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_jump].SetLoopFlag(false);
	m_animClips[enAnimationClip_damage].SetLoopFlag(false);
	m_animClips[enAnimationClip_down].SetLoopFlag(false);
	m_animClips[enAnimationClip_clear].SetLoopFlag(false);

}