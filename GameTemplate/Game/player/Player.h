#pragma once
#include "character/CharacterController.h"
#include "../gimmick/MoveFloor.h"
#include "../item/Star.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "../stage/BackGround.h"
#include "PlayerWarpState.h"

class JumpFloor;
class Game;

namespace {
	const float GRAVITY = 400.0f;					//�d��
	const float PLAYER_COLLIDER_HIGHT = 100.0f;		//�J�v�Z���R���C�_�[�̍���
	const float PLAYER_COLLIDER_RADIUS = 10.0f;		//�J�v�Z���R���C�_�[�̔��a
}
class Player final : public IGameObject
{
public:
	Player();
	~Player();
	/*
	* @brieef �X�V
	*/
	void Update() override;
	/*
	* @brieef �`��
	*/
	void Draw() override;
	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	const CVector3& GetPositon() const
	{
		return m_position;
	}
	/// <summary>
	/// ��]�̎擾
	/// </summary>
	/// <returns></returns>
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/*!
	*@brief �L�����R���̏�����
	*@param[in]	pos	���W
	*/
	void InitCharaCon(const CVector3& pos)
	{
		//�L�����N�^�[�R���g���[���[
		m_charaCon.Init(
			PLAYER_COLLIDER_RADIUS,			//���a
			PLAYER_COLLIDER_HIGHT,			//����
			pos								//�������W
		);
	}
	/// <summary>
	/// �L�����R�����W�ݒ�
	/// </summary>
	/// <param name="v">���W</param>
	void SetCharaConPos(CVector3 v)
	{
		m_charaCon.SetPosition(v);
		m_position = m_charaCon.GetPosition();
	}
	/// <summary>
	/// ��]�̐ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// �g�嗦�̐ݒ�
	/// </summary>
	/// <param name="scale">�g�嗦</param>
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// �����x�̐ݒ�
	/// </summary>
	/// <param name="addSpeed">�����x</param>
	void SetAddSpeed(const CVector3& addSpeed)
	{
		m_addSpeed = addSpeed;
	}
	/// <summary>
	/// �U�����󂯂Ă邩�ǂ����B
	/// </summary>
	/// <param name="isAttacked">�t���O</param>
	void SetIsAttacked(bool isAttacked)
	{
		m_isAttacked = isAttacked;
	}
	/// <summary>
	/// �U�����󂯂Ă邩�ǂ������擾
	/// </summary>
	/// <returns>�U�����󂯂Ă邩�ǂ����̃t���O</returns>
	bool GetIsAttacked() const
	{
		return m_isAttacked;
	}
	/// <summary>
	/// �W�����v���Ă邩�ǂ���
	/// </summary>
	/// <param name="jumpFlag">�W�����v�t���O</param>
	void SetJumpFlag(bool jumpFlag)
	{
		m_jumpFlag = jumpFlag;
		m_jumpSpeed = 4000.0f;
		m_gravity = GRAVITY;
		m_se[enSE_jump]->Play(false);
	}
	/// <summary>
	/// �������̑��x�̐ݒ�
	/// </summary>
	/// <param name="floorSpeed">�������̑��x</param>
	void SetFloorSpeed(const CVector3& floorSpeed)
	{
		m_floorSpeed = floorSpeed;
	}
	/// <summary>
	/// �X�L�����f���̎擾
	/// </summary>
	/// <returns>�X�L�����f��</returns>
	SkinModel* GetSkinModel()
	{
		return &m_skinModelCircle;
	}
	/// <summary>
	/// �ړ����x�̎擾
	/// </summary>
	/// <returns>�ړ����x</returns>
	const CVector3& GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
	/// <summary>
	/// �q�b�v�h���b�v��
	/// </summary>
	/// <returns></returns>
	bool IsHipDrop() const
	{
		return m_isHipDrop;
	}
	/// <summary>
	/// �_���[�W����炵�����ݒ�
	/// </summary>
	/// <param name="SE">�炵����</param>
	void SetIsDamageSE(bool SE)
	{
		m_isDamageSE = SE;
	}
	/// <summary>
	/// �A�C�e���擾�H
	/// </summary>
	/// <returns>�t���O</returns>
	bool GetisItem() const
	{
		return m_isItem;
	}
	/// <summary>
	/// �{�^���X�e�[�g
	/// </summary>
	enum EnButtonState {
		enButtonState_0,	//�{�^���O
		enButtonState_1,	//�{�^���P
		enButtonState_Num	//��
	};
	/// <summary>
	/// �{�^���X�e�[�g�擾
	/// </summary>
	/// <returns>�{�^���X�e�[�g</returns>
	int GetButtonState() const
	{
		return m_buttonState;
	}
	/// <summary>
	/// �{�^�������ĂȂ��ݒ�
	/// </summary>
	void SetIsButtonFalse()
	{
		m_isButton = false;
	}
	/// <summary>
	/// �n�ʂɂ��邩
	/// </summary>
	/// <returns>�n�ʂɂ��邩</returns>
	bool IsOnGround() const
	{
		if (m_charaCon.IsOnGround()) {
			return true;
		}
		else {
			return false;
		}
	}
	/// <summary>
	/// �{�b�N�X�q�b�v�h���b�v������
	/// </summary>
	bool IsHipDropBox() const
	{
		return m_isHipDropBox;
	}
	/// <summary>
	/// �������_���[�W�󂯂�
	/// </summary>
	void SetIsAchichi()
	{
		m_jumpSpeed = 3500.0f;
		m_jumpFlag = true;
		m_isAchichi = true;
	}
	/// <summary>
	/// ���������x�N�g��
	/// </summary>
	/// <param name="vec">�x�N�g��</param>
	void SetAchichiVec(const CVector3& vec)
	{
		m_achichiVec = vec;
	}
protected:
	bool IsInputJump() const
	{
		return g_pad[0].IsTrigger(enButtonA);
	}
	bool IsInputDash() const
	{
		return g_pad[0].IsPress(enButtonB);
	}
	bool IsInputFireBall() const
	{
		return g_pad[0].IsTrigger(enButtonRB1);
	}
	bool IsInputHipDrop() const
	{
		return g_pad[0].IsTrigger(enButtonRB2);
	}
	bool IsInputMenu() const
	{
		return g_pad[0].IsTrigger(enButtonStart);
	}
	float GetInputLStickXF() const
	{
		return g_pad[0].GetLStickXF();
	}
	float GetInputLStickYF() const
	{
		return g_pad[0].GetLStickYF();
	}
private:
	void Playing();
	void HipDrop();
	void Damage();
	void FireDamage();
	void GameClear();
	void GameOver();
	/// <summary>
	/// �J�������l�������X�e�B�b�N�ł̈ړ�
	/// </summary>
	void PadMove();
	/// <summary>
	/// �v���C���[�̉�]
	/// </summary>
	//void Rotation();
	/// <summary>
	/// �t�@�C�A�{�[������
	/// </summary>
	void FireBallGenerate();
	/// <summary>
	/// �A�j���[�V�����N���b�v�̃��[�h
	/// ���[�v�t���O�ݒ�
	/// </summary>
	void InitAnimationClip();
	/// <summary>
	/// �A�j���[�V�����R���g���[���[
	/// </summary>
	//void AnimationController();
	/// <summary>
	/// �v���C���[�Ƒ��̃S�[�X�g�Ƃ̐ڐG����
	/// </summary>
	void GhostContact();
	/// <summary>
	/// �T�E���h�̏�����
	/// </summary>
	void InitSound();
	/// <summary>
	/// �T�E���h�Đ�
	/// </summary>
	void SoundPlay();
private:
	SkinModel m_skinModel;								//�X�L�����f���B
	SkinModel m_skinModelCircle;						//�~�p�X�L�����f��
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[
	CVector3 m_position = CVector3::Zero();				//�ʒu
	CVector3 m_circlePos = CVector3::Zero();			//�~�̈ʒu
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x
	CVector3 m_addSpeed = CVector3::Zero();				//�����x
	CQuaternion m_jumpRot = CQuaternion::Identity();	//3�i�W�����v�ڂ̉�]
	CVector3 m_posXZ;									//XZ�x�N�g��
	CVector3 m_floorSpeed = CVector3::Zero();			//���̑��x
	CVector3 m_achichiVec;								//���������x�N�g��
	CVector3 m_achichiMove = CVector3::Zero();			//���������ړ�
	JumpFloor* m_jumpFloor = nullptr;				//�W�����v��
	MoveFloor* m_moveFloor = nullptr;				//������
	BackGround* m_backGround = nullptr;				//�w�i
	Game* m_game = nullptr;							//�Q�[��
	Star* m_star = nullptr;							//��
	PlayerWarpState m_playerWarpState;
	enum EnState {
		enState_Playing,
		enState_HipDrop,
		enState_GetStar,
		enState_Damage,
		enState_FireDamage,
		enState_GameClear,
		enState_GameOver,
		enState_Warp
	};
	EnState m_currentState = enState_Playing;
	enum EnAnimationClip {
		enAnimationClip_idle,	//�ҋ@�A�j���[�V�����B
		enAnimationClip_run,	//����A�j���[�V����
		enAnimationClip_jump,	//�W�����v�A�j���[�V�����B
		enAnimationClip_damage,	//�_���[�W�A�j���[�V����
		enAnimationClip_walk,	//�����A�j���[�V����
		enAnimationClip_down,	//�_�E���A�j���[�V����
		enAnimationClip_clear,	//�N���A�A�j���[�V����
		enAnimationClip_Num		//�A�j���[�V�����N���b�v�̐��B
	};
	AnimationClip m_animClips[enAnimationClip_Num];		//�A�j���[�V�����N���b�v�B
	Animation m_animation;								//�A�j���[�V����
	enum EnSE {
		enSE_jump,		//�W�����v��
		enSE_jumpFloor,	//�W�����v����
		enSE_walk,		//���s��
		enSE_dash,		//�_�b�V����
		enSE_damage,	//�_���[�W��
		enSE_kyodaika,	//���剻
		enSE_awawaVoice,//������
		enSE_Num		//SE�̐�
	};
	CSoundSource* m_se[enSE_Num];	//���ʉ�[SE�̐���]	
private:
	int m_fireBallTimer = 0;		//�t�@�C�A�{�[�������^�C�}�[
	int m_flashingTimer = 0;		//�_�Ń^�C�}�[
	int m_threeStep = 0;			//3�i�W�����v�J�E���g
	int m_timer = 0;				//�^�C�}�[ �P�ʁF�b
	int m_hipDropTimer = 0;			//�q�b�v�h���b�v
	int m_threeStepRotTimer = 0;	//�O�i�ڃW�����v��]
	int m_buttonState = 0;			//�{�^���X�e�[�g
	int m_waitTimer = 0;			//�U�����ꂽ���̑҂�����
	int m_achichiTimer = 0;			//����������
	float m_jumpSpeed;				//�W�����v���x
	float m_rotSpeed = 0.0f;		//��]���x
	float angle = 0.0f;				//�p�x
	float m_gravity = 0.0f;			//�d��
	bool m_isAttacked = false;		//�U�����󂯂Ă邩�ǂ���
	bool m_jumpFlag = false;		//�W�����v���Ă邩�ǂ���
	bool m_contactFloor = false;	//���ƐڐG���Ă邩�ǂ���
	bool m_contactJumpFloor = false;//�W�����v���ƐڐG���Ă邩�ǂ���
	bool m_isHipDrop = false;		//�q�b�v�h���b�v��
	bool m_isDamageSE = false;		//�_���[�W���Ȃ炵����
	bool m_hitBox = false;			//���ɂԂ�������
	bool m_isItem = false;			//�A�C�e���������
	bool m_isSetGravity = false;	//�d��
	bool m_isBigSE = false;			//���剻SE
	bool m_isFireBall = false;		//�t�@�C�A�{�[���������H
	bool m_isFlashing = false;		//�_�Ńt���O
	bool m_isButton = false;		//�{�^�������Ă邩
	//bool m_isFall = false;			//�����Ă邩
	bool m_isHipDropBox = false;	//�{�b�N�X���q�b�v�h���b�v������
	bool m_isThreeStepRot = false;	//�R�i�ڃW�����v�̉�]
	bool m_isAchichi = false;		//�������H
	bool m_isVoicePlay = false;		//���������Đ����ꂽ�H	
	bool m_isInitGravity = false;
};
