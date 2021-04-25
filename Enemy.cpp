#include "Enemy.h"
#include<cmath>
#include<ctime>


Enemy::Enemy() {
	this->x = 1900;
	this->y = rand() % 1000 + 50;
	this->dx = (rand() % 2000 + 1) / 1000000.0;
	this->dy = (0.025 + (rand() % 500) / 10000.0) / 100.0;
	this->enemy_hp = 40000;
	this->hp = rand() % enemy_hp;

}

Enemy::~Enemy() {

}

void Enemy::check(bool f, float dalek_x, float dalek_y) {
	if (y < 10 || y>1000)dy = -dy;
	if (x < 10)x = 1900;
	if (f) {
		if (abs(y - dalek_y) < 32 && dalek_x < x) {
			hp--;
		}
	}
}

void Enemy::step() {
	x -= dx;
	y += dy;
}

void Enemy::update(bool f, float dalek_x, float dalek_y) {
	step();
	check(f, dalek_x, dalek_y);
}

void Enemy::draw(HDC hDC) {
	SelectObject(hDC, enemyPenStroke);
	SelectObject(hDC, enemyBrush[2]);
	Rectangle(hDC, x - 16, y - 16, x - 16 + 32 * hp / (float)enemy_hp, y + 16);
	SelectObject(hDC, enemyBrush[1]);
	Rectangle(hDC, x - 16 + 32 * hp / (float)enemy_hp, y - 16, x + 16, y + 16);
}

bool Enemy::death() {
	if (hp == 0) {
		x = 1900;
		y = rand() % 1000 + 50;
		dx = (rand() % 2000 + 1) / 1000000.0;
		dy = (0.025 + (rand() % 500) / 10000.0) / 100.0;
		enemy_hp += rand() % 10000;
		hp = rand() % enemy_hp;
		return 1;
	}
	else return 0;
}

bool Enemy::collision(float dalek_x, float dalek_y) {
	if (abs(y - dalek_y) < 100 && abs(x - dalek_x) < 100)return 1;
	else return 0;
}