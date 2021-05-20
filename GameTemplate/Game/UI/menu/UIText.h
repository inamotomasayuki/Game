#pragma once
#include "IUIObject.h"
#include "../../graphics/2D/Font.h"
#include "UIData.h"
class UIText : public IUIObject
{
public:
	UIText();
	~UIText();
	/*!
	*@brief �X�V
	*/
	void Update() override;
	/*!
	*@brief �t�H���g�`��
	*/
	void DrawFont() override;
protected:
	/*!
	*@brief	�e�L�X�g�̐F�̍X�V
	*@param[in]	color			�ύX����F [ �z�� ]
	*@param[in]	array_Num		�z��̐��@�f�t�H���g�P
	*@param[in] Current_Num		�ύX�������v�f
	*@param[in] setColor0		�w�肵���ύX�������v�f�ɑ΂���F
	*@param[in] setColor1		����ȊO�̗v�f�̐F
	*/
	void ColorUpdate(
		CVector4 color[],
		int array_Num,
		int Current_Num,
		const CVector4& setColor0,
		const CVector4& setColor1
	);
	/*!
	*@brief	�e�L�X�g�̐F�̍X�V
	*@param[in]	color			�ύX����F [ �z�� ]
	*@param[in]	array_Num		�z��̐��@�f�t�H���g�P	
	*@param[in] Current_Num		�ύX�������v�f
	*@param[in] setColor0		�w�肵���ύX�������v�f�ɑ΂���F
	*@param[in] setColor1		����ȊO�̗v�f�̐F
	*/
	void ColorUpdate(
		CVector4 color[],
		int array_Num,
		int Current_Num,
		const CVector4 setColor0[],
		const CVector4& setColor1
	);

	/*!
	*@brief�@�f�t�H���g�J���[�ɐݒ�
	*@param[in] color�@�@�@�@�@�ύX����F�@[ �z�� ]
	*@param[in] defaultcolor�@�@�f�t�H���g�J���[
	*@param[in]	array_Num�@�@�z��v�f���@�f�t�H���g�P
	*/
	void DefaultColor(
		CVector4 color[],
		const CVector4& defaultColor,
		int array_Num = 1
	);
	/*!
	*@brief�@�ړ�����
	*@param[in] movePos�@�ʒu�@[ �z�� ]
	*@param[in] en_Num�@�z��v�f��
	*/
	void MovePosUpdate(CVector2 movePos[], int en_Num = 1);
	/*!
	*@brief�@�I���A�C�R���̈ʒu�ݒ�
	*@param[in] setPos�@�I���ʒu�@[ �z�� ]
	*@param[in] CurrentNum  �I�𒆂̗v�f
	*@param[in] arrayNum�@�z��v�f��
	*@param[in] posX �ݒ肷��X���W
	*@param[in] posY �ݒ肷��Y���W
	*/
	void SetSelectPos(CVector2 setPos[], int CurrentNum = 0, int arrayNum = 1, float posX = 0.0f, float posY = 0.0f);
private:
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// �F����
	/// </summary>
	void ColorControl();
	/*!
	*@brief �I���A�C�R������
	*/
	void SelectControl();
protected:
	UIData* m_uiData = nullptr;					//UI�f�[�^
	Font m_font;								//�t�H���g
	wchar_t m_titleText[256];									//�^�C�g���e�L�X�g
	CVector2 m_titleFontPosition = CVector2::Zero();			//�^�C�g���̈ʒu
	CVector4 m_titleFontColor = CVector4::White();				//�^�C�g���̐F

	CVector2 m_explanationTextPos = CVector2::Zero();

	CVector2 m_objTextPosition[UIData::Obj::enObj_Num];			//�I�u�W�F�N�g�e�L�X�g�̈ʒu
	CVector4 m_objTextColor[UIData::Obj::enObj_Num];			//�I�u�W�F�N�g�e�L�X�g�̐F

	CVector2 m_gimmickTextPosition[UIData::Gimmick::enGimmick_Num];		//�M�~�b�N�e�L�X�g�̈ʒu
	CVector4 m_gimmickTextColor[UIData::Gimmick::enGimmick_Num];		//�M�~�b�N�e�L�X�g�̐F

	CVector2 m_enemyTextPosition[UIData::Enemy::enEnemy_Num];			//�G�e�L�X�g�̈ʒu
	CVector4 m_enemyTextColor[UIData::Enemy::enEnemy_Num];				//�G�e�L�X�g�̐F

	CVector2 m_bloomTextPosition[UIData::Bloom::enBloom_Num];			//�u���[���e�L�X�g�̈ʒu
	CVector4 m_bloomTextColor[UIData::Bloom::enBloom_Num];				//�u���[���e�L�X�g�̐F

	CVector2 m_lightTextPosition[UIData::Light::enLight_Num];			//���C�g�e�L�X�g�̈ʒu
	CVector4 m_lightTextColor[UIData::Light::enLight_Num];				//���C�g�e�L�X�g�̐F

	CVector2 m_lightColorTextPosition[UIData::LightColor::enLightColor_Num];			//���C�g�J���[�e�L�X�g�̈ʒu
	CVector4 m_lightColorTextColor[UIData::LightColor::enLightColor_Num];				//���C�g�J���[�e�L�X�g�̐F

	CVector2 m_textScale = CVector2::One();								//�e�L�X�g�̊g�嗦
	CVector2 m_optionTextScale = CVector2::One();						//�I�v�V�����e�L�X�g�̊g�嗦
	CVector2 m_rgbScale = CVector2::One();								//�q�f�a�̃e�L�X�g�g�嗦

	CVector2 m_objMenuFontPosition[UIData::ObjMenu::enObjMenu_Num];		//�I�u�W�F�N�g���j���[�e�L�X�g�̈ʒu
	CVector4 m_objMenuFontColor[UIData::ObjMenu::enObjMenu_Num];		//�I�u�W�F�N�g���j���[�e�L�X�g�̐F
	CVector2 m_objMenuFontScale = CVector2::One();						//�I�u�W�F�N�g���j���[�̊g�嗦

	CVector2 m_moveSpeed;												//�ړ����x
	CVector2 m_pos;														//�ʒu
	CVector2 m_scale = CVector2::One() * 0.8f;							//�g�嗦
	OptionData* m_optionData = nullptr;									//�I�v�V�����f�[�^

	CVector2 m_selectPos = CVector2::Zero();						//�I���A�C�R���̈ʒu
	CVector4 m_selectColor = CVector4::White();						//�I���A�C�R���̐F
	CVector2 m_selectScale = CVector2::One();						//�I���A�C�R���̊g�嗦
	float m_selectRotation = 0.0f;									//�I���A�C�R����]
};
