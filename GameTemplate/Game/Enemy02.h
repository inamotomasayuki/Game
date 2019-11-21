#pragma once
#include "EnemyBase.h"
class Enemy02 : public EnemyBase 
{
public:
	Enemy02();
	void Update();
	void Move();
	void Rotation();
private:
	bool m_isJump = false;		//ジャンプフラグ
	float m_jumpSpeed = 0.0f;	//ジャンプ速度
	int m_timer = 0;
	float m_speed = 10.0f;
};

