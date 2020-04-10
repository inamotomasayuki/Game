#pragma once
#include "graphics/2D/Sprite.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Fade.h"

class Title : public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Draw() {}
	void Draw2D();
private:
	enum EnSprite
	{
		enSprite_back,		//背景
		enSprite_title,		//タイトル
		enSprite_start,		//スタート	
		enSprite_Num		//数
	};
	Sprite m_sprite[enSprite_Num];		//スプライト
	Sprite m_kariSprite;				//仮スプライト
	CSoundSource* m_bgm = nullptr;		//BGM
	CVector3 m_position[enSprite_Num];
	CVector3 m_kariPos;					//仮位置
	CQuaternion m_rotation = CQuaternion::Identity();		//回転
	CQuaternion m_backRot = CQuaternion::Identity();		//背景回転
	CQuaternion m_startRot = CQuaternion::Identity();		//スタート回転
	CVector3 m_scale = CVector3::One();						//スケール
	CVector3 m_kariScale;					//仮スケール
	bool m_isKari = false;					//仮表示可？
	bool m_isStart = false;					//スタート表示可？
	int m_timer = 0;						//タイマー
	Fade* m_fade = nullptr;							//フェードイン
	bool m_isSelect = false;							//セレクトにいくか
	bool m_isGo = false;					//行けるかどうか
};

