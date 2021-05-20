#pragma once
#include <vector>
#include "IGameObject.h"
#include "util/Util.h"

class GameObjectManager
{
private:
	/*!
*@brief	�Q�[���I�u�W�F�N�g�̖��O�L�[���쐬�B
*/
	static unsigned int MakeGameObjectNameKey(const char* objectName)
	{
		static const unsigned int defaultNameKey = Util::MakeHash("Undefined");	//���O�L�[�B
		unsigned int hash;
		if (objectName == nullptr) {
			hash = defaultNameKey;
		}
		else {
			hash = Util::MakeHash(objectName);
		}
		return hash;
	}

public:
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
	/// �|�[�Y���X�V
	/// </summary>
	void PauseUpdate();
	/// <summary>
	/// 3D��`��
	/// </summary>
	void Draw3D();
	/// <summary>
	/// 2D��`��B
	/// </summary>
	void Draw2D();
	/// <summary>
	/// �t�F�[�h��`��
	/// </summary>
	void DrawFade();
	/// <summary>
	/// �G�t�F�N�g�̕`��
	/// </summary>
	void DrawEffect();
	/// <summary>
	/// �t�H���g�̕`��
	/// </summary>
	void DrawFont();
	/// <summary>
	/// �Q�[���I�u�W�F�N�g��ǉ��B
	/// </summary>
	/// <param name="objectName">�I�u�W�F�N�g��</param>
	/// <returns></returns>
	template <class T>
	T* NewGameObject(const char* objectName)
	{
		(void*)objectName;
		T* newObj = new T;
		m_goList.push_back(newObj);
		unsigned int hash = MakeGameObjectNameKey(objectName);
		newObj->m_nameKey = hash;
		return newObj;
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�����X�g����폜����B
	/// </summary>
	/// <param name="go">�폜����Q�[���I�u�W�F�N�g</param>
	void DeleteGameObject(IGameObject* go)
	{
		//���X�g���猟�����āA����������폜����B
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++
			) {
			if ((*it) == go) {
				//�폜���N�G�X�g�𑗂�
				go->RequestDelete();
				return;
			}
		}
	}
	bool Find(IGameObject* go)
	{
		//���X�g���猟�����āA����������폜����B
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++
			) {
			if ((*it) == go) {
				return true;
			}
		}
		return false;
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̌���
	/// </summary>
	/// <param name="objectName">�I�u�W�F�N�g��</param>
	/// <returns></returns>
	template <class T>
	T* FindGameObject(const char* objectName)
	{
		unsigned int nameKey = Util::MakeHash(objectName);
		//���X�g���猟������B
		for (auto go : m_goList) {
			if (go->m_nameKey == nameKey) {
				//������
				T* p = dynamic_cast<T*>(go);
				return p;
			}
		}
		//������Ȃ�����
		return nullptr;
	}
	/*!
	*@brief	�w�肵���^�O�̂����ꂩ�����܂܂��Q�[���I�u�W�F�N�g���������āA���������ꍇ�w�肳�ꂽ�R�[���o�b�N�֐����Ăяo���B
	*/
	template<class T>
	void FindGameObjects(const char* objectName, std::function<bool(T* go)> func)
	{
		unsigned int nameKey = Util::MakeHash(objectName);
		for (auto go : m_goList) {
			if (go->m_nameKey == nameKey) {
				//�������B
				T* p = dynamic_cast<T*>(go);
				if (func(p) == false) {
					//�N�G�����f�B
					return;
				}
			}
		}
	}
	/// <summary>
	/// �폜
	/// </summary>
	void Delete();
private:

	std::list< IGameObject* > m_goList;		//�Q�[���I�u�W�F�N�g�̃��X�g�B
};
//�O������A�N�Z�X����̂ŁAextern�錾���K�v�B
extern GameObjectManager g_goMgr;
