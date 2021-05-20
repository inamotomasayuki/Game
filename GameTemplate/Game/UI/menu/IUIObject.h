#pragma once
class IUIObject
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~IUIObject() {};
	/// <summary>
	/// 更新関数。
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 2D描画
	/// </summary>
	virtual void Draw2D() {};
	/// <summary>
	/// フォント描画
	/// </summary>
	virtual void DrawFont() {}
	/// <summary>
	/// 削除
	/// </summary>
	void Delete()
	{
		m_IsDeleteUI = true;
	}
	/// <summary>
	/// 削除したか。
	/// </summary>
	/// <returns>削除フラグ</returns>
	bool GetIsDelete() const
	{
		return m_IsDeleteUI;
	}
private:
	bool m_IsDeleteUI = false;		//削除した？
};

