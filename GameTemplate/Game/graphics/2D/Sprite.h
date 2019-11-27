#pragma once

#include "graphics/shader.h"

class Sprite {
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Sprite::Sprite();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	Sprite::~Sprite();
	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="textureFilePath">テクスチャのファイルパス。</param>
	void Init(const wchar_t* textureFilePath, float w, float h);
	void Sprite::Init(ID3D11ShaderResourceView* srv, float w, float h)
	{
		//共通の初期化処理を呼び出す。
		InitCommon(w, h);
		m_texture = srv;
		m_texture->AddRef();	//参照カウンタを増やす。
	}

	/// <summary>
	/// ワールド行列を更新。
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">拡大率</param>
	void UpdateWorldMatrix(CVector3 pos, CQuaternion rot, CVector3 scale);
	/// <summary>
	/// 描画。
	/// </summary>
	/// <param name="mView">カメラ行列</param>
	/// /// <param name="mView">プロジェクション行列</param>
	void Draw(CMatrix mView, CMatrix mProj);
	/// <summary>
/// αを変位させる
/// </summary>
/// <param name="delta">乗算αを変位させる量</param>
	void DeltaAlpha(float delta)
	{
		m_alpha += delta;
		//数値の境界チェック。
		if (m_alpha > 1.0f) {
			m_alpha = 1.0f;
		}
		else if (m_alpha < 0.0f) {
			m_alpha = 0.0f;
		}
	}

private:
	/// <summary>
	/// シェーダーをロード。
	/// </summary>
	void LoadShader();
	/// <summary>
	/// 頂点バッファを作成。
	/// </summary>
	void CreateVertexBuffer(float w, float h);
	/// <summary>
	/// インデックスバッファを作成。
	/// </summary>
	void CreateIndexBuffer();
	/// <summary>
	/// サンプラステートを作成。
	/// </summary>
	void CreateSamplerState();
	/// <summary>
	/// 定数バッファの作成。
	/// </summary>
	void CreateConstantBuffer();
	/// <summary>
	/// テクスチャをロ―ド。
	/// </summary>
	/// <param name="textureFIlePath">ロードするテクスチャのファイルパス。</param>
	void LoadTexture(const wchar_t* textureFIlePath);
	/// <summary>
/// 初期化の共通処理。
/// </summary>
	void InitCommon(float w, float h);

private:

	Shader	m_vs;											//頂点シェーダー。
	Shader	m_ps;											//ピクセルシェーダー。
	ID3D11Buffer*	m_vertexBuffer = nullptr;	//VRAM上の頂点バッファにアクセスするためのインターフェース。
	ID3D11Buffer*	m_indexBuffer = nullptr;		//VRAM上のインデックスバッファにアクセスするためのインターフェース。
	ID3D11Buffer*	m_cbGPU = nullptr;			//GPU側の定数バッファにアクセスするためのインターフェース。
	ID3D11ShaderResourceView* m_texture = nullptr;	//テクスチャにアクセスするためのインターフェース。
	ID3D11SamplerState* m_samplerState = nullptr;	//サンプラステート。
	CMatrix m_world = CMatrix::Identity();					//ワールド行列。
	float						m_alpha = 1.0f;							//スプライトのα値。
	CVector2					m_size = CVector2::Zero();				//画像のサイズ。

};