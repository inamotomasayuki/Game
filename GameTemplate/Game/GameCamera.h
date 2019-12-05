#pragma once
#include "Player.h"
class Game;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	void Update();
	void Draw();
	void SetCameraPos(CVector3 pos)
	{
		m_cameraPos = m_cameraTarget + pos;
		g_camera3D.SetPosition(m_cameraPos);
	}
private:
	CVector3 m_cameraPos;					//視点
	CVector3 m_cameraTarget;				//注視点
	CVector3 m_toCameraPos;					//座標
	CQuaternion m_rotation;					//回転
	Player* m_player = nullptr;				//プレイヤー
	Game* m_game = nullptr;					//ゲーム
};

