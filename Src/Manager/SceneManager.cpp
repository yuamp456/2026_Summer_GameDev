#include <chrono>
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../Scene/PauseScene.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "SceneManager.h"

SceneManager* SceneManager::instance_ = nullptr;

void SceneManager::CreateInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();
}

SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

void SceneManager::Init(void)
{

	// カメラ
	camera_ = std::make_unique<Camera>();
	camera_->Init();

	// デルタタイム
	preTime_ = std::chrono::system_clock::now();

	// 3D用の設定
	Init3D();

	// 初期シーンの設定
	ChangeScene(SCENE_ID::TITLE);

}

void SceneManager::Init3D(void)
{

	// 背景色設定
	SetBackgroundColor(0, 139, 139);

	// Zバッファを有効にする
	SetUseZBuffer3D(true);

	// Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(true);

	// バックカリングを有効にする
	SetUseBackCulling(true);

	// ライトの設定
	SetUseLighting(true);
	
	// ライトの設定
	ChangeLightTypeDir({ 0.3f, -0.7f, 0.8f });


	// フォグ設定
	SetFogEnable(true);
	SetFogColor(5, 5, 5);
	SetFogStartEnd(10000.0f, 20000.0f);

}

void SceneManager::Update(void)
{

	if (scenes_.empty())
	{
		return;
	}

	// デルタタイム
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;

	scenes_.back()->Update();
	
	// カメラ更新
	camera_->Update();

}

void SceneManager::Draw(void)
{
	
	// 描画先グラフィック領域の指定
	// (３Ｄ描画で使用するカメラの設定などがリセットされる)
	SetDrawScreen(DX_SCREEN_BACK);

	// 画面を初期化
	ClearDrawScreen();

	// カメラ設定
	camera_->SetBeforeDraw();

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();

	// シーン描画
	for (auto& scene : scenes_)
	{
		scene->Draw();
	}

	// 主にポストエフェクト用
	camera_->Draw();

	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
	

}

void SceneManager::Destroy(void)
{

	delete instance_;

}

void SceneManager::ChangeScene(SCENE_ID sceneId)
{
	if (scenes_.empty())
	{
		scenes_.push_back(CreateSceneById(sceneId));
	}
	else
	{
		scenes_.back() = CreateSceneById(sceneId);
	}
}

void SceneManager::PushScene(SCENE_ID sceneId)
{
	scenes_.push_back(CreateSceneById(sceneId));
}

void SceneManager::PopScene(void)
{
	if (scenes_.size()>1)
	{
		scenes_.pop_back();
	}
}

float SceneManager::GetDeltaTime(void) const
{
	//return 1.0f / 60.0f;
	return deltaTime_;
}

Camera* SceneManager::GetCamera(void) const
{
	return camera_.get();
}

SceneManager::SceneManager(void)
{
}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();
}

std::unique_ptr<SceneBase> SceneManager::CreateSceneById(SCENE_ID sceneId)
{
	static const std::unordered_map<SCENE_ID, std::function<std::unique_ptr<SceneBase>()>> sceneFactory = {
		{ SCENE_ID::TITLE, []() { return std::make_unique<TitleScene>(); } },
		{ SCENE_ID::GAME, []() { return std::make_unique<GameScene>(); } },
		{ SCENE_ID::PAUSE, []() { return std::make_unique<PauseScene>(); } },
	};

	return sceneFactory.at(sceneId)();
}


