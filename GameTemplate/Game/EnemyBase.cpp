#include "stdafx.h"
#include "EnemyBase.h"
#include "Game.h"

void EnemyBase::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
}
void EnemyBase::Attack()
{
	//UŒ‚’†‚¶‚á‚È‚©‚Á‚½‚çUŒ‚
	if (m_isAttack == false) {
		if (fabs(m_angle) > CMath::DegToRad(80) && m_len < 50.0f) {
			m_v.y = 0.0f;
			//ƒmƒbƒNƒoƒbƒN‚³‚¹‚é‘¬“x
			m_player->SetAddSpeed(m_v * 2500.0f);
			m_player->SetIsAttacked(true);	//UŒ‚‚³‚ê‚½B
			m_isAttack = true;	//UŒ‚‚µ‚½B
		}
	}
	//UŒ‚‚µ‚½‚ç­‚µ‘Ò‚Â
	else {
		m_waitTimer++;
		if (m_waitTimer == 40) {
			m_waitTimer = 0;
			m_isAttack = false;		//UŒ‚‚µ‚Ä‚È‚¢B
			m_player->SetIsAttacked(false);		//UŒ‚‚³‚ê‚Ä‚È‚¢B
		}
	}
}

void EnemyBase::Death(int score)
{
	//UŒ‚‚³‚ê‚Ä‚È‚©‚Á‚½‚ç
	if (m_isAttacked == false) {
		if (fabs(m_angle) <= CMath::DegToRad(80) && m_len < 50.0f) {
			m_scale.z /= 2;
			m_player->SetJumpFlag(true);	//ƒWƒƒƒ“ƒv‚³‚¹‚é
			m_isAttacked = true;		//UŒ‚‚³‚ê‚½
		}
	}
	//UŒ‚‚³‚ê‚½‚ç­‚µ‘Ò‚Á‚Ä‚©‚çíœ
	if (m_isAttacked == true) {
		m_waitTimer++;
		if (m_waitTimer == 20) {
			m_game->SetScore(score);
			g_goMgr.DeleteGameObject(this);
		}
	}
}