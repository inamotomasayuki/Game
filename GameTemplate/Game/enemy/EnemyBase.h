#pragma once
#include "../player/Player.h"
#include "sound/SoundSource.h"
#include "../player/FireBall.h"
#include "GameData.h"
#include "../gimmick/Warp.h"
class EnemyBall;
class Game;

namespace {
	const float ENEMY_COLLIDER_RADIUS = 28.0f;		//�J�v�Z���R���C�_�[�̔��a
	const float ENEMY_COLLIDER_HIGHT = 30.0f;		//�J�v�Z���R���C�_�[�̍���
	const float SPRITE_INIT_ROT_DEG = 180.0f;		//�X�v���C�g������]
}

class EnemyBase : public IGameObject
{
public:
	~EnemyBase() {};
	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw() override;
	void Draw2D();
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
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
	/*!
	*@brief �L�����R���̏�����
	*@param[in]	pos	���W
	*/
	void InitCharaCon(const CVector3& pos)
	{
		//�L�����N�^�[�R���g���[���[
		if (g_gameData.GetStageNo() != g_gameData.enStage_One) {
			m_charaCon.Init(
				ENEMY_COLLIDER_RADIUS,			//���a
				ENEMY_COLLIDER_HIGHT,			//����
				pos		//�������W
			);
		}
		else {
			m_charaCon.Init(
				0.0f,	//���a
				0.0f,	//����
				pos		//�������W
			);
		}
	}
	/// <summary>
	/// �X�L�����f���̎擾
	/// </summary>
	/// <returns>�X�L�����f��</returns>
	SkinModel* GetSkinModel() 
	{
		return &m_skinModel;
	}
	/// <summary>
	/// EnemyBall�̃Z�b�g
	/// </summary>
	/// <param name="enemyBall">EnemyBall</param>
	void SetEnemyBall(EnemyBall* enemyBall)
	{
		m_enemyBall = enemyBall;
	}

protected:
	/// <summary>
	/// �U��
	/// </summary>
	virtual void Attack() = 0;
	/// <summary>
	///	���S
	/// </summary>
	/// <param name="score">�X�R�A</param>
	virtual void Death(int score) = 0;
	/// <summary>
	/// ��]
	/// </summary>
	virtual void Rotation() = 0;
	/// <summary>
	/// �v���C���[�ɐL�т�x�N�g��&���K��    
	/// </summary>
	void VectorToPlayer()
	{
		m_v = m_player->GetPositon() - m_position;
		m_len = m_v.Length();
		m_v.Normalize();
	}
	/// <summary>
	/// �p�x�����߂�
	/// </summary>
	void Angle()
	{
		m_naiseki = m_v.Dot(m_up);
		m_angle = acos(m_naiseki);
	}
	/// <summary>
	/// �ʂɓ������Ď���
	/// </summary>
	void DeathEnemyBallContact(int score);
	/// <summary>
	/// �t�@�C�A�[�{�[���Ŏ���
	/// </summary>
	/// <param name="score">�X�R�A</param>
	void DeathFireBall(int score);

	SkinModel m_skinModel;								//�X�L�����f���B		
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CVector3 m_v = CVector3::Zero();					//�x�N�g��
	CVector3 m_up = CVector3::AxisY();					//�����
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x
	Player* m_player = nullptr;				//�v���C���[
	Game* m_game = nullptr;					//�Q�[��
	EnemyBall* m_enemyBall = nullptr;		//�b��
	FireBall* m_fireBall = nullptr;			//�t�@�C�A�[�{�[��
	CSoundSource* m_fumuSE = nullptr;		//���ʉ�
	bool m_isDeath = false;					//����
	int m_timer = 0;						//���S�^�C�}�[�@�P�ʁF�b
	float m_gravity = 0.0f;					//�d��
	float m_len = 0.0f;						//����
	float m_naiseki = 0.0f;					//���ς����߂�
	float m_angle = 0.0f;					//�p�x
	Sprite m_sprite;										//�X�v���C�g
	CQuaternion m_spriteRot = CQuaternion::Identity();		//��]		
	Sprite m_spriteBack;									//�X�v���C�g
	CQuaternion m_spriteBackRot = CQuaternion::Identity();	//��]		
	float m_rotSpeed = 0.0f;								//��]���x
	float m_backRotSpeed = SPRITE_INIT_ROT_DEG;				//��]���x
	bool m_isDisplay = false;								//�\���H
};

