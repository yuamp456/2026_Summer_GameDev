#pragma once
#include "SceneBase.h"
class Stage;
class SkyDome;
class Player;

class GameScene : public SceneBase
{

public:
	
	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	int fadeCounter_;

	//Update関数ポインタ
	void (GameScene::* updateFunc_)(void);
	//Draw関数ポインタ
	void (GameScene::* drawFunc_)(void);

	//Update関数
	void FadeInUpdate(void);
	void FadeOutUpdate(void);
	void NormalUpdate(void);

	//Draw関数
	void FadeDraw(void);
	void NormalDraw(void);
};
