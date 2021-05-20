#pragma once

class GameData final
{
public:
	GameData();
	~GameData();
	/// <summary>
	/// 現在のステージ番号を取得。
	/// </summary>
	/// <returns>ステージ番号</returns>
	int GetStageNo() const
	{
		return stageNo;
	}
	/// <summary>
	/// ステージ番号を次のステージに進める。
	/// </summary>
	/// <returns>falseが返ってきたら、次のステージはない。</returns>
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
	* @brief ステージを設定
	* @param no ステージの番号
	*/
	void SetStageNo(int no)
	{
		stageNo = no;
	}
	/*!
	* @enum EnStage
	*　ステージ番号 
	*/
	enum EnStage
	{
		enStage_Zero,
		enStage_One,
		enStage_Num
	};
	/// <summary>
	/// ポーズオン設定
	/// </summary>
	void SetPause() 
	{
		m_isPause = true;
	}
	/// <summary>
	/// ポーズオフ設定
	/// </summary>
	void SetPauseCancel()
	{
		m_isPause = false;
	}
	/// <summary>
	/// ポーズ中か取得
	/// </summary>
	/// <returns>ポーズ中？</returns>
	bool GetIsPause() const
	{
		return m_isPause;
	}
private:
	int stageNo = 0;	//現在のステージの番号。
	bool m_isPause = false;		//ポーズしてるか。
};
extern GameData g_gameData;


