#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
	:SceneBase(),
	fadeCounter_(fade_interval),
	updateFunc_(&TitleScene::FadeInUpdate),
	drawFunc_(&TitleScene::FadeDraw)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	fadeCounter_ = fade_interval;
	// 定点カメラ
	SceneManager::GetInstance().GetCamera()->ChangeMode(Camera::MODE::FIXED_POINT);

}

void TitleScene::Update(void)
{
	(this->*updateFunc_)();
}

void TitleScene::Draw(void)
{
	DrawFormatString(20, 20, 0x000000, "TitleScene");
	(this->*drawFunc_)();
}

void TitleScene::FadeInUpdate(void)
{
	if (--fadeCounter_ <= 0)
	{
		updateFunc_ = &TitleScene::NormalUpdate;
		drawFunc_ = &TitleScene::NormalDraw;
	}
}

void TitleScene::FadeOutUpdate(void)
{
	if (++fadeCounter_ >= fade_interval)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		return;
	}
}

void TitleScene::NormalUpdate(void)
{
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		updateFunc_ = &TitleScene::FadeOutUpdate;
		drawFunc_ = &TitleScene::FadeDraw;
	}
}

void TitleScene::FadeDraw(void)
{
	NormalDraw();
	auto screenSize = Application::GetInstance().GetScreenSize();
	float rate = static_cast<float>(fadeCounter_) / fade_interval;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,rate * 255);
	DrawBox(0, 0, screenSize.x, screenSize.y, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw(void)
{
}
