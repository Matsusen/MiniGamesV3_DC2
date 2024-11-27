#include "STAGE.h"
#include"GAME10_GAME.h"
#include"CONTAINER.h"
#include "../../libOne/inc/libOne.h"
#include"GAME10_GAME.h"
#include"HANDGUN_BULLETS.h"
#include"ENEMYS.h"
#include"WEAPONS.h"
STAGE::STAGE(GAME10_GAME* game) :SCENE(game) {}
STAGE::~STAGE() {
}
void STAGE::init() {
	Stage = game()->container()->stage();
	game()->player()->init();
	game()->time()->init();
	game()->enemies()->init();
	game()->bullets(GAME10_GAME::HANDGUNBULLET_ID)->init();
}
void STAGE::goalStage() {
	Stage.bworldX = NULL;
	Stage.fworldX = NULL;
	game()->bullets(GAME10_GAME::HANDGUNBULLET_ID)->AllKill();//弾丸を全部消す
	game()->bullets(GAME10_GAME::SHOTGUN_ID)->AllKill();//弾丸を全部消す
	game()->enemies()->AllKill();//敵を全部消す
	//game()->objects()->AllKill();//オブジェクトを全部消す
	game()->player()->stageGoal();
}
void STAGE::appear() {
	game()->enemies()->appear();
	//game()->objects()->appear();
}
void STAGE::update() {
	//ステージの強制スクロール（スピードはプレイヤーのスピードの依存する）
	if (Stage.gPos.x - Stage.fworldX > width / 2 
		&& (int)game()->player()->playerData().Opos.x == (int)game()->player()->playerData().Pos.x) {
		Stage.frontMx = game()->player()->playerData().speed;
		Stage.fworldX += Stage.frontMx;
		if (game()->player()->playerData().speed >= Stage.backMx) {
			Stage.bworldX += game()->player()->playerData().speed - Stage.backMx;
		}
		game()->time()->timeCount();//強制スクロール中のみ時間が進む
		if(Stage.gPos.x - Stage.fworldX > width ){
			appear();//敵の出現だけ制限する
		}
	}
	//ゴールテープが画面の中央に来た時、プレイヤーだけ動くようにするために少しだけプレイヤーを動かす。
	else if(game()->player()->playerData().Opos.x == game()->player()->playerData().Pos.x){
		game()->player()->playerMove();
	}

	//プレイヤーがgoalしたときの処理
	if (game()->player()->playerData().Pos.x > width) {
		goalStage();
	}
	//エネミーのスピードを変える（プレイヤーの速度依存のため）
	game()->enemies()->update();
	game()->player()->update();
	//game()->objects()->update();
}
void STAGE::create() {
	Stage = game()->container()->stage();
	game()->player()->create();
	game()->enemies()->create();
	//game()->objects()->create();
	game()->Hp_gauge(GAME10_GAME::PLAYERHP_ID)->create();
	game()->Hp_gauge(GAME10_GAME::ENEMYHP_ID)->create();
	game()->Hp_gauge(GAME10_GAME::OBJECTHP_ID)->create();
}
void STAGE::draw() {
	clear(255);
	printSize(200);
	image(Stage.stageImg, Stage.imgPos.x, Stage.imgPos.y);
	for (int i = 0; i < Stage.bImgNum; i++) {
		image(Stage.backImg, (Stage.backPos.x + Stage.ImgLen * i) - Stage.bworldX, Stage.backPos.y);
	}
	for (int i = 0; i < Stage.fImgNum; i++) {
		image(Stage.frontImg, (Stage.frontPos.x + Stage.ImgLen * i) - Stage.fworldX, Stage.frontPos.y);
	}
	for (int j = 0; j < Stage.LaneLenNum; j++) {
		for (int i = 0; i < Stage.LaneNum; i++) {
			image(Stage.Lanes[i].LaneImg, (Stage.Lanes[i].Pos.x + width * j) - Stage.fworldX, Stage.Lanes[i].Pos.y);
		}
	}
	if (Stage.gPos.x - Stage.fworldX < width) {
		image(Stage.GoalImg, Stage.gPos.x - Stage.fworldX, Stage.gPos.y);
	}

	//game()->bullets(GAME10_GAME::HANDGUNBULLET_ID)->draw();
	//game()->bullets(GAME10_GAME::SHOTGUN_ID)->draw();
	//for (int i = 0; i < game()->enemies()->uniEnemy().nowNum; i++) {
	//	if (game()->player()->playerRight() > game()->enemies()->EnemiesLeft(i)) {//敵とプレイヤーがかぶった瞬間だけ前後の処理をする
	//		if (game()->player()->playerData().nowLane < game()->enemies()->EnemiesLane(i)) {//敵が手前だった場合後で描画する
	//			game()->player()->draw();
	//			Stage.frontImgNumber = i;
	//		}
	//		else {
	//			game()->enemies()->draw(i);
	//			game()->player()->draw();
	//		}
	//	
	//	else {
	//		game()->enemies()->draw(i);
	//		game()->player()->draw();
	//	}
	//}
	//if (Stage.frontImgNumber != Stage.NofrontImg) {
	//	game()->enemies()->draw(Stage.frontImgNumber);
	//	Stage.frontImgNumber = Stage.NofrontImg;
	//}

	for (int LNum = 0; Stage.LaneNum > LNum; LNum++) {
		layer(LNum);
	}

	if (game()->enemies()->uniEnemy().nowNum == NULL) {
		game()->player()->draw();//敵がいなかった場合はプレイヤーのみ描画される
	}
	game()->time()->draw();
	fill(255);
}
void STAGE::layer(int drawLane) {
	for (int ENum = 0; ENum < game()->enemies()->uniEnemy().nowNum; ENum++) {
		if (drawLane == game()->enemies()->EnemiesLane(ENum)) {
			game()->enemies()->draw(ENum);
		}
	}	

	for (int HBNum = 0; game()->bullets(GAME10_GAME::HANDGUNBULLET_ID)->BulletNum() > HBNum;HBNum++) {
		if (drawLane == game()->bullets(GAME10_GAME::HANDGUNBULLET_ID)->bulletLane(HBNum)) {
			game()->bullets(GAME10_GAME::HANDGUNBULLET_ID)->draw(HBNum);
		}
	}

	for (int SBNum = 0; game()->bullets(GAME10_GAME::SHOTGUNBULLET_ID)->BulletNum() > SBNum; SBNum++) {
		if (drawLane == game()->bullets(GAME10_GAME::SHOTGUNBULLET_ID)->bulletLane(SBNum)) {
			game()->bullets(GAME10_GAME::SHOTGUNBULLET_ID)->draw(SBNum);
		}
	}

	if (game()->player()->playerData().nowLane == drawLane) {
		game()->player()->draw();
	}
}
void STAGE::nextScene() {
	if (game()->time()->nowTime() <= NULL) {
		game()->changeScene(GAME10_GAME::RESULT_ID);
	}
}
