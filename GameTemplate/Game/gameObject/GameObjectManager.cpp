#include "stdafx.h"
#include "GameObjectManager.h"
#include "../time/GameTime.h"

//GameObjectManager�N���X�̃C���X�^���X�B
GameObjectManager g_goMgr;

/// <summary>
/// 3D��`��
/// </summary>
void GameObjectManager::Draw3D()
{
	for (auto go : m_goList) {
		go->Draw();
	}
}
/// <summary>
/// 2D��`��B
/// </summary>
void GameObjectManager::Draw2D()
{
	for (auto go : m_goList) {
		go->Draw2D();
	}
}

void GameObjectManager::DrawFade()
{
	for (auto go : m_goList) {
		go->DrawFade();
	}
}

void GameObjectManager::DrawEffect()
{
	for (auto go : m_goList) {
		go->DrawEffect();
	}
}

void GameObjectManager::DrawFont()
{
	for (auto go : m_goList) {
		go->DrawFont();
	}
}
void GameObjectManager::Update()
{
	//�o�^����Ă���Q�[���I�u�W�F�N�g�̍X�V�������ĂԁB
	const float GAME_BASE_DELTA_TIME = 1.0f / 60.0f;
	int updateCount = (int)( GameTime().GetFrameDeltaTime() / GAME_BASE_DELTA_TIME);
	//�X�V�񐔂͍ő�Q��B
	updateCount = 1;// min(2, updateCount);

	for (int i = 0; i < updateCount; i++){
		for (auto go : m_goList) {
			if (go->IsRequestDelete() == false) {
				go->Update();
			}
		}
	}
	for (auto go : m_goList) {
		if (go->IsRequestDelete() == false) {
			go->NewUpdate();
		}
	}
}
void GameObjectManager::PauseUpdate()
{
	for (auto go : m_goList) {
		if (go->IsRequestDelete() == false) {
			go->PauseUpdate();
		}
	}
}

void GameObjectManager::Delete()
{
	//�S�ẴQ�[���I�u�W�F�N�g��1�t���[�����̏������I����Ă���A�폜����B
	for (auto it = m_goList.begin(); it != m_goList.end();) {
		if ((*it)->IsRequestDelete()) {		
			//�폜���N�G�X�g���󂯂Ă���̂ō폜�B
			delete* it;
			it = m_goList.erase(it);
		}
		else {
			//���N�G�X�g���󂯂Ă��Ȃ��́B
			it++;
		}
	}
}