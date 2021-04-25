#include <iostream>
#include <Windows.h>
#include <ctime>
#include <conio.h>
#include <thread>
#include <vector>

#include "Enemy.h"
#include "Dalek.h"

using namespace std;

//const int N = 16;
#define max 64
int score = 0;

bool running = 1;

Dalek *dalek = new Dalek(200, 200);
//Enemy *enemy[N];
vector<Enemy*> enemy;

HDC winDC = GetDC(GetConsoleWindow());
HDC hDC;

HBRUSH white = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));

COORD scrn;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

unsigned long long timer;


void graphics() {
	while (running) {
		hDC = CreateCompatibleDC(winDC);
		HBITMAP hBmp = CreateCompatibleBitmap(winDC, 1900, 1300);
		HBITMAP hOldBmp = (HBITMAP)SelectObject(hDC, hBmp);

#if 1
		SelectObject(hDC, white);
		Rectangle(hDC, -100, -100, 1900, 1300);
		dalek->draw(hDC);
		for (int i = 0; i < enemy.size(); i++) {
			enemy[i]->draw(hDC);
		}
		scrn.X = 0; scrn.Y = 0;
		SetConsoleCursorPosition(h, scrn);
		cout << "Ваш счёт: " << score << " очков";
#endif

		BitBlt(winDC, -100, -100, 2000, 1400, hDC, -100, -100, SRCCOPY);

		SelectObject(hDC, hOldBmp);
		DeleteObject(hBmp);
		DeleteDC(hDC);
	}
}

int main() {
	enemy.resize(16);
	for (int i = 0; i < enemy.size(); i++) {
		enemy[i] = new Enemy();
	}
	thread graphicsThread(graphics);
	graphicsThread.detach();
	setlocale(LC_ALL, "Russian");
	SetConsoleTextAttribute(h, 0xf9);
	SetConsoleTitle("The Dalek: RETURN");

	srand(time(0));




	timer = clock();
	while (!GetAsyncKeyState(VK_ESCAPE)) {
		/*if ((clock() - timer) >= 1000 / fps) {
		timer = clock();
		SelectObject(hDC, white);
		Rectangle(hDC, -100, -100, 1900, 1300);
		dalek->draw(hDC);
		for (int i = 0; i < N; i++) {
		enemy[i]->draw(hDC);
		}
		scrn.X = 0; scrn.Y = 0;
		SetConsoleCursorPosition(h, scrn);
		cout << "Ваш счёт: " << score << " очков";

		}
		else {*/
		if (GetAsyncKeyState(VK_TAB)) {
			while (!GetAsyncKeyState(VK_SPACE));
		}
		if (enemy.size() == 0) {
			running = 0;
			SetConsoleTextAttribute(h, 10);
			system("cls");
			scrn.X = 60; scrn.Y = 20;
			SetConsoleCursorPosition(h, scrn);
			cout << "Вы победили";
			scrn.X = 60; scrn.Y = 21;
			SetConsoleCursorPosition(h, scrn);
			score *= 2;
			cout << "Ваш счёт: " << score << " очков";
			Sleep(1000);
			system("pause >nul");
			goto out;
		}
		if (rand() % 100000 == 0 && enemy.size()<max)enemy.push_back(new Enemy());
		dalek->update();
		/*for (int i = 0; i<N; i++)
		enemy[i]->update(0, dalek->coord_x(), dalek->coord_y());*/
		if (dalek->fire()) {
			for (int i = enemy.size() - 1; i >= 0; i--) {
				enemy[i]->update(1, dalek->coord_x(), dalek->coord_y());
				if (enemy[i]->death()) {
					score++;
					delete enemy[i];
					enemy.erase(enemy.begin() + i);
				}

			}
		}
		else {
			for (int i = 0; i<enemy.size(); i++)
				enemy[i]->update(0, dalek->coord_x(), dalek->coord_y());
		}
		bool c = 0;
		float x = dalek->coord_x(), y = dalek->coord_y();
		for (int i = 0; i < enemy.size(); i++) {
			c |= enemy[i]->collision(x, y);
		}
		if (c) {
			running = 0;
			SetConsoleTextAttribute(h, 10);
			system("cls");
			scrn.X = 60; scrn.Y = 20;
			SetConsoleCursorPosition(h, scrn);
			cout << "Вы проиграли";
			scrn.X = 60; scrn.Y = 21;
			SetConsoleCursorPosition(h, scrn);
			cout << "Ваш счёт: " << score << " очков";
			Sleep(1000);
			system("pause >nul");
			goto out;
		}
	}
	//}
out:
	delete dalek;
	for (int i = 0; i < enemy.size(); i++) {
		delete enemy[i];
	}
}