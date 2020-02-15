#pragma once

class StageSelect : public IGameObject
{
public:
	StageSelect();
	~StageSelect();
	void Update();
	void Draw() {}
	void Draw2D();

private:
	enum EnSprite	{
		enSprite_back,		//背景
		enSprite_select,	//セレクト	
		enSprite_ok,		//OK
		enSprite_leftTriangle,	//左三角
		enSprite_rightTriangle,	//右三角
		enSprite_upTriangle,	//上三角
		enSprite_downTriangle,	//下三角
		enSprite_Num		//数
	};
	enum EnStage
	{
		enStage_One,		//1
		enStage_Two,		//2
		enStage_Num			//数
	};
	enum EnSelect
	{
		enSelect_stage,		//ステージセレクト中
		enSelect_ok,		//OK中
		enSelect_Num		//数
	};
	int stageNo = 0;	//現在のステージの番号。
	Sprite m_sprite[enSprite_Num];						//スプライト
	Sprite m_stageSprite[enStage_Num];					//スプライト
	CVector3 m_position[enSprite_Num];					//位置
	CVector3 m_stagePos[enStage_Num];					//位置
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//スケール
	int m_selectNo = 1;									//セレクトの数
};

