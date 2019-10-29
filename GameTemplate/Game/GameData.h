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
		if (stageNo == 2) {
			stageNo = 0;
			return false;
		}
		return true;
	}
private:
	int stageNo = 0;	//現在のステージの番号。
};
extern GameData g_gameData;


