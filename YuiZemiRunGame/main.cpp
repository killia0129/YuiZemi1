#include<math.h>
#include<vector>
#include"DxLib.h"
#include"Camera.h"
#include"Stage.h"
#include"LineEffect.h"
#include"Player.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(FALSE);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// 画面モードのセット
	SetUseLighting(false);
	SetGraphMode(1920, 1080, 32);
	SetDrawScreen(DX_SCREEN_BACK);
	
	SetFontSize(40);

	SetCameraNearFar(1.0f, 499.0f);

	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 0), VGet(0.0f, 0.0f, 250.0f));


	LineEffect* lineEff = new LineEffect;
	Stage* stage = new Stage;
	Player* player = new Player(VGet(0, -10, 20));

	float nowTime = GetNowCount();
	float prevTime = GetNowCount();
	float deltaTime = 0.f;

	float lineCool = 0.f;

	int seed = 0;

	std::vector<LineEffect*>lineEffBuff;

	while (CheckHitKey(KEY_INPUT_ESCAPE)==0)
	{
		ClearDrawScreen();

		nowTime = GetNowCount();
		deltaTime = (float)(nowTime - prevTime) / 1000.f;
		prevTime = nowTime;

		lineCool += deltaTime;
		seed++;

		if (seed > 1000)seed = 0;

		srand(seed);

		if (lineCool >= 0.3f)
		{
			for (int i = 0; i < 50; i++)
			{
				LineEffect* newObj = new LineEffect();
				lineEffBuff.emplace_back(newObj);
			}
			lineCool = 0.0f;
		}

		for (auto deleteLine: lineEffBuff)
		{
			if (deleteLine->IsEnd())
			{

				auto iter = std::find(lineEffBuff.begin(), lineEffBuff.end(), deleteLine);
				if (iter != lineEffBuff.end())
				{
					std::iter_swap(iter, lineEffBuff.end() - 1);
					lineEffBuff.pop_back();
				}
			}
		}

		stage->Update(deltaTime);
		for (auto ptr : lineEffBuff)
		{
			ptr->Update(deltaTime);
		}
		player->Update(deltaTime);

		for (auto ptr : lineEffBuff)
		{
			ptr->Draw();
		}

		stage->Draw();

		player->Draw();

		ScreenFlip();
		
	}

	DxLib_End();

	return 0;
}