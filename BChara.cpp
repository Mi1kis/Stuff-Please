//-----------------------------------------------------------------------------
//キャラクタ汎用スーパークラス
//-----------------------------------------------------------------------------
#include "BChara.h"
#include  "MyPG.h"
#include  "Task_Game.h"
#include  "Task_Player.h"

//-----------------------------------------------------------------------------
//モーションを更新（変更なしの場合	false)
/*bool  BChara::UpdateMotion(Motion  nm_)
{
	if (nm_ == this->motion) {
		return  false;
	}
	else {
		this->motion = nm_;		//モーション変更
		this->moveCnt = 0;		//行動カウンタクリア
		this->animCnt = 0;		//アニメーションカウンタのクリア
		return  true;
	}
}

//-----------------------------------------------------------------------------
//頭上接触判定
bool  BChara::CheckHead()
{
	//あたり判定を基にして頭上矩形を生成
	ML::Box2D  head(this->hitBase.x,
		this->hitBase.y - 1,
		this->hitBase.w,
		1);
	head.Offset((int)this->pos.x, (int)this->pos.y);


	auto   map = ge->GetTask_One_GN<Map2D::Object>("フィールド", "マップ");
	if (nullptr == map) { return false; }//マップが無ければ判定しない(出来ない）
	return map->CheckHit(head);
}
//-----------------------------------------------------------------------------
//めり込まない移動処理
void BChara::CheckMove(ML::Vec2&  e_)
{
	//マップが存在するか調べてからアクセス
	auto   map = ge->GetTask_One_GN<Map2D::Object>("フィールド", "マップ");
	if (nullptr == map) { return; }//マップが無ければ判定しない(出来ない）

								   //横軸に対する移動
	while (e_.x != 0) {
		float  preX = this->pos.x;
		if (e_.x >= 1) { this->pos.x += 1;		e_.x -= 1; }
		else if (e_.x <= -1) { this->pos.x -= 1;		e_.x += 1; }
		else { this->pos.x += e_.x;		e_.x = 0; }
		ML::Box2D  hit = this->hitBase.OffsetCopy(this->pos);
		if (true == map->CheckHit(hit)) {
			this->pos.x = preX;		//移動をキャンセル
			break;
		}
	}
	//縦軸に対する移動
	while (e_.y != 0) {
		float  preY = this->pos.y;
		if (e_.y >= 1) { this->pos.y += 1;		e_.y -= 1; }
		else if (e_.y <= -1) { this->pos.y -= 1;		e_.y += 1; }
		else { this->pos.y += e_.y;		e_.y = 0; }
		ML::Box2D  hit = this->hitBase.OffsetCopy(this->pos);
		if (true == map->CheckHit(hit)) {
			this->pos.y = preY;		//移動をキャンセル
			break;
		}
	}
}
//-----------------------------------------------------------------------------
//足元接触判定
bool  BChara::CheckFoot()
{
	//あたり判定を基にして足元矩形を生成
	ML::Box2D  foot(this->hitBase.x,
		this->hitBase.y + this->hitBase.h,
		this->hitBase.w,
		1);
	foot.Offset(this->pos);

	auto   map = ge->GetTask_One_GN<Map2D::Object>("フィールド", "マップ");
	if (nullptr == map) { return false; }//マップが無ければ判定しない(出来ない）
	return map->CheckHit(foot);
}*/
bool BChara::CheckRes() {
	switch (this->category) {
	case Normal:
		if (this->route == Straight) {
			return true;
		}
		break;
	case Transfer:
		if (this->route == Trans)
			return true;
		break;
	case Explosive:
		break;
	case Hydro:
		break;
	case Weapon:
		break;
	case Drug:
		if (this->route == Dog)
			return true;
		break;
	case Overvalue:
		if (this->route == Customs)
			return true;
		break;
	}
	return false;
}


void  BChara::ChangeRoute(Route r) {
	this->route = r;
}

void  BChara::Focus() {

}
void  BChara::XRay() {

}
bool  BChara::CheckDogDrug()
{

	return 0;
}
void  BChara::IncreMoney(Category cat)
{
	auto p = Player::Object::Create(true);
	switch (cat) {
		
	}
}
bool  BChara::CheckNormal()
{
	if (this->category != Normal)
		return false;
	else
		return true;
}

void  BChara::PatrolDog()
{

}

void  BChara::Tax()
{

}

int  BChara::getMoveSpeed() 
{
	auto p = ge->GetTask_One_GN<Player::Object>("プレイヤ", "仮");
	if (ge->mouse) {
		auto inp = ge->mouse->GetState();
		if (inp.wheel > 0)
			p->speed += 0.25f;
		else if (inp.wheel < 0)
			p->speed -= 0.25f;
	}
	if (p->speed > 10)
		p->speed = 10;
	if (p->speed < -10)
		p->speed = -10;
	return p->speed;
}