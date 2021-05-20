#pragma once

#include "Skeleton.h"
#include "SkinModelEffect.h"
#include "../gameObject/GameObjectManager.h"
#include "../option/OptionData.h"
#include "../culling/Aabb.h"
#include "../culling/ObjectFrustumCulling.h"
/*!
*@brief	FBX�̏�����B
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};
const int NUM_DIRECTION_LIG = 4;
const int DITHERING_KILL_PIXEL = 63;
/*!
*@brief	�f�B���N�V�������C�g�B
*/
struct SDirectionLight {
	CVector4 direction[NUM_DIRECTION_LIG];		//���C�g�̕����B
	CVector4 color[NUM_DIRECTION_LIG];			//���C�g�̃J���[�B
	CVector3			eyePos;				//���_�̍��W�B
	float				specPow;			//���ʔ��˂̍i��B
	CVector4			ambient;
	CVector3			eyeDir;
	int isRimLight;	
	float				brightnessPow = 1.0f;	//��̖��邳
	float				ligBrightness = 1.0f;	//���邳
	int isToon;
};
//�|�C���g���C�g�\���́B
struct SPointLight {
	CVector3 position;	//���W�B
	float pad0;			//�p�f�B���O
	CVector3 color;		//���C�g�̃J���[
	float range;		//���C�g�̉e����^����͈́B
};
/*!
*@brief	�X�L�����f���N���X�B
*/
class SkinModel
{
public:
	/// <summary>
	/// �������C�g���I�t�ɂ���
	/// </summary>
	void RimLightOff()
	{
		m_dirLight.isRimLight = 0;
		m_isRim = true;
	}
	/// <summary>
	/// �g�D�[�����I�t�ɂ���
	/// </summary>
	void ToonOff()
	{
		m_dirLight.isToon = 1;
		m_isToon = true;
	}
	/// <summary>
	/// �f�B�U�����O���I���ɂ���
	/// </summary>
	void DitheringOn()
	{
		m_isDithering = true;
	}
	/// <summary>
	/// �f�B�U�����O���I�t�ɂ���
	/// </summary>
	void DitheringOff()
	{
		m_isDithering = false;
	}
	/// <summary>
	/// �V���h�E���V�[�o�[���I�t�ɂ���
	/// </summary>
	void ShadowReciverOff()
	{
		m_isShadowReciver = true;
	}
	/// <summary>
	/// �f�B���N�V�������C�g�̔ԍ��ƕ����̐ݒ�
	/// </summary>
	void SetDligDir(int num, float x, float y, float z)
	{
		CVector4 dir = { x,y,z,1.0f };
		dir.Normalize();
		m_dirLight.direction[num] = dir;
	}
	/// <summary>
	/// �f�B���N�V�������C�g�̐F�i���邳�j�̐ݒ�
	/// </summary>
	/// <param name="color">�F�i���邳�j</param>
	void SetDligColor(int num,float color)
	{
		m_color[num] = color;
	}
	/// <summary>
	/// ��̖��邳�ݒ�
	/// </summary>
	/// <param name="lig">��̖��邳</param>
	void SetSkyBrightness(float lig)
	{
		m_dirLight.ligBrightness = lig;
	}
	/// <summary>
	/// �A���r�G���g���C�g�̐ݒ�
	/// </summary>
	/// <param name="ambient">�A���r�G���g���C�g</param>
	void SetAmbient(const CVector4& ambient)
	{
		m_dirLight.ambient = ambient;
	}
	/// <summary>
	/// �X�y�L�����̐ݒ�
	/// </summary>
	/// <param name="specPow">�X�y�L�����̍i��l</param>
	void SetDligSpecPow(float specPow)
	{
		m_dirLight.specPow = specPow;
	}
	/// <summary>
	/// ��̖��邳�̐ݒ�
	/// </summary>
	/// <param name="brightPow">���邳�̋���</param>
	void SetBrightnessPow(float brightPow)
	{
		m_dirLight.brightnessPow = brightPow;
	}
	/// <summary>
	/// �f�B�U�����O�����X�ɋ��߂�
	/// </summary>
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
	/// <summary>
	/// �f�B�U�����O�̋����̎擾
	/// </summary>
	/// <returns>�f�B�U�����O�̋���</returns>
	int GetDitheringPow() const
	{
		return m_ditheringPow;
	}
	/// <summary>
	/// �f�B�U�����O�����̐ݒ�
	/// </summary>
	/// <param name="len">����</param>
	void SetDitheringLength(float len)
	{
		m_len = len;
	}
	/// <summary>
	/// ������J�����O�t���O
	/// </summary>
	/// <param name="flag">�t���O</param>
	void SetFrustumCullingFlag(bool flag) 
	{
		m_isFrustumCulling = flag;
	}
	//���b�V�������������Ƃ��̃R�[���o�b�N�֐��B
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~SkinModel();
	/*!
	*@brief	�������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*@param[in] enFbxUpAxis		fbx�̏㎲�B�f�t�H���g��enFbxUpAxisZ�B
	*/
	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	���f�������[���h���W�n�ɕϊ����邽�߂̃��[���h�s����X�V����B
	*@param[in]	position	���f���̍��W�B
	*@param[in]	rotation	���f���̉�]�B
	*@param[in]	scale		���f���̊g�嗦�B
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
	/*!
	*@brief	�{�[���������B
	*@param[in]		boneName	�{�[���̖��O�B
	*@return	���������{�[���B������Ȃ������ꍇ��nullptr��Ԃ��܂��B
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}
	/*!
	*@brief	���f����`��B
	*@param[in]	viewMatrix		�J�����s��B
	*  ���[���h���W�n��3D���f�����J�������W�n�ɕϊ�����s��ł��B
	*@param[in]	projMatrix		�v���W�F�N�V�����s��B
	*  �J�������W�n��3D���f�����X�N���[�����W�n�ɕϊ�����s��ł��B
	* param [in]renderMode
	*  �`��X�e�b�v�B0�Ȃ�ʏ�`��A1�Ȃ�V���G�b�g�`��B
	*/
	void Draw( CMatrix viewMatrix, CMatrix projMatrix, EnRenderMode renderMode);
	/*!
	*@brief	�X�P���g���̎擾�B
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}
	/*!
	*@brief	���b�V������������B
	*@param[in] onFindMesh		���b�V�������������Ƃ��̃R�[���o�b�N�֐�
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
	*@brief	SRV�̃��W�X�^�ԍ��B
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<�f�B�t���[�Y�e�N�X�`���B
		enSkinModelSRVReg_BoneMatrix,				//!<�{�[���s��B
	};
	/*!
	*@brief	�@���}�b�v�̃��[�h
	*@param[in]	filePath		���[�h����dds�t�@�C���̃t�@�C���p�X�B
	*/
	void LoadNormalMap(const wchar_t* filePath);
	/*!
	*@brief	�X�y�L�����}�b�v�̃��[�h
	*@param[in]	filePath		���[�h����dds�t�@�C���̃t�@�C���p�X�B
	*/
	void LoadSpecularMap(const wchar_t* filePath);
	/*!
	*@brief	AO�}�b�v�̃��[�h
	*@param[in]	filePath		���[�h����dds�t�@�C���̃t�@�C���p�X�B
	*/
	void LoadAoMap(const wchar_t* filePath);
private:
	/*!
	*@brief	�T���v���X�e�[�g�̏������B
	*/
	void InitSamplerState();
	/*!
	*@brief	�萔�o�b�t�@�̍쐬�B
	*/
	void InitConstantBuffer();
	/*!
	*@brief	�X�P���g���̏������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*/
	void InitSkeleton(const wchar_t* filePath);
	//�f�B���N�V�������C�g�̏������B
	void InitDirectionLight();
private:
	//�萔�o�b�t�@�B
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
		CMatrix mLightView;	//���C�g�r���[�s��B
		CMatrix mLightProj;	//���C�g�v���W�F�N�V�����s��B
		int isShadowReciever;	//�V���h�E���V�[�o�[�t���O�B
		int isHasNormalMap;		//�@���}�b�v��ێ����Ă���H
		int isHasSpecuraMap;	//�X�y�L�����}�b�v��ێ����Ă���H
		int isHasAoMap;			//AO�}�b�v��ێ����Ă���H
		int isDithering;		//�f�B�U�����O�H	
		int ditheringPow;
	};
	int m_ditheringPow = DITHERING_KILL_PIXEL;			//�f�B�U�����O�ŃL������s�N�Z��
	bool m_isDecDithe = false;
	bool m_isRim = false;					//�������C�g���邩
	bool m_isToon = false;					//�g�D�[�����邩
	bool m_isDithering = false;				//�f�B�U�����O�H
	bool m_isShadowReciver = false;			//�V���h�E���V�[�o�[�ɂ��邩
	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBX�̏�����B
	ID3D11Buffer*		m_cb = nullptr;					//!<�萔�o�b�t�@�B
	ID3D11Buffer*		m_lightCb = nullptr;				//!<���C�g�p�̒萔�o�b�t�@�B	
	ID3D11Buffer*		m_pointLightCb = nullptr;			//!<�|�C���g���C�g�p�̒萔�o�b�t�@�B
	SDirectionLight		m_dirLight;							//!<�f�B���N�V�������C�g�B
	SPointLight			m_pointLight;						//!<�|�C���g���C�g�B
	Skeleton			m_skeleton;						//!<�X�P���g���B
	CMatrix				m_worldMatrix;					//!<���[���h�s��B
	DirectX::Model*		m_modelDx;						//!<DirectXTK���񋟂��郂�f���N���X�B
	ID3D11SamplerState* m_samplerState = nullptr;		//!<�T���v���X�e�[�g�B
	ID3D11ShaderResourceView* m_normalMapSRV = nullptr;		//�@���}�b�v��SRV
	ID3D11ShaderResourceView* m_specularMapSRV = nullptr;	//�X�y�L�����}�b�v��SRV
	ID3D11ShaderResourceView* m_aoMapSRV = nullptr;			//AO�}�b�v��SRV
	Aabb m_aabb;										//aabb
	ObjectFrustumCulling m_frustumCulling;				//������J�����O
	bool m_isFrustumCulling = true;					//������J�����O���邩�H
	OptionData* m_optionData = nullptr;					//�I�v�V�����f�[�^
	CVector3 m_pos = CVector3::Zero();					//���W
	float m_len = 80.0f;								//����
	float m_color[4] = { 0.0f };						//�F
};