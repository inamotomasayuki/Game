#pragma once

#include "Skeleton.h"
#include "SkinModelEffect.h"
#include "../gameObject/GameObjectManager.h"
/*!
*@brief	FBXの上方向。
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};
const int NUM_DIRECTION_LIG = 4;
const int DITHERING_KILL_PIXEL = 63;
/*!
*@brief	ディレクションライト。
*/
struct SDirectionLight {
	CVector4 direction[NUM_DIRECTION_LIG];		//ライトの方向。
	CVector4 color[NUM_DIRECTION_LIG];			//ライトのカラー。
	CVector3			eyePos;				//視点の座標。
	float				specPow;			//鏡面反射の絞り。
	CVector4			ambient;
	CVector3			eyeDir;
	int isRimLight;	
	float				brightnessPow = 1.0f;	//空の明るさ
};
/*!
*@brief	スキンモデルクラス。
*/
class SkinModel
{
public:
	/// <summary>
	/// リムライトをオフにする
	/// </summary>
	void RimLightOff()
	{
		m_dirLight.isRimLight = 0;
		m_isRim = true;
	}
	void DitheringOn()
	{
		m_isDithering = true;
	}
	void DitheringOff()
	{
		m_isDithering = false;
	}
	void ShadowReciverOff()
	{
		m_isShadowReciver = true;
	}
	/// <summary>
	/// ディレクションライトの番号と方向の設定
	/// </summary>
	void SetDligDir(int num, float x, float y, float z)
	{
		CVector4 dir = { x,y,z,1.0f };
		dir.Normalize();
		m_dirLight.direction[num] = dir;
	}
	/// <summary>
	/// ディレクションライトの番号と色（明るさ）の設定
	/// </summary>
	/// <param name="num">ディレクションライトの番号</param>
	/// <param name="color">色（明るさ）</param>
	void SetDligColor(int num, float color)
	{
		m_dirLight.color[num] = { color,color,color,1.0f };	
	}
	/// <summary>
	/// スペキュラの設定
	/// </summary>
	/// <param name="specPow">スペキュラの絞り値</param>
	void SetDligSpecPow(float specPow)
	{
		m_dirLight.specPow = specPow;
	}
	/// <summary>
	/// 空の明るさの設定
	/// </summary>
	/// <param name="brightPow">明るさの強さ</param>
	void SetBrightnessPow(float brightPow)
	{
		m_dirLight.brightnessPow = brightPow;
	}
	void DecDitheringPow()
	{
		m_isDecDithe = true;
		if (m_ditheringPow > 0){
			m_ditheringPow--;
		}
		else {
			m_ditheringPow = 0;
		}
	}
	int GetDitheringPow()
	{
		return m_ditheringPow;
	}
	//メッシュが見つかったときのコールバック関数。
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	/*!
	*@brief	デストラクタ。
	*/
	~SkinModel();
	/*!
	*@brief	初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*@param[in] enFbxUpAxis		fbxの上軸。デフォルトはenFbxUpAxisZ。
	*/
	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	モデルをワールド座標系に変換するためのワールド行列を更新する。
	*@param[in]	position	モデルの座標。
	*@param[in]	rotation	モデルの回転。
	*@param[in]	scale		モデルの拡大率。
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
	/*!
	*@brief	ボーンを検索。
	*@param[in]		boneName	ボーンの名前。
	*@return	見つかったボーン。見つからなかった場合はnullptrを返します。
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}
	/*!
	*@brief	モデルを描画。
	*@param[in]	viewMatrix		カメラ行列。
	*  ワールド座標系の3Dモデルをカメラ座標系に変換する行列です。
	*@param[in]	projMatrix		プロジェクション行列。
	*  カメラ座標系の3Dモデルをスクリーン座標系に変換する行列です。
	* param [in]renderMode
	*  描画ステップ。0なら通常描画、1ならシルエット描画。
	*/
	void Draw( CMatrix viewMatrix, CMatrix projMatrix, EnRenderMode renderMode);
	/*!
	*@brief	スケルトンの取得。
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}
	/*!
	*@brief	メッシュを検索する。
	*@param[in] onFindMesh		メッシュが見つかったときのコールバック関数
	*/
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}
	/*!
	*@brief	SRVのレジスタ番号。
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<ディフューズテクスチャ。
		enSkinModelSRVReg_BoneMatrix,				//!<ボーン行列。
	};
	/*!
	*@brief	法線マップのロード
	*@param[in]	filePath		ロードするddsファイルのファイルパス。
	*/
	void LoadNormalMap(const wchar_t* filePath);
	/*!
	*@brief	スペキュラマップのロード
	*@param[in]	filePath		ロードするddsファイルのファイルパス。
	*/
	void LoadSpecularMap(const wchar_t* filePath);
	/*!
	*@brief	AOマップのロード
	*@param[in]	filePath		ロードするddsファイルのファイルパス。
	*/
	void LoadAoMap(const wchar_t* filePath);
private:
	/*!
	*@brief	サンプラステートの初期化。
	*/
	void InitSamplerState();
	/*!
	*@brief	定数バッファの作成。
	*/
	void InitConstantBuffer();
	/*!
	*@brief	スケルトンの初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*/
	void InitSkeleton(const wchar_t* filePath);
	//ディレクションライトの初期化。
	void InitDirectionLight();
private:
	//定数バッファ。
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
		CMatrix mLightView;	//ライトビュー行列。
		CMatrix mLightProj;	//ライトプロジェクション行列。
		int isShadowReciever;	//シャドウレシーバーフラグ。
		int isHasNormalMap;		//法線マップを保持している？
		int isHasSpecuraMap;	//スペキュラマップを保持している？
		int isHasAoMap;			//AOマップを保持している？
		int isDithering;		//ディザリング？	
		int ditheringPow;
	};
	int m_ditheringPow = DITHERING_KILL_PIXEL;			//ディザリングでキルするピクセル
	bool m_isDecDithe = false;
	bool m_isRim = false;					//リムライトするか
	bool m_isDithering = false;				//ディザリング？
	bool m_isShadowReciver = false;			//シャドウレシーバーにするか
	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBXの上方向。
	ID3D11Buffer*		m_cb = nullptr;					//!<定数バッファ。
	ID3D11Buffer*		m_lightCb = nullptr;				//!<ライト用の定数バッファ。
	SDirectionLight		m_dirLight;							//!<ディレクションライト。
	Skeleton			m_skeleton;						//!<スケルトン。
	CMatrix				m_worldMatrix;					//!<ワールド行列。
	DirectX::Model*		m_modelDx;						//!<DirectXTKが提供するモデルクラス。
	ID3D11SamplerState* m_samplerState = nullptr;		//!<サンプラステート。
	ID3D11ShaderResourceView* m_normalMapSRV = nullptr;		//法線マップのSRV
	ID3D11ShaderResourceView* m_specularMapSRV = nullptr;	//スペキュラマップのSRV
	ID3D11ShaderResourceView* m_aoMapSRV = nullptr;	//AOマップのSRV
};

