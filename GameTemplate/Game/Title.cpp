#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "StageSelect.h"

const float VIEW_BOLUME_WIDTH = 1280.0f;		//ビューボリュームの幅
const float VIEW_BOLUME_HIGHT = 720.0f;			//ビューボリュームの高さ
const float F_NEAR = 0.1f;						//近平面
const float F_FAR = 100.0f;						//遠平面

const CVector3 CAMERA_POSITION = { 0, 0, -1 };		//カメラの位置
const CVector3 CAMERA_TARGET = { 0, 0, 0 };			//カメラの注視点
const CVector3 CAMERA_UP = { 0,1,0 };				//カメラの上方向

const float BACK_WIDTH = 1500.0f;			//背景の幅
const float BACK_HIGHT = 1500.0f;			//背景の高さ
const float TITLE_WIDTH = 1280.0f;			//タイトルの幅
const float TITLE_HIGHT = 720.0f;			//タイトルの高さ
const float KARI_WIDTH = 1280.0f;			//仮の幅
const float KARI_HIGHT = 720.0f;			//仮の高さ
const float START_WIDTH = 1280.0f;			//スタートの幅
const float START_HIGHT = 720.0f;			//スタートの高さ
const CVector3 BACK_POS = CVector3::Zero();				//背景位置
const CVector3 TITLE_POS = { 0.0f,500.0f,0.0f };		//タイトル位置
const CVector3 START_POS = { 0.0f,-200.0f,0.0f };		//スタート位置
const CVector3 KARI_SCALE = { 10.0f,10.0f,10.0f };		//仮位置
const float TITLE_Y_POS = 200.0f;						//最終的なタイトルのY位置
const float TITLE_DOWN_SPEED = 5.0f;					//タイトルが下りてくるスピード
const float ALPHA_MINUS = -1.0f;						//アルファ値マイナス
const float ALPHA_PLUS = 1.0f;							//アルファ値プラス
const float DELTA_ALPHA = 0.1f;							//徐々にアルファ
const float BACK_ROT_SPEED = -0.2f;						//背景回転速度
const float KARI_SCALE_REDUCTION = 0.93f;				//仮縮小スピード

Title::Title()
{
	m_sprite[enSprite_back].Init(L"Assets/sprite/back.dds", BACK_WIDTH, BACK_HIGHT);
	m_position[enSprite_back] = BACK_POS;
	m_sprite[enSprite_title].Init(L"Assets/sprite/TitleMoji.dds", TITLE_WIDTH, TITLE_HIGHT);
	m_position[enSprite_title] = TITLE_POS;
	m_sprite[enSprite_start].Init(L"Assets/sprite/start.dds", START_WIDTH, START_HIGHT);
	m_position[enSprite_start] = START_POS;
	m_kariSprite.Init(L"Assets/sprite/kari.dds", KARI_WIDTH, KARI_HIGHT);
	m_kariPos = CVector3::Zero();
	m_kariScale = KARI_SCALE;
	m_bgm.Init(L"Assets/sound/TitleBGM.wav");
	m_bgm.Play(true);
}


Title::~Title()
{
}

void Title::Update()
{
	//タイトル下りてくる処理
	if (m_position[enSprite_title].y == TITLE_Y_POS) {
		m_position[enSprite_title].y = TITLE_Y_POS;
		m_isKari = true;
	}
	else {
		m_position[enSprite_title].y -= TITLE_DOWN_SPEED;
	}
	//仮をボンと出す処理
	if (!m_isKari) {
		m_kariSprite.SetAlpha(ALPHA_MINUS);
	}
	else {
		m_kariSprite.SetAlpha(ALPHA_PLUS);
		m_kariScale *= KARI_SCALE_REDUCTION;
		if (m_kariScale.x <= CVector3::One().x) {
			m_kariScale = CVector3::One();
			m_isStart = true;
		}
	}
	//スタートをふわっと出す処理
	if (!m_isStart) {
		m_sprite[enSprite_start].SetAlpha(ALPHA_MINUS);
	}
	else {
		m_sprite[enSprite_start].DeltaAlpha(DELTA_ALPHA);
		//遷移
		if (g_pad[0].IsTrigger(enButtonA)) {
			g_goMgr.NewGameObject<StageSelect>(0);
			g_goMgr.DeleteGameObject(this);
		}
	}
	CQuaternion addRot;
	float rotSpeed;
	//更新
	for (int i = 0; i < enSprite_Num; i++) {
		if (i == enSprite_back) {
			rotSpeed = BACK_ROT_SPEED;
			addRot.SetRotationDeg(CVector3::AxisZ(), rotSpeed);
			m_backRot.Multiply(addRot);
			m_sprite[i].UpdateWorldMatrix(m_position[i], m_backRot, m_scale);
		}
		else if (i == enSprite_start) {
			m_timer++;
			if (m_timer >= 120 && m_timer <= 125) {
				rotSpeed = -5.0f;
			}
			else if (m_timer > 125 && m_timer < 135) {
				rotSpeed = 5.0f;
			}
			else if (m_timer == 135) {
				m_timer = 0;
			}
			else {
				rotSpeed = 0.0f;
				m_startRot = CQuaternion::Identity();
			}
			addRot.SetRotationDeg(CVector3::AxisZ(), rotSpeed);
			m_startRot.Multiply(addRot);
			m_sprite[i].UpdateWorldMatrix(m_position[i], m_startRot, m_scale);
		}
		else {
			m_sprite[i].UpdateWorldMatrix(m_position[i], m_rotation, m_scale);
		}
	}
	m_kariSprite.UpdateWorldMatrix(m_kariPos, m_rotation, m_kariScale);
}


void Title::Draw2D()
{
	CMatrix mView;
	CMatrix mProj;
	mView.MakeLookAt(
		CAMERA_POSITION,
		CAMERA_TARGET,
		CAMERA_UP
	);
	mProj.MakeOrthoProjectionMatrix(VIEW_BOLUME_WIDTH, VIEW_BOLUME_HIGHT, F_NEAR, F_FAR);
	for (int i = 0; i < enSprite_Num; i++) {
		m_sprite[i].Draw(mView, mProj);
	}
	m_kariSprite.Draw(mView, mProj);
}