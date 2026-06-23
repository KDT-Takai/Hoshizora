#include "Tittle.h"
#include "ScreenManager.h"
#include "Home.h"

void Tittle::Update() {
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	bool hoverBack = (mouseX >= menuX && mouseX <= menuX + menuW && mouseY >= menuY && mouseY <= menuY + menuH);
	//if (hoverBack && InputManager::Instance().IsGetMouse(MOUSE_INPUT_LEFT)) {
	///	mode = MenuMode::DoDraw;
	//}
	//else if(InputManager::Instance().IsGetMouse(MOUSE_INPUT_LEFT))
	if(InputManager::Instance().IsGetMouse(MOUSE_INPUT_LEFT))
	ScreenManager::Instance().ChangeScreen<Home>();

}

void Tittle::Draw() {
//	DrawGraph(0,0,image,true);
//	DrawRotaGraph(WINDOW_W/2,WINDOW_H/2,1,0,image,1);
	DrawRotaGraph(WINDOW_W/2-70,WINDOW_H/2,0.3,0, tittle,1);
	DrawFormatString(WINDOW_W / 2 - 80, WINDOW_H - 50, GetColor(180, 180, 180),"Left Mouse Click");
//	DrawFormatString(10,10,GetColor(WHITE),"Title");
	//switch (mode)
	//{
	//case MenuMode::NoDraw:
	//	break;
	//case MenuMode::DoDraw:
	//	DrawFillBox(0,0,100,100,GetColor(RED));
	//	break;
	//default:
	//	break;
	//}

	// メニューボタン
//	DrawFillBox(menuX, menuY, menuX + menuW, menuY + menuH,GetColor(WHITE));

	// 楕円
//	DrawOvalAA(150,100,50,50,64,GetColor(BLUE),false,20);
}