#pragma once
#include "../UI/Fade.h"
#include "GameData.h"
class StageSelect final : public IGameObject
{
public:
	StageSelect();
	~StageSelect();
	/*
	* @brieef 更新
	*/
	void Update() override;
	/*
	* @brieef オブジェクト生成がある更新
	*/
	void NewUpdate() override;
	/*
	* @brieef 描画
	*/
	void Draw() override {}
	/*
	* @brieef 2D描画
	*/
	void Draw2D() override;
private:
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/*
	* @enum EnSprite
	*　スプライトの種類
	*/
	enum EnSprite	{
		enSprite_back,			//背景
		enSprite_select,		//セレクト	
		enSprite_ok,			//OK
		enSprite_leftTriangle,	//左三角
		enSprite_rightTriangle,	//右三角
		enSprite_upTriangle,	//上三角
		enSprite_downTriangle,	//下三角
		enSprite_Num			//数
	};
	/*
	* @enum EnSelect
	*  選択の種類
	*/
	enum EnSelect
	{
		enSelect_stage,		//ステージセレクト中
		enSelect_ok,		//OK中
		enSelect_Num		//数
	};
	Sprite m_sprite[enSprite_Num];						//スプライト
	Sprite m_stageSprite[g_gameData.enStage_Num];		//スプライト
	CVector3 m_position[enSprite_Num];					//位置
	CVector3 m_stagePos[g_gameData.enStage_Num];		//位置
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//スケール	
	Fade* m_fade = nullptr;								//フェード
	int stageNo = g_gameData.GetStageNo();				//現在のステージの番号。
	int m_selectNo = 0;									//セレクトの数
	bool m_isGame = false;								//ゲームにいくか
	bool m_isTitle = false;								//タイトルにいくか
	bool m_isGo = false;								//行けるかどうか
	bool m_isOK = false;								//決定
};