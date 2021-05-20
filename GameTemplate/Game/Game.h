#pragma once
#include "level/Level.h"
#include "GameCamera.h"
#include "item/Coin.h"
#include "player/Player.h"
#include "enemy/Enemy01.h"
#include "enemy/Enemy02.h"
#include "enemy/Enemy03.h"
#include "enemy/Enemy04.h"
#include "enemy/EnemyBall.h"
#include "stage/BackGround.h"
#include "gimmick/MoveFloor.h"
#include "gimmick/JumpFloor.h"
#include "graphics/ShadowMap.h"
#include "result/GameClear.h"
#include "result/GameOver.h"
#include "item/Star.h"
#include "item/Item.h"
#include "stage/Sky.h"
#include "UI/Fade.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "UI/SpriteUI.h"
#include "UI/FontUI.h"
#include "gimmick/Bridge.h"
#include "gimmick/Wall.h"
#include "UI/menu/UIManager.h"
#include "gimmick/Warp.h"
#include "gimmick/Box.h"

namespace {
	const int HP_UPPER = 5;		//HP���
}
class Game final : public IGameObject
{
public:
	Game();
	~Game();
	/*
	* @brief �X�V
	*/
	void Update() override;
	/*!
	* @ brief ���t���[���P�񂾂��X�V
	*	�I�u�W�F�N�g�𐶐�����R�[�h�����邽��
	*/
	void NewUpdate() override;
	/*!
	* @brief �`��
	*/
	void Draw() override;
public:
	/// <summary>
	/// �X�R�A�̐ݒ�
	/// </summary>
	/// <param name="i">���Z����X�R�A�̒l</param>
	void SetScore(int score)
	{
		m_score += score;
		if (m_score < 0) {
			m_score = 0;
		}
	}
	/// <summary>
	/// �X�R�A�̎擾
	/// </summary>
	/// <returns>�X�R�A�̒l</returns>
	int GetScore() const
	{
		return m_score;
	}
	/// <summary>
	/// Hp�̐ݒ�
	/// </summary>
	/// <param name="hp">HP</param>
	void SetHP(int hp) 
	{
		m_hp += hp;

		if (m_hp < 0) {
			m_hp = 0;
		}
		if (m_hp > HP_UPPER) {
			m_hp = HP_UPPER;
		}
	}
	/// <summary>
	/// HP�̎擾
	/// </summary>
	/// <returns></returns>
	int GetHP() const 
	{
		return m_hp;
	}
	/// <summary>
	/// �Q�[���I�[�o�[���ǂ���
	/// </summary>
	/// <returns></returns>
	bool GetGameOverFlag() const
	{
		return m_gameOverFlag;
	}
	/// <summary>
	/// �Q�[���N���A�������ǂ���
	/// </summary>
	/// <returns></returns>
	bool GetGameClearFlag() const
	{
		return m_gameClearFlag;
	}
	/// <summary>
	/// ����������t���O�̐ݒ�
	/// </summary>
	void SetGetStarFlag()
	{
		m_getStar = true;
	}
	/// <summary>
	/// ������������ǂ���
	/// </summary>
	/// <returns></returns>
	bool GetStar() const
	{
		return m_getStar;
	}
	/// <summary>
	/// �{�^���ݒ�
	/// </summary>
	/// <param name="button"></param>
	void SetIsButton(bool button)
	{
		m_isButton = button;
	}
	/// <summary>
	/// �{�^���ݒ���擾
	/// </summary>
	/// <returns></returns>
	bool GetIsButton() const
	{
		return m_isButton;
	}
	/// <summary>
	/// �~�܂��Ă邩�擾
	/// </summary>
	/// <returns>�~�܂��Ă邩</returns>
	bool GetIsStop() const
	{
		return m_isStop;
	}
	/// <summary>
	/// HP�O�ɂ��Q�[���I�[�o�[���擾
	/// </summary>
	/// <returns>HP�O�ɂ��Q�[���I�[�o�[��</returns>
	bool GetIsHp0GameOver() const
	{
		return m_isHp0GameOver;
	}
	/// <summary>
	/// ������������擾
	/// </summary>
	/// <returns>�����������</returns>
	bool GetIsStar() const
	{
		return m_isGetStar;
	}
private:
	/// <summary>
	/// �X�e�[�W01������
	/// </summary>
	void Stage01Init();
	/// <summary>
	/// �X�e�[�W02������
	/// </summary>
	void Stage02Init();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �폜
	/// </summary>
	void Delete();
	/// <summary>
	/// �T�E���h������
	/// </summary>
	void InitSound();
	/// <summary>
	/// �T�E���h�Đ�
	/// </summary>
	void SoundPlay();
private:
	Level m_level;							//���x��
	Player* m_player = nullptr;				//�v���C���[
	Coin* m_coin = nullptr;					//�R�C��
	Enemy01* m_enemy01 = nullptr;			//�G01
	Enemy02* m_enemy02 = nullptr;			//�G02
	Enemy03* m_enemy03 = nullptr;			//�G03
	Enemy04* m_enemy04 = nullptr;			//�G04
	GameCamera* m_gameCamera = nullptr;		//�Q�[���J����
	BackGround* m_stage01[BackGround::enStage01Obj_Num] = { nullptr };		//�X�e�[�W1
	BackGround* m_stage02[BackGround::enStage02Obj_Num] = { nullptr };		//�X�e�[�W2
	MoveFloor* m_moveFloor = nullptr;		//������
	SpriteUI* m_spriteUI = nullptr;			//�X�v���C�g
	JumpFloor* m_jumpFloor = nullptr;		//�W�����v��
	Warp* m_warp = nullptr;					//���[�v��
	GameOver* m_gameOver = nullptr;			//�Q�[���I�[�o�[
	GameClear* m_gameClear = nullptr;		//�Q�[���N���A
	Star* m_star = nullptr;					//��
	Box* m_box = nullptr;					//��
	Sky* m_sky = nullptr;					//��
	Fade* m_fade = nullptr;					//�t�F�[�h
	Item* m_item = nullptr;					//�A�C�e��
	FontUI* m_fontUI = nullptr;				//�t�H���g
	Bridge* m_bridge = nullptr;				//��
	Button* m_button = nullptr;				//�{�^��
	Wall* m_wall = nullptr;					//��
	UIManager* m_uiManager = nullptr;		//UI�}�l�[�W���[
	CSoundSource* m_bgm = nullptr;			//BGM	
	enum EnSE{
		enSE_gameClear,		//�Q�[���N���A��
		enSE_gameOver,		//�Q�[���I�[�o�[��
		enSE_menu,			//���j���[�J����
		enSE_Num			//���ʉ��̐�
	};				
	CSoundSource* m_se[enSE_Num];			//���ʉ�
private:
	int m_score = 0;				//�X�R�A
	int m_hp = HP_UPPER;			//HP
	int m_stopTime = 0;				//�~�߂�
	int m_clearTimer = 0;			//�N���A�܂ł̃^�C�}�[
	bool m_gameOverFlag = false;	//�Q�[���I�[�o�[�t���O
	bool m_isHp0GameOver = false;	//HP�O�ɂ��Q�[���I�[�o�[��
	bool m_gameClearFlag = false;	//�Q�[���N���A�t���O
	bool m_getStar = false;			//������������ǂ���
	bool m_isGameClearSE = false;	//SE�炵����
	bool m_isGameOverSE = false;	//SE�炵����
	bool m_isFade = false;			//�t�F�[�h
	bool m_isGo = false;			//�s���邩�ǂ���
	bool m_isButton = false;		//�{�^����������
	bool m_isStop = false;			//�~�܂��Ă邩
	bool m_isGetStar = false;		//���������
};
