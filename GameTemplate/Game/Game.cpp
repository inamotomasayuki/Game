#include "stdafx.h"
#include "Game.h"
#include "GameData.h"
#include "Title.h"
#include "FireBall.h"
#include "StageSelect.h"
const float PLAYER_FALL_GAMEOVER_POS_Y = -1000.0f;		//プレイヤーのY位置
const float CAMERA_ZOOM_SPEED = 0.97f;					//カメラのズーム速度
const float CAMERA_CLEAR_START_LENGTH = 1000.0f;		//クリアした時のカメラの距離
const float CAMERA_CLEAR_END_LENGTH = 300.0f;			//ズームした後のカメラの距離
const int CLEAR_TIME = 25;								//クリアまでの時間
const float DELETE_THIS_ALPHA = 0.95f;			//フェードがこのアルファ値で削除する

Game::Game()
{
	if (g_gameData.GetStageNo() == 0) {
		m_level.Init(L"Assets/level/stage_01_final.tkl", [&](LevelObjectData& objData) {
			if (objData.EqualObjectName(L"unityChan")) {
				m_player = g_goMgr.NewGameObject<Player>("player");
				m_player->SetPosition(objData.position);
				m_player->SetRotation(objData.rotation);
				m_player->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"coin")) {
				m_coin = g_goMgr.NewGameObject<Coin>("coin");
				m_coin->SetPosition(objData.position);
				m_coin->SetRotation(objData.rotation);
				m_coin->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"kuribo")) {
				m_enemy01 = g_goMgr.NewGameObject<Enemy01>("enemy01");
				m_enemy01->SetPosition(objData.position);
				m_enemy01->SetRotation(objData.rotation);
				m_enemy01->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"wingKuribo")) {
				m_enemy02 = g_goMgr.NewGameObject<Enemy02>("enemy02");
				m_enemy02->SetPosition(objData.position);
				m_enemy02->SetRotation(objData.rotation);
				m_enemy02->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"turtle")) {

				m_enemy03 = g_goMgr.NewGameObject<Enemy03>("enemy03");
				m_enemy03->SetPosition(objData.position);
				m_enemy03->SetRotation(objData.rotation);
				m_enemy03->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"gameStage01_final")) {
				m_backGround = g_goMgr.NewGameObject<BackGround>("backGround");
				m_backGround->SetPosition(objData.position);
				m_backGround->SetRotation(objData.rotation);
				m_backGround->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"skybox")) {
				m_sky = g_goMgr.NewGameObject<Sky>("sky");
				m_sky->SetPosition(objData.position);
				m_sky->SetRotation(objData.rotation);
				m_sky->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"moveFloor")) {
				m_moveFloor = g_goMgr.NewGameObject<MoveFloor>("moveFloor");
				m_moveFloor->SetPosition(objData.position);
				m_moveFloor->SetRotation(objData.rotation);
				m_moveFloor->SetScale(objData.scale);
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
				m_warp00 = g_goMgr.NewGameObject<Warp00>("warp00");
				m_warp00->SetPosition(objData.position);
				m_warp00->SetRotation(objData.rotation);
				m_warp00->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"warp02")) {
				m_warp01 = g_goMgr.NewGameObject<Warp01>("warp01");
				m_warp01->SetPosition(objData.position);
				m_warp01->SetRotation(objData.rotation);
				m_warp01->SetScale(objData.scale);
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
			return false;
			});
		m_spriteUI = g_goMgr.NewGameObject<SpriteUI>(0);
		m_gameCamera = g_goMgr.NewGameObject<GameCamera>("gameCamera");
		InitSound();
	}
	if (g_gameData.GetStageNo() == 1) {
		m_level.Init(L"Assets/level/stage_02_01.tkl", [&](LevelObjectData& objData) {
			if (objData.EqualObjectName(L"unityChan")) {
				m_player = g_goMgr.NewGameObject<Player>("player");
				m_player->SetPosition(objData.position);
				m_player->SetRotation(objData.rotation);
				m_player->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"coin")) {
				m_coin = g_goMgr.NewGameObject<Coin>("coin");
				m_coin->SetPosition(objData.position);
				m_coin->SetRotation(objData.rotation);
				m_coin->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"kuribo")) {
				m_enemy01 = g_goMgr.NewGameObject<Enemy01>("enemy01");
				m_enemy01->SetPosition(objData.position);
				m_enemy01->SetRotation(objData.rotation);
				m_enemy01->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"wingKuribo")) {
				m_enemy02 = g_goMgr.NewGameObject<Enemy02>("enemy02");
				m_enemy02->SetPosition(objData.position);
				m_enemy02->SetRotation(objData.rotation);
				m_enemy02->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"turtle")) {

				m_enemy03 = g_goMgr.NewGameObject<Enemy03>("enemy03");
				m_enemy03->SetPosition(objData.position);
				m_enemy03->SetRotation(objData.rotation);
				m_enemy03->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"gameStage_02_01")) {
				m_backGround = g_goMgr.NewGameObject<BackGround>("backGround");
				m_backGround->SetPosition(objData.position);
				m_backGround->SetRotation(objData.rotation);
				m_backGround->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"moveFloor")) {
				m_moveFloor = g_goMgr.NewGameObject<MoveFloor>("moveFloor");
				m_moveFloor->SetPosition(objData.position);
				m_moveFloor->SetRotation(objData.rotation);
				m_moveFloor->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"warp01")) {
				m_warp00 = g_goMgr.NewGameObject<Warp00>("warp00");
				m_warp00->SetPosition(objData.position);
				m_warp00->SetRotation(objData.rotation);
				m_warp00->SetScale(objData.scale);
				return true;
			}
			if (objData.EqualObjectName(L"warp02")) {
				m_warp01 = g_goMgr.NewGameObject<Warp01>("warp01");
				m_warp01->SetPosition(objData.position);
				m_warp01->SetRotation(objData.rotation);
				m_warp01->SetScale(objData.scale);
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
				m_box->SetItem(m_box->enItem_coin);
				return true;
			}
			if (objData.EqualObjectName(L"skybox")) {
				m_sky = g_goMgr.NewGameObject<Sky>("sky");
				m_sky->SetPosition(objData.position);
				m_sky->SetRotation(objData.rotation);
				m_sky->SetScale(objData.scale);
				return true;
			}
			return false;
			});
		m_spriteUI = g_goMgr.NewGameObject<SpriteUI>(0);
		m_gameCamera = g_goMgr.NewGameObject<GameCamera>("gameCamera");
		InitSound();
	}
}


Game::~Game()
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
	g_goMgr.DeleteGameObject(m_warp00);
	g_goMgr.DeleteGameObject(m_warp01);
	g_goMgr.DeleteGameObject(m_moveFloor);
	g_goMgr.DeleteGameObject(m_star);
	g_goMgr.DeleteGameObject(m_player);
	g_goMgr.DeleteGameObject(m_backGround);
	g_goMgr.DeleteGameObject(m_jumpFloor);
	g_goMgr.DeleteGameObject(m_spriteUI);
	g_goMgr.DeleteGameObject(m_gameOver);
	g_goMgr.DeleteGameObject(m_gameCamera);
	g_goMgr.DeleteGameObject(m_gameClear);
	g_goMgr.DeleteGameObject(m_sky);
	g_goMgr.DeleteGameObject(m_bgm);
}

void Game::Update()
{
	//ファイアボール
	if (m_player->GetisItem()) {
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
	if (m_fireBallTimer == 10) {
		m_fireBallTimer = 0;
		m_isFireBall = false;
	}
	SoundPlay();
	//シャドウキャスターを登録。
	//g_shadowMap->RegistShadowCaster(m_backGround->GetSkinModel());
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
	if (m_star->GetStarFlag()) {
		m_clearTimer++;
		if (m_gameClear == nullptr) {
			m_gameClear = g_goMgr.NewGameObject<GameClear>(0);
			if (!m_gameClearFlag) {
				m_cameraPos = m_player->GetPositon() - g_camera3D.GetPosition();
				m_cameraPos.y = 0.0f;
				m_cameraPos.Normalize();
				m_nextCameraPos = m_cameraPos;
				m_nextCameraPos *= CAMERA_CLEAR_END_LENGTH;
				m_cameraPos *= CAMERA_CLEAR_START_LENGTH;
				m_gameClearFlag = true;
			}
		}
		//遷移
		if (m_clearTimer >= CLEAR_TIME) {
			if (g_pad[0].IsTrigger(enButtonA)) {
				g_goMgr.NewGameObject<StageSelect>(0);
				g_goMgr.DeleteGameObject(this);
			}
		}
		//ズーム
		if (m_gameClearFlag) {
			if (m_nextCameraPos.Length() < m_cameraPos.Length()) {
				m_cameraPos *= CAMERA_ZOOM_SPEED;
			}
		}
		m_gameCamera->SetCameraPos(m_cameraPos);
	}
	if (m_isFade) {
		if (m_fade->GetAlpha() >= DELETE_THIS_ALPHA) {
			g_goMgr.NewGameObject<StageSelect>(0);
			g_goMgr.DeleteGameObject(this);
		}
	}
	if (g_pad[0].IsTrigger(enButtonStart)) {
		g_goMgr.NewGameObject<Title>(0);
		g_goMgr.DeleteGameObject(this);
	}
}

void Game::Draw()
{

}


void Game::InitSound()
{
	m_bgm = g_goMgr.NewGameObject<CSoundSource>(0);
	m_bgm->Init(L"Assets/sound/BGM.wav");
	m_bgm->Play(true);
	for (int i = 0; i < enSE_Num; i++) {
		m_se[i] = g_goMgr.NewGameObject<CSoundSource>(0);
	}
	m_se[enSE_gameClear]->Init(L"Assets/sound/gameClear.wav");
	m_se[enSE_gameOver]->Init(L"Assets/sound/gameOver.wav");
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