#pragma once

class GameData final
{
public:
	GameData();
	~GameData();
	/// <summary>
	/// ���݂̃X�e�[�W�ԍ����擾�B
	/// </summary>
	/// <returns>�X�e�[�W�ԍ�</returns>
	int GetStageNo() const
	{
		return stageNo;
	}
	/// <summary>
	/// �X�e�[�W�ԍ������̃X�e�[�W�ɐi�߂�B
	/// </summary>
	/// <returns>false���Ԃ��Ă�����A���̃X�e�[�W�͂Ȃ��B</returns>
	bool ProgressNextStageNo()
	{
		stageNo++;
		if (stageNo == enStage_Num) {
			stageNo = enStage_Zero;
			return false;
		}
		return true;
	}
	/*!
	* @brief �X�e�[�W��ݒ�
	* @param no �X�e�[�W�̔ԍ�
	*/
	void SetStageNo(int no)
	{
		stageNo = no;
	}
	/*!
	* @enum EnStage
	*�@�X�e�[�W�ԍ� 
	*/
	enum EnStage
	{
		enStage_Zero,
		enStage_One,
		enStage_Num
	};
	/// <summary>
	/// �|�[�Y�I���ݒ�
	/// </summary>
	void SetPause() 
	{
		m_isPause = true;
	}
	/// <summary>
	/// �|�[�Y�I�t�ݒ�
	/// </summary>
	void SetPauseCancel()
	{
		m_isPause = false;
	}
	/// <summary>
	/// �|�[�Y�����擾
	/// </summary>
	/// <returns>�|�[�Y���H</returns>
	bool GetIsPause() const
	{
		return m_isPause;
	}
private:
	int stageNo = 0;	//���݂̃X�e�[�W�̔ԍ��B
	bool m_isPause = false;		//�|�[�Y���Ă邩�B
};
extern GameData g_gameData;


