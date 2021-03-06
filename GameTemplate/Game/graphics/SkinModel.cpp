#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelDataManager.h"
#include"SkinModelShaderConst.h"
#include "ShadowMap.h"

SkinModel::~SkinModel()
{
	if (m_cb != nullptr) {
		//定数バッファを解放。
		m_cb->Release();
	}
	//ライト用の定数バッファの解放。
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}
	if (m_samplerState != nullptr) {
		//サンプラステートを解放。
		m_samplerState->Release();
	}
	//todo 法線マップを解放。
	if (m_normalMapSRV != nullptr) {
		m_normalMapSRV->Release();
	}
	if (m_specularMapSRV != nullptr) {
		m_specularMapSRV->Release();
	}
	if (m_aoMapSRV != nullptr) {
		m_aoMapSRV->Release();
	}

}
void SkinModel::Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis)
{
	//スケルトンのデータを読み込む。
	InitSkeleton(filePath);

	//定数バッファの作成。
	InitConstantBuffer();

	//サンプラステートの初期化。
	InitSamplerState();

	//ディレクションライトの初期化。
	InitDirectionLight();

	//SkinModelDataManagerを使用してCMOファイルのロード。
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton);

	m_enFbxUpAxis = enFbxUpAxis;
}
//ディレクションライトの初期化。
void SkinModel::InitDirectionLight()
{
	m_dirLight.direction[0] = { 1.0f, 0.0f, 0.0f, 0.0f };
	m_dirLight.color[0] = { 0.5f, 0.5f, 0.5f, 1.0f };

	m_dirLight.direction[1] = { -0.707f, -0.707f, 0.0f, 0.0f };
	m_dirLight.color[1] = { 0.5f, 0.5f, 0.5f, 1.0f };

	m_dirLight.direction[2] = { 0.0f, -0.707f, 0.707f, 0.0f };
	m_dirLight.color[2] = { 0.5f, 0.5f, 0.5f, 1.0f };

	m_dirLight.direction[3] = { 1.0f, 0.0f, -1.0f, 0.0f };
	m_dirLight.direction[3].Normalize();
	m_dirLight.color[3] = { 0.5f, 0.5f, 0.5f, 1.0f };
	
	m_dirLight.specPow = 10.0f;
	m_dirLight.ambient = { 10.0f,10.0f,10.0f,1.0f };
}
void SkinModel::InitSkeleton(const wchar_t* filePath)
{
	//スケルトンのデータを読み込む。
	//cmoファイルの拡張子をtksに変更する。
	std::wstring skeletonFilePath = filePath;
	//文字列から.cmoファイル始まる場所を検索。
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmoファイルを.tksに置き換える。
	skeletonFilePath.replace(pos, 4, L".tks");
	//tksファイルをロードする。
	bool result = m_skeleton.Load(skeletonFilePath.c_str());
	if (result == false) {
		//スケルトンが読み込みに失敗した。
		//アニメーションしないモデルは、スケルトンが不要なので
		//読み込みに失敗することはあるので、ログ出力だけにしておく。
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tksファイルの読み込みに失敗しました。%ls\n", skeletonFilePath.c_str());
		OutputDebugStringA(message);
#endif
	}
}
void SkinModel::InitConstantBuffer()
{
	//作成するバッファのサイズをsizeof演算子で求める。
	int bufferSize = sizeof(SVSConstantBuffer);
	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//０でクリア。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//バッファは16バイトアライメントになっている必要がある。
																//アライメントって→バッファのサイズが16の倍数ということです。
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
																//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	bufferDesc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
																//CPUアクセスが不要な場合は0。
	//作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);
	//続いて、ライト用の定数バッファを作成。
	//作成するバッファのサイズを変更するだけ。
	bufferSize = sizeof(SDirectionLight);
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);
}
void SkinModel::InitSamplerState()
{
	//テクスチャのサンプリング方法を指定するためのサンプラステートを作成。
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}
void SkinModel::UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale)
{
	//3dsMaxと軸を合わせるためのバイアス。
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;
	//平行移動行列を作成する。
	transMatrix.MakeTranslation(position);
	//回転行列を作成する。
	rotMatrix.MakeRotationFromQuaternion(rotation);
	rotMatrix.Mul(mBias, rotMatrix);
	//拡大行列を作成する。
	scaleMatrix.MakeScaling(scale);
	//ワールド行列を作成する。
	//拡大×回転×平行移動の順番で乗算するように！
	//順番を間違えたら結果が変わるよ。
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);

	//スケルトンの更新。
	m_skeleton.Update(m_worldMatrix);
}
void SkinModel::Draw(CMatrix viewMatrix, CMatrix projMatrix, EnRenderMode renderMode)
{
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	//定数バッファの内容を更新。
	SVSConstantBuffer vsCb;
	vsCb.mWorld = m_worldMatrix;
	vsCb.mProj = projMatrix;
	vsCb.mView = viewMatrix;
	vsCb.mLightView = g_shadowMap->GetLighViewMatrix();	//ライトビュー行列。
	vsCb.mLightProj = g_shadowMap->GetLightProjMatrix();	//ライトプロジェクション行列。
	if (!m_isShadowReciver) {
		vsCb.isShadowReciever = 1;	//シャドウレシーバーフラグ。
	}
	else {
		vsCb.isShadowReciever = 0;
	}
	//todo 法線マップを使用するかどうかのフラグを送る。
	if (m_normalMapSRV != nullptr) {
		vsCb.isHasNormalMap = true;
	}
	else {
		vsCb.isHasNormalMap = false;
	}
	//スペキュラマップを使用するかどうかのフラグを送る。
	if (m_specularMapSRV != nullptr) {
		vsCb.isHasSpecuraMap = true;
	}
	else {
		vsCb.isHasSpecuraMap = false;
	}
	//AOマップを使用するかどうかのフラグを送る。
	if (m_aoMapSRV != nullptr) {
		vsCb.isHasAoMap = true;
	}
	else {
		vsCb.isHasAoMap = false;
	}
	if (m_isDithering) {
		vsCb.isDithering = true;
	}
	else {
		vsCb.isDithering = false;
	}
	if (m_isDecDithe) {
		vsCb.ditheringPow = m_ditheringPow;
	}
	else {
		vsCb.ditheringPow = 20;
	}
	d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &vsCb, 0, 0);
	//視点を更新
	//視点を設定。
	m_dirLight.eyePos = g_camera3D.GetPosition();
	CVector3 eyeDir = g_camera3D.GetTarget() - g_camera3D.GetPosition();
	eyeDir.Normalize();
	m_dirLight.eyeDir = eyeDir;
	if (!m_isRim) {
		m_dirLight.isRimLight = 1;
	}
	//ライト用の定数バッファを更新。
	d3dDeviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_dirLight, 0, 0);
	//定数バッファをGPUに転送。
	d3dDeviceContext->VSSetConstantBuffers(enSkinModelCBReg_VSPS, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(enSkinModelCBReg_VSPS, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(enSkinModelCBReg_Light, 1, &m_lightCb);
	//サンプラステートを設定。
	d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//ボーン行列をGPUに転送。
	m_skeleton.SendBoneMatrixArrayToGPU();
	//エフェクトにクエリを行う。
	m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
		auto modelMaterial = reinterpret_cast<SkinModelEffect*>(material);
		modelMaterial->SetRenderMode(renderMode);
		});
	if (m_normalMapSRV != nullptr) {
		//法線マップが設定されていたらをレジスタt2に設定する。
		d3dDeviceContext->PSSetShaderResources(2, 1, &m_normalMapSRV);
	}
	if (m_specularMapSRV != nullptr) {
		//スペキュラマップが設定されていたらレジスタt4に設定する。
		d3dDeviceContext->PSSetShaderResources(4, 1, &m_specularMapSRV);
	}
	if (m_aoMapSRV != nullptr) {
		//AOマップが設定されていたらレジスタt4に設定する。
		d3dDeviceContext->PSSetShaderResources(5, 1, &m_aoMapSRV);
	}
	//描画。
	m_modelDx->Draw(
		d3dDeviceContext,
		state,
		m_worldMatrix,
		viewMatrix,
		projMatrix
	);
}
void SkinModel::LoadNormalMap(const wchar_t* filePath)
{
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), filePath, 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_normalMapSRV);
}

void SkinModel::LoadSpecularMap(const wchar_t* filePath)
{
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), filePath, 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_specularMapSRV);
}

void SkinModel::LoadAoMap(const wchar_t* filePath)
{
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), filePath, 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_aoMapSRV);
}