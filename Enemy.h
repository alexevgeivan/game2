#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <Windows.h>

const HPEN enemyPenStroke = CreatePen(PS_SOLID, 2, RGB(0, 255, 255));
const HBRUSH enemyBrush[3] = { CreateSolidBrush(RGB(0,0,0)),CreateSolidBrush(RGB(255,0,0)),CreateSolidBrush(RGB(0,255,0)) };


class Enemy {
public:
	Enemy();
	~Enemy();


	void draw(HDC);
	void update(bool, float, float);
	bool death();
	bool collision(float, float);

private:
	long double x, y, dx, dy;
	int enemy_hp;
	int hp;
	void step();
	void check(bool, float, float);


};

#endif