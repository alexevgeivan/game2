#include "Dalek.h"
#include <ctime>

#define shoot_time 1000

Dalek::Dalek(float x, float y) {
	this->x = x;
	this->y = y;
	this->timer_firing = -shoot_time;
	this->timer_reload = 0;
}

Dalek::~Dalek() {

}



void Dalek::check() {
	if (x > 1800)x -= 0.005;
	if (x < 50)x += 0.005;
	if (y > 1050)y -= 0.005;
	if (y < 20)y += 0.005;
}

void Dalek::shot(HDC hDC) {

}

void Dalek::step() {
	if (GetAsyncKeyState(VK_RIGHT)) {
		x += 0.005;
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		x -= 0.005;
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		y += 0.005;
	}
	if (GetAsyncKeyState(VK_UP)) {
		y -= 0.005;
	}
	if (GetAsyncKeyState(VK_SPACE) && clock() - timer_reload>1000) {
		timer_firing = clock();
		timer_reload = clock();
	}
}

void Dalek::draw(HDC hDC) {
	SelectObject(hDC, dalekPart1);
	SelectObject(hDC, dalekPartFill1);
	Rectangle(hDC, x + 20, y - 2, x + 70, y + 2);
	Rectangle(hDC, x, y - 50, x + 35, y - 48);
	MoveToEx(hDC, x + 18, y - 52, NULL);
	LineTo(hDC, x + 18, y - 46);
	MoveToEx(hDC, x + 20, y - 54, NULL);
	LineTo(hDC, x + 20, y - 44);
	MoveToEx(hDC, x + 22, y - 55, NULL);
	LineTo(hDC, x + 22, y - 43);
	MoveToEx(hDC, x + 24, y - 55, NULL);
	LineTo(hDC, x + 24, y - 43);
	MoveToEx(hDC, x + 26, y - 54, NULL);
	LineTo(hDC, x + 26, y - 44);
	MoveToEx(hDC, x + 28, y - 52, NULL);
	LineTo(hDC, x + 28, y - 46);
	SelectObject(hDC, dalekPartFill2);
	Ellipse(hDC, x + 35, y - 56, x + 49, y - 42);
	Ellipse(hDC, x + 65, y - 10, x + 85, y + 10);
	SelectObject(hDC, brushWhite);
	SelectObject(hDC, penWhite);
	Rectangle(hDC, x + 75, y - 11, x + 86, y + 11);
	SelectObject(hDC, dalekHullFill);
	SelectObject(hDC, dalekPenStroke);
	Ellipse(hDC, x - 30, y - 55, x + 15, y - 15);
	Rectangle(hDC, x - 30, y - 35, x + 15, y - 25);
	POINT p[4] = { { x + 15,y - 25 },{ x + 50,y + 65 },{ x - 40,y + 65 },{ x - 30,y - 25 } };
	Polygon(hDC, p, 4);
	if ((clock() - timer_firing<shoot_time) && ((clock() - timer_firing) % 40 <= 15)) {
		SelectObject(hDC, fireBrush);
		SelectObject(hDC, firePen);
		Rectangle(hDC, x + 75, y - 3, 2000, y + 3);

	}
}

void Dalek::update() {
	step();
	check();
}

bool Dalek::fire() {
	return clock() - timer_firing < shoot_time;
}

float Dalek::coord_x() {
	return x;
}

float Dalek::coord_y() {
	return y;
}