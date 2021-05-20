#pragma once
#include "graphics/2D/Sprite.h"

class Game;
class SpriteUI final : public IGameObject
{
public:
	SpriteUI();
	~SpriteUI();
	/*
	* @brieef 更新
	*/
	void Update() override;
	/*
	* @brieef 描画
	*/
	void Draw() override {}
	/*
	* @brief 2D描画
	*/
	void Draw2D() override;
	/*
	* @enum EnSpriteUI
	* スプライトUIの種類
	*/
	enum EnSpriteUI {
		enSpriteUI_unityChan,		//ユニティちゃん
		enSpriteUI_kakeru,			//×
		enSpriteUI_coin,			//コイン
		enSpriteUI_Num
	};
	/*
	* @enum EnSpriteScore
	* スコア用のスプライト
	*/
	enum EnSpriteScore {
		enSpriteScore_zero,		//スコア0
		enSpriteScore_one,		//スコア1
		enSpriteScore_two,		//スコア2
		enSpriteScore_three,	//スコア3
		enSpriteScore_four,		//スコア4
		enSpriteScore_five,		//スコア5
		enSpriteScore_six,		//スコア6
		enSpriteScore_seven,	//スコア7
		enSpriteScore_eight,	//スコア8
		enSpriteScore_nine,		//スコア9
		enSpriteScore_Num		//数
	};
	/*
	* @enum EnSpriteHP
	* HP用のスプライト
	*/
	enum EnSpriteHP {
		enSpriteHP_zero,		//HP0
		enSpriteHP_one,			//HP1
		enSpriteHP_two,			//HP2
		enSpriteHP_three,		//HP3
		enSpriteHP_four,		//HP4
		enSpriteHP_five,		//HP5
		enSpriteHP_Num			//数
	};
private:
	Sprite m_spriteUI[enSpriteUI_Num];			//UIスプライト
	Sprite m_spriteScoreUI[enSpriteScore_Num];	//スコアスプライト
	Sprite m_spriteScoreUI2[enSpriteScore_Num];	//スコアスプライト
	Sprite m_spriteScoreUI3[enSpriteScore_Num];	//スコアスプライト
	Sprite m_spriteHP[enSpriteHP_Num];			//HPスプライト
	CVector3 m_positionUI[enSpriteUI_Num];		//UI位置
	CVector3 m_positionScoreUI;					//スコア位置
	CVector3 m_positionScoreUI2;				//スコア２位置
	CVector3 m_positionScoreUI3;				//スコア３位置
	CVector3 m_positionHP;						//HP位置
	CQuaternion m_rotation = CQuaternion::Identity();		//回転
	CVector3 m_scale = CVector3::One();						//スケール
	Game* m_game = nullptr;			//ゲーム
	bool m_isHpUp = true;			//HPアップできるかどうか
};