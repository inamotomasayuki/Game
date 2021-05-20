#pragma once
#include "../graphics/2D/Font.h"

class Game;
class FontUI final : public IGameObject
{
public:
	FontUI();
	~FontUI();
	/*!
	* @brief 更新
	*/
	void Update() override;
	/*!
	* @brief 描画
	*/
	void Draw() override {}
	/*!
	* @brief フォント描画
	*/
	void DrawFont() override;
private:
	Game* m_game = nullptr;				//ゲーム
	Font m_font;						//フォント
	CVector2 m_fontScale;				//拡大率
	float m_scaleTimer = 0.0f;			//拡大タイマー
	float m_timer = 0.0f;				//タイマー
};

