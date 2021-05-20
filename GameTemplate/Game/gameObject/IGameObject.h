#pragma once
class IGameObject
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~IGameObject() {};
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	virtual void Update() = 0;
	virtual void NewUpdate() {}
	virtual void PauseUpdate() {}
	virtual void Draw() = 0;
	virtual void Draw2D() {}
	virtual void DrawFade()	{}
	virtual void DrawEffect() {}
	virtual void DrawFont() {}
	/// <summary>
	/// �폜���N�G�X�g���s��
	/// </summary>
	void RequestDelete()
	{
		isReqDelete = true;
	}
	/// <summary>
	/// �폜���N�G�X�g���󂯂Ă��邩���ׂ�
	/// </summary>
	/// <returns>
	/// true���Ԃ��Ă�����A���N�G�X�g���󂯂Ă���
	/// </returns>
	bool IsRequestDelete() const
	{
		return isReqDelete;
	}
	unsigned int m_nameKey = 0;			//!<���O�L�[�B
private:
	bool isReqDelete = false;		//�폜���N�G�X�g
};

