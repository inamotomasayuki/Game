#pragma once
#include "../graphics/2D/Font.h"

class Game;
class FontUI final : public IGameObject
{
public:
	FontUI();
	~FontUI();
	/*!
	* @brief �X�V
	*/
	void Update() override;
	/*!
	* @brief �`��
	*/
	void Draw() override {}
	/*!
	* @brief �t�H���g�`��
	*/
	void DrawFont() override;
private:
	Game* m_game = nullptr;				//�Q�[��
	Font m_font;						//�t�H���g
	CVector2 m_fontScale;				//�g�嗦
	float m_scaleTimer = 0.0f;			//�g��^�C�}�[
	float m_timer = 0.0f;				//�^�C�}�[
};

