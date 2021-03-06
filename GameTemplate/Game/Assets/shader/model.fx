/*!
 * @brief	モデルシェーダー。
 */

 //ディザパターン
static const int pattern[] = {
 0, 32,  8, 40,  2, 34, 10, 42,   /* 8x8 Bayer ordered dithering  */
 48, 16, 56, 24, 50, 18, 58, 26,  /* pattern.  Each input pixel   */
 12, 44,  4, 36, 14, 46,  6, 38,  /* is scaled to the 0..63 range */
 60, 28, 52, 20, 62, 30, 54, 22,  /* before looking in this table */
 3, 35, 11, 43,  1, 33,  9, 41,   /* to determine the action.     */
 51, 19, 59, 27, 49, 17, 57, 25,
 15, 47,  7, 39, 13, 45,  5, 37,
 63, 31, 55, 23, 61, 29, 53, 21
};

/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	
Texture2D<float4> g_shadowMap : register(t1);		//todo シャドウマップ。
Texture2D<float4> g_normalMap : register(t2);		//	法線マップ。
Texture2D<float4> toonMap : register(t3);  //toonシェーダー用のテクスチャー
Texture2D<float4> g_specularMap : register(t4);		//スペキュラマップ。
Texture2D<float4> g_aoMap : register(t5);			//AOマップ。


//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t2);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	//todo ライトビュー行列を追加。
	float4x4 mLightView;	//ライトビュー行列。
	float4x4 mLightProj;	//ライトプロジェクション行列。
	int isShadowReciever;	//シャドウレシーバーフラグ。
	int isHasNormalMap;		//法線マップある？
	int isHasSpecularMap;	//スペキュラマップある？
	int isHasAoMap;			//AOマップある？
	int isDithering;		//ディザリング？
	int ditheringPow;		//ディザリングの強さ
};
static const int NUM_DIRECTION_LIG = 4;
/*!
 *@brief	ライト用の定数バッファ。
 */
cbuffer LightCb : register(b1) {
	float3 dligDirection[NUM_DIRECTION_LIG];
	float4 dligColor[NUM_DIRECTION_LIG];
	float3 eyePos;		//カメラの視点	
	float specPow;		//スペキュラライトの絞り
	float3 ambient;		//アンビエントライト
	float3 eyeDir;		//カメラの前方向
	int isRimLight;	
	float brightnessPow;	//空の明るさ
};
/// <summary>
/// シャドウマップ用の定数バッファ。
/// </summary>
//cbuffer ShadowMapCb : register(b3) {
//	float4x4 lightViewProjMatrix;	//ライトビュープロジェクション行列。
//}

/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;	//ワールド座標。
	float4 posInLVP		: TEXCOORD2;	//ライトビュープロジェクション空間での座標。
};
/// <summary>
/// シャドウマップ用のピクセルシェーダへの入力構造体。
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//座標。
};

/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);
	float4 worldPos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	if (isShadowReciever == 1) {
		//続いて、ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
	    pos = mul(skinning, In.Position);
	}
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	float4 worldPos = pos;
	if (isShadowReciever == 1) {
		//続いて、ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
    return psInput;
}
//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	
	//albedoテクスチャからカラーをフェッチする。
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
		//法線を計算する。
	float3 normal = 0;
	if(isHasNormalMap == 1){
		//法線マップがある。
		//法線と接ベクトルの外積を計算して、従ベクトルを計算する。
		float3 biNormal = cross(In.Normal, In.Tangent);
		normal = g_normalMap.Sample(Sampler, In.TexCoord);
		//0.0〜1.0の範囲になっているタンジェントスペース法線を
		//-1.0〜1.0の範囲に変換する。
		normal =(normal * 2.0f)- 1.0f;
		//法線をタンジェントスペースから、ワールドスペースに変換する。
		normal = In.Tangent * normal.x + biNormal * normal.y + In.Normal * normal.z;
	}else{
		//ない。
		normal = In.Normal;
	}

	//ディレクションライトの拡散反射光を計算する。
	float3 lig = 0.0f;
	for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
		//lig += max(0.0f, dot(normal * -1.0f, dligDirection[i])) * dligColor[i];
		//ディレクションライトの鏡面反射光を計算する。
		{
			//実習　鏡面反射を計算しなさい。
			//?@　反射ベクトルRを求める。
			float3 R = dligDirection[i]
				+ 2 * dot(In.Normal , -dligDirection[i])
				* In.Normal;
			//?A　視点からライトを当てる物体に伸びるベクトルEを求める。
			float3 E = normalize(In.worldPos - eyePos);
			//?@と?Aで求まったベクトルの内積を計算する。
			//スペキュラ反射の強さを求める。
			float specPower = max(0, dot(R, -E));
			float spec;
			if (isHasSpecularMap == 1) {
				//スペキュラマップがある。
				spec = g_specularMap.Sample(Sampler, In.TexCoord).r;

				float3 specLig = pow(specPower, 2.0f) * dligColor[i] * spec *  7.0f;
				//?D スペキュラ反射が求まったら、ligに加算する。
				//鏡面反射を反射光に加算する。
				lig += specLig;
			}
			else {
				specPower = pow(specPower, specPow);
				lig += dligColor[i] * specPower;
			}
		}
	}		
	//アンビエント
	{
		float3 ao = 1.0f;
		if (isHasAoMap == 1) {
			ao = g_aoMap.Sample(Sampler, In.TexCoord).xyz;
		}
		lig += ambient * ao;
	}
	//lig += ambient;
	if (isShadowReciever == 1) {	//シャドウレシーバー。
	//LVP空間から見た時の最も手前の深度値をシャドウマップから取得する。
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//シャドウマップの範囲内かどうかを判定する。
		if (shadowMapUV.x < 1.0f
			&& shadowMapUV.x > 0.0f
			&& shadowMapUV.y < 1.0f
			&& shadowMapUV.y > 0.0f
			) {
			///LVP空間での深度値を計算。
			float zInLVP = In.posInLVP.z / In.posInLVP.w;
			//シャドウマップに書き込まれている深度値を取得。
			float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);
			//float zInLVP = 1.0f;
			//float zInShadowMap = 0.0f;
			if (zInLVP > zInShadowMap + 0.01f
				) {
				//影が落ちているので、光を弱くする
				lig *= 0.5f;
			}
		}
	}
	if (isRimLight == 1) {
		//リムライトの計算
		float rim = saturate( 1.0f - dot(-eyeDir, In.Normal) );
		rim = pow(rim, 3.0f);
		//黄色
		lig += float3(50.5f, 50.5f, 0.5f) * rim;
	}
	if (isDithering == 1) {
		 //ディザリングを試す
		float2 pos = In.Position.xy / In.Position.w;

		pos *= 0.5f;
		pos += 0.5f;
		float2 uv = fmod(pos * 1000.0f, 8.0f);
		int t = 0;
		int x = (int)clamp(uv.x, 0.0f, 7.0f);
		int y = (int)clamp(uv.y, 0.0f, 7.0f);
		int index = y * 8 + x;
		t = pattern[index];
		if (t >= ditheringPow) {
			clip(-1);
		}
	}
	{
		//ハーフランバート拡散照明によるライティング計算
		float p[NUM_DIRECTION_LIG];
		float4 Col[NUM_DIRECTION_LIG];
		for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
			p[i] = dot(normal * -1.0f, dligDirection[i].xyz);
			p[i] = p[i] * 0.5f + 0.5f;
			p[i] = p[i] * p[i];
			//計算結果よりトゥーンシェーダー用のテクスチャから色をフェッチする
			Col[i] = toonMap.Sample(Sampler, float2(p[i], 0.0f));

			//求まった色を乗算する
			albedoColor.xyz *= Col[i].xyz;
		}
	}
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;

}
/// <summary>
/// シャドウマップ生成用の頂点シェーダー。
/// </summary>
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

//--------------------------------------------------------------------------------------
// シルエット描画用のピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4(0.4f, 0.4f, 1.0f, 1.0f);
}
/// <summary>
/// ピクセルシェーダーのエントリ関数。
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//射影空間でのZ値を返す。
	return In.Position.z / In.Position.w;
}

float4 PSMain_Sky(PSInput In) : SV_Target0
{
	return albedoTexture.Sample(Sampler, In.TexCoord) * brightnessPow;
}