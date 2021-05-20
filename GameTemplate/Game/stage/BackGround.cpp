#include "stdafx.h"
#include "BackGround.h"
#include "GameData.h"

namespace {
	const float DITHE_LEN = 260.0f;		//ディザリング距離
}

BackGround::BackGround()
{
}


BackGround::~BackGround()
{
}
void BackGround::Update()
{
	//まずは初期化（一回だけ実行される）
	Init();
	//GhostUpdate
	if (m_isGhost) {
		m_ghostObject.SetPosition(m_position);
	}
	//PhysicsUpdate
	if (m_isPhysics) {
		m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);
	}
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void BackGround::Draw()
{
	if (m_isDraw && m_isInit) {
		m_skinModel.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			enRenderMode_Normal
		);
		//リムライトとトゥーンをオフ
		m_skinModel.RimLightOff();
		m_skinModel.ToonOff();
	}
}
void BackGround::Stage01Init()
{
	//physics作るやつはフラグをtrueに
	//当たり判定用でDrawしないやつはフラグをfalseに
	if (g_gameData.GetStageNo() == g_gameData.enStage_Zero) {
		switch (m_stage01ObjState) {
		case enStage01Obj_floor0:
			m_skinModel.SetFrustumCullingFlag(false);
			m_skinModel.Init(L"Assets/modelData/UCW_Floor0.cmo");
			m_skinModel.LoadNormalMap(L"Assets/modelData/WoodenFlooring_Normal.dds");
			m_skinModel.LoadAoMap(L"Assets/modelData/WoodenFlooring_AO.dds");
			m_isPhysics = true;
			break;
		case enStage01Obj_floor1:
			m_skinModel.Init(L"Assets/modelData/UCW_Floor1.cmo");
			m_skinModel.LoadNormalMap(L"Assets/modelData/BasketWeaveBricks_Normal.dds");
			m_skinModel.LoadAoMap(L"Assets/modelData/BasketWeaveBricks_ao.dds");
			m_isPhysics = true;
			break;
		case enStage01Obj_floor2:
			m_skinModel.SetFrustumCullingFlag(false);
			m_skinModel.Init(L"Assets/modelData/UCW_Floor2.cmo");
			m_skinModel.LoadNormalMap(L"Assets/modelData/stone_tile_normal.dds");
			m_skinModel.LoadSpecularMap(L"Assets/modelData/stone_tile_specular.dds");
			m_skinModel.SetDligSpecPow(0.1f);
			m_isPhysics = true;
			break;
		case enStage01Obj_floor3:
			m_skinModel.Init(L"Assets/modelData/UCW_Floor3.cmo");
			m_skinModel.LoadNormalMap(L"Assets/modelData/ClumpMud_Normal.dds");
			m_skinModel.LoadAoMap(L"Assets/modelData/ClumpMud_Grass_Ao.dds");
			m_isPhysics = true;
			break;
		case enStage01Obj_floor4:
			m_skinModel.Init(L"Assets/modelData/UCW_Floor4.cmo");
			m_skinModel.LoadNormalMap(L"Assets/modelData/WoodenFlooring_Normal.dds");
			m_skinModel.LoadAoMap(L"Assets/modelData/WoodenFlooring_AO.dds");
			m_isPhysics = true;
			break;
		case enStage01Obj_ceiling:
			m_skinModel.Init(L"Assets/modelData/UCW_Ceiling.cmo");
			m_isDraw = false;
			m_isGhost = true;
			break;
		case enStage01Obj_bridge:
			m_skinModel.Init(L"Assets/modelData/UCW_Bridge2.cmo");
			m_skinModel.LoadNormalMap(L"Assets/modelData/stone_tile_normal.dds");
			m_skinModel.LoadSpecularMap(L"Assets/modelData/stone_tile_specular.dds");
			m_isPhysics = true;
			break;
		case enStage01Obj_step:
			m_skinModel.Init(L"Assets/modelData/UCW_Step.cmo");
			m_skinModel.LoadNormalMap(L"Assets/modelData/RedBricks_normal.dds");
			m_skinModel.LoadAoMap(L"Assets/modelData/RedBricks_ao.dds");
			m_isPhysics = true;
			break;
		case enStage01Obj_fence:
			m_skinModel.Init(L"Assets/modelData/UCW_Fence.cmo");
			m_skinModel.SetDitheringLength(DITHE_LEN);
			break;
		case enStage01Obj_stoneFence:
			m_skinModel.Init(L"Assets/modelData/UCW_StoneFence.cmo");
			break;
		case enStage01Obj_square:
			m_skinModel.Init(L"Assets/modelData/UCW_Square.cmo");
			m_skinModel.LoadNormalMap(L"Assets/modelData/vol_2_3_Normal.dds");
			m_skinModel.LoadAoMap(L"Assets/modelData/vol_2_3_Ambient_Occlusion.dds");
			m_skinModel.SetDitheringLength(DITHE_LEN);
			m_isPhysics = true;
			break;
		case enStage01Obj_physicsFence:
			m_skinModel.Init(L"Assets/modelData/UCW_PhysicsFence.cmo");
			m_isPhysics = true;
			m_isDraw = false;
			break;
		}
	}
}
void BackGround::Stage02Init()
{
	//physics作るやつはフラグをtrueに
	//当たり判定用でDrawしないやつはフラグをfalseに
	if (g_gameData.GetStageNo() == g_gameData.enStage_One) {
		switch (m_stage02ObjState) {
		case enStage02Obj_square:
			m_skinModel.Init(L"Assets/modelData/UCW_Square.cmo");
			m_skinModel.LoadNormalMap(L"Assets/modelData/vol_2_3_Normal.dds");
			m_skinModel.LoadAoMap(L"Assets/modelData/vol_2_3_Ambient_Occlusion.dds");
			m_isPhysics = true;
			break;
		case enStage02Obj_step:
			m_skinModel.Init(L"Assets/modelData/UCW_Step.cmo");
			m_skinModel.LoadNormalMap(L"Assets/modelData/RedBricks_normal.dds");
			m_skinModel.LoadAoMap(L"Assets/modelData/RedBricks_ao.dds");
			m_isPhysics = true;
			break;
		case enStage02Obj_floor0:
			m_skinModel.Init(L"Assets/modelData/UCW_Floor0.cmo");
			m_skinModel.LoadNormalMap(L"Assets/modelData/WoodenFlooring_Normal.dds");
			m_skinModel.LoadAoMap(L"Assets/modelData/WoodenFlooring_AO.dds");
			m_isPhysics = true;
			break;
		case enStage02Obj_physicsFence:
			m_skinModel.Init(L"Assets/modelData/UCW_PhysicsFence.cmo");
			m_isPhysics = true;
			m_isDraw = false;
			break;
		case enStage02Obj_floor1:
			m_skinModel.Init(L"Assets/modelData/UCW_Wall0.cmo");
			m_skinModel.LoadNormalMap(L"Assets/modelData/Stone_floor_n.dds");
			m_isPhysics = true;
			break;
		}
	}
}
void BackGround::Init()
{
	if (!m_isInit) {
		Stage01Init();	//ステージ１なら１を初期化
		Stage02Init();	//ステージ２なら２を初期化
		//physicsの初期化
		if (m_isPhysics) {
			m_physicsStaticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
		}
		//Ghostの初期化
		if (m_isGhost) {
			m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
		}
		//モデルの都合上のため変換
		auto y = m_scale.z;
		m_scale.z = m_scale.y;
		m_scale.y = y;
		//初期化したのでtrue
		m_isInit = true;
	}
}