#include "stdafx.h"
#include "StageSelect.h"
#include "../title/Title.h"
#include "Game.h"
#include "GameData.h"
namespace {
	const float VIEW_BOLUME_WIDTH = 1280.0f;		//ビューボリュームの幅
	const float VIEW_BOLUME_HIGHT = 720.0f;			//ビューボリュームの高さ
	const float F_NEAR = 0.1f;						//近平面
	const float F_FAR = 100.0f;						//遠平面

	const CVector3 CAMERA_POSITION = { 0, 0, -1 };		//カメラの位置
	const CVector3 CAMERA_TARGET = { 0, 0, 0 };			//カメラの注視点
	const CVector3 CAMERA_UP = { 0,1,0 };				//カメラの上方向

	const int STAGE_NUM = 1;				//ステージの数
	const int SELECT_NUM = 1;				//セレクトの数

	const float TOUMEI_ALPHA = 0.3f;			//アルファ値をマイナス
	const float ALPHA_PLUS = 1.0f;			//アルファ値をプラス

	const float BACK_WIDTH = 1280.0f;				//背景の幅
	const float BACK_HIGHT = 720.0f;				//背景の高さ
	const float SELECT_WIDTH = 1280.0f;				//セレクト幅
	const float SELECT_HIGHT = 720.0f;				//セレクト高さ
	const float OK_WIDTH = 720.0f;					//OKの幅
	const float OK_HIGHT = 360.0f;					//OKの高さ
	const float STAGE_ZERO_WIDTH = 100.0f;			//０の幅
	const float STAGE_ZERO_HIGHT = 100.0f;			//０の高さ
	const float STAGE_ONE_WIDTH = 100.0f;			//１の幅
	const float STAGE_ONE_HIGHT = 100.0f;			//１の高さ
	const float LEFT_TRIANGLE_WIDTH = 100.0f;		//左三角の幅
	const float LEFT_TRIANGLE_HIGHT = 100.0f;		//左三角の高さ
	const float RIGHT_TRIANGLE_WIDTH = 100.0f;		//右三角の幅
	const float RIGHT_TRIANGLE_HIGHT = 100.0f;		//右三角の高さ
	const float UP_TRIANGLE_WIDTH = 100.0f;			//上三角の幅
	const float UP_TRIANGLE_HIGHT = 100.0f;			//上三角の高さ
	const float DOWN_TRIANGLE_WIDTH = 100.0f;		//下三角の幅
	const float DOWN_TRIANGLE_HIGHT = 100.0f;		//下三角の高さ
	const float DELETE_THIS_ALPHA = 1.0f;			//フェードがこのアルファ値で削除する

	const CVector3 SELECT_POS = { 0.0f,200.0f,0.0f };			//セレクトの位置
	const CVector3 OK_POS = { 15.0f,-210.0f,0.0f };				//OKの位置
	const CVector3 STAGE_ZERO_POS = { -100.0f,0.0f,0.0f };		//０の位置
	const CVector3 STAGE_ONE_POS = { 100.0f,0.0f,0.0f };		//１の位置
	const CVector3 LEFT_TRIANGLE_POS = { -200.0f,0.0f,0.0f };	//左三角の位置
	const CVector3 RIGHT_TRIANGLE_POS = { 200.0f,0.0f,0.0f };	//右三角の位置
	const CVector3 UP_TRIANGLE_POS = { 0.0f,-100.0f,0.0f };		//上三角の位置
	const CVector3 DOWN_TRIANGLE_POS = { 0.0f,-150.0f,0.0f };	//下三角の位置
}

StageSelect::StageSelect()
{
	//初期化
	Init();
}


StageSelect::~StageSelect()
{
}

void StageSelect::Update()
{
}

void StageSelect::NewUpdate()
{

	g_gameData.SetStageNo(stageNo);
	if (!m_isOK) {
		//セレクトかOKかを選択する処理
		if (g_pad[0].IsTrigger(enButtonUp)) {
			m_selectNo--;
		}
		if (g_pad[0].IsTrigger(enButtonDown)) {
			m_selectNo++;
		}
		if (m_selectNo < 0) {
			m_selectNo = SELECT_NUM;
		}
		if (m_selectNo > SELECT_NUM) {
			m_selectNo = 0;
		}
		if (g_pad[0].IsTrigger(enButtonA)) {
			m_selectNo = enSelect_ok;
		}
		//ステージを選択する処理
		if (m_selectNo == enSelect_stage) {
			//透けるか透けないか
			m_sprite[enSprite_upTriangle].SetAlpha(ALPHA_PLUS);
			m_sprite[enSprite_leftTriangle].SetAlpha(ALPHA_PLUS);
			m_sprite[enSprite_rightTriangle].SetAlpha(ALPHA_PLUS);
			m_sprite[enSprite_downTriangle].SetAlpha(TOUMEI_ALPHA);
			m_sprite[enSprite_ok].SetAlpha(TOUMEI_ALPHA);
			//選択
			if (g_pad[0].IsTrigger(enButtonRight)) {
				stageNo++;
			}
			if (g_pad[0].IsTrigger(enButtonLeft)) {
				stageNo--;
			}
		}
	}
	//OK中にAボタンでゲームに遷移
	if (m_selectNo == enSelect_ok) {
		//透けるか透けないか
		m_sprite[enSprite_leftTriangle].SetAlpha(TOUMEI_ALPHA);
		m_sprite[enSprite_rightTriangle].SetAlpha(TOUMEI_ALPHA);
		m_sprite[enSprite_downTriangle].SetAlpha(ALPHA_PLUS);
		m_sprite[enSprite_upTriangle].SetAlpha(TOUMEI_ALPHA);
		m_sprite[enSprite_ok].SetAlpha(ALPHA_PLUS);
		if (!m_isGame) {
			if (g_pad[0].IsTrigger(enButtonA)) {
				m_isOK = true;
				if (m_fade == nullptr) {
					m_fade = g_goMgr.NewGameObject<Fade>("fade");
					//ゲームへ
					m_isGame = true;
				}
			}
		}
	}
	//Bボタンでタイトルに戻る
	if (!m_isTitle) {
		if (g_pad[0].IsTrigger(enButtonB)) {
			m_isOK = true;
			if (m_fade == nullptr) {
				m_fade = g_goMgr.NewGameObject<Fade>("fade");
				//タイトルへ
				m_isTitle = true;
			}
		}
	}
	//選択されてなかったら半透明にする処理
	for (int i = 0; i < g_gameData.enStage_Num; i++) {
		if (stageNo == i) {
			m_stageSprite[i].DeltaAlpha(ALPHA_PLUS);
		}
		else {
			m_stageSprite[i].SetAlpha(TOUMEI_ALPHA);
		}
	}
	if (stageNo < 0) {
		stageNo = STAGE_NUM;
	}
	if (stageNo > STAGE_NUM) {
		stageNo = 0;
	}
	//ゲームへ遷移
	if (m_isGame) {
		if (m_fade->GetAlpha() >= DELETE_THIS_ALPHA) {
			g_goMgr.NewGameObject<Game>("game");
			g_goMgr.DeleteGameObject(this);
		}
	}
	//タイトルへ遷移
	if (m_isTitle) {
		if (m_fade->GetAlpha() >= DELETE_THIS_ALPHA) {
			g_goMgr.NewGameObject<Title>(0);
			g_goMgr.DeleteGameObject(this);
		}
	}
	//更新
	for (int i = 0; i < enSprite_Num; i++) {
		m_sprite[i].UpdateWorldMatrix(m_position[i], m_rotation, m_scale);
	}
	for (int i = 0; i < g_gameData.enStage_Num; i++) {
		m_stageSprite[i].UpdateWorldMatrix(m_stagePos[i], m_rotation, m_scale);
	}

}
void StageSelect::Draw2D()
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
	for (int i = 0; i < g_gameData.enStage_Num; i++) {
		m_stageSprite[i].Draw(mView, mProj);
	}
}
void StageSelect::Init()
{
	//背景
	m_sprite[enSprite_back].Init(L"Assets/sprite/back.dds", BACK_WIDTH, BACK_HIGHT);
	m_position[enSprite_back] = CVector3::Zero();
	//セレクト
	m_sprite[enSprite_select].Init(L"Assets/sprite/select.dds", SELECT_WIDTH, SELECT_HIGHT);
	m_position[enSprite_select] = SELECT_POS;
	//OK
	m_sprite[enSprite_ok].Init(L"Assets/sprite/ok.dds", OK_WIDTH, OK_HIGHT);
	m_position[enSprite_ok] = OK_POS;
	//左△
	m_sprite[enSprite_leftTriangle].Init(L"Assets/sprite/left_triangle.dds", LEFT_TRIANGLE_WIDTH, LEFT_TRIANGLE_HIGHT);
	m_position[enSprite_leftTriangle] = LEFT_TRIANGLE_POS;
	//右△
	m_sprite[enSprite_rightTriangle].Init(L"Assets/sprite/right_triangle.dds", RIGHT_TRIANGLE_WIDTH, RIGHT_TRIANGLE_HIGHT);
	m_position[enSprite_rightTriangle] = RIGHT_TRIANGLE_POS;
	//上△
	m_sprite[enSprite_upTriangle].Init(L"Assets/sprite/up_triangle.dds", UP_TRIANGLE_WIDTH, UP_TRIANGLE_HIGHT);
	m_position[enSprite_upTriangle] = UP_TRIANGLE_POS;
	//下△
	m_sprite[enSprite_downTriangle].Init(L"Assets/sprite/down_triangle.dds", DOWN_TRIANGLE_WIDTH, DOWN_TRIANGLE_HIGHT);
	m_position[enSprite_downTriangle] = DOWN_TRIANGLE_POS;
	//１
	m_stageSprite[g_gameData.enStage_Zero].Init(L"Assets/sprite/white_one.dds", STAGE_ZERO_WIDTH, STAGE_ZERO_HIGHT);
	m_stagePos[g_gameData.enStage_Zero] = STAGE_ZERO_POS;
	//２
	m_stageSprite[g_gameData.enStage_One].Init(L"Assets/sprite/white_two.dds", STAGE_ONE_WIDTH, STAGE_ONE_HIGHT);
	m_stagePos[g_gameData.enStage_One] = STAGE_ONE_POS;
}