#pragma once
#include "EnemyBase.h"
class Enemy02 : public EnemyBase 
{
public:
	Enemy02();
	void Update();
	void Move();
private:
	bool m_isJump = false;		//ジャンプフラグ
	float m_jumpSpeed = 0.0f;	//ジャンプ速度
};

