//-------------------------------------------------------------------
//プレイヤ
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Player.h"

namespace  Player
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//リソースの初期化
	bool  Resource::Initialize()
	{
		
		return true;
	}
	//-------------------------------------------------------------------
	//リソースの解放
	bool  Resource::Finalize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//「初期化」タスク生成時に１回だけ行う処理
	bool  Object::Initialize()
	{
		//スーパークラス初期化
		__super::Initialize(defGroupName, defName, true);
		//リソースクラス生成orリソース共有
		this->res = Resource::Create();

		//★データ初期化
		this->speed = 5;
		//★タスクの生成

		return  true;
	}
	//-------------------------------------------------------------------
	//「終了」タスク消滅時に１回だけ行う処理
	bool  Object::Finalize()
	{
		//★データ＆タスク解放


		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//★引き継ぎタスクの生成
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//「更新」１フレーム毎に行う処理
	void  Object::UpDate()
	{
		
	}
	//-------------------------------------------------------------------
	//「２Ｄ描画」１フレーム毎に行う処理
	void  Object::Render2D_AF()
	{
	}
	//-----------------------------------------------------------------------------
	//思考＆状況判断　モーション決定
	
	//-----------------------------------------------------------------------------
	//アニメーション制御
	/*BChara::DrawInfo  Object::Anim()
	{
		ML::Color  defColor(1, 1, 1, 1);
		BChara::DrawInfo imageTable[] = {
			//draw							src
			{ ML::Box2D(-16, -40, 32, 80), ML::Box2D(0, 0, 32, 80), defColor },	//停止
			{ ML::Box2D(-4, -40, 32, 80), ML::Box2D(32, 0, 32, 80), defColor },	//歩行１
			{ ML::Box2D(-20, -40, 48, 80), ML::Box2D(64, 0, 48, 80), defColor },	//歩行２
			{ ML::Box2D(-20, -40, 48, 80), ML::Box2D(112, 0, 48, 80), defColor },	//歩行３
			{ ML::Box2D(-24, -40, 48, 80), ML::Box2D(48, 80, 48, 80), defColor },	//ジャンプ
			{ ML::Box2D(-24, -40, 48, 80), ML::Box2D(96, 80, 48, 80), defColor },	//落下
			{ ML::Box2D(-24, -24, 48, 64), ML::Box2D(0, 80, 48, 64), defColor },	//飛び立つ直前
			{ ML::Box2D(-24, -24, 48, 64), ML::Box2D(144, 80, 48, 64), defColor },	//着地
		};
		BChara::DrawInfo  rtv;
		int  work;
		switch (this->motion) {
		default:		rtv = imageTable[0];	break;
		//	ジャンプ------------------------------------------------------------------------
		case  Jump:		rtv = imageTable[4];	break;
		//	停止----------------------------------------------------------------------------
		case  Stand:	rtv = imageTable[0];	break;
		//	歩行----------------------------------------------------------------------------
		case  Walk:
			work = this->animCnt / 8;
			work %= 3;
			rtv = imageTable[work + 1];
			break;
		//	落下----------------------------------------------------------------------------
		case  Fall:		rtv = imageTable[5];	break;
		}
		//	向きに応じて画像を左右反転する
		if (Left == this->angle_LR) {
			rtv.draw.x = -rtv.draw.x;
			rtv.draw.w = -rtv.draw.w;
		}
		return rtv;
	}*/
	//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	//以下は基本的に変更不要なメソッド
	//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	//-------------------------------------------------------------------
	//タスク生成窓口
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//ゲームエンジンに登録
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//イニシャライズに失敗したらKill
			}
			return  ob;
		}
		return nullptr;
	}
	//-------------------------------------------------------------------
	bool  Object::B_Initialize()
	{
		return  this->Initialize();
	}
	//-------------------------------------------------------------------
	Object::~Object() { this->B_Finalize(); }
	bool  Object::B_Finalize()
	{
		auto  rtv = this->Finalize();
		return  rtv;
	}
	//-------------------------------------------------------------------
	Object::Object() {	}
	//-------------------------------------------------------------------
	//リソースクラスの生成
	Resource::SP  Resource::Create()
	{
		if (auto sp = instance.lock()) {
			return sp;
		}
		else {
			sp = Resource::SP(new  Resource());
			if (sp) {
				sp->Initialize();
				instance = sp;
			}
			return sp;
		}
	}
	//-------------------------------------------------------------------
	Resource::Resource() {}
	//-------------------------------------------------------------------
	Resource::~Resource() { this->Finalize(); }
}