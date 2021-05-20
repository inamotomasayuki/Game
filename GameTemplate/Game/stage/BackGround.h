#pragma once
#include "physics/PhysicsStaticObject.h"
#include "physics/PhysicsGhostObject.h"

class BackGround final : public IGameObject
{
public:
	BackGround();
	~BackGround();
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 拡大率の設定
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// 静的オブジェクトの取得
	/// </summary>
	/// <returns>静的オブジェクト</returns>
	const PhysicsStaticObject* GetPhysicsStaticObject() const
	{
		return &m_physicsStaticObject;
	}
	/// <summary>
	/// ゴーストの取得
	/// </summary>
	/// <returns>ゴースト</returns>
	const PhysicsGhostObject* GetGhost() const
	{
		return &m_ghostObject;
	}
	/// <summary>
	/// ステージ01オブジェクト
	/// </summary>
	enum Stage01Obj {
		enStage01Obj_floor0,			//床０
		enStage01Obj_floor1,			//床１
		enStage01Obj_floor2,			//床２
		enStage01Obj_floor3,			//床３
		enStage01Obj_floor4,			//床４
		enStage01Obj_ceiling,			//当たり判定用天井
		enStage01Obj_bridge,			//橋
		enStage01Obj_step,				//段
		enStage01Obj_fence,				//フェンス
		enStage01Obj_stoneFence,		//石のフェンス
		enStage01Obj_square,			//四角
		enStage01Obj_physicsFence,		//当たり判定用フェンス
		enStage01Obj_Num				//数
	};
	/// <summary>
	/// ステージ02オブジェクト
	/// </summary>
	enum Stage02Obj {
		enStage02Obj_floor0,			//床０
		enStage02Obj_floor1,			//床１
		enStage02Obj_square,			//四角
		enStage02Obj_step,				//段
		enStage02Obj_physicsFence,		//当たり判定用フェンス
		enStage02Obj_Num				//数
	};
	/// <summary>
	/// ステージ01ステート設定
	/// </summary>
	/// <param name="i">ステート番号（オブジェクト番号）</param>
	void SetStage01ObjState(int i) {
		m_stage01ObjState = i;
	}
	/// <summary>
	/// ステージ02ステート設定
	/// </summary>
	/// <param name="i">ステート番号（オブジェクト番号）</param>
	void SetStage02ObjState(int i) {
		m_stage02ObjState = i;
	}
private:
	/// <summary>
	/// ステージ01初期化
	/// </summary>
	void Stage01Init();
	/// <summary>
	/// ステージ０２初期化
	/// </summary>
	void Stage02Init();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	SkinModel m_skinModel;								//スキンモデル
	PhysicsGhostObject m_ghostObject;					//ゴースト
	PhysicsStaticObject m_physicsStaticObject;			//静的物理オブジェクト
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	int m_stage01ObjState;				//ステージ１のステート
	int m_stage02ObjState;				//ステージ２のステート
	bool m_isInit = false;				//初期化した？
	bool m_isPhysics = false;			//physics作る？
	bool m_isGhost = false;				//ゴースト作る？
	bool m_isDraw = true;				//描画する？
};

