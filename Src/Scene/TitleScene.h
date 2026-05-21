#pragma once
#include "SceneBase.h"

class TitleScene : public SceneBase
{

public:

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	static constexpr int fade_interval = 60;
	int fadeCounter_;

	//Update関数ポインタ
	void (TitleScene::* updateFunc_)(void);
	//Draw関数ポインタ
	void (TitleScene::* drawFunc_)(void);

	//Update関数
	void FadeInUpdate(void);
	void FadeOutUpdate(void);
	void NormalUpdate(void);

	//Draw関数
	void FadeDraw(void);
	void NormalDraw(void);
};
