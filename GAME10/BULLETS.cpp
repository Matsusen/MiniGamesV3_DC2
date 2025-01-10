#include "BULLETS.h"
BULLETS::BULLETS(class GAME10_GAME* game):GAME_OBJECT10(game){
}
BULLETS::~BULLETS(){
	delete[] Bullets;
}
void BULLETS::SetBullets(const BULLETS::DATA& data){
	Bullet = data;
	Bullets = new BULLET[Bullet.totalNum];
}
void BULLETS::init(){
	Bullet.curNum = 0;
}
void BULLETS::launch(const VECTOR2& pos,int speed,int lane) {
	if (Bullet.curNum < Bullet.totalNum) {
		if (Bullet.BulletNum < 2 ) {
			int i = Bullet.curNum;
			Bullets[i].pos.x = pos.x + Bullet.ImgHalf;
			Bullets[i].pos.y = pos.y + Bullet.ImgHalf;
			Bullets[i].Lane = lane;
			Bullet.speed = speed;
			Bullet.curNum++;
		}
		else {
			for (int Bnum = 0; Bnum < Bullet.BulletNum; Bnum++) {
				if (lane + (Bnum - 1) > -1 && lane + (Bnum - 1) < Bullet.LaneMax) {
					int i = Bullet.curNum;
					Bullets[i].pos.x = pos.x + Bullet.ImgHalf;
					Bullets[i].pos.y = pos.y + Bullet.ImgHalf + ((Bnum - 1) * Bullet.Bmy);
					Bullets[i].Lane = lane + (Bnum - 1);
					Bullet.speed = speed;
					Bullet.curNum++;
				}
			}
		}
	}
}
void BULLETS::update(){
	for (int i = Bullet.curNum - 1; i >= 0; i--) {
		Bullets[i].pos.x += Bullet.speed;
		if (Bullets[i].pos.x > width) {
			kill(i);
		}
	}
}
void BULLETS::kill(int i) {
	Bullet.curNum--;
	Bullets[i] = Bullets[Bullet.curNum];
}
void BULLETS::AllKill() {
	for (int i = 0; i < Bullet.curNum; i++) {
		Bullets[i] = Bullets[Bullet.curNum];
	}
	Bullet.curNum = NULL;
}
void BULLETS::draw(int bulletKind){
	image(Bullet.imgShadow, Bullets[bulletKind].pos.x, Bullets[bulletKind].pos.y + 100);
	image(Bullet.img, Bullets[bulletKind].pos.x, Bullets[bulletKind].pos.y);
}