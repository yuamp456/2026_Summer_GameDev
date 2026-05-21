#pragma once
#include <chrono>
#include<memory>
#include<list>

class SceneBase;
class Camera;

class SceneManager
{

public:

	// シーン管理用
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		GAME,
		PAUSE,
	};
	
	// インスタンスの生成
	static void CreateInstance(void);

	// インスタンスの取得
	static SceneManager& GetInstance(void);

	void Init(void);
	void Init3D(void);
	void Update(void);
	void Draw(void);

	// リソースの破棄
	void Destroy(void);

	// 状態遷移
	void ChangeScene(SCENE_ID sceneId);
	void PushScene(SCENE_ID sceneId);
	void PopScene(void);

	// デルタタイムの取得
	float GetDeltaTime(void) const;

	// カメラの取得
	Camera* GetCamera(void) const;

private:

	// 静的インスタンス
	static SceneManager* instance_;

	//SCENE_ID sceneId_;
	//SCENE_ID waitSceneId_;

	// 各種シーン
	std::list<std::unique_ptr<SceneBase>> scenes_;

	// カメラ
	std::unique_ptr<Camera> camera_;

	// デルタタイム
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;
	
	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	SceneManager(void);
	// コピーコンストラクタも同様
	SceneManager(const SceneManager& manager) = default;
	// デストラクタも同様
	~SceneManager(void) = default;

	// デルタタイムをリセットする
	void ResetDeltaTime(void);

	std::unique_ptr<SceneBase> CreateSceneById(SCENE_ID sceneId);
};
