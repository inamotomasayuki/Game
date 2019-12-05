#include "stdafx.h"
#include "SpriteUI.h"
#include "Game.h"

const float VIEW_BOLUME_WIDTH = 1280.0f;		//ビューボリュームの幅
const float VIEW_BOLUME_HIGHT = 720.0f;			//ビューボリュームの高さ
const float F_NEAR = 0.1f;						//近平面
const float F_FAR = 100.0f;						//遠平面

const CVector3 CAMERA_POSITION = { 0, 0, -1 };		//カメラの位置
const CVector3 CAMERA_TARGET = { 0, 0, 0 };			//カメラの注視点
const CVector3 CAMERA_UP = { 0,1,0 };				//カメラの上方向

const float NUM_SPRITE_WIDTH = 50.0f;		//数字の横幅
const float NUM_SPRITE_HIGHT = 50.0f;		//数字の縦幅

const float ALPHA_MINUS = -1.0f;		//アルファ値をマイナス
const float ALPHA_PLUS = 1.0f;			//アルファ値をプラス



SpriteUI::SpriteUI()
{
	// 半透明合成のブレンドステートを初期化。
	//InitTranslucentBlendState();

	m_spriteUI[enSprite_unityChan].Init(L"Assets/sprite/unityChan.dds", 500, 200);
	m_positionUI[enSprite_unityChan] = { -380.0f,250.0f,0.0f };
	m_spriteUI[enSprite_kakeru].Init(L"Assets/sprite/kakeru.dds", 30, 30);
	m_positionUI[enSprite_kakeru] = { -550.0f,310.0f,0.0f };
	m_spriteUI[enSprite_coin].Init(L"Assets/sprite/coin.dds", 50, 50);
	m_positionUI[enSprite_coin] = { 500.0f,320.0f,0.0f };

	//一桁目の数字の画像初期化
	m_spriteNumUI[enSpriteNum_zero].Init(L"Assets/sprite/zero.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI[enSpriteNum_one].Init(L"Assets/sprite/one.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI[enSpriteNum_two].Init(L"Assets/sprite/two.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI[enSpriteNum_three].Init(L"Assets/sprite/three.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI[enSpriteNum_four].Init(L"Assets/sprite/four.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI[enSpriteNum_five].Init(L"Assets/sprite/five.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI[enSpriteNum_six].Init(L"Assets/sprite/six.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI[enSpriteNum_seven].Init(L"Assets/sprite/seven.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI[enSpriteNum_eight].Init(L"Assets/sprite/eight.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI[enSpriteNum_nine].Init(L"Assets/sprite/nine.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	//二桁目の数字の画像初期化
	m_spriteNumUI2[enSpriteNum_zero].Init(L"Assets/sprite/zero.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI2[enSpriteNum_one].Init(L"Assets/sprite/one.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI2[enSpriteNum_two].Init(L"Assets/sprite/two.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI2[enSpriteNum_three].Init(L"Assets/sprite/three.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI2[enSpriteNum_four].Init(L"Assets/sprite/four.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI2[enSpriteNum_five].Init(L"Assets/sprite/five.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI2[enSpriteNum_six].Init(L"Assets/sprite/six.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI2[enSpriteNum_seven].Init(L"Assets/sprite/seven.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI2[enSpriteNum_eight].Init(L"Assets/sprite/eight.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteNumUI2[enSpriteNum_nine].Init(L"Assets/sprite/nine.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	//HPの数字の画像の初期化
	m_spriteHP[enSpriteHP_zero].Init(L"Assets/sprite/zero_blue.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteHP[enSpriteHP_one].Init(L"Assets/sprite/one_blue.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteHP[enSpriteHP_two].Init(L"Assets/sprite/two_blue.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteHP[enSpriteHP_three].Init(L"Assets/sprite/three_blue.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteHP[enSpriteHP_four].Init(L"Assets/sprite/four_blue.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);
	m_spriteHP[enSpriteHP_five].Init(L"Assets/sprite/five_blue.dds", NUM_SPRITE_WIDTH, NUM_SPRITE_HIGHT);

	m_positionNum = { 580.0f,320.0f,0.0f };		//一桁目の数字の位置
	m_positionNum2 = { 550.0f,320.0f,0.0f };	//二桁目の数字の位置
	m_positionHP = { -520.0f,315.0f,0.0f };		//HPの数字の位置
}
SpriteUI::~SpriteUI()
{
	//if (m_translucentBlendState != nullptr) {
	//	m_translucentBlendState->Release();
	//}
}
void SpriteUI::Update()
{
	m_game = g_goMgr.FindGameObject<Game>("game");

	if (m_game != nullptr) {
		//値に応じて表示・非表示切り替え
		for (int i = 0; i < enSpriteNum_Num; i++) {
			//スコアの１の位
			if (i == m_game->GetScore() % 10) {
				m_spriteNumUI[i].DeltaAlpha(ALPHA_PLUS);	//表示
			}
			else {
				m_spriteNumUI[i].DeltaAlpha(ALPHA_MINUS);	//非表示
			}
			//スコアの１０の位
			if ((i * 10) <= m_game->GetScore() && m_game->GetScore() < ((i + 1) * 10)) {
				m_spriteNumUI2[i].DeltaAlpha(ALPHA_PLUS);	//表示
			}
			else {
				m_spriteNumUI2[i].DeltaAlpha(ALPHA_MINUS);	//非表示
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
	for (int i = 0; i < enSprite_Num; i++) {
		m_spriteUI[i].UpdateWorldMatrix(m_positionUI[i], m_rotation, m_scale);
	}
	for (int i = 0; i < enSpriteNum_Num; i++) {
		m_spriteNumUI[i].UpdateWorldMatrix(m_positionNum, m_rotation, m_scale);
		m_spriteNumUI2[i].UpdateWorldMatrix(m_positionNum2, m_rotation, m_scale);
	}
	for (int i = 0; i < enSpriteHP_Num; i++) {
		m_spriteHP[i].UpdateWorldMatrix(m_positionHP, m_rotation, m_scale);
	}

}
void SpriteUI::Draw2D()
{
	
	//auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	////半透明合成のブレンドステートを設定する。
	//d3dDeviceContext->OMSetBlendState(
	//	m_translucentBlendState,	//設定するブレンディングステート
	//	blendFactor,				//ブレンディングファクター。気にしなくてよい
	//	0xffffffff					//サンプリングマスク。気にしなくてよい。
	//);
	CMatrix mView;
	CMatrix mProj;
	mView.MakeLookAt(
		CAMERA_POSITION,
		CAMERA_TARGET,
		CAMERA_UP
	);
	mProj.MakeOrthoProjectionMatrix(VIEW_BOLUME_WIDTH, VIEW_BOLUME_HIGHT, F_NEAR, F_FAR);

	for (int i = 0; i < enSprite_Num; i++) {
		m_spriteUI[i].Draw(mView, mProj);
	}
	for (int i = 0; i < enSpriteNum_Num; i++) {
		m_spriteNumUI[i].Draw(mView, mProj);
		m_spriteNumUI2[i].Draw(mView, mProj);
	}
	for (int i = 0; i < enSpriteHP_Num; i++) {
		m_spriteHP[i].Draw(mView, mProj);
	}

}
//void SpriteUI::InitTranslucentBlendState()
//{
//	//例のごとく、作成するブレンドステートの情報を設定する。
//	CD3D11_DEFAULT defaultSettings;
//	//デフォルトセッティングで初期化する。
//	CD3D11_BLEND_DESC blendDesc(defaultSettings);
//
//	//αブレンディングを有効にする。
//	blendDesc.RenderTarget[0].BlendEnable = true;
//
//	//ソースカラーのブレンディング方法を指定している。
//	//ソースカラーとはピクセルシェーダ―からの出力を指している。
//	//この指定では、ソースカラーをSRC(rgba)とすると、
//	//最終的なソースカラーは下記のように計算される。
//	//最終的なソースカラー = SRC.rgb × SRC.a・・・・・・　①
//	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
//
//	//ディスティネーションカラーのブレンディング方法を指定している。
//	//ディスティネーションカラーとは、
//	//すでに描き込まれているレンダリングターゲットのカラーを指している。
//	//この指定では、ディスティネーションカラーをDEST(rgba)、
//	//ソースカラーをSRC(RGBA)とすると、最終的なディスティネーションカラーは
//	//下記のように計算される。
//	//最終的なディスティネーションカラー = DEST.rgb × (1.0f - SRC.a)・・・・・②
//	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
//
//	//最終的にレンダリングターゲットに描き込まれるカラーの計算方法を指定している。
//	//この指定だと、①＋②のカラーが書き込まれる。
//	//つまり、最終的にレンダリングターゲットに描き込まれるカラーは
//	//SRC.rgb × SRC.a + DEST.rgb × (1.0f - SRC.a)
//	//となる。
//	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
//
//	//この設定で、ブレンドステートを作成すると
//	//半透明合成を行えるブレンドステートが作成できる。
//	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
//	d3dDevice->CreateBlendState(&blendDesc, &m_translucentBlendState);
//}