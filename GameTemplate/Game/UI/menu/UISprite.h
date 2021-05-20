#pragma once
#include "IUIObject.h"
#include "UIData.h"
class UISprite final : public IUIObject
{
public:
	UISprite();
	~UISprite();
	/*!
	*@brief 更新
	*/
	void Update() override;
	/*!
	*@brief 2D描画
	*/
	void Draw2D() override;
	/*!
	* enum EnLightBar
	*　ライト調整バー
	*/
	enum EnLightBar {
		enLightBar_r,				//R
		enLightBar_g,				//G
		enLightBar_b,				//B
		enLightBar_brightness,		//明るさ
		enLightBar_skyBrightness,	//空の明るさ
		enLightBar_Num				//数
	};
	/*!
	* enum EnBloomBar
	*	ブルーム調整バー
	*/
	enum EnBloomBar {
		enBloomBar_lum,				//輝度
		enBloomBar_pow,				//強さ
		enBloomBar_Num				//数
	};

private:
	/// <summary>
	/// 初期化もろもろ
	/// </summary>
	void Init();
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// モノクロ操作
	/// </summary>
	void MonochromeControl();
	/*!
	*@brief		ステートによるモノクロ処理
	そのステートが選択されていたらモノクロ解除　それ以外はモノクロ
	*@param[in]	ステート
	*@param[in]	ステート（画像）の数
	*@param[in]	モノクロにする画像
	*/
	void MonochromeUpdate(int state, int en_Num, Sprite* sprite);
	UIData* m_uiData = nullptr;								//UIでーた　
	CVector2 m_moveSpeed;									//移動速度

	Sprite m_backSprite;									//背景スプライト
	CVector3 m_backSpritePosition = CVector3::Zero();		//背景位置
	CQuaternion m_rotation = CQuaternion::Identity();		//回転
	CVector3 m_backSpriteScale = CVector3::One();			//背景スケール

	Sprite m_objSprite[UIData::Obj::enObj_Num];							//オブジェクトスプライト
	CVector3 m_objSpritePosition[UIData::Obj::enObj_Num];				//オブジェクト位置
	CVector3 m_objSpriteScale = CVector3::One();						//オブジェクトスケール

	Sprite m_gimmickSprite[UIData::Gimmick::enGimmick_Num];					//ギミックスプライト
	CVector3 m_gimmickSpritePosition[UIData::Gimmick::enGimmick_Num];		//ギミック位置
	CVector3 m_gimmickSpriteScale = CVector3::One();						//ギミックスケール

	Sprite m_enemySprite[UIData::Enemy::enEnemy_Num];						//敵スプライト
	CVector3 m_enemySpritePosition[UIData::Enemy::enEnemy_Num];				//敵位置
	CVector3 m_enemySpriteScale = CVector3::One();							//敵スケール

	Sprite m_lightBarSprite[enLightBar_Num];			//ライト調整バーのスプライト	
	Sprite m_bloomBarSprite[enBloomBar_Num];			//ブルーム調整バーのスプライト
	CVector3 m_lightBarPos[enLightBar_Num];				//ライト調整バーの位置
	CVector3 m_bloomBarPos[enBloomBar_Num];				//ブルーム調整バーの位置
	CVector3 m_barScale = CVector3::One();				//調整バーの拡大率
};

