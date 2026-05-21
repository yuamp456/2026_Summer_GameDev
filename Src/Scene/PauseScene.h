#pragma once
#include "SceneBase.h"
class PauseScene : public SceneBase
{
public:
	PauseScene();
	~PauseScene();
	void Init() override;
	void Update() override;
	void Draw() override;

private:

	int expandCnt_;

	void(PauseScene::* updateFunc_)(void);
	void(PauseScene::* drawFunc_)(void);

	void AppearUpdate(void);
	void NormalUpdate(void);
	void DisappearUpdate(void);

	void ExpandDraw(void);
	void NormalDraw(void);

	void DrawFrame(float rate);
};

