#include "stdafx.h"
#include "SpriteUI.h"
#include "Game.h"
namespace {
	const float VIEW_BOLUME_WIDTH = 1280.0f;		//ビューボリュームの幅
	const float VIEW_BOLUME_HIGHT = 720.0f;			//ビューボリュームの高さ
	const float F_NEAR = 0.1f;						//近平面
	const float F_FAR = 100.0f;						//遠平面

	const CVector3 CAMERA_POSITION = { 0, 0, -1 };		//カメラの位置
	const CVector3 CAMERA_TARGET = { 0, 0, 0 };			//カメラの注視点
	const CVector3 CAMERA_UP = { 0,1,0 };				//カメラの上方向

	const int TEN = 10;									//10
	const int ONE_HUNDRED = 100;						//100
	const int ONE_THOUSAND = 1000;						//1000

	const float NUM_SPRITE_WIDTH = 50.0f;		//数字の横幅
	const float NUM_SPRITE_HIGHT = 50.0f;		//数字の縦幅

	const float ALPHA_MINUS = -1.0f;		//アルファ値をマイナス
	const float ALPHA_PLUS = 1.0f;			//アルファ値をプラス

	const float UNITY_SPRITE_WIDTH = 500.0f;		//ユニティの横幅
	const float UNITY_SPRITE_HIGHT = 200.0f;		//ユニティの縦幅
	const float COIN_SPRITE_WIDTH = 50.0f;			//コインの横幅
	const float COIN_SPRITE_HIGHT = 50.0f;			//コインの縦幅
	const float KAKERU_SPRITE_WIDTH = 50.0f;		//×の横幅
	const float KAKERU_SPRITE_HIGHT = 50.0f;		//×の縦幅

	const CVector3 UNITYCHAN_POS = { -380.0f,250.0f,0.0f };		//ユニティちゃん位置
	const CVector3 KAKERU_POS = { -550.0f,310.0f,0.0f };		//×位置
	const CVector3 COIN_POS = { 470.0f,320.0f,0.0f };				//コイン位置
	const CVector3 SCORE_ONE_POS = { 580.0f,320.0f,0.0f };		//スコア1桁目
	const CVector3 SCORE_TWO_POS = { 550.0f,320.0f,0.0f };		//スコア２桁目
	const CVector3 SCORE_THREE_POS = { 520.0f,320.0f,0.0f };	//スコア3桁目
	const CVector3 HP_POS = { -520.0f,315.0f,0.0f };			//HP位置
}
SpriteUI::SpriteUI()
{
	m_spriteUI[enSpriteUI_unityChan].Init(L"Assets/sprite/unityChan.dds", UNITY_SPRITE_WIDTH, UNITY_SPRITE_HIGHT);
	m_positionUI[enSpriteUI_unityChan] = UNITYCHAN_POS;
	m_spriteUI[enSpriteUI_kakeru].Init(L"Assets/sprite/kakeru.dds", KAKERU_SPRITE_WIDTH, KAKERU_SPRITE_HIGHT);
	m_positionUI[enSpriteUI_kakeru] = KAKERU_POS;
	m_spriteUI[enSpriteUI_coin].Init(L"Assets/sprite/coin.dds", COIN_SPRITE_WIDTH, COIN_SPRITE_HIGHT);
	m_positionUI[enSpriteUI_coin] = COIN_POS;

	//一桁目の数字の画像初期化
	m_spriteScoreUI[enSpriteScore_zero].Init(L"Assets/sprite/zero.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI[enSpriteScore_one].Init(L"Assets/sprite/one.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI[enSpriteScore_two].Init(L"Assets/sprite/two.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI[enSpriteScore_three].Init(L"Assets/sprite/three.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI[enSpriteScore_four].Init(L"Assets/sprite/four.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI[enSpriteScore_five].Init(L"Assets/sprite/five.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI[enSpriteScore_six].Init(L"Assets/sprite/six.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI[enSpriteScore_seven].Init(L"Assets/sprite/seven.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI[enSpriteScore_eight].Init(L"Assets/sprite/eight.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI[enSpriteScore_nine].Init(L"Assets/sprite/nine.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	//二桁目の数字の画像初期化
	m_spriteScoreUI2[enSpriteScore_zero].Init(L"Assets/sprite/zero.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI2[enSpriteScore_one].Init(L"Assets/sprite/one.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI2[enSpriteScore_two].Init(L"Assets/sprite/two.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI2[enSpriteScore_three].Init(L"Assets/sprite/three.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI2[enSpriteScore_four].Init(L"Assets/sprite/four.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI2[enSpriteScore_five].Init(L"Assets/sprite/five.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI2[enSpriteScore_six].Init(L"Assets/sprite/six.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI2[enSpriteScore_seven].Init(L"Assets/sprite/seven.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI2[enSpriteScore_eight].Init(L"Assets/sprite/eight.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI2[enSpriteScore_nine].Init(L"Assets/sprite/nine.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	//三桁目の数字の画像初期化
	m_spriteScoreUI3[enSpriteScore_zero].Init(L"Assets/sprite/zero.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI3[enSpriteScore_one].Init(L"Assets/sprite/one.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI3[enSpriteScore_two].Init(L"Assets/sprite/two.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI3[enSpriteScore_three].Init(L"Assets/sprite/three.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI3[enSpriteScore_four].Init(L"Assets/sprite/four.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI3[enSpriteScore_five].Init(L"Assets/sprite/five.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI3[enSpriteScore_six].Init(L"Assets/sprite/six.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI3[enSpriteScore_seven].Init(L"Assets/sprite/seven.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI3[enSpriteScore_eight].Init(L"Assets/sprite/eight.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteScoreUI3[enSpriteScore_nine].Init(L"Assets/sprite/nine.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	//HPの数字の画像の初期化
	m_spriteHP[enSpriteHP_zero].Init(L"Assets/sprite/zero_blue.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteHP[enSpriteHP_one].Init(L"Assets/sprite/one_blue.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteHP[enSpriteHP_two].Init(L"Assets/sprite/two_blue.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteHP[enSpriteHP_three].Init(L"Assets/sprite/three_blue.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteHP[enSpriteHP_four].Init(L"Assets/sprite/four_blue.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteHP[enSpriteHP_five].Init(L"Assets/sprite/five_blue.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);

	m_positionScoreUI = SCORE_ONE_POS;		//一桁目の数字の位置
	m_positionScoreUI2 = SCORE_TWO_POS;		//二桁目の数字の位置
	m_positionScoreUI3 = SCORE_THREE_POS;	//三桁目の数字の位置
	m_positionHP = HP_POS;					//HPの数字の位置
}
SpriteUI::~SpriteUI()
{
}
void SpriteUI::Update()
{
	m_game = g_goMgr.FindGameObject<Game>("game");
	if (m_game != nullptr) {
		auto ten = m_game->GetScore() % ONE_HUNDRED;
		auto Hundred = m_game->GetScore() % ONE_THOUSAND;
		//値に応じて表示・非表示切り替え
		for (int i = 0; i < enSpriteScore_Num; i++) {
			//スコアの１の位
			if (i == m_game->GetScore() % TEN) {
				m_spriteScoreUI[i].DeltaAlpha(ALPHA_PLUS);	//表示
			}
			else {
				m_spriteScoreUI[i].DeltaAlpha(ALPHA_MINUS);	//非表示
			}
			//スコアの１０の位
			if ((i * TEN) <= ten && ten < ((i + 1) * TEN)) {
				m_spriteScoreUI2[i].DeltaAlpha(ALPHA_PLUS);	//表示
			}
			else {
				m_spriteScoreUI2[i].DeltaAlpha(ALPHA_MINUS);	//非表示
			}
			if ((i * ONE_HUNDRED) <= Hundred && Hundred < ((i + 1) * ONE_HUNDRED)) {
				m_spriteScoreUI3[i].DeltaAlpha(ALPHA_PLUS);	//表示
			}
			else {
				m_spriteScoreUI3[i].DeltaAlpha(ALPHA_MINUS);	//非表示
			}
		}
		for (int i = 0; i < enSpriteHP_Num; i++) {
			//HP
			if (i == m_game->GetHP()) {
				m_spriteHP[i].DeltaAlpha(ALPHA_PLUS);		//表示
			}
			else {
				m_spriteHP[i].DeltaAlpha(ALPHA_MINUS);		//非表示
			}
		}
	}
	//更新
	for (int i = 0; i < enSpriteUI_Num; i++) {
		m_spriteUI[i].UpdateWorldMatrix(m_positionUI[i], m_rotation, m_scale);
	}
	for (int i = 0; i < enSpriteScore_Num; i++) {
		m_spriteScoreUI[i].UpdateWorldMatrix(m_positionScoreUI, m_rotation, m_scale);
		m_spriteScoreUI2[i].UpdateWorldMatrix(m_positionScoreUI2, m_rotation, m_scale);
		m_spriteScoreUI3[i].UpdateWorldMatrix(m_positionScoreUI3, m_rotation, m_scale);
	}
	for (int i = 0; i < enSpriteHP_Num; i++) {
		m_spriteHP[i].UpdateWorldMatrix(m_positionHP, m_rotation, m_scale);
	}
}

void SpriteUI::Draw2D()
{	

	CMatrix mView;
	CMatrix mProj;
	mView.MakeLookAt(
		CAMERA_POSITION,
		CAMERA_TARGET,
		CAMERA_UP
	);
	mProj.MakeOrthoProjectionMatrix(VIEW_BOLUME_WIDTH, VIEW_BOLUME_HIGHT, F_NEAR, F_FAR);

	//描画
	for (int i = 0; i < enSpriteUI_Num; i++) {
		m_spriteUI[i].Draw(mView, mProj);
	}
	for (int i = 0; i < enSpriteScore_Num; i++) {
		m_spriteScoreUI[i].Draw(mView, mProj);
		m_spriteScoreUI2[i].Draw(mView, mProj);
		m_spriteScoreUI3[i].Draw(mView, mProj);
	}
	for (int i = 0; i < enSpriteHP_Num; i++) {
		m_spriteHP[i].Draw(mView, mProj);
	}
}
