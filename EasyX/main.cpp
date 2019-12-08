#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define WIDTH 640
#define HEIGHT 480
#define SIZE 20
#define MAXSNACKSIZE 1000
#define SPEED 150
#define MKLBUTTON 1

typedef struct {
	int x;
	int y;
}Coor;
enum Ch { up = 72,down = 80, left = 75,right=77 };
struct snackStruct{
	int snackSize;
	Coor scr[MAXSNACKSIZE];
	Ch ch;
}SnackStruct;
struct foodStruct{
	Coor foodweizhi;
	int flag;	

}FoodStruct;
IMAGE  food, body, snackright, snackleft, snackup, snackdown;

MOUSEMSG MouseMsg;

void ChangeDirection();
void GameInit();
void FoodCoor();
void FoodPaint();
void SnackMove();
void SnackPaint(IMAGE image);
void EatFood();
bool SnackDead();
void GameStart();
int CatchMouseMsg();
void GameRecord();
bool SnackDeadSelf();
IMAGE JudgeDirection();

int main() {
	
	GameStart();

	if (CatchMouseMsg() == MKLBUTTON) {
		GameInit();
		GameRecord();
		mciSendString("open shuohao.mp3 alias music", 0, 0, 0);
		mciSendString("play music repeat", 0, 0, 0);

		while (1) {
			while (!_kbhit()) {

				EatFood();
				SnackMove();
				if (SnackDead()||SnackDeadSelf()) {
					closegraph();
					exit(1);
				}
				Sleep(SPEED);
			}
			ChangeDirection();
		}
	}
	
	return 0;
}

void GameInit() {

	loadimage(&food, "food.jpg", SIZE, SIZE);
	loadimage(&snackright, "snackright.jpg", SIZE , SIZE );
	loadimage(&snackleft, "snackleft.jpg", SIZE, SIZE);
	loadimage(&snackup, "snackup.jpg", SIZE , SIZE );
	loadimage(&snackdown, "snackdown.jpg", SIZE, SIZE);
	loadimage(&body, "body.jpg", SIZE, SIZE);

	FoodStruct.flag = 0;
	SnackStruct.ch = right;
	SnackStruct.scr[0].x = 100;
	SnackStruct.scr[0].y = 100;
	SnackStruct.snackSize = 1;
	FoodCoor();
}
void FoodCoor() {
	srand((unsigned int)time(NULL));
	FoodStruct.foodweizhi.x = (rand() % 31 + 1) * SIZE;
	FoodStruct.foodweizhi.y = (rand() % 23 + 1) * SIZE;
	FoodStruct.flag = 1;
}
void FoodPaint() {
	putimage(FoodStruct.foodweizhi.x, FoodStruct.foodweizhi.y,&food);
}
void ChangeDirection() {
	char key;
	key = _getch();
	switch (key) {
	case 72:
		if (SnackStruct.ch != down) {
			SnackStruct.ch = up;
		}
		break;
	case 80:
		if (SnackStruct.ch != up) {
			SnackStruct.ch = down;
		}
		break;
	case 75:
		if (SnackStruct.ch != right) {
			SnackStruct.ch = left;
		}
		break;
	case 77:
		if (SnackStruct.ch != left) {
			SnackStruct.ch = right;
		}
		break;
	}

}
void SnackPaint(IMAGE image) {

	putimage(SnackStruct.scr[0].x, SnackStruct.scr[0].y, &image);
	for (int i = SnackStruct.snackSize; i > 0; i--) {
		putimage(SnackStruct.scr[i].x, SnackStruct.scr[i].y, &body);
	}
}
IMAGE JudgeDirection() {
	switch(SnackStruct.ch) {
	case up:
		return snackup;
	case down:
		return snackdown;
	case left:
		return snackleft;
	case right:
		return snackright;
	}
	return NULL;
}
void SnackMove() {

	IMAGE image = JudgeDirection();

	for (int i = SnackStruct.snackSize ; i > 0; i--) {
		SnackStruct.scr[i].x = SnackStruct.scr[i - 1].x;
		SnackStruct.scr[i].y = SnackStruct.scr[i - 1].y;
	}
	switch (SnackStruct.ch) {
	case up:
		SnackStruct.scr[0].y = SnackStruct.scr[0].y - SIZE;
		break;
	case down:
		SnackStruct.scr[0].y = SnackStruct.scr[0].y + SIZE;
		break;
	case left:
		SnackStruct.scr[0].x = SnackStruct.scr[0].x - SIZE;
		break;
	case right:
		SnackStruct.scr[0].x = SnackStruct.scr[0].x + SIZE;
		break;
	}
	cleardevice();
	SnackPaint(image);
	FoodPaint();
	GameRecord();
}
void EatFood() {
	if (SnackStruct.scr[0].x == FoodStruct.foodweizhi.x && SnackStruct.scr[0].y == FoodStruct.foodweizhi.y) {
		SnackStruct.snackSize++;
		FoodCoor();
		cleardevice();
	}
}
bool SnackDead(){
	if (SnackStruct.scr[0].x < 0 || SnackStruct.scr[0].x>680 || SnackStruct.scr[0].y < 0 || SnackStruct.scr[0].y>480) {
		return true;
	}
	else {
		return false;
	}


}
bool SnackDeadSelf() {
	for (int i = 1; i <= SnackStruct.snackSize; i++) {
		if (SnackStruct.scr[0].x == SnackStruct.scr[i].x && SnackStruct.scr[0].y == SnackStruct.scr[i].y) {
			return true;
		}
	}
	return false;
}
void GameStart() {

	char s[] = "Ì°³ÔÉß";
	char str[] = "¿ªÊ¼ÓÎÏ·";

	initgraph(WIDTH, HEIGHT);
	setbkcolor(WHITE);
	cleardevice();

	setcolor(BLACK);
	rectangle(210, 300, 422, 369);
	
	setcolor(BLACK);
	rectangle(205, 295, 427, 374);

	setcolor(RED);
	settextstyle(100, 60, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(150, 100, s);

	settextstyle(40, 20, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(230, 318, str);
}
int CatchMouseMsg() {
	while (1) {
		MouseMsg = GetMouseMsg();
		if ((MouseMsg.x > 213 && MouseMsg.x < 422) && (MouseMsg.y > 300 && MouseMsg.y < 369)) {
			if (MouseMsg.mkLButton) {
				cleardevice();
				return 1;
			}
		}
	}
}
void GameRecord() {
	char record[] = "·ÖÊý£º";
	char c[10];
	_itoa_s((SnackStruct.snackSize - 1) * 10, c, 10);
	setcolor(RED);
	settextstyle(25,10 , _T("Î¢ÈíÑÅºÚ"));
	outtextxy(5, 5, record);

	setcolor(RED);
	settextstyle(25, 10, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(60, 5, c);

	setcolor(RED);
	rectangle(0, 0, 100, 40);
}