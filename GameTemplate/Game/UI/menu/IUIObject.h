#pragma once
class IUIObject
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~IUIObject() {};
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 2D�`��
	/// </summary>
	virtual void Draw2D() {};
	/// <summary>
	/// �t�H���g�`��
	/// </summary>
	virtual void DrawFont() {}
	/// <summary>
	/// �폜
	/// </summary>
	void Delete()
	{
		m_IsDeleteUI = true;
	}
	/// <summary>
	/// �폜�������B
	/// </summary>
	/// <returns>�폜�t���O</returns>
	bool GetIsDelete() const
	{
		return m_IsDeleteUI;
	}
private:
	bool m_IsDeleteUI = false;		//�폜�����H
};

