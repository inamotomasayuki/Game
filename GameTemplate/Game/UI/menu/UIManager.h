#pragma once
#include "IUIObject.h"
class UIManager final: public IGameObject
{
public:
	UIManager();
	~UIManager();
	/*
	* @brief �X�V
	*/
	void Update() override {};
	/*
	* @brief �`��
	*/
	void Draw() override {};
	/*
	* @brief �|�[�Y���X�V
	*/
	void PauseUpdate() override;
	/*
	* @brief 2D�`��
	*/
	void Draw2D() override;
	/*
	* @brief �t�H���g�`��
	*/
	void DrawFont() override;
private:
	/// <summary>
	/// UI�Q�[���I�u�W�F�N�g��ǉ��B
	/// </summary>
	/// <param name="objectName">�I�u�W�F�N�g��</param>
	/// <returns></returns>
	template <class T>
	T* NewUIObject()
	{
		T* newObj = new T;
		m_uiList.push_back(newObj);
		return newObj;
	}
	std::list< IUIObject* > m_uiList;	//UI�Q�[���I�u�W�F�N�g�̃��X�g
};
