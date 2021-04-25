#ifndef __DALEK_H__
#define __DALEK_H__

#include <Windows.h>

const HPEN dalekPenStroke = CreatePen(PS_SOLID, 2, RGB(0xa8, 0x89, 0x12));
const HBRUSH dalekHullFill = CreateSolidBrush(RGB(0xa8, 0x89, 0x12));
const HBRUSH dalekPartFill1 = CreateSolidBrush(RGB(0x80, 0x80, 0x80));
const HBRUSH dalekPartFill2 = CreateSolidBrush(RGB(0, 0, 0));
const HPEN dalekPart1 = CreatePen(PS_SOLID, 1, RGB(0x80, 0x80, 0x80));
const HBRUSH brushWhite = CreateSolidBrush(RGB(255, 255, 255));
const HPEN penWhite = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
const HPEN firePen = CreatePen(PS_SOLID, 1, RGB(0x0, 0xa9, 0xdf));
const HBRUSH fireBrush = CreateSolidBrush(RGB(0x0, 0xa9, 0xdf));


class Dalek {
public:
	Dalek(float, float);
	~Dalek();

	bool fire();
	float coord_x();
	float coord_y();
	void draw(HDC);
	void update();

private:
	float x, y;
	unsigned long long timer_reload;
	unsigned long long timer_firing;


	void step();
	void check();
	void shot(HDC);
};

#endif