#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelDataManager.h"
#include"SkinModelShaderConst.h"
#include "ShadowMap.h"
namespace
{
	const int DITHERING_POW = 20;	//�f�B�U�����O�̋���
	//�f�B���N�V����
	const CVector4 DLIG_DIRECTION[4] = {
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ -0.707f, -0.707f, 0.0f, 0.0f },
		{ 0.0f, -0.707f, 0.707f, 0.0f },
		{ 1.0f, 0.0f, -1.0f, 0.0f }
	};
	const float SPEC = 0.0f;							//�X�y�L����
	const CVector4 AMBIENT = { 0.1f,0.1f,0.1f,1.0f };	//�A���r�G���g
}
SkinModel::~SkinModel()
{
	if (m_cb != nullptr) {
		//�萔�o�b�t�@������B
		m_cb->Release();
	}
	//���C�g�p�̒萔�o�b�t�@�̉���B
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}
	if (m_samplerState != nullptr) {
		//�T���v���X�e�[�g������B
		m_samplerState->Release();
	}
	//todo �@���}�b�v������B
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
	//�X�P���g���̃f�[�^��ǂݍ��ށB
	InitSkeleton(filePath);

	//�萔�o�b�t�@�̍쐬�B
	InitConstantBuffer();

	//�T���v���X�e�[�g�̏������B
	InitSamplerState();

	//�f�B���N�V�������C�g�̏������B
	InitDirectionLight();

	//SkinModelDataManager���g�p����CMO�t�@�C���̃��[�h�B
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton);

	m_enFbxUpAxis = enFbxUpAxis;
	FindMesh([&](auto& mesh) {
		auto vMax = CVector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		auto vMin = CVector3(FLT_MAX, FLT_MAX, FLT_MAX);
		auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
		{
			D3D11_MAPPED_SUBRESOURCE subresource;
			auto hr = deviceContext->Map(mesh->vertexBuffer.Get(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
			if (FAILED(hr)) {
				return;
			}
			D3D11_BUFFER_DESC bufferDesc;
			mesh->vertexBuffer->GetDesc(&bufferDesc);
			auto vertexCount = (int)(bufferDesc.ByteWidth / mesh->vertexStride);
			auto pData = reinterpret_cast<char*>(subresource.pData);
			for (int i = 0; i < vertexCount; i++) {
				auto pos = *reinterpret_cast<CVector3*>(pData);
				vMax.Max(pos);
				vMin.Min(pos);
				//���̒��_�ցB
				pData += mesh->vertexStride;
			}
			//���_�o�b�t�@���A�����b�N
			deviceContext->Unmap(mesh->vertexBuffer.Get(), 0);
		}

		auto halfSize = (vMax - vMin) * 0.5f;
		m_aabb.Init(halfSize);
		});

	if (m_isFrustumCulling) {
		FindMesh([&](auto& mesh) {
			auto vMax = CVector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
			auto vMin = CVector3(FLT_MAX, FLT_MAX, FLT_MAX);
			auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
			{
				D3D11_MAPPED_SUBRESOURCE subresource;
				auto hr = deviceContext->Map(mesh->vertexBuffer.Get(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
				if (FAILED(hr)) {
					return;
				}
				D3D11_BUFFER_DESC bufferDesc;
				mesh->vertexBuffer->GetDesc(&bufferDesc);
				auto vertexCount = (int)(bufferDesc.ByteWidth / mesh->vertexStride);
				auto pData = reinterpret_cast<char*>(subresource.pData);
				for (int i = 0; i < vertexCount; i++) {
					auto pos = *reinterpret_cast<CVector3*>(pData);
					vMax.Max(pos);
					vMin.Min(pos);
					//���̒��_�ցB
					pData += mesh->vertexStride;
				}
				//���_�o�b�t�@���A�����b�N
				deviceContext->Unmap(mesh->vertexBuffer.Get(), 0);
			}

			auto halfSize = (vMax - vMin) * 0.5f;
			m_aabb.Init(halfSize);
			});
	}
}
//�f�B���N�V�������C�g�̏������B
void SkinModel::InitDirectionLight()
{
	m_optionData = &GetOptionData();
	m_dirLight.direction[0] = DLIG_DIRECTION[0];
	m_dirLight.color[0] = m_optionData->GetColor();

	m_dirLight.direction[1] = DLIG_DIRECTION[1];
	m_dirLight.color[1] = m_optionData->GetColor();

	m_dirLight.direction[2] = DLIG_DIRECTION[2];
	m_dirLight.color[2] = m_optionData->GetColor();

	m_dirLight.direction[3] = DLIG_DIRECTION[3];
	m_dirLight.direction[3].Normalize();
	m_dirLight.color[3] = m_optionData->GetColor();
	
	m_dirLight.specPow = SPEC;
	m_dirLight.ambient = AMBIENT;
}
void SkinModel::InitSkeleton(const wchar_t* filePath)
{
	//�X�P���g���̃f�[�^��ǂݍ��ށB
	//cmo�t�@�C���̊g���q��tks�ɕύX����B
	std::wstring skeletonFilePath = filePath;
	//�����񂩂�.cmo�t�@�C���n�܂�ꏊ�������B
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmo�t�@�C����.tks�ɒu��������B
	skeletonFilePath.replace(pos, 4, L".tks");
	//tks�t�@�C�������[�h����B
	bool result = m_skeleton.Load(skeletonFilePath.c_str());
	if (result == false) {
		//�X�P���g�����ǂݍ��݂Ɏ��s�����B
		//�A�j���[�V�������Ȃ����f���́A�X�P���g�����s�v�Ȃ̂�
		//�ǂݍ��݂Ɏ��s���邱�Ƃ͂���̂ŁA���O�o�͂����ɂ��Ă����B
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tks�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B%ls\n", skeletonFilePath.c_str());
		OutputDebugStringA(message);
#endif
	}
}
void SkinModel::InitConstantBuffer()
{
	//�쐬����o�b�t�@�̃T�C�Y��sizeof���Z�q�ŋ��߂�B
	int bufferSize = sizeof(SVSConstantBuffer);
	//�ǂ�ȃo�b�t�@���쐬����̂�������bufferDesc�ɐݒ肷��B
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//�O�ŃN���A�B
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//�o�b�t�@�őz�肳��Ă���A�ǂݍ��݂���я������ݕ��@�B
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//�o�b�t�@��16�o�C�g�A���C�����g�ɂȂ��Ă���K�v������B
																//�A���C�����g���ā��o�b�t�@�̃T�C�Y��16�̔{���Ƃ������Ƃł��B
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//�o�b�t�@���ǂ̂悤�ȃp�C�v���C���Ƀo�C���h���邩���w�肷��B
																//�萔�o�b�t�@�Ƀo�C���h����̂ŁAD3D11_BIND_CONSTANT_BUFFER���w�肷��B
	bufferDesc.CPUAccessFlags = 0;								//CPU �A�N�Z�X�̃t���O�ł��B
																//CPU�A�N�Z�X���s�v�ȏꍇ��0�B
	//�쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);
	//�����āA���C�g�p�̒萔�o�b�t�@���쐬�B
	//�쐬����o�b�t�@�̃T�C�Y��ύX���邾���B
	bufferSize = sizeof(SDirectionLight);
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);
}
void SkinModel::InitSamplerState()
{
	//�e�N�X�`���̃T���v�����O���@���w�肷�邽�߂̃T���v���X�e�[�g���쐬�B
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
	m_pos = position;
	//3dsMax�Ǝ������킹�邽�߂̃o�C�A�X�B
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;
	//���s�ړ��s����쐬����B
	transMatrix.MakeTranslation(position);
	//��]�s����쐬����B
	rotMatrix.MakeRotationFromQuaternion(rotation);
	rotMatrix.Mul(mBias, rotMatrix);
	//�g��s����쐬����B
	scaleMatrix.MakeScaling(scale);
	//���[���h�s����쐬����B
	//�g��~��]�~���s�ړ��̏��Ԃŏ�Z����悤�ɁI
	//���Ԃ��ԈႦ���猋�ʂ��ς���B
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);
	//�X�P���g���̍X�V�B
	m_skeleton.Update(m_worldMatrix);
}
void SkinModel::Draw(CMatrix viewMatrix, CMatrix projMatrix, EnRenderMode renderMode)
{
	//������J�����O	
	if (m_isFrustumCulling) {
		m_aabb.Update(m_worldMatrix);
		m_frustumCulling.Execute(m_aabb);
		if (m_frustumCulling.IsCulling()) {
			return;
		}
	}

	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	//�萔�o�b�t�@�̓��e���X�V�B
	SVSConstantBuffer vsCb;
	vsCb.mWorld = m_worldMatrix;
	vsCb.mProj = projMatrix;
	vsCb.mView = viewMatrix;
	vsCb.mLightView = g_shadowMap->GetLighViewMatrix();	//���C�g�r���[�s��B
	vsCb.mLightProj = g_shadowMap->GetLightProjMatrix();	//���C�g�v���W�F�N�V�����s��B
	if (!m_isShadowReciver) {
		vsCb.isShadowReciever = true;	//�V���h�E���V�[�o�[�t���O�B
	}
	else {
		vsCb.isShadowReciever = false;
	}
	//todo �@���}�b�v���g�p���邩�ǂ����̃t���O�𑗂�B
	if (m_normalMapSRV != nullptr) {
		vsCb.isHasNormalMap = true;
	}
	else {
		vsCb.isHasNormalMap = false;
	}
	//�X�y�L�����}�b�v���g�p���邩�ǂ����̃t���O�𑗂�B
	if (m_specularMapSRV != nullptr) {
		vsCb.isHasSpecuraMap = true;
	}
	else {
		vsCb.isHasSpecuraMap = false;
	}
	//AO�}�b�v���g�p���邩�ǂ����̃t���O�𑗂�B
	if (m_aoMapSRV != nullptr) {
		vsCb.isHasAoMap = true;
	}
	else {
		vsCb.isHasAoMap = false;
	}
	//�f�B�U�����O���g�p���邩�ǂ����̃t���O�𑗂�B
	if (m_isDithering) {
		vsCb.isDithering = true;
	}
	else {
		vsCb.isDithering = false;
	}
	//�f�B�U�����O���Ă�����
	if (m_isDecDithe) {
		vsCb.ditheringPow = m_ditheringPow;
	}
	else {
		vsCb.ditheringPow = DITHERING_POW;
	}
	//�ȈՓI�E�J�������߂��ƃf�B�U�����O
	auto vec = g_camera3D.GetPosition() - m_pos;
	auto len = vec.Length();
	if (len <= m_len) {
		vsCb.isDithering = true;
		vsCb.ditheringPow = DITHERING_POW;
	}
	d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &vsCb, 0, 0);
	//���_���X�V
	//���_��ݒ�B
	m_optionData = &GetOptionData();
	m_dirLight.eyePos = g_camera3D.GetPosition();
	CVector3 eyeDir = g_camera3D.GetTarget() - g_camera3D.GetPosition();
	eyeDir.Normalize();
	m_dirLight.eyeDir = eyeDir;
	if (!m_isRim) {
		m_dirLight.isRimLight = true;
	}
	if (!m_isToon) {
		m_dirLight.isToon = false;
	}
	//�I�v�V��������̐ݒ���Z
	for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
		m_dirLight.color[i].x = m_optionData->GetColorR();
		m_dirLight.color[i].y = m_optionData->GetColorG();
		m_dirLight.color[i].z = m_optionData->GetColorB();
	}
	//�F�ݒ肳��Ă�������Z
	for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
		m_dirLight.color[i].x += m_color[i];
		m_dirLight.color[i].y += m_color[i];
		m_dirLight.color[i].z += m_color[i];
	}
	m_dirLight.ligBrightness = m_optionData->GetBrightness();
	m_dirLight.brightnessPow = m_optionData->GetSkyBrightness();
	//���C�g�p�̒萔�o�b�t�@���X�V�B
	d3dDeviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_dirLight, 0, 0);
	//�萔�o�b�t�@��GPU�ɓ]���B
	d3dDeviceContext->VSSetConstantBuffers(enSkinModelCBReg_VSPS, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(enSkinModelCBReg_VSPS, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(enSkinModelCBReg_Light, 1, &m_lightCb);
	//�T���v���X�e�[�g��ݒ�B
	d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//�{�[���s���GPU�ɓ]���B
	m_skeleton.SendBoneMatrixArrayToGPU();
	//�G�t�F�N�g�ɃN�G�����s���B
	m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
		auto modelMaterial = reinterpret_cast<SkinModelEffect*>(material);
		modelMaterial->SetRenderMode(renderMode);
		});
	if (m_normalMapSRV != nullptr) {
		//�@���}�b�v���ݒ肳��Ă���������W�X�^t2�ɐݒ肷��B
		d3dDeviceContext->PSSetShaderResources(2, 1, &m_normalMapSRV);
	}
	if (m_specularMapSRV != nullptr) {
		//�X�y�L�����}�b�v���ݒ肳��Ă����烌�W�X�^t4�ɐݒ肷��B
		d3dDeviceContext->PSSetShaderResources(4, 1, &m_specularMapSRV);
	}
	if (m_aoMapSRV != nullptr) {
		//AO�}�b�v���ݒ肳��Ă����烌�W�X�^t4�ɐݒ肷��B
		d3dDeviceContext->PSSetShaderResources(5, 1, &m_aoMapSRV);
	}
	//�`��B
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