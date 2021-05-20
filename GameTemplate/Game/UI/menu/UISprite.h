#pragma once
#include "IUIObject.h"
#include "UIData.h"
class UISprite final : public IUIObject
{
public:
	UISprite();
	~UISprite();
	/*!
	*@brief �X�V
	*/
	void Update() override;
	/*!
	*@brief 2D�`��
	*/
	void Draw2D() override;
	/*!
	* enum EnLightBar
	*�@���C�g�����o�[
	*/
	enum EnLightBar {
		enLightBar_r,				//R
		enLightBar_g,				//G
		enLightBar_b,				//B
		enLightBar_brightness,		//���邳
		enLightBar_skyBrightness,	//��̖��邳
		enLightBar_Num				//��
	};
	/*!
	* enum EnBloomBar
	*	�u���[�������o�[
	*/
	enum EnBloomBar {
		enBloomBar_lum,				//�P�x
		enBloomBar_pow,				//����
		enBloomBar_Num				//��
	};

private:
	/// <summary>
	/// �������������
	/// </summary>
	void Init();
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// ���m�N������
	/// </summary>
	void MonochromeControl();
	/*!
	*@brief		�X�e�[�g�ɂ�郂�m�N������
	���̃X�e�[�g���I������Ă����烂�m�N�������@����ȊO�̓��m�N��
	*@param[in]	�X�e�[�g
	*@param[in]	�X�e�[�g�i�摜�j�̐�
	*@param[in]	���m�N���ɂ���摜
	*/
	void MonochromeUpdate(int state, int en_Num, Sprite* sprite);
	UIData* m_uiData = nullptr;								//UI�Ł[���@
	CVector2 m_moveSpeed;									//�ړ����x

	Sprite m_backSprite;									//�w�i�X�v���C�g
	CVector3 m_backSpritePosition = CVector3::Zero();		//�w�i�ʒu
	CQuaternion m_rotation = CQuaternion::Identity();		//��]
	CVector3 m_backSpriteScale = CVector3::One();			//�w�i�X�P�[��

	Sprite m_objSprite[UIData::Obj::enObj_Num];							//�I�u�W�F�N�g�X�v���C�g
	CVector3 m_objSpritePosition[UIData::Obj::enObj_Num];				//�I�u�W�F�N�g�ʒu
	CVector3 m_objSpriteScale = CVector3::One();						//�I�u�W�F�N�g�X�P�[��

	Sprite m_gimmickSprite[UIData::Gimmick::enGimmick_Num];					//�M�~�b�N�X�v���C�g
	CVector3 m_gimmickSpritePosition[UIData::Gimmick::enGimmick_Num];		//�M�~�b�N�ʒu
	CVector3 m_gimmickSpriteScale = CVector3::One();						//�M�~�b�N�X�P�[��

	Sprite m_enemySprite[UIData::Enemy::enEnemy_Num];						//�G�X�v���C�g
	CVector3 m_enemySpritePosition[UIData::Enemy::enEnemy_Num];				//�G�ʒu
	CVector3 m_enemySpriteScale = CVector3::One();							//�G�X�P�[��

	Sprite m_lightBarSprite[enLightBar_Num];			//���C�g�����o�[�̃X�v���C�g	
	Sprite m_bloomBarSprite[enBloomBar_Num];			//�u���[�������o�[�̃X�v���C�g
	CVector3 m_lightBarPos[enLightBar_Num];				//���C�g�����o�[�̈ʒu
	CVector3 m_bloomBarPos[enBloomBar_Num];				//�u���[�������o�[�̈ʒu
	CVector3 m_barScale = CVector3::One();				//�����o�[�̊g�嗦
};

