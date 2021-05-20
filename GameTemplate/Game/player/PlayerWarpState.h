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
	/// 更新
	/// </summary>
	/// <param name="">プレイヤー</param>
	void Update(Player*);
private:
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 削除
	/// </summary>
	void Delete();
	/// <summary>
	/// 回転
	/// </summary>
	void Rotation(Player*);
	/// <summary>
	/// サウンド
	/// </summary>
	void Sound();
	float m_rotSpeed = 0.0f;		//回転速度
	int m_warpTimer = 0;			//ワープに使うタイマー　単位：秒
	bool m_isRotStart = false;		//回転開始
	bool m_isRotReverse = false;	//逆回転
	enum EnSE {
		enSE_warp0,		//ワープ前
		enSE_warp1,		//ワープ後
		enSE_Num		//SEの数
	};
	CSoundSource* m_se[enSE_Num];	//効果音[SEの数分]	
};

