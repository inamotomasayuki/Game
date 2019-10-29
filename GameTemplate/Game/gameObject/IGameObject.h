#pragma once
class IGameObject
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~IGameObject() {};
	/// <summary>
	/// 更新関数。
	/// </summary>
	virtual void Update() = 0;
	virtual void Draw() = 0;

	/// <summary>
	/// 削除リクエストを行う
	/// </summary>
	void RequestDelete()
	{
		isReqDelete = true;
	}
	/// <summary>
	/// 削除リクエストを受けているか調べる
	/// </summary>
	/// <returns>
	/// trueが返ってきたら、リクエストを受けている
	/// </returns>
	bool IsRequestDelete()
	{
		return isReqDelete;
	}
	unsigned int m_nameKey = 0;			//!<名前キー。
private:
	bool isReqDelete = false;		//削除リクエスト
};

