#pragma once
#include "Player.h"
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	void Update();
	void Draw();
private:
	CVector3 m_cameraPos;					//視点
	CVector3 m_cameraTarget;				//注視点
	CVector3 m_toCameraPos;					//座標
	CQuaternion m_rotation;					//回転
	Player* m_player;						//プレイヤー
};

