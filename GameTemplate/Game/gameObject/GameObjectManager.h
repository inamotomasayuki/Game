#pragma once
#include <vector>
#include "IGameObject.h"
#include "util/Util.h"

class GameObjectManager
{
private:
	/*!
*@brief	ゲームオブジェクトの名前キーを作成。
*/
	static unsigned int MakeGameObjectNameKey(const char* objectName)
	{
		static const unsigned int defaultNameKey = Util::MakeHash("Undefined");	//名前キー。
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
	/// 更新。
	/// </summary>
	void Update();
	/// <summary>
	/// ポーズ中更新
	/// </summary>
	void PauseUpdate();
	/// <summary>
	/// 3Dを描画
	/// </summary>
	void Draw3D();
	/// <summary>
	/// 2Dを描画。
	/// </summary>
	void Draw2D();
	/// <summary>
	/// フェードを描画
	/// </summary>
	void DrawFade();
	/// <summary>
	/// エフェクトの描画
	/// </summary>
	void DrawEffect();
	/// <summary>
	/// フォントの描画
	/// </summary>
	void DrawFont();
	/// <summary>
	/// ゲームオブジェクトを追加。
	/// </summary>
	/// <param name="objectName">オブジェクト名</param>
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
	/// ゲームオブジェクトをリストから削除する。
	/// </summary>
	/// <param name="go">削除するゲームオブジェクト</param>
	void DeleteGameObject(IGameObject* go)
	{
		//リストから検索して、見つかったら削除する。
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++
			) {
			if ((*it) == go) {
				//削除リクエストを送る
				go->RequestDelete();
				return;
			}
		}
	}
	bool Find(IGameObject* go)
	{
		//リストから検索して、見つかったら削除する。
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
	/// ゲームオブジェクトの検索
	/// </summary>
	/// <param name="objectName">オブジェクト名</param>
	/// <returns></returns>
	template <class T>
	T* FindGameObject(const char* objectName)
	{
		unsigned int nameKey = Util::MakeHash(objectName);
		//リストから検索する。
		for (auto go : m_goList) {
			if (go->m_nameKey == nameKey) {
				//見つけた
				T* p = dynamic_cast<T*>(go);
				return p;
			}
		}
		//見つからなかった
		return nullptr;
	}
	/*!
	*@brief	指定したタグのいずれかがが含まれるゲームオブジェクトを検索して、見つかった場合指定されたコールバック関数を呼び出す。
	*/
	template<class T>
	void FindGameObjects(const char* objectName, std::function<bool(T* go)> func)
	{
		unsigned int nameKey = Util::MakeHash(objectName);
		for (auto go : m_goList) {
			if (go->m_nameKey == nameKey) {
				//見つけた。
				T* p = dynamic_cast<T*>(go);
				if (func(p) == false) {
					//クエリ中断。
					return;
				}
			}
		}
	}
	/// <summary>
	/// 削除
	/// </summary>
	void Delete();
private:

	std::list< IGameObject* > m_goList;		//ゲームオブジェクトのリスト。
};
//外部からアクセスするので、extern宣言も必要。
extern GameObjectManager g_goMgr;
