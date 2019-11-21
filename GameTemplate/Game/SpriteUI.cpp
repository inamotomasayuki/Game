#include "stdafx.h"
#include "SpriteUI.h"


SpriteUI::SpriteUI()
{
	//半透明合成のブレンドステートを初期化する。
	InitTranslucentBlendState();
	m_spriteUI[enSprite_unityChan].Init(L"Assets/sprite/unityChan.dds", 500, 200);
	m_position[enSprite_unityChan] = { -380.0f,250.0f,0.0f };
}
SpriteUI::~SpriteUI()
{
	if (m_translucentBlendState != nullptr) {
		m_translucentBlendState->Release();
	}
}
void SpriteUI::Update()
{
	if (g_pad[0].IsPress(enButtonLeft)) {
		//α値を0.02減らす。
		m_spriteUI[enSprite_unityChan].DeltaAlpha(-0.2f);

	}
	else if (g_pad[0].IsPress(enButtonRight)) {
		//α値を0.02増やす。
		m_spriteUI[enSprite_unityChan].DeltaAlpha(0.2f);
	}

	m_spriteUI[enSprite_unityChan].UpdateWorldMatrix(m_position[enSprite_unityChan], m_rotation, m_scale);
}
void SpriteUI::Draw()
{
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	//半透明合成のブレンドステートを設定する。
	d3dDeviceContext->OMSetBlendState(
		m_translucentBlendState,	//設定するブレンディングステート
		blendFactor,				//ブレンディングファクター。気にしなくてよい
		0xffffffff					//サンプリングマスク。気にしなくてよい。
	);
	CMatrix mView;
	CMatrix mProj;
	mView.MakeLookAt(
		{ 0, 0, -1 },
		{ 0, 0, 0 },
		{ 0,1,0 }
	);
	mProj.MakeOrthoProjectionMatrix(1280.0f, 720.0f, 0.1f, 100.0f);
	m_spriteUI[enSprite_unityChan].Draw(mView, mProj);
}
void SpriteUI::InitTranslucentBlendState()
{
	//例のごとく、作成するブレンドステートの情報を設定する。
	CD3D11_DEFAULT defaultSettings;
	//デフォルトセッティングで初期化する。
	CD3D11_BLEND_DESC blendDesc(defaultSettings);

	//αブレンディングを有効にする。
	blendDesc.RenderTarget[0].BlendEnable = true;

	//ソースカラーのブレンディング方法を指定している。
	//ソースカラーとはピクセルシェーダ―からの出力を指している。
	//この指定では、ソースカラーをSRC(rgba)とすると、
	//最終的なソースカラーは下記のように計算される。
	//最終的なソースカラー = SRC.rgb × SRC.a・・・・・・　①
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;

	//ディスティネーションカラーのブレンディング方法を指定している。
	//ディスティネーションカラーとは、
	//すでに描き込まれているレンダリングターゲットのカラーを指している。
	//この指定では、ディスティネーションカラーをDEST(rgba)、
	//ソースカラーをSRC(RGBA)とすると、最終的なディスティネーションカラーは
	//下記のように計算される。
	//最終的なディスティネーションカラー = DEST.rgb × (1.0f - SRC.a)・・・・・②
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	//最終的にレンダリングターゲットに描き込まれるカラーの計算方法を指定している。
	//この指定だと、①＋②のカラーが書き込まれる。
	//つまり、最終的にレンダリングターゲットに描き込まれるカラーは
	//SRC.rgb × SRC.a + DEST.rgb × (1.0f - SRC.a)
	//となる。
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	//この設定で、ブレンドステートを作成すると
	//半透明合成を行えるブレンドステートが作成できる。
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBlendState(&blendDesc, &m_translucentBlendState);
}
