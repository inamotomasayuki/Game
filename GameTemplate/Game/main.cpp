#include "stdafx.h"
#include "system/system.h"
#include "graphics/ShadowMap.h"
#include "gameObject/GameObjectManager.h"
#include "title/Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "time/Stopwatch.h"
#include "time/GameTime.h"
#include "GameData.h"
void GameUpdate()
{
	//�Q�[���p�b�h�̍X�V�B	
	for (auto& pad : g_pad) {
		pad.Update();
	}
	//�����G���W���̍X�V�B
	g_physics.Update();
	g_soundEngine->Update();
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V
	if (!g_gameData.GetIsPause()) {
		//�ʏ펞
		g_goMgr.Update();
	}
	else {
		//�|�[�Y��
		g_goMgr.PauseUpdate();
	}
}	

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{	
	g_soundEngine = new CSoundEngine;
	g_soundEngine->Init();

	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	g_shadowMap = new ShadowMap;	

	g_goMgr.NewGameObject<Title>(0);
	//g_goMgr.NewGameObject<Game>("game");

	CStopwatch sw;

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		sw.Start();
		//�X�V
		GameUpdate();
		//�`��
		g_graphicsEngine->GameDraw();
		//�폜
		g_goMgr.Delete();
		sw.Stop();
		GameTime().PushFrameDeltaTime((float)sw.GetElapsed());
	}
}
