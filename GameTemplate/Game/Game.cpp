#include "stdafx.h"
#include "Game.h"
#include "GameData.h"
#include "title/Title.h"
#include "select/StageSelect.h"
#include "gimmick/Box.h"
#include "gimmick/Button.h"
#include "enemy/EnemyFireBall.h"
namespace {
	const float PLAYER_FALL_GAMEOVER_POS_Y = -1000.0f;		//プレイヤーのY位置
	const int CLEAR_TIME = 25;								//クリアまでの時間
	const float DELETE_THIS_ALPHA = 1.0f;			//フェードがこのアルファ値で削除する
}
Game::Game()
{
	//初期化
	Init();
}


Game::~Game()
{
	Delete();
}

void Game::Update()
{
}
void Game::NewUpdate()
{
	//スタートボタンでメニューを開く
	if (g_pad->IsTrigger(enButtonStart)) {
		m_uiManager = g_goMgr.NewGameObject<UIManager>(0);
		m_se[enSE_menu]->Play(false);
		g_gameData.SetPause();
	}
	//サウンド再生
	SoundPlay();
	//シャドウキャスターを登録。
	g_shadowMap->RegistShadowCaster(m_star->GetSkinModel());
	g_shadowMap->RegistShadowCaster(m_player->GetSkinModel());
	g_goMgr.FindGameObjects<Enemy01>("enemy01", [](Enemy01* enemy01)->bool {
		g_shadowMap->RegistShadowCaster(enemy01->GetSkinModel());
		return true;
		});
	g_goMgr.FindGameObjects<Enemy02>("enemy02", [](Enemy02* enemy02)->bool {
		g_shadowMap->RegistShadowCaster(enemy02->GetSkinModel());
		return true;
		});
	g_goMgr.FindGameObjects<Enemy03>("enemy03", [](Enemy03* enemy03)->bool {
		g_shadowMap->RegistShadowCaster(enemy03->GetSkinModel());
		return true;
		});
	//g_goMgr.FindGameObjects<Enemy04>("enemy04", [](Enemy04* enemy04)->bool {
	//	g_shadowMap->RegistShadowCaster(enemy04->GetSkinModel());
	//	return true;
	//	});
	g_goMgr.FindGameObjects<Coin>("coin", [this](Coin* coin)->bool {
		g_shadowMap->RegistShadowCaster(coin->GetSkinModel());
		return true;
		});
	g_goMgr.FindGameObjects<Box>("box", [](Box* box)->bool {
		g_shadowMap->RegistShadowCaster(box->GetSkinModel());
		return true;
		});
	//ゲームオーバー
	if (m_gameOver == nullptr) {
		if (m_hp == 0
			|| m_player->GetPositon().y < PLAYER_FALL_GAMEOVER_POS_Y) {
			m_hp = 0;
			m_gameOver = g_goMgr.NewGameObject<GameOver>(0);
			m_gameOverFlag = true;
		}

	}
	//遷移
	else {
		m_stopTime++;
		if (m_stopTime >= 100) {
			m_isStop = true;
		}
		if (!m_isFade) {
			if (g_pad[0].IsTrigger(enButtonA)
				&& m_gameOver->GetButtonFlag()) {
				if (m_fade == nullptr) {
					m_fade = g_goMgr.NewGameObject<Fade>("fade");
					m_isFade = true;
				}
			}
		}
	}
	//ゲームクリア
	if (m_star != nullptr) {
		if (m_star->GetStarFlag()) {
			m_clearTimer++;
			m_isGetStar = true;
			if (m_gameClear == nullptr) {
				m_gameClear = g_goMgr.NewGameObject<GameClear>("gameClear");
				m_gameClearFlag = true;
			}
			//遷移
			if (m_clearTimer >= CLEAR_TIME) {
				if (!m_isFade) {
					if (g_pad[0].IsTrigger(enButtonA)) {
						if (m_fade == nullptr) {
							m_fade = g_goMgr.NewGameObject<Fade>("fade");
							m_isFade = true;
						}
					}
				}
			}
		}
	}
	//セレクトボタンでフェードに入ってステージ選択画面に戻る
	if (m_isFade) {
		if (m_fade->GetAlpha() >= DELETE_THIS_ALPHA) {
			g_goMgr.DeleteGameObject(m_fontUI);
			g_goMgr.NewGameObject<StageSelect>(0);
			g_goMgr.DeleteGameObject(this);
		}
	}
	if (!m_fade) {
		if (g_pad[0].IsTrigger(enButtonSelect)) {
			if (m_fade == nullptr) {
				m_fade = g_goMgr.NewGameObject<Fade>("fade");
				m_isFade = true;
			}
		}
	}
}
void Game::Draw()
{
}
void Game::InitSound()
{
	//BGM
	m_bgm = g_goMgr.NewGameObject<CSoundSource>(0);
	m_bgm->Init(L"Assets/sound/gameplay.wav");
	m_bgm->Play(true);
	for (int i = 0; i < enSE_Num; i++) {
		m_se[i] = g_goMgr.NewGameObject<CSoundSource>(0);
	}
	//効果音
	m_se[enSE_gameClear]->Init(L"Assets/sound/gameClear.wav");
	m_se[enSE_gameOver]->Init(L"Assets/sound/gameOver.wav");
	m_se[enSE_menu]->Init(L"Assets/sound/menu.wav");
}
void Game::SoundPlay()
{
	//ゲームクリア音
	if (m_gameClearFlag) {
		if (!m_isGameClearSE) {
			m_se[enSE_gameClear]->Play(false);
			m_isGameClearSE = true;
		}
	}
	//ゲームオーバー音
	if (m_gameOverFlag) {
		if (!m_isGameOverSE) {
			m_se[enSE_gameOver]->Play(false);
			m_isGameOverSE = true;
		}
	}
}

void Game::Stage01Init()
{
	CVector3 playerPos;
	CQuaternion playerRot;
	CVector3 playerScale;
	if (g_gameData.GetStageNo() == 0) {
		m_warp = g_goMgr.NewGameObject<Warp>("warp");
		m_level.Init(L"Assets/level/ucw_stage00.tkl", [&](LevelObjectData& objData) {
			if (objData.EqualObjectName(L"unityChan")) {
				playerPos = objData.position;
				playerRot = objData.rotation;
				playerScale = objData.scale;
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Floor0")) {
				m_stage01[BackGround::enStage01Obj_floor0] = g_goMgr.NewGameObject<BackGround>("UCW_Floor0");
				m_stage01[BackGround::enStage01Obj_floor0]->SetStage01ObjState(BackGround::enStage01Obj_floor0);
				m_stage01[BackGround::enStage01Obj_floor0]->SetPosition(objData.position);
				m_stage01[BackGround::enStage01Obj_floor0]->SetRotation(objData.rotation);
				m_stage01[BackGround::enStage01Obj_floor0]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Floor1")) {
				m_stage01[BackGround::enStage01Obj_floor1] = g_goMgr.NewGameObject<BackGround>("UCW_Floor1");
				m_stage01[BackGround::enStage01Obj_floor1]->SetStage01ObjState(BackGround::enStage01Obj_floor1);
				m_stage01[BackGround::enStage01Obj_floor1]->SetPosition(objData.position);
				m_stage01[BackGround::enStage01Obj_floor1]->SetRotation(objData.rotation);
				m_stage01[BackGround::enStage01Obj_floor1]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Floor2")) {
				m_stage01[BackGround::enStage01Obj_floor2] = g_goMgr.NewGameObject<BackGround>("UCW_Floor2");
				m_stage01[BackGround::enStage01Obj_floor2]->SetStage01ObjState(BackGround::enStage01Obj_floor2);
				m_stage01[BackGround::enStage01Obj_floor2]->SetPosition(objData.position);
				m_stage01[BackGround::enStage01Obj_floor2]->SetRotation(objData.rotation);
				m_stage01[BackGround::enStage01Obj_floor2]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Floor3")) {
				m_stage01[BackGround::enStage01Obj_floor3] = g_goMgr.NewGameObject<BackGround>("UCW_Floor3");
				m_stage01[BackGround::enStage01Obj_floor3]->SetStage01ObjState(BackGround::enStage01Obj_floor3);
				m_stage01[BackGround::enStage01Obj_floor3]->SetPosition(objData.position);
				m_stage01[BackGround::enStage01Obj_floor3]->SetRotation(objData.rotation);
				m_stage01[BackGround::enStage01Obj_floor3]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Floor4")) {
				m_stage01[BackGround::enStage01Obj_floor4] = g_goMgr.NewGameObject<BackGround>("UCW_Floor4");
				m_stage01[BackGround::enStage01Obj_floor4]->SetStage01ObjState(BackGround::enStage01Obj_floor4);
				m_stage01[BackGround::enStage01Obj_floor4]->SetPosition(objData.position);
				m_stage01[BackGround::enStage01Obj_floor4]->SetRotation(objData.rotation);
				m_stage01[BackGround::enStage01Obj_floor4]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Ceiling")) {
				m_stage01[BackGround::enStage01Obj_ceiling] = g_goMgr.NewGameObject<BackGround>("UCW_Ceiling");
				m_stage01[BackGround::enStage01Obj_ceiling]->SetStage01ObjState(BackGround::enStage01Obj_ceiling);
				m_stage01[BackGround::enStage01Obj_ceiling]->SetPosition(objData.position);
				m_stage01[BackGround::enStage01Obj_ceiling]->SetRotation(objData.rotation);
				m_stage01[BackGround::enStage01Obj_ceiling]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Bridge2")) {
				m_stage01[BackGround::enStage01Obj_bridge] = g_goMgr.NewGameObject<BackGround>("UCW_Bridge2");
				m_stage01[BackGround::enStage01Obj_bridge]->SetStage01ObjState(BackGround::enStage01Obj_bridge);
				m_stage01[BackGround::enStage01Obj_bridge]->SetPosition(objData.position);
				m_stage01[BackGround::enStage01Obj_bridge]->SetRotation(objData.rotation);
				m_stage01[BackGround::enStage01Obj_bridge]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Step")) {
				m_stage01[BackGround::enStage01Obj_step] = g_goMgr.NewGameObject<BackGround>("UCW_Step");
				m_stage01[BackGround::enStage01Obj_step]->SetStage01ObjState(BackGround::enStage01Obj_step);
				m_stage01[BackGround::enStage01Obj_step]->SetPosition(objData.position);
				m_stage01[BackGround::enStage01Obj_step]->SetRotation(objData.rotation);
				m_stage01[BackGround::enStage01Obj_step]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Fence")) {
				m_stage01[BackGround::enStage01Obj_fence] = g_goMgr.NewGameObject<BackGround>("UCW_Fence");
				m_stage01[BackGround::enStage01Obj_fence]->SetStage01ObjState(BackGround::enStage01Obj_fence);
				m_stage01[BackGround::enStage01Obj_fence]->SetPosition(objData.position);
				m_stage01[BackGround::enStage01Obj_fence]->SetRotation(objData.rotation);
				m_stage01[BackGround::enStage01Obj_fence]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_StoneFence")) {
				m_stage01[BackGround::enStage01Obj_stoneFence] = g_goMgr.NewGameObject<BackGround>("UCW_StoneFence");
				m_stage01[BackGround::enStage01Obj_stoneFence]->SetStage01ObjState(BackGround::enStage01Obj_stoneFence);
				m_stage01[BackGround::enStage01Obj_stoneFence]->SetPosition(objData.position);
				m_stage01[BackGround::enStage01Obj_stoneFence]->SetRotation(objData.rotation);
				m_stage01[BackGround::enStage01Obj_stoneFence]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Square")) {
				m_stage01[BackGround::enStage01Obj_square] = g_goMgr.NewGameObject<BackGround>("UCW_Square");
				m_stage01[BackGround::enStage01Obj_square]->SetStage01ObjState(BackGround::enStage01Obj_square);
				m_stage01[BackGround::enStage01Obj_square]->SetPosition(objData.position);
				m_stage01[BackGround::enStage01Obj_square]->SetRotation(objData.rotation);
				m_stage01[BackGround::enStage01Obj_square]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_PhysicsFence")) {
				m_stage01[BackGround::enStage01Obj_physicsFence] = g_goMgr.NewGameObject<BackGround>("UCW_PhysicsFence");
				m_stage01[BackGround::enStage01Obj_physicsFence]->SetStage01ObjState(BackGround::enStage01Obj_physicsFence);
				m_stage01[BackGround::enStage01Obj_physicsFence]->SetPosition(objData.position);
				m_stage01[BackGround::enStage01Obj_physicsFence]->SetRotation(objData.rotation);
				m_stage01[BackGround::enStage01Obj_physicsFence]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"bridge")) {
				m_bridge = g_goMgr.NewGameObject<Bridge>("bridge");
				m_bridge->SetPosition(objData.position);
				m_bridge->SetRotation(objData.rotation);
				m_bridge->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Wall0")) {
				m_wall = g_goMgr.NewGameObject<Wall>("wall");
				m_wall->SetPosition(objData.position);
				m_wall->SetRotation(objData.rotation);
				m_wall->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"moveFloor")) {
				m_moveFloor = g_goMgr.NewGameObject<MoveFloor>("moveFloor");
				m_moveFloor->SetPosition(objData.position);
				m_moveFloor->SetRotation(objData.rotation);
				m_moveFloor->SetScale(objData.scale);
				m_moveFloor->InitCharaCon(objData.position);
				return true;
			}
			if (objData.EqualObjectName(L"jumpFloor")) {
				m_jumpFloor = g_goMgr.NewGameObject<JumpFloor>("jumpFloor");
				m_jumpFloor->SetPosition(objData.position);
				m_jumpFloor->SetRotation(objData.rotation);
				m_jumpFloor->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"warp01")) {
				m_warp->SetPosition(objData.position, Warp::enState_00);
				m_warp->SetRotation(objData.rotation, Warp::enState_00);
				m_warp->SetScale(objData.scale, Warp::enState_00);
				return true;
			}
			if (objData.EqualObjectName(L"warp02")) {
				m_warp->SetPosition(objData.position, Warp::enState_01);
				m_warp->SetRotation(objData.rotation, Warp::enState_01);
				m_warp->SetScale(objData.scale, Warp::enState_01);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Kuribo")) {
				m_enemy01 = g_goMgr.NewGameObject<Enemy01>("enemy01");
				m_enemy01->SetPosition(objData.position);
				m_enemy01->SetRotation(objData.rotation);
				m_enemy01->SetScale(objData.scale);
				m_enemy01->InitCharaCon(objData.position);
				return true;
			}
			//エネミー０４テスト中
			//if (objData.EqualObjectName(L"UCW_Kuribo")) {
			//	m_enemy04 = g_goMgr.NewGameObject<Enemy04>("enemy04");
			//	m_enemy04->SetPosition(objData.position);
			//	m_enemy04->SetRotation(objData.rotation);
			//	m_enemy04->SetScale(objData.scale);
			//	m_enemy04->InitCharaCon(objData.position);
			//	return true;
			//}
			if (objData.EqualObjectName(L"wingKuribo")) {
				m_enemy02 = g_goMgr.NewGameObject<Enemy02>("enemy02");
				m_enemy02->SetPosition(objData.position);
				m_enemy02->SetRotation(objData.rotation);
				m_enemy02->SetScale(objData.scale);
				m_enemy02->InitCharaCon(objData.position);
				return true;
			}
			if (objData.EqualObjectName(L"turtle")) {
				m_enemy03 = g_goMgr.NewGameObject<Enemy03>("enemy03");
				m_enemy03->SetPosition(objData.position);
				m_enemy03->SetRotation(objData.rotation);
				m_enemy03->SetScale(objData.scale);
				m_enemy03->InitCharaCon(objData.position);
				return true;
			}
			if (objData.EqualObjectName(L"coin")) {
				m_coin = g_goMgr.NewGameObject<Coin>("coin");
				m_coin->SetPosition(objData.position);
				m_coin->SetRotation(objData.rotation);
				m_coin->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"star")) {
				m_star = g_goMgr.NewGameObject<Star>("star");
				m_star->SetPosition(objData.position);
				m_star->SetRotation(objData.rotation);
				m_star->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"Boxmae")) {
				m_box = g_goMgr.NewGameObject<Box>("box");
				m_box->SetPosition(objData.position);
				m_box->SetRotation(objData.rotation);
				m_box->SetScale(objData.scale);
				m_box->SetItem(Box::enItem_mikan);
				return true;
			}
			if (objData.EqualObjectName(L"Boxcoin")) {
				m_box = g_goMgr.NewGameObject<Box>("box");
				m_box->SetPosition(objData.position);
				m_box->SetRotation(objData.rotation);
				m_box->SetScale(objData.scale);
				m_box->SetItem(m_box->enItem_coin);
				return true;
			}
			if (objData.EqualObjectName(L"mikan")) {
				m_item = g_goMgr.NewGameObject<Item>("item");
				m_item->SetPosition(objData.position);
				m_item->SetRotation(objData.rotation);
				m_item->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"button")) {
				m_button = g_goMgr.NewGameObject<Button>("button");
				m_button->SetPosition(objData.position);
				m_button->SetRotation(objData.rotation);
				m_button->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"button1")) {
				m_button = g_goMgr.NewGameObject<Button>("button1");
				m_button->SetPosition(objData.position);
				m_button->SetRotation(objData.rotation);
				m_button->SetScale(objData.scale);
				return true;
			}

			if (objData.EqualObjectName(L"UCW_Sky")) {
				m_sky = g_goMgr.NewGameObject<Sky>("sky");
				m_sky->SetPosition(objData.position);
				m_sky->SetRotation(objData.rotation);
				m_sky->SetScale(objData.scale);
				return true;
			}
			return false;
			});
		m_player = g_goMgr.NewGameObject<Player>("player");
		m_player->SetPosition(playerPos);
		m_player->SetRotation(playerRot);
		m_player->SetScale(playerScale);
		m_player->InitCharaCon(playerPos);

		m_spriteUI = g_goMgr.NewGameObject<SpriteUI>(0);
		m_fontUI = g_goMgr.NewGameObject<FontUI>(0);
		m_gameCamera = g_goMgr.NewGameObject<GameCamera>("gameCamera");
		InitSound();
	}

}
void Game::Stage02Init()
{
	CVector3 playerPos;
	CQuaternion playerRot;
	CVector3 playerScale;
	if (g_gameData.GetStageNo() == 1) {
		m_level.Init(L"Assets/level/ucw_stage01.tkl", [&](LevelObjectData& objData) {
			if (objData.EqualObjectName(L"unityChan")) {
				playerPos = objData.position;
				playerRot = objData.rotation;
				playerScale = objData.scale;
				return true;
			}

			if (objData.EqualObjectName(L"UCW_Square")) {
				m_stage02[BackGround::enStage02Obj_square] = g_goMgr.NewGameObject<BackGround>("UCW_Square");
				m_stage02[BackGround::enStage02Obj_square]->SetStage02ObjState(BackGround::enStage02Obj_square);
				m_stage02[BackGround::enStage02Obj_square]->SetPosition(objData.position);
				m_stage02[BackGround::enStage02Obj_square]->SetRotation(objData.rotation);
				m_stage02[BackGround::enStage02Obj_square]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Step")) {
				m_stage02[BackGround::enStage02Obj_step] = g_goMgr.NewGameObject<BackGround>("UCW_Step");
				m_stage02[BackGround::enStage02Obj_step]->SetStage02ObjState(BackGround::enStage02Obj_step);
				m_stage02[BackGround::enStage02Obj_step]->SetPosition(objData.position);
				m_stage02[BackGround::enStage02Obj_step]->SetRotation(objData.rotation);
				m_stage02[BackGround::enStage02Obj_step]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Floor0")) {
				m_stage02[BackGround::enStage02Obj_floor0] = g_goMgr.NewGameObject<BackGround>("UCW_Floor0");
				m_stage02[BackGround::enStage02Obj_floor0]->SetStage02ObjState(BackGround::enStage02Obj_floor0);
				m_stage02[BackGround::enStage02Obj_floor0]->SetPosition(objData.position);
				m_stage02[BackGround::enStage02Obj_floor0]->SetRotation(objData.rotation);
				m_stage02[BackGround::enStage02Obj_floor0]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Wall0")) {
				m_stage02[BackGround::enStage02Obj_floor1] = g_goMgr.NewGameObject<BackGround>("UCW_Floor1");
				m_stage02[BackGround::enStage02Obj_floor1]->SetStage02ObjState(BackGround::enStage02Obj_floor1);
				m_stage02[BackGround::enStage02Obj_floor1]->SetPosition(objData.position);
				m_stage02[BackGround::enStage02Obj_floor1]->SetRotation(objData.rotation);
				m_stage02[BackGround::enStage02Obj_floor1]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_PhysicsFence")) {
				m_stage02[BackGround::enStage02Obj_physicsFence] = g_goMgr.NewGameObject<BackGround>("UCW_PhysicsFence");
				m_stage02[BackGround::enStage02Obj_physicsFence]->SetStage02ObjState(BackGround::enStage02Obj_physicsFence);
				m_stage02[BackGround::enStage02Obj_physicsFence]->SetPosition(objData.position);
				m_stage02[BackGround::enStage02Obj_physicsFence]->SetRotation(objData.rotation);
				m_stage02[BackGround::enStage02Obj_physicsFence]->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"wingKuribo")) {
				m_enemy02 = g_goMgr.NewGameObject<Enemy02>("enemy02");
				m_enemy02->SetPosition(objData.position);
				m_enemy02->SetRotation(objData.rotation);
				m_enemy02->SetScale(objData.scale);
				m_enemy02->InitCharaCon(objData.position);
				return true;
			}
			if (objData.EqualObjectName(L"moveFloor")) {
				m_moveFloor = g_goMgr.NewGameObject<MoveFloor>("moveFloor");
				m_moveFloor->SetPosition(objData.position);
				m_moveFloor->SetRotation(objData.rotation);
				m_moveFloor->SetScale(objData.scale);
				m_moveFloor->InitCharaCon(objData.position);
				return true;
			}
			if (objData.EqualObjectName(L"button")) {
				m_button = g_goMgr.NewGameObject<Button>("button");
				m_button->SetPosition(objData.position);
				m_button->SetRotation(objData.rotation);
				m_button->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"coin")) {
				m_coin = g_goMgr.NewGameObject<Coin>("coin");
				m_coin->SetPosition(objData.position);
				m_coin->SetRotation(objData.rotation);
				m_coin->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"star")) {
				m_star = g_goMgr.NewGameObject<Star>("star");
				m_star->SetPosition(objData.position);
				m_star->SetRotation(objData.rotation);
				m_star->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"UCW_Sky")) {
				m_sky = g_goMgr.NewGameObject<Sky>("sky");
				m_sky->SetPosition(objData.position);
				m_sky->SetRotation(objData.rotation);
				m_sky->SetScale(objData.scale);
				return true;
			}
			return false;
			});
		m_player = g_goMgr.NewGameObject<Player>("player");
		m_player->SetPosition(playerPos);
		m_player->SetRotation(playerRot);
		m_player->SetScale(playerScale);
		m_player->InitCharaCon(playerPos);

		m_spriteUI = g_goMgr.NewGameObject<SpriteUI>(0);
		m_fontUI = g_goMgr.NewGameObject<FontUI>(0);
		m_gameCamera = g_goMgr.NewGameObject<GameCamera>("gameCamera");
		InitSound();
	}
}
void Game::Init()
{
	auto optionData = &GetOptionData();
	optionData->InitBloomParameter();
	optionData->InitLightParameter();
	//ステージ１なら1を初期化
	Stage01Init();
	//ステージ２なら２を初期化
	Stage02Init();
}
void Game::Delete()
{
	g_goMgr.FindGameObjects<Coin>("coin", [](Coin* coin)->bool {
		g_goMgr.DeleteGameObject(coin);
		return true;
		});
	g_goMgr.FindGameObjects<Enemy01>("enemy01", [](Enemy01* enemy01)->bool {
		g_goMgr.DeleteGameObject(enemy01);
		return true;
		});
	g_goMgr.FindGameObjects<Enemy02>("enemy02", [](Enemy02* enemy02)->bool {
		g_goMgr.DeleteGameObject(enemy02);
		return true;
		});
	g_goMgr.FindGameObjects<Enemy03>("enemy03", [](Enemy03* enemy03)->bool {
		g_goMgr.DeleteGameObject(enemy03);
		return true;
		});
	g_goMgr.FindGameObjects<Enemy04>("enemy04", [](Enemy04* enemy04)->bool {
		g_goMgr.DeleteGameObject(enemy04);
		return true;
		});
	g_goMgr.FindGameObjects<EnemyBall>("enemyBall", [](EnemyBall* enemyBall)->bool {
		g_goMgr.DeleteGameObject(enemyBall);
		return true;
		});
	g_goMgr.FindGameObjects<Box>("box", [](Box* box)->bool {
		g_goMgr.DeleteGameObject(box);
		return true;
		});
	g_goMgr.FindGameObjects<Item>("item", [](Item* item)->bool {
		g_goMgr.DeleteGameObject(item);
		return true;
		});
	g_goMgr.FindGameObjects<FireBall>("fireBall", [](FireBall* fireBall)->bool {
		g_goMgr.DeleteGameObject(fireBall);
		return true;
		});
	g_goMgr.FindGameObjects<Button>("button", [](Button* button)->bool {
		g_goMgr.DeleteGameObject(button);
		return true;
		});
	g_goMgr.FindGameObjects<Button>("button1", [](Button* button)->bool {
		g_goMgr.DeleteGameObject(button);
		return true;
		});
	g_goMgr.FindGameObjects<BackGround>("UCW_Floor0", [](BackGround* bg)->bool {
		g_goMgr.DeleteGameObject(bg);
		return true;
		});
	g_goMgr.FindGameObjects<BackGround>("UCW_Floor1", [](BackGround* bg)->bool {
		g_goMgr.DeleteGameObject(bg);
		return true;
		});
	g_goMgr.FindGameObjects<BackGround>("UCW_Floor2", [](BackGround* bg)->bool {
		g_goMgr.DeleteGameObject(bg);
		return true;
		});
	g_goMgr.FindGameObjects<BackGround>("UCW_Floor3", [](BackGround* bg)->bool {
		g_goMgr.DeleteGameObject(bg);
		return true;
		});
	g_goMgr.FindGameObjects<BackGround>("UCW_Floor4", [](BackGround* bg)->bool {
		g_goMgr.DeleteGameObject(bg);
		return true;
		});
	g_goMgr.FindGameObjects<BackGround>("UCW_Ceiling", [](BackGround* bg)->bool {
		g_goMgr.DeleteGameObject(bg);
		return true;
		});
	g_goMgr.FindGameObjects<BackGround>("UCW_Bridge2", [](BackGround* bg)->bool {
		g_goMgr.DeleteGameObject(bg);
		return true;
		});
	g_goMgr.FindGameObjects<BackGround>("UCW_Step", [](BackGround* bg)->bool {
		g_goMgr.DeleteGameObject(bg);
		return true;
		});
	g_goMgr.FindGameObjects<BackGround>("UCW_Fence", [](BackGround* bg)->bool {
		g_goMgr.DeleteGameObject(bg);
		return true;
		});
	g_goMgr.FindGameObjects<BackGround>("UCW_StoneFence", [](BackGround* bg)->bool {
		g_goMgr.DeleteGameObject(bg);
		return true;
		});
	g_goMgr.FindGameObjects<BackGround>("UCW_Square", [](BackGround* bg)->bool {
		g_goMgr.DeleteGameObject(bg);
		return true;
		});
	g_goMgr.FindGameObjects<BackGround>("UCW_PhysicsFence", [](BackGround* bg)->bool {
		g_goMgr.DeleteGameObject(bg);
		return true;
		});
	g_goMgr.FindGameObjects<BackGround>("UCW_BackWall", [](BackGround* bg)->bool {
		g_goMgr.DeleteGameObject(bg);
		return true;
		});
	g_goMgr.DeleteGameObject(m_warp);
	g_goMgr.DeleteGameObject(m_moveFloor);
	g_goMgr.DeleteGameObject(m_star);
	g_goMgr.DeleteGameObject(m_player);
	g_goMgr.DeleteGameObject(m_jumpFloor);
	g_goMgr.DeleteGameObject(m_spriteUI);
	g_goMgr.DeleteGameObject(m_gameOver);
	g_goMgr.DeleteGameObject(m_gameCamera);
	g_goMgr.DeleteGameObject(m_gameClear);
	g_goMgr.DeleteGameObject(m_sky);
	g_goMgr.DeleteGameObject(m_bgm);
	g_goMgr.DeleteGameObject(m_fontUI);
	g_goMgr.DeleteGameObject(m_bridge);
	g_goMgr.DeleteGameObject(m_wall);
	g_goMgr.DeleteGameObject(m_uiManager);
	g_goMgr.FindGameObjects<EnemyFireBall>("enemyFireBall", [](EnemyFireBall* enemyFB)->bool {
		g_goMgr.DeleteGameObject(enemyFB);
		return true;
		});

}