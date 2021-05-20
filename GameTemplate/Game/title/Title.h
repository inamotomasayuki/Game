#pragma once
#include "graphics/2D/Sprite.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "../UI/Fade.h"

class Title final : public IGameObject
{
public:
	Title();
	~Title();
	/*
	* @brief 更新
	*/
	void Update() override {};
	/*
	* @brief 生成処理がある更新
	*/
	void NewUpdate() override;
	/*
	* @brief 描画
	*/
	void Draw() override {}
	/*
	* @brief 2D描画
	*/
	void Draw2D() override;
private:
	/*!
	* @enum EnSprite
	* スプライトの種類
	*/
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
	CVector3 m_position[enSprite_Num];	//位置
	CVector3 m_kariPos;					//仮位置
	CQuaternion m_rotation = CQuaternion::Identity();		//回転
	CQuaternion m_backRot = CQuaternion::Identity();		//背景回転
	CQuaternion m_startRot = CQuaternion::Identity();		//スタート回転
	CVector3 m_scale = CVector3::One();						//スケール
	CVector3 m_kariScale;					//仮スケール
	Fade* m_fade = nullptr;					//フェードイン
	int m_timer = 0;						//タイマー
	bool m_isKari = false;					//仮表示可？
	bool m_isStart = false;					//スタート表示可？
	bool m_isSelect = false;				//セレクトにいくか
	bool m_isGo = false;					//行けるかどうか
};

