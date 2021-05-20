#pragma once
#include "player/Player.h"
class Game;
class GameCamera final : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	/*!
	*@brief 更新
	*/
	void Update() override;
	/*!
	*@brief 描画
	*/
	void Draw() override {}
private:
	/*!
	*@brief カメラを考慮した回転
	*/
	void Rotation();
	/*!
	*@brief ズームイン・アウト
	*/
	void ZoomInAndOut();
	/*!
	*@brief ステージ１カメラ
	*/
	void StageOneCamera();
	/*!
	*@brief ゲームクリアカメラ
	*/
	void GameClearCamera();
	/*!
	*@brief ゲームオーバーカメラ
	*/
	void GameOverCamera();
private:	
	Player* m_player = nullptr;				//プレイヤー
	Game* m_game = nullptr;					//ゲーム
	CVector3 m_cameraPos;					//視点
	CVector3 m_cameraTarget;				//注視点
	CVector3 m_toCameraPos;					//座標
	CVector3 m_oldPos;						//前の座標	
	CVector3 m_nextCameraPos;				//次の座標
	CVector3 m_clearPos = CVector3::Zero();	//クリアカメラ位置
	CVector3 m_moveSpeed;					//移動速度
	CQuaternion m_rotation;					//回転
	bool m_isButtonYoko = false;			//横向きか
	bool m_isButtonMae = false;				//前向きか
	bool m_isStop = false;					//止める
	bool m_isClearCameraInit = false;		//クリアカメラ初期化
};

