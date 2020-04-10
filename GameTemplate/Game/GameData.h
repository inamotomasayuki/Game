#pragma once
//このクラスはシングルトンにしましょう
//ゲームオブジェクトマネージャーも同様です

class GameData
{
public:
	GameData();
	~GameData();
	/// <summary>
	/// 現在のステージ番号を取得。
	/// </summary>
	/// <returns>ステージ番号</returns>
	int GetStageNo()
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
	void SetStageNo(int no)
	{
		stageNo = no;
	}
	enum Stage
	{
		enStage_Zero,
		enStage_One,
		enStage_Num
	};
private:
	int stageNo = 0;	//現在のステージの番号。
};
extern GameData g_gameData;


