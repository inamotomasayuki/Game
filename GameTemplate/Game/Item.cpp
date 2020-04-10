#include "stdafx.h"
#include "Item.h"
#include "Box.h"
#include "Player.h"

const float DELTA_TIME = 1.0f / 60.0f;			//経過時間　単位：秒
const float ITEM_GRAVITY = 20.0f;				//重力	
const float MOVE_UP_SPEED = 2.0f;				//上がる速度
const float ITEM_END_POS_Y = 80.0f;				//アイテム最終位置
const float ROTATION_SPEED = 3.0f;				//回転速度
const float DLIG_COLOR = 30.0f;					//ディレクションライトの明るさ
Item::Item()
{
	m_skinModel.Init(L"Assets/modelData/mikan.cmo");
	m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
	m_se = g_goMgr.NewGameObject<CSoundSource>(0);
	m_se->Init(L"Assets/sound/kyodaika.wav");		//巨大化
	g_goMgr.FindGameObjects<Box>("box", [&](Box* box)->bool {
		m_boxPos = box->GetPosition();
		m_posUp = m_boxPos.y + ITEM_END_POS_Y;
		return true;
		});
}


Item::~Item()
{
}

void Item::Update()
{
	m_player = g_goMgr.FindGameObject<Player>("player");
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_ghostObject.SetPosition(m_position);
	if (m_player != nullptr) {
		if (!m_isHipDrop) {
			if (!m_player->GetIsHipDropBox()) {
				if (m_posUp > m_position.y) {
					m_position.y += MOVE_UP_SPEED;
				}
				else {
					m_isHipDrop = true;
				}
			}
			else {
				m_moveSpeed.y -= ITEM_GRAVITY;
				m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);
				if (m_charaCon.IsOnGround()) {
					m_isHipDrop = true;
				}
			}
		}
	}
	//削除
	if (m_isGet) {
		if (m_player != nullptr) {
			if (!m_player->GetisItem()) {
				{
					m_se->Play(false);
				}
			}
		}
		g_goMgr.DeleteGameObject(this);
	}
	Rotation();
}
void Item::Rotation()
{
	//一定速度で回転させる
	float rotSpeed = 0.0f;;
	rotSpeed += ROTATION_SPEED;
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
	m_rotation.Multiply(addRot);

}
void Item::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	m_skinModel.RimLightOff();
	m_skinModel.SetDligColor(0, DLIG_COLOR);
	m_skinModel.SetDligColor(1, DLIG_COLOR);
}