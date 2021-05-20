#pragma once
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Player;
class Warp;

class PlayerWarpState
{
public:
	PlayerWarpState();
	~PlayerWarpState();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="">�v���C���[</param>
	void Update(Player*);
private:
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �폜
	/// </summary>
	void Delete();
	/// <summary>
	/// ��]
	/// </summary>
	void Rotation(Player*);
	/// <summary>
	/// �T�E���h
	/// </summary>
	void Sound();
	float m_rotSpeed = 0.0f;		//��]���x
	int m_warpTimer = 0;			//���[�v�Ɏg���^�C�}�[�@�P�ʁF�b
	bool m_isRotStart = false;		//��]�J�n
	bool m_isRotReverse = false;	//�t��]
	enum EnSE {
		enSE_warp0,		//���[�v�O
		enSE_warp1,		//���[�v��
		enSE_Num		//SE�̐�
	};
	CSoundSource* m_se[enSE_Num];	//���ʉ�[SE�̐���]	
};

