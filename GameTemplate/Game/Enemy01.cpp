#include "stdafx.h"
#include "Enemy01.h"
#include "Game.h"

const float LENGTH_UPPER = 1000.0f;			//追跡上限距離
const float LENGTH_UNDER = 50.0f;			//追跡下限距離
const float MOVE_SPEED = 400.0f;			//移動速度
const float MINIMUM = 0.0001f;				//極小
const float DELTA_TIME = 1.0f / 60.0f;		//経過時間　単位：秒

Enemy01::Enemy01()
{
	//cmoファイルの読み込み。
	m_skinModel.Init(L"Assets/modelData/kuribo.cmo");
}

void Enemy01::Update()
{
	m_player = g_goMgr.FindGameObject<Player>("player");
	m_game = g_goMgr.FindGameObject<Game>("game");

	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	if (m_player != nullptr
		&& m_game != nullptr
		&& !m_game->GetGameClearFlag()
		&& !m_game->GetStar()) {
		//プレイヤーに伸びるベクトル＆正規化
		VectorToPlayer();
		//角度を求める
		Angle();
		//追跡
		Search();
		//攻撃（プレイヤーをノックバック）
		Attack();
		//元の位置に戻る
		Return();

		m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);

		//回転
		Rotation();
		//死亡
		Death(5);
	}
}
void Enemy01::Search()
{
	//攻撃していないかつ攻撃を受けていない
	if (m_isAttack == false
		&& m_isAttacked == false) {
		//下記の距離の範囲ならかつプレイヤーが攻撃を受けていなかったら
		if (m_len > LENGTH_UNDER
			&& m_len < LENGTH_UPPER
			&& m_player->GetIsAttacked() == false) {
			//プレイヤーを追跡
			m_moveSpeed = m_v * MOVE_SPEED;
			m_moveSpeed.y = 0.0f;
		}
		else {
			//追跡しない。
			//回転させるために０ではない。
			m_moveSpeed = m_v * MINIMUM;
		}
	}
}
void Enemy01::Return()
{
	//下記の距離の範囲なら
	if (m_len > LENGTH_UPPER) {
		auto initPos = m_initialPos - m_position;
		auto len = initPos.Length();
		initPos.Normalize();
		if (len < 1.0f) {
			//戻ったら動かない
			m_moveSpeed = CVector3::Zero();
		}
		else {
			//元の位置に戻る
			m_moveSpeed = initPos * MOVE_SPEED;
		}
	}
}
void Enemy01::Rotation()
{
	//ｘとｚのベクトルから角度を求めて回転させる。
	auto moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(moveSpeedXZ.x, moveSpeedXZ.z));  //角度を求める関数
}
