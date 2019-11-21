#include "stdafx.h"
#include "Sprite.h"


//頂点構造体。
struct Vertex {
	CVector4	pos;		//座標。
	CVector2	uv;			//UV座標。
};

/// <summary>
/// 2D描画で使用する定数バッファ構造体。
/// </summary>
struct SSpriteCB {
	CMatrix mWVP;		//ワールド×ビュー×プロジェクション行列。
	float alpha;		//α値。
};

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
	if (m_vertexBuffer != nullptr) {
		m_vertexBuffer->Release();
	}
	if (m_indexBuffer != nullptr) {
		m_indexBuffer->Release();
	}
	if (m_cbGPU != nullptr) {
		m_cbGPU->Release();
	}
	if (m_texture != nullptr) {
		m_texture->Release();
	}
	if (m_samplerState != nullptr) {
		m_samplerState->Release();
	}
}

void Sprite::Init(const wchar_t* textureFilePath, float w, float h)
{
	//シェーダーをロード。
	LoadShader();
	//頂点バッファを作成。
	CreateVertexBuffer(w, h);
	//インデックスバッファを作成。
	CreateIndexBuffer();
	//定数バッファを作成。
	CreateConstantBuffer();
	//サンプラステートを作成。
	CreateSamplerState();
	//テクスチャをロード。
	LoadTexture(textureFilePath);
}

void Sprite::LoadShader()
{
	//シェーダーをロードする。
	m_ps.Load("Assets/shader/sprite.fx", "PSMain", Shader::EnType::PS);
	m_vs.Load("Assets/shader/sprite.fx", "VSMain", Shader::EnType::VS);
}
void Sprite::CreateConstantBuffer()
{
	int bufferSize = sizeof(SSpriteCB);
	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC desc = { 0 };
	desc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	desc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//定数バッファは16バイトアライメントになっている必要がある。
															//アライメントって→バッファのサイズが16の倍数ということです。
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
															//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	desc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
															//CPUアクセスが不要な場合は0。
	//作成。
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBuffer(&desc, NULL, &m_cbGPU);
}
void Sprite::CreateVertexBuffer(float w, float h)
{
	float halfW = w * 0.5f;
	float halfH = h * 0.5f;

	//頂点バッファの元データ。
	//引数で指定された縦、横のサイズの板ポリ。
	Vertex vertices[] = {
		{
			CVector4(-halfW, -halfH, 0.0f, 1.0f),
			CVector2(0.0f, 1.0f),
		},
		{
			CVector4(halfW, -halfH, 0.0f, 1.0f),
			CVector2(1.0f, 1.0f),
		},
		{
			CVector4(-halfW, halfH, 0.0f, 1.0f),
			CVector2(0.0f, 0.0f)
		},
		{
			CVector4(halfW, halfH, 0.0f, 1.0f),
			CVector2(1.0f, 0.0f)
		}
	};

	//頂点バッファを作成するための情報を設定する。
	D3D11_BUFFER_DESC desc = { 0 };					//構造体のメンバを0で初期化する。
	desc.Usage = D3D11_USAGE_DEFAULT;				//気にしなくてよい。
	desc.StructureByteStride = sizeof(Vertex);		//構造体バッファの１要素のサイズ。(頂点一個分のサイズです。)
	desc.ByteWidth = sizeof(Vertex) * 4;			//頂点バッファのサイズ。
													//四角形のポリゴンを描画するので、４頂点必要。
													//なので、一つの頂点のサイズ×４のサイズが必要となる。
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//作成するバッファが頂点バッファであることを指定する。
	desc.CPUAccessFlags = 0;						//CPUから頂点バッファにアクセスするかのフラグ。
													//編集したりはしないので、０にしておく。

	//続いて、元データの情報を作る。
	//元データがないならこれはいらない。
	//今回は必要。
	D3D11_SUBRESOURCE_DATA initData = { 0 };		//構造体のメンバを0で初期化する。
	initData.pSysMem = vertices;					//元データのアドレスを代入。

	//ここまで設定してきた情報を使って、VRAM上に頂点バッファを作成する。
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBuffer(&desc, &initData, &m_vertexBuffer);
}

void Sprite::CreateIndexBuffer()
{
	//インデックスバッファの元データ。
	short indices[] = { 0,1,2,3 };

	//インデックスバッファを作るための情報を設定する。
	D3D11_BUFFER_DESC desc = { 0 };					//構造体のメンバを0で初期化する。
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.StructureByteStride = 2;					//インデックス一個分のサイズ。shortなので2バイト。
	desc.ByteWidth = sizeof(indices);				//インデックスバッファのサイズ。
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;		//作成するバッファがインデックスバッファであることを指定する。
	desc.CPUAccessFlags = 0;						//CPUから頂点バッファにアクセスするかのフラグ。
													//編集したりはしないので、０にしておく。

	D3D11_SUBRESOURCE_DATA initData = { 0 };			//構造体のメンバを0で初期化する。
	initData.pSysMem = indices;						//元データのアドレスを代入する。

	//ここまで設定してきた情報を使って、VRAM上にインデックスバッファを作成する。
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBuffer(&desc, &initData, &m_indexBuffer);
}

void Sprite::CreateSamplerState()
{
	//テクスチャのサンプリング方法を指定するためのサンプラステートを作成。
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	//Clamp+バイリニアフィルタをかけるサンプラステートを作成する。
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}
void Sprite::LoadTexture(const wchar_t* textureFIlePath)
{
	//D3Dデバイスを取得。
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();

	DirectX::CreateDDSTextureFromFileEx(
		d3dDevice,
		textureFIlePath,
		0,
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE,
		0,
		0,
		false,
		nullptr,
		&m_texture);
}

void Sprite::UpdateWorldMatrix(CVector3 pos, CQuaternion rot, CVector3 scale)
{
	//ワールド行列を計算する
	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(pos);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_world.Mul(mScale, mRot);
	m_world.Mul(m_world, mTrans);
}
void Sprite::Draw(CMatrix mView, CMatrix mProj)
{
	//デバイスコンテキストを引っ張ってくる。
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();

	//定数バッファを更新。
	SSpriteCB cb;
	//ワールド×ビュー×プロジェクション行列を計算。
	cb.mWVP.Mul(m_world, mView);
	cb.mWVP.Mul(cb.mWVP, mProj);
	cb.alpha = m_alpha;
	//定数バッファの内容をメインメモリからVRAMにコピー。
	deviceContext->UpdateSubresource(m_cbGPU, 0, nullptr, &cb, 0, 0);
	//定数バッファをレジスタb0にバインドする。
	deviceContext->VSSetConstantBuffers(0, 1, &m_cbGPU);
	deviceContext->PSSetConstantBuffers(0, 1, &m_cbGPU);

	//テクスチャをレジスタt0にバインドする。
	deviceContext->PSSetShaderResources(0, 1, &m_texture);
	//サンプラステートをレジスタs0にバインドする。
	deviceContext->PSSetSamplers(0, 1, &m_samplerState);

	//頂点バッファを設定。
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	//インデックスバッファを設定。
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	//頂点レイアウトを設定。
	deviceContext->IASetInputLayout(m_vs.GetInputLayout());
	//頂点シェーダーを設定。
	deviceContext->VSSetShader((ID3D11VertexShader *)m_vs.GetBody(), nullptr, 0);
	//ピクセルシェーダを設定。
	deviceContext->PSSetShader((ID3D11PixelShader *)m_ps.GetBody(), nullptr, 0);
	//プリミティブのトポロジーを設定。
	deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//ここまで設定した内容でドロー
	deviceContext->DrawIndexed(4, 0, 0);
}