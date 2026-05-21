#include<DxLib.h>
#include"../Application.h"
#include"../Common/Vector2.h"
#include"../Manager/InputManager.h"
#include"../Manager/SceneManager.h"
#include "PauseScene.h"

namespace {
	constexpr int margin_size = 50;		// 画面端からの余白
	constexpr int expand_interval = 30;	// のフレーム数
}

PauseScene::PauseScene() :
	expandCnt_(0),
	updateFunc_(&PauseScene::AppearUpdate),
	drawFunc_(&PauseScene::ExpandDraw)
{
}

PauseScene::~PauseScene()
{
}

void PauseScene::Init()
{
}

void PauseScene::Update()
{
	(this->*updateFunc_)();
}

void PauseScene::Draw()
{
	(this->*drawFunc_)();
}

void PauseScene::AppearUpdate()
{
	if (++expandCnt_ >= expand_interval)
	{
		updateFunc_ = &PauseScene::NormalUpdate;
		drawFunc_ = &PauseScene::NormalDraw;
	}
}

void PauseScene::NormalUpdate()
{
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_P))
	{
		updateFunc_ = &PauseScene::DisappearUpdate;
		drawFunc_ = &PauseScene::ExpandDraw;
	}
}

void PauseScene::DisappearUpdate()
{
	if (--expandCnt_ <= 0)
	{
		SceneManager::GetInstance().PopScene();
	}
}

void PauseScene::ExpandDraw()
{
	DrawFrame(static_cast<float>(expandCnt_) / static_cast<float>(expand_interval));
}

void PauseScene::NormalDraw()
{
	DrawFrame(1.0f);
}

void PauseScene::DrawFrame(float rate)
{
	const auto& windowSize = Application::GetInstance().GetScreenSize();

	auto centerY = windowSize.y / 2;
	auto height = (windowSize.y - margin_size) / 2 * rate;
	//黒影表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 168);
	DrawBoxAA(margin_size, centerY - height, windowSize.x - margin_size, centerY + height, 0, true, 3.0f);

	//枠の表示
	DrawBoxAA(margin_size, centerY - height, windowSize.x - margin_size, centerY + height,0xffffff,false,3.0f);
}