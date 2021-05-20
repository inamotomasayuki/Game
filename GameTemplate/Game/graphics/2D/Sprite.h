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
	void UpdateWorldMatrix(const CVector3& pos, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot = CVector2::Zero());
	/// <summary>
	/// 描画。
	/// </summary>
	/// <param name="mView">カメラ行列</param>
	/// /// <param name="mView">プロジェクション行列</param>
	void Draw(const CMatrix& mView, const CMatrix& mProj);
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
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
		//数値の境界チェック。
		if (m_alpha > 1.0f) {
			m_alpha = 1.0f;
		}
		else if (m_alpha < 0.0f) {
			m_alpha = 0.0f;
		}

	}
	/// <summary>
	/// アルファ値取得
	/// </summary>
	/// <returns></returns>
	float GetAlpha() const
	{
		return m_alpha;
	}
	/// <summary>
	/// モノクロか設定
	/// </summary>
	/// <param name="monochrome"></param>
	void SetIsMonochrome(bool monochrome)
	{
		m_isMonochrome = monochrome;
	}
	/// <summary>
/// 初期化の共通処理。
/// </summary>
	void InitCommon(float w, float h);

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

private:
	ID3D11DepthStencilState* m_depthStencilState = nullptr;
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
	bool m_isMonochrome = false;			//モノクロ？
};