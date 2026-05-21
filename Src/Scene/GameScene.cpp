#include <DxLib.h>
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Camera.h"
#include "../Manager/InputManager.h"
#include "../Object/Common/Capsule.h"
#include "../Object/Common/Collider.h"
#include "GameScene.h"

namespace{
	static constexpr int fade_interval = 60;
}

GameScene::GameScene(void)
	:SceneBase(),
	fadeCounter_(fade_interval),
	updateFunc_(&GameScene::FadeInUpdate),
	drawFunc_(&GameScene::FadeDraw)
{

}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	//SceneManager::GetInstance().GetCamera()->SetFollow(&player_->GetTransform());
	SceneManager::GetInstance().GetCamera()->ChangeMode(Camera::MODE::FOLLOW);

}

void GameScene::Update(void)
{
	(this->*updateFunc_)();

}

void GameScene::Draw(void)
{

	DrawFormatString(20, 20, 0x000000, "GameScene");

	(this->*drawFunc_)();

	//// ヘルプ
	//DrawFormatString(840, 20, 0x000000, "移動　　：WASD");
	//DrawFormatString(840, 40, 0x000000, "カメラ　：矢印キー");
	//DrawFormatString(840, 60, 0x000000, "ダッシュ：右Shift");
	//DrawFormatString(840, 80, 0x000000, "ジャンプ：＼(バクスラ)");

}

void GameScene::FadeInUpdate(void)
{
	if (--fadeCounter_ <= 0)
	{
		updateFunc_ = &GameScene::NormalUpdate;
		drawFunc_ = &GameScene::NormalDraw;
	}
}

void GameScene::FadeOutUpdate(void)
{
	if (++fadeCounter_ >= fade_interval)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
		return;
	}
}

void GameScene::NormalUpdate(void)
{
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		updateFunc_ = &GameScene::FadeOutUpdate;
		drawFunc_ = &GameScene::FadeDraw;
	}
	if (ins.IsTrgDown(KEY_INPUT_P))
	{
		SceneManager::GetInstance().PushScene(SceneManager::SCENE_ID::PAUSE);
	}
}

void GameScene::FadeDraw(void)
{
}

void GameScene::NormalDraw(void)
{
}
