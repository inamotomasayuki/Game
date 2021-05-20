#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "../gimmick/JumpFloor.h"
#include "GameData.h"
#include "../gimmick/Button.h"
#include "FireBall.h"
#include "../gimmick/Box.h"
#include "../item/Item.h"
#include "../gimmick/Warp.h"

namespace {
	const float DELTA_TIME = 1.0f / 60.0f;			//経過時間　単位：秒
	const float INTERPOLATE_TIME = 0.1f;			//補完時間　単位：秒

	const float MOVE_SPEED = 50.0f;					//移動速度
	float SPEED = 1.0f;								//速度
	const float WALK_SPEED = 1.0f;					//歩き速度
	const float DASH_SPEED = 2.0f;					//ダッシュ速度
	const float KNOCK_BACK_SPEED = 800.0f;			//ノックバック速度
	const float MOVE_SPEED_DECAY = 0.95f;			//移動速度減衰
	const float JUMP_SPEED_DECAY = 0.85f;			//ジャンプ速度減衰
	const float JUMP_FLOOR_SPEED_DECAY = 0.90f;		//ジャンプ床時の速度減衰
	const float ADD_SPEED_DECAY = 0.75f;			//加算速度減衰
	const float ACHICHI_RUN_SPEED = 2000.0f;		//あちち走り速度
	const float TURN_POW = 0.05f;					//曲がる強さ
	const float GRAVITY_ACCELERATION = 1.05f;		//重力加速度

	const float MOVE_SPEED_LENGTH = 40.0f;					//移動中
	const float DASH_SPEED_LENGTH = 2000.0f;				//ダッシュ中
	const float JUMP_FLOOR_SPEED_LENGTH = 8000.0f;			//ジャンプ床のジャンプ中
	const float ADD_SPEED_LENGTH = 0.01f;					//加速度加算中
	const float INPUT_AMOUNT_LENGTH = 0.8f;					//角度を求めるときの入力量
	const int WARP_TIMER = 100;									//ワープ時間

	const float STEP_JUMP_ONE = 4000.0f;						//ジャンプ1段目
	const float STEP_JUMP_TWO = 5000.0f;						//ジャンプ２段目
	const float STEP_JUMP_THREE = 8000.0f;						//ジャンプ３段目	
	const int TIMER = 12;										//３段ジャンプリセットタイマー

	const int HIPDROP_TIMER = 15;								//ヒップドロップ静止時間
	const float HIPDROP_GRAVITY = 3000.0f;						//ヒップドロップ中重力
	const float HIPDROP_GRAVITY_ACCELERATION = 1.03f;			//ヒップドロップ重力加速度
	const int HIPDROP_ROT_TIMER = 7;							//ヒップドロップ回転タイマー
	const float HIPDROP_ROT_SPEED = 60.0f;						//ヒップドロップ回転速度
	const float THREE_STEP_ROT_SPEED = 30.0f;					//三段目ジャンプ回転
	const int THREE_STEP_ROT_TIMER = 25;						//三段目ジャンプ回転タイマー

	//アイテム取得時の巨大化用
	const float BIG_SCALE = 1.5f;								//大きくなる
	const float BIG_SCALE_SPEED = 1.02f;						//大きくなる速度
	const float SMALL_SCALE_SPEED = 0.97f;						//小さくなる速度
	const float CHARACON_SCALE = 1.1f;							//キャラコン大きさ

	const float JUMP_FLOOR_SPEED = 10000.0f;					//ジャンプ床の速度

	const float SE_VOLUME = 1.0f;								//ボリューム
	const float SE_RATIO = 1.5f;								//周波数
	
	//アニメーション用
	const float INPUT_AMOUNT_DASH_LENGTH = 1000000.0f;			//走りアニメーションさせる
	const float INPUT_AMOUNT_WALK_LENGTH = 10.0f;				//歩きアニメーションさせる
	const float RUN_ANIMATION_SPEED = 3.0f;						//走りアニメーション速度
	const float ACHICHI_RUN_ANIMATION_SPEED = 10.0f;			//あちち走りアニメーション速度
	const float WALK_ANIMATION_SPEED = 2.0f;					//歩きアニメーション速度	
	const float ANIMATION_DOWN_SPEED = 3.0f;					//ダウンアニメーションスピード
	const float ANIMATION_CLEAR_SPEED = 2.0f;					//クリアアニメーションスピード

	const int FIREBALL_GENERATE_INTERVAL = 10;		//ファイアボール生成間隔
	const int FLASH_TIME = 4;						//点滅時間
	const int FLASH_INTERVAL = 2;					//点滅間隔

	const int ATTACK_WAIT_TIME = 40;				//攻撃されたときの待ち時間
	const int ACHICHI_TIME = 55;					//あちち時間
	//影用の円
	const float CIRCLE_POS_Y = 18.0f;				//円の位置
	const float CIRCLE_SCALE = 0.8f;				//円のスケール
}

Player::Player()
{
	m_skinModel.SetFrustumCullingFlag(false);
	//cmoファイルの読み込み。
	m_skinModel.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);
	m_skinModelCircle.Init(L"Assets/modelData/Circle.cmo");
	m_skinModel.LoadNormalMap(L"Assets/modelData/utc_nomal.dds");
	m_skinModel.LoadSpecularMap(L"Assets/modelData/utc_spec.dds");
	m_skinModel.LoadAoMap(L"Assets/modelData/utc_ao.dds");
	//アニメーションクリップの
	//ロードとループフラグ設定
	InitAnimationClip();

	m_animation.Init(m_skinModel, m_animClips, enAnimationClip_Num);

	//サウンドの初期化
	InitSound();
}


Player::~Player()
{
	for (int i = 0; i < enSE_Num; i++) {
		g_goMgr.DeleteGameObject(m_se[i]);
	}
}

void Player::Update()
{
	const auto& warp = g_goMgr.FindGameObject<Warp>("warp");
	m_game = g_goMgr.FindGameObject<Game>("game");
	//NullCheck
	if (m_game == nullptr) {
		return;
	}
	if (warp == nullptr) {
		return;
	}
	//StateSet
	if (m_game->GetStar()) {
		m_currentState = enState_GetStar;
	}
	if (m_game->GetGameClearFlag()) {
		m_currentState = enState_GameClear;
	}
	if (m_game->GetGameOverFlag()) {
		m_currentState = enState_GameOver;
	}
	if (warp->IsWarp()) {
		m_currentState = enState_Warp;
	}
	if (m_isAttacked) {
		m_currentState = enState_Damage;
	}
	if (m_isHipDrop) {
		m_currentState = enState_HipDrop;
	}
	if (m_isAchichi) {
		m_currentState = enState_FireDamage;
	}
	if (!warp->IsWarp()
		&& !m_isHipDrop) {
		m_currentState = enState_Playing;
	}

	//パッド操作
	PadMove();
	//プレイヤーと他のゴーストとの接触処理
	GhostContact();

	switch (m_currentState)
	{
	case enState_Playing:
		Playing();
		FireBallGenerate();
		break;
	case enState_Damage:
		Damage();
		break;
	case enState_FireDamage:
		FireDamage();
		break;
	case enState_HipDrop:
		HipDrop();
		break;
	case enState_Warp:
		m_playerWarpState.Update(this);
		m_se[enSE_walk]->Stop();
		m_se[enSE_dash]->Stop();
		break;
	case enState_GameClear:
		GameClear();
		break;
	case enState_GameOver:
		GameOver();
		break;
	default:
		break;
	}
	if (m_currentState != enState_FireDamage) {
		m_isVoicePlay = false;
	}
	//クリアしたらカメラに向ける
	if (!m_game->GetStar()) {
		m_posXZ = m_position - g_camera3D.GetPosition();
		m_posXZ.y = 0.0f;
		m_posXZ.Normalize();
	}
	if (m_game->GetIsStop()) {
		m_moveSpeed = CVector3::Zero();
		m_gravity = 0.0f;
	}
	//効果音再生処理
	SoundPlay();

	//円の位置
	m_circlePos = m_position;
	m_circlePos.y += CIRCLE_POS_Y;

	//ワールド行列の更新。
	//プレイヤー
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//円
	m_skinModelCircle.UpdateWorldMatrix(m_circlePos, m_rotation, m_scale * CIRCLE_SCALE);

	}

void Player::Draw()
{
	//攻撃を受けたときは点滅するようにする
	if (m_game != nullptr) {
		if (m_game->GetHP() != 0 && m_isAttacked
			|| m_game->GetHP() != 0 && m_isAchichi && !m_charaCon.IsOnGround()) {
			m_flashingTimer++;
			if (m_flashingTimer % FLASH_TIME == FLASH_INTERVAL) {
				m_isFlashing = true;
			}
			if (m_flashingTimer % FLASH_TIME == 0) {
				m_isFlashing = false;
			}
		}
		else {
			m_flashingTimer = 0;
			m_isFlashing = false;
		}
	}
	if (!m_isFlashing) {
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
	//レシーバーオフ
	m_skinModel.ShadowReciverOff();
}

void Player::Playing()
{
	//ステージ1での移動
	if (g_gameData.GetStageNo() == g_gameData.enStage_One) {
		if (m_buttonState == enButtonState_0) {
			m_moveSpeed.x -= g_pad[0].GetLStickXF() * MOVE_SPEED * SPEED;
			m_moveSpeed.z = 0.0f;
		}
		else if (m_buttonState == enButtonState_1) {
			m_moveSpeed.z += g_pad[0].GetLStickXF() * MOVE_SPEED * SPEED;
			m_moveSpeed.x = 0.0f;
		}
	}
	//カメラを考慮したスティックでのプレイヤー移動
	//前方向の移動
	if (g_gameData.GetStageNo() != g_gameData.enStage_One) {
		auto v = g_camera3D.GetTarget() - g_camera3D.GetPosition();
		v.Normalize();
		v.y = 0.0f;
		m_moveSpeed += v * g_pad[0].GetLStickYF() * MOVE_SPEED * SPEED;
		//横方向の移動
		CVector3 cameraSide;
		cameraSide.Cross(v, CVector3::AxisY());
		cameraSide.Normalize();
		m_moveSpeed -= cameraSide * g_pad[0].GetLStickXF() * MOVE_SPEED * SPEED;
	}
	//ジャンプ三段目回転させる。
	if (m_isThreeStepRot) {
		m_threeStepRotTimer++;
		if (m_threeStepRotTimer < THREE_STEP_ROT_TIMER) {
			CQuaternion rot;
			if (m_isThreeStepRot) {
				rot.SetRotationDeg(CVector3::AxisX(), THREE_STEP_ROT_SPEED);
			}
			m_rotation.Multiply(rot);
		}
		else {
			m_threeStepRotTimer = 0;
			m_isThreeStepRot = false;
		}
	}
	//プレイヤーの回転
	//ｘとｚのベクトルから角度を求めて回転させる。
	auto moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	if (moveSpeedXZ.LengthSq() < INPUT_AMOUNT_LENGTH) {
		return;		//入力量が小さいときは回転しない
	}
	if (m_threeStep < 3) {
		m_rotation.SetRotation(
			CVector3::AxisY(),
			atan2f(moveSpeedXZ.x, moveSpeedXZ.z)
		);
	}
	//ヒップドロップへ
	if (!m_charaCon.IsOnGround()) {
		if (IsInputHipDrop()) {
			m_isHipDrop = true;
		}
	}
	//Bダッシュ
	if (g_pad[0].IsPress(enButtonB)) {
		SPEED = DASH_SPEED;
		if (m_moveSpeed.Length() < DASH_SPEED_LENGTH) {
			m_contactJumpFloor = false;
		}
	}
	else {
		SPEED = WALK_SPEED;
	}

	//３段ジャンプ
	if (m_charaCon.IsOnGround()) {
		m_jumpFlag = false;
		if (g_pad[0].IsTrigger(enButtonA)) {
			//ジャンプ音
			m_se[enSE_jump]->Play(false);
			//移動しながらジャンプしてたら段を進める
			if (m_moveSpeed.x || m_moveSpeed.z != 0) {
				m_threeStep++;
			}
			else {
				m_threeStep = 0;
			}
			if (m_threeStep <= 1) {
				m_jumpSpeed = STEP_JUMP_ONE;
			}
			if (m_threeStep == 2) {
				m_jumpSpeed = STEP_JUMP_TWO;
			}
			if (m_threeStep == 3) {
				m_jumpSpeed = STEP_JUMP_THREE;
				m_isThreeStepRot = true;
			}
			m_jumpFlag = true;
			m_isHipDropBox = false;
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
	if (m_charaCon.IsOnGround()) {
		//ダッシュ中
		if (m_moveSpeed.LengthSq() >= INPUT_AMOUNT_DASH_LENGTH) {
			//走りアニメーション
			m_animation.Play(enAnimationClip_run, INTERPOLATE_TIME);
			m_animation.Update(DELTA_TIME * RUN_ANIMATION_SPEED);
		}
		//通常移動中
		else if (m_moveSpeed.LengthSq() >= INPUT_AMOUNT_WALK_LENGTH) {
			//歩きアニメーション
			m_animation.Play(enAnimationClip_walk, INTERPOLATE_TIME);
			m_animation.Update(DELTA_TIME * WALK_ANIMATION_SPEED);
		}
		//何も操作されてない
		else {
			//立ちアニメーション
			m_animation.Play(enAnimationClip_idle, INTERPOLATE_TIME);
			m_animation.Update(DELTA_TIME);
		}
	}
	else {
		//ジャンプアニメーション
		m_animation.Play(enAnimationClip_jump, INTERPOLATE_TIME);
		m_animation.Update(DELTA_TIME);
	}
}

void Player::FireBallGenerate()
{
	//ファイアボール
	if (m_isItem) {
		if (!m_isFireBall) {
			if (g_pad[0].IsTrigger(enButtonRB1)) {
				g_goMgr.NewGameObject<FireBall>("fireBall");
				m_isFireBall = true;
			}
		}
	}
	if (m_isFireBall) {
		m_fireBallTimer++;
	}
	if (m_fireBallTimer == FIREBALL_GENERATE_INTERVAL) {
		m_fireBallTimer = 0;
		m_isFireBall = false;
	}
}

void Player::GhostContact()
{
	bool isContact = false;
	bool isJump = m_jumpFlag;
	bool isButton = false;
	if (m_buttonState > enButtonState_1) {
		m_buttonState = enButtonState_0;
	}
	if (g_gameData.GetStageNo() == g_gameData.enStage_One) {
		g_goMgr.FindGameObjects<Button>("button", [&](Button* button)->bool {
			if (!isButton) {
				button->SetState(button->enState_stop);
			}
			return true;
		});
	}
	auto button1 = g_goMgr.FindGameObject<Button>("button1");
	g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
		g_goMgr.FindGameObjects<Button>("button", [&](Button* button)->bool {
			if (g_gameData.GetStageNo() == g_gameData.enStage_Zero) {
				//ボタンに当たった
				if (button->GetGhost()->IsSelf(contactObject) == true) {
					isButton = true;
					button->IsPush();
				}
				if (isButton) {
					button->SetState(button->enState_0);
				}
			}
			else {
				if (button->GetGhost()->IsSelf(contactObject) == true) {
					isButton = true;
					button->IsPush();
					if (!m_isButton) {
						m_buttonState++;
						m_isButton = true;
					}
				}
				if (isButton) {
					button->SetState(button->enState_2);
				}
			}
			return true;
		});
		//ボタン踏んだ
		if (button1->GetGhost()->IsSelf(contactObject) == true) {
			button1->SetState(button1->enState_1);
			button1->IsPush();
		}
		//星とぶつかった
		m_star = g_goMgr.FindGameObject<Star>("star");
		if (m_star->GetGhost()->IsSelf(contactObject) == true) {
			m_game->SetGetStarFlag();
		}
		//動く床とぶつかった
		m_moveFloor = g_goMgr.FindGameObject<MoveFloor>("moveFloor");
		if (m_moveFloor->GetGhost()->IsSelf(contactObject) == true) {
			m_floorSpeed.y = 0.0f;
			m_addSpeed = m_floorSpeed;
			m_contactFloor = true;
			isContact = true;
		}
		//ジャンプ床とぶつかった
		m_jumpFloor = g_goMgr.FindGameObject<JumpFloor>("jumpFloor");
		if (m_jumpFloor->GetGhost()->IsSelf(contactObject) == true) {
			m_jumpSpeed = JUMP_FLOOR_SPEED;
			m_se[enSE_jumpFloor]->Play(false);
			m_contactJumpFloor = true;
		}
		if (g_gameData.GetStageNo() == 0) {
			g_goMgr.FindGameObjects<BackGround>("UCW_Ceiling", [&](BackGround* bg)->bool {
				if (bg->GetGhost()->IsSelf(contactObject) == true) {
					m_threeStep = 0;
					m_jumpSpeed = 0.0f;
					m_moveSpeed.y = 0.0f;
					m_moveSpeed.y -= m_gravity;
				}
				return true;
			});
		}
		g_goMgr.FindGameObjects<Box>("box", [&](Box* box)->bool {
			//箱に下からぶつかった
			if (box->GetGhost()->IsSelf(contactObject) == true) {
				m_threeStep = 0;
				box->SetIsContact(true);
				if (!m_hitBox) {
					m_jumpSpeed = 0.0f;
					m_moveSpeed.y = 0.0f;
					m_hitBox = true;
				}
				m_moveSpeed.y -= m_gravity;
			}
			//ヒップドロップした。
			if (box->GetMeshGhost()->IsSelf(contactObject) == true) {
				if (m_isHipDropBox) {
					box->SetIsHipDrop(true);
				}
			}
			return true;
		});
		g_goMgr.FindGameObjects<Item>("item", [&](Item* item)->bool {
			//アイテムにぶつかった
			if (item->GetGhost()->IsSelf(contactObject) == true) {
				item->SetIsGet();
				m_isItem = true;
			}
			return true;
		});
	});
	//大きくなる
	if (m_isItem) {
		auto scale = CVector3::One() * BIG_SCALE;
		if (m_scale.Length() < scale.Length()) {

			m_scale *= BIG_SCALE_SPEED;
		}
		else {
			m_scale = CVector3::One() * BIG_SCALE;
			auto radius = PLAYER_COLLIDER_RADIUS * CHARACON_SCALE;
			auto height = PLAYER_COLLIDER_HIGHT * CHARACON_SCALE;
			m_charaCon.SetColliderRadiusAndHeight(radius, height);

		}
	}
	//小さくなる
	else {
		m_isBigSE = false;
		if (m_scale.Length() > CVector3::One().Length()) {
			m_scale *= SMALL_SCALE_SPEED;
		}
		else {
			m_scale = CVector3::One();
			m_charaCon.SetColliderRadiusAndHeight(PLAYER_COLLIDER_RADIUS, PLAYER_COLLIDER_HIGHT);
		}
	}
	if (m_charaCon.IsOnGround()) {
		m_hitBox = false;
	}
	//ジャンプ床ジャンプ
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
	//動く床の上でのジャンプに少し慣性
	if (!isJump && m_jumpFlag) {
		m_moveSpeed += m_addSpeed;
	}
	if (m_contactFloor) {
		auto movespeed = m_moveSpeed + m_addSpeed;
		m_position = m_charaCon.Execute(DELTA_TIME, movespeed);
	}
	else {
		if (!m_isAttacked) {
			m_addSpeed = CVector3::Zero();
		}
		m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);
	}
}

void Player::HipDrop()
{
	if (m_charaCon.IsOnGround()) {
		//フラグを戻す
		m_isHipDrop = false;
		m_isSetGravity = false;
		m_hipDropTimer = 0;
	}
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_hipDropTimer++;
	//一瞬空中で止まる
	if (m_hipDropTimer < HIPDROP_TIMER) {
		m_moveSpeed = CVector3::Zero();
		m_gravity = 0.0f;
	}
	//落下
	else {
		if (!m_isSetGravity) {
			m_gravity = HIPDROP_GRAVITY;
			m_isSetGravity = true;
			m_isHipDropBox = true;
		}
	}
	if (m_isSetGravity) {
		m_gravity *= HIPDROP_GRAVITY_ACCELERATION;
	}
	//ヒップドロップで１回転させる。
	if (m_hipDropTimer < HIPDROP_ROT_TIMER) {
		CQuaternion rot;
		rot.SetRotationDeg(CVector3::AxisX(), HIPDROP_ROT_SPEED);
		m_rotation.Multiply(rot);
	}
}

void Player::Damage()
{
	m_isAchichi = false;
	m_isItem = false;
	//ノックバック
	if (g_gameData.GetStageNo() == g_gameData.enStage_One) {
		m_addSpeed.z = 0.0f;
	}
	m_moveSpeed = m_addSpeed;
	m_moveSpeed.y -= KNOCK_BACK_SPEED;
	m_addSpeed *= ADD_SPEED_DECAY;
	if (m_addSpeed.Length() < ADD_SPEED_LENGTH) {
		m_addSpeed = CVector3::Zero();
	}
	//攻撃受けたら敵の方向く
	auto moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	m_rotation.SetRotation(
		CVector3::AxisY(),
		atan2f(-moveSpeedXZ.x, -moveSpeedXZ.z)
	);
	//硬直タイム
	m_waitTimer++;
	if (m_waitTimer == ATTACK_WAIT_TIME) {
		m_waitTimer = 0;
		m_currentState = enState_Playing;
		m_isAttacked = false;
	}
	//ダメージアニメーション
	m_animation.Play(enAnimationClip_damage, INTERPOLATE_TIME);
	m_animation.Update(DELTA_TIME);
}

void Player::FireDamage()
{
	m_isItem = false;
	//前方向の移動
	auto v = g_camera3D.GetTarget() - g_camera3D.GetPosition();
	v.Normalize();
	v.y = 0.0f;
	m_achichiVec += v * g_pad[0].GetLStickYF() * TURN_POW;
	//横方向の移動
	CVector3 cameraSide;
	cameraSide.Cross(v, CVector3::AxisY());
	cameraSide.Normalize();
	m_achichiVec -= cameraSide * g_pad[0].GetLStickXF() * TURN_POW;
	//移動ベクトルを代入
	m_achichiVec.Normalize();
	m_achichiMove = m_achichiVec * ACHICHI_RUN_SPEED;
	m_moveSpeed = m_achichiMove;
	//あちち走りアニメーション
	m_animation.Play(enAnimationClip_run, INTERPOLATE_TIME);
	m_animation.Update(DELTA_TIME * ACHICHI_RUN_ANIMATION_SPEED);
	//SE再生
	if (!m_isVoicePlay) {
		m_se[enSE_awawaVoice]->Play(false);
		m_isVoicePlay = true;
	}
	//あちち終了
	m_achichiTimer++;
	if (m_achichiTimer == ACHICHI_TIME) {
		m_achichiTimer = 0;
		m_isAchichi = false;
	}
}

void Player::GameClear()
{
	m_rotation.SetRotation(
		CVector3::AxisY(),
		atan2f(m_posXZ.x, m_posXZ.z)
	);
	//クリアアニメーション
	m_animation.Play(enAnimationClip_clear, INTERPOLATE_TIME);
	m_animation.Update(DELTA_TIME * ANIMATION_CLEAR_SPEED);
}

void Player::GameOver()
{
	//ダウンアニメーション
	m_animation.Play(enAnimationClip_down, INTERPOLATE_TIME);
	m_animation.Update(DELTA_TIME * ANIMATION_DOWN_SPEED);
}

void Player::PadMove()
{
	if (m_game->GetStar()) {
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}
	//ジャンプ
	if (m_jumpFlag) {
		m_moveSpeed.y = m_jumpSpeed;
		m_jumpSpeed *= JUMP_SPEED_DECAY;
		if (m_threeStep == 3) {
			m_threeStep = 0;
		}
	}
	//重力
	if (!m_charaCon.IsOnGround()) {
		if (!m_isInitGravity) {
			m_gravity = GRAVITY;
			//m_isInitGravity = true;
		}
		m_gravity *= GRAVITY_ACCELERATION;
		m_moveSpeed.y -= m_gravity;
	}
	else {
		m_isInitGravity = false;
	}
	//移動速度減衰
	m_moveSpeed.x *= MOVE_SPEED_DECAY;
	m_moveSpeed.z *= MOVE_SPEED_DECAY;
	if (m_moveSpeed.Length() < MOVE_SPEED_LENGTH) {
		m_moveSpeed = CVector3::Zero();
	}

	if (m_charaCon.IsOnGround() && !m_jumpFlag) {
		m_moveSpeed.y = 0.0f;
	}
}

void Player::InitAnimationClip()
{
	//アニメーションクリップのロード。
	m_animClips[enAnimationClip_idle].Load(L"Assets/animData/idle.tka");		//立ち
	m_animClips[enAnimationClip_run].Load(L"Assets/animData/run.tka");			//走り
	m_animClips[enAnimationClip_jump].Load(L"Assets/animData/jump.tka");		//ジャンプ
	m_animClips[enAnimationClip_damage].Load(L"Assets/animData/damage.tka");	//ダメージ
	m_animClips[enAnimationClip_walk].Load(L"Assets/animData/walk.tka");		//歩き
	m_animClips[enAnimationClip_down].Load(L"Assets/animData/KneelDown.tka");	//ダウン
	m_animClips[enAnimationClip_clear].Load(L"Assets/animData/clear.tka");		//クリア
	//ループフラグを設定する
	//走りアニメーションはループフラグを設定していないのでワンショット再生で停止。
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);		//立ち
	m_animClips[enAnimationClip_run].SetLoopFlag(true);			//走り
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);		//歩き
	m_animClips[enAnimationClip_jump].SetLoopFlag(false);		//ジャンプ
	m_animClips[enAnimationClip_damage].SetLoopFlag(false);		//ダメージ
	m_animClips[enAnimationClip_down].SetLoopFlag(false);		//ダウン
	m_animClips[enAnimationClip_clear].SetLoopFlag(false);		//クリア
}

void Player::InitSound()
{
	for (int i = 0; i < enSE_Num; i++) {
		m_se[i] = g_goMgr.NewGameObject<CSoundSource>(0);
	}
	//サウンドの初期化
	m_se[enSE_jump]->Init(L"Assets/sound/jump.wav");				//ジャンプ
	m_se[enSE_walk]->Init(L"Assets/sound/walk.wav");				//歩き
	m_se[enSE_dash]->Init(L"Assets/sound/dash.wav");				//走り
	m_se[enSE_jumpFloor]->Init(L"Assets/sound/jumpFloor.wav");		//ジャンプ床
	m_se[enSE_damage]->Init(L"Assets/sound/damage.wav");			//ダメージ
	m_se[enSE_kyodaika]->Init(L"Assets/sound/kyodaika.wav");		//巨大化
	m_se[enSE_awawaVoice]->Init(L"Assets/sound/awawaVoice.wav");	//あわわ
}

void Player::SoundPlay()
{
	if (!m_jumpFlag) {
		//ダッシュ中
		if (m_moveSpeed.LengthSq() >= INPUT_AMOUNT_DASH_LENGTH) {
			//ダッシュ音
			m_se[enSE_dash]->SetVolume(1.0f);
			m_se[enSE_dash]->Play(false);
			m_se[enSE_walk]->Stop();
		}
		//通常移動中
		else if (m_moveSpeed.LengthSq() >= INPUT_AMOUNT_WALK_LENGTH) {
			//歩き音
			m_se[enSE_walk]->SetVolume(SE_VOLUME);
			m_se[enSE_walk]->SetFrequencyRatio(SE_RATIO);
			m_se[enSE_walk]->Play(false);
			m_se[enSE_dash]->Stop();
		}
		//何も操作されてない
		else {
			m_se[enSE_walk]->Stop();
		}
	}
	if (!m_charaCon.IsOnGround()) {
		m_se[enSE_walk]->Pause();
		m_se[enSE_dash]->Pause();
	}
	//ダメージ音
	if (m_isDamageSE) {
		m_se[enSE_damage]->Play(false);
		m_isDamageSE = false;
	}
	if (m_game->GetGameClearFlag()
		|| m_game->GetGameOverFlag()) {
		m_se[enSE_walk]->Stop();
		m_se[enSE_dash]->Stop();
	}
	if (m_isItem) {
		if (!m_isBigSE) {
			m_se[enSE_kyodaika]->Play(false);
			m_isBigSE = true;
		}
	}
	//メニュー表示時効果音全消し
	if (IsInputMenu()) {
		for (int seCount = 0; seCount < enSE_Num; seCount++) {
			m_se[seCount]->Stop();
		}
	}
}