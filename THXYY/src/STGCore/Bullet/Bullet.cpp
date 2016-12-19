#include "Bullet.h"
#include "BulletDelegate.h"
#include "../STGEngine.h"

BulletDelegate::BulletDelegate(Bullet* bullet)
{
	this->bullet = bullet;
}

BulletDelegate::~BulletDelegate()
{

}

////////////////////   Bullet    //////////////////////

Bullet::Bullet()
{
	bulletDelegate = nullptr;

	dirSame = true;
}

Bullet::~Bullet()
{
	TH_SAFE_RELEASE(bulletDelegate);
}

void Bullet::Update()
{	
	Sprite::Update();

	auto engine = STGEngine::GetInstance();

	auto player = engine->GetPlayer();
	if (player->IsInvincible())
	{
		if (Hit(player->GetPosition().x, player->GetPosition().y, player->GetRadius()))
		{
			MarkDestroy();
		}
	}
	else if (player->IsDamageable())
	{
		if (Hit(player->GetPosition().x, player->GetPosition().y, player->GetRadius()))
		{
			player->Hitten();
			MarkDestroy();
		}
	}

	if (dirSame)
	{
		SetRotation(angle - 90);
	}

	if (autoDelete)
	{
		if (position.x < -32 || position.x > 416 || position.y < -32 || position.y > 480)
		{
			MarkDestroy();
		}
	}
}

void Bullet::OnDie()
{
	MarkDestroy();

	auto engine = STGEngine::GetInstance();
	auto stgResources = STGResources::GetInstance();

	Particle3D* effect[1];
	for (int i = 0; i < 1; i++)
	{
		int effectLife = 40;

		effect[i] = new Particle3D();
		effect[i]->SetTexture(stgResources->texFourAngleStar);
		effect[i]->SetPosition(position);
		effect[i]->SetLife(effectLife);

		switch (bulletColor)
		{
		case RED:
			effect[i]->SetTexRect(Rect(0, 32, 0, 32));
			break;
		case PURPLE:
			effect[i]->SetTexRect(Rect(32, 64, 0, 32));
			break;
		case BLUE:
			effect[i]->SetTexRect(Rect(64, 96, 0, 32));
			break;
		case TEAL:
			effect[i]->SetTexRect(Rect(96, 128, 0, 32));
			break;
		case GREEN:
			effect[i]->SetTexRect(Rect(0, 32, 32, 64));
			break;
		case YELLOW:
			effect[i]->SetTexRect(Rect(32, 64, 32, 64));
			break;
		case ORANGE:
			effect[i]->SetTexRect(Rect(64, 96, 32, 64));
			break;
		case GREY:
			effect[i]->SetTexRect(Rect(96, 128, 32, 64));
			break;
		}

		float effectAngle = ToRad(Random(0, 359));
		float dist = Random(0, 20);

		float effectScale = Random(20, 50) / 100.0f;
		effect[i]->SetScale(Vector3f(effectScale, effectScale, 1));

		effect[i]->SetRotatingAxis(Vector3f(Random(0, 100), Random(0, 100), Random(0, 100)));
		effect[i]->SetRotatingSpeed(Random(50, 100) / 10.0f);
		effect[i]->SetAlpha(0.6f);

		TweenSequence* sequence = new TweenSequence();
		sequence->AddTween(new Delay(effectLife / 2));
		sequence->AddTween(new ScaleTo(Vector3f(0, 0, 1), 30, Tweener::SIMPLE));
		effect[i]->AddTween(sequence);

		effect[i]->AddTween(new MoveBy(Vector3f(dist*cos(effectAngle), dist*sin(effectAngle), 0),
			effectLife, Tweener::EASE_OUT));

		engine->AddParticle(effect[i]);
	}
}

void Bullet::SetType(Type type)
{
	auto stgResources = STGResources::GetInstance();

	TH_SAFE_RELEASE(bulletDelegate);

	switch (type)
	{
	case LINDAN_RED:
		bulletDelegate = new LinDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(32, 48, 16, 32));
		SetBulletColor(RED);
		break;
	case LINDAN_PURPLE:
		bulletDelegate = new LinDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(64, 80, 16, 32));
		SetBulletColor(PURPLE);
		break;
	case LINDAN_BLUE:
		bulletDelegate = new LinDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(96, 112, 16, 32));
		SetBulletColor(BLUE);
		break;
	case LINDAN_TEAL:
		bulletDelegate = new LinDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(128, 144, 16, 32));
		SetBulletColor(TEAL);
		break;
	case LINDAN_GREEN:
		bulletDelegate = new LinDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(160, 176, 16, 32));
		SetBulletColor(GREEN);
		break;
	case LINDAN_YELLOW:
		bulletDelegate = new LinDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(192, 208, 16, 32));
		SetBulletColor(YELLOW);
		break;
	case LINDAN_ORANGE:
		bulletDelegate = new LinDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(224, 240, 16, 32));
		SetBulletColor(ORANGE);
		break;
	case LINDAN_GREY:
		bulletDelegate = new LinDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(240, 256, 16, 32));
		SetBulletColor(GREY);
		break;
	case SMALLJADEROUND_RED:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(32, 48, 32, 48));
		SetBulletColor(RED);
		break;
	case SMALLJADEROUND_PURPLE:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(64, 80, 32, 48));
		SetBulletColor(PURPLE);
		break;
	case SMALLJADEROUND_BLUE:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(96, 112, 32, 48));
		SetBulletColor(BLUE);
		break;
	case SMALLJADEROUND_TEAL:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(128, 144, 32, 48));
		SetBulletColor(TEAL);
		break;
	case SMALLJADEROUND_GREEN:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(160, 176, 32, 48));
		SetBulletColor(GREEN);
		break;
	case SMALLJADEROUND_YELLOW:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(192, 208, 32, 48));
		SetBulletColor(YELLOW);
		break;
	case SMALLJADEROUND_ORANGE:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(224, 240, 32, 48));
		SetBulletColor(ORANGE);
		break;
	case SMALLJADEROUND_GREY:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(240, 256, 32, 48));
		SetBulletColor(GREY);
		break;
	case SMALLJADE_RED:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(32, 48, 48, 64));
		SetBulletColor(RED);
		break;
	case SMALLJADE_PURPLE:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(64, 80, 48, 64));
		SetBulletColor(PURPLE);
		break;
	case SMALLJADE_BLUE:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(96, 112, 48, 64));
		SetBulletColor(BLUE);
		break;
	case SMALLJADE_TEAL:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(128, 144, 48, 64));
		SetBulletColor(TEAL);
		break;
	case SMALLJADE_GREEN:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(160, 176, 48, 64));
		SetBulletColor(GREEN);
		break;
	case SMALLJADE_YELLOW:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(192, 208, 48, 64));
		SetBulletColor(YELLOW);
		break;
	case SMALLJADE_ORANGE:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(224, 240, 48, 64));
		SetBulletColor(ORANGE);
		break;
	case SMALLJADE_GREY:
		bulletDelegate = new SmallJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(240, 256, 48, 64));
		SetBulletColor(GREY);
		break;
	case CHAIN_RED:
		bulletDelegate = new Chain(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(32, 48, 80, 96));
		SetBulletColor(RED);
		break;
	case CHAIN_PURPLE:
		bulletDelegate = new Chain(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(64, 80, 80, 96));
		SetBulletColor(PURPLE);
		break;
	case CHAIN_BLUE:
		bulletDelegate = new Chain(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(96, 112, 80, 96));
		SetBulletColor(BLUE);
		break;
	case CHAIN_TEAL:
		bulletDelegate = new Chain(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(128, 144, 80, 96));
		SetBulletColor(TEAL);
		break;
	case CHAIN_GREEN:
		bulletDelegate = new Chain(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(160, 176, 80, 96));
		SetBulletColor(GREEN);
		break;
	case CHAIN_YELLOW:
		bulletDelegate = new Chain(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(192, 208, 80, 96));
		SetBulletColor(YELLOW);
		break;
	case CHAIN_ORANGE:
		bulletDelegate = new Chain(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(224, 240, 80, 96));
		SetBulletColor(ORANGE);
		break;
	case CHAIN_GREY:
		bulletDelegate = new Chain(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(240, 256, 80, 96));
		SetBulletColor(GREY);
		break;
	case RICE_RED:
		bulletDelegate = new Rice(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(32, 48, 65, 79));
		SetBulletColor(RED);
		break;
	case RICE_PURPLE:
		bulletDelegate = new Rice(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(64, 80, 65, 79));
		SetBulletColor(PURPLE);
		break;
	case RICE_BLUE:
		bulletDelegate = new Rice(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(96, 112, 65,79));
		SetBulletColor(BLUE);
		break;
	case RICE_TEAL:
		bulletDelegate = new Rice(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(128, 144, 65, 79));
		SetBulletColor(TEAL);
		break;
	case RICE_GREEN:
		bulletDelegate = new Rice(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(160, 176, 65, 79));
		SetBulletColor(GREEN);
		break;
	case RICE_YELLOW:
		bulletDelegate = new Rice(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(192, 208, 65, 79));
		SetBulletColor(YELLOW);
		break;
	case RICE_ORANGE:
		bulletDelegate = new Rice(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(224, 240, 65, 79));
		SetBulletColor(ORANGE);
		break;
	case RICE_GREY:
		bulletDelegate = new Rice(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(240, 256, 65, 79));
		SetBulletColor(GREY);
		break;
	case CHONGDAN_RED:
		bulletDelegate = new ChongDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(32, 48, 128, 144));
		SetBulletColor(RED);
		break;
	case CHONGDAN_PURPLE:
		bulletDelegate = new ChongDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(64, 80, 128, 144));
		SetBulletColor(PURPLE);
		break;
	case CHONGDAN_BLUE:
		bulletDelegate = new ChongDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(96, 112, 128, 144));
		SetBulletColor(BLUE);
		break;
	case CHONGDAN_TEAL:
		bulletDelegate = new ChongDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(128, 144, 128, 144));
		SetBulletColor(TEAL);
		break;
	case CHONGDAN_GREEN:
		bulletDelegate = new ChongDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(160, 176, 128, 144));
		SetBulletColor(GREEN);
		break;
	case CHONGDAN_YELLOW:
		bulletDelegate = new ChongDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(192, 208, 128, 144));
		SetBulletColor(YELLOW);
		break;
	case CHONGDAN_ORANGE:
		bulletDelegate = new ChongDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(224, 240, 128, 144));
		SetBulletColor(ORANGE);
		break;
	case CHONGDAN_GREY:
		bulletDelegate = new ChongDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(240, 256, 128, 144));
		SetBulletColor(GREY);
		break;
	case ZHADAN_RED:
		bulletDelegate = new ZhaDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(32, 48, 112, 128));
		SetBulletColor(RED);
		break;
	case ZHADAN_PURPLE:
		bulletDelegate = new ZhaDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(64, 80, 112, 128));
		SetBulletColor(PURPLE);
		break;
	case ZHADAN_BLUE:
		bulletDelegate = new ZhaDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(96, 112, 112, 128));
		SetBulletColor(BLUE);
		break;
	case ZHADAN_TEAL:
		bulletDelegate = new ZhaDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(128, 144, 112, 128));
		SetBulletColor(TEAL);
		break;
	case ZHADAN_GREEN:
		bulletDelegate = new ZhaDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(160, 176, 112, 128));
		SetBulletColor(GREEN);
		break;
	case ZHADAN_YELLOW:
		bulletDelegate = new ZhaDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(192, 208, 112, 128));
		SetBulletColor(YELLOW);
		break;
	case ZHADAN_ORANGE:
		bulletDelegate = new ZhaDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(224, 240, 112, 128));
		SetBulletColor(ORANGE);
		break;
	case ZHADAN_GREY:
		bulletDelegate = new ZhaDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(240, 256, 112, 128));
		SetBulletColor(GREY);
		break;
	case BACILLI_RED:
		bulletDelegate = new Bacilli(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(16, 32, 144, 160));
		SetBulletColor(RED);
		break;
	case BACILLI_PURPLE:
		bulletDelegate = new Bacilli(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(48, 64, 144, 160));
		SetBulletColor(PURPLE);
		break;
	case BACILLI_BLUE:
		bulletDelegate = new Bacilli(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(80, 96, 144, 160));
		SetBulletColor(BLUE);
		break;
	case BACILLI_TEAL:
		bulletDelegate = new Bacilli(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(112, 128, 144, 160));
		SetBulletColor(TEAL);
		break;
	case BACILLI_GREEN:
		bulletDelegate = new Bacilli(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(144, 160, 144, 160));
		SetBulletColor(GREEN);
		break;
	case BACILLI_YELLOW:
		bulletDelegate = new Bacilli(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(176, 192, 144, 160));
		SetBulletColor(YELLOW);
		break;
	case BACILLI_ORANGE:
		bulletDelegate = new Bacilli(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(208, 224, 144, 160));
		SetBulletColor(ORANGE);
		break;
	case BACILLI_GREY:
		bulletDelegate = new Bacilli(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(240, 256, 144, 160));
		SetBulletColor(GREY);
		break;
	case STARSMALL_RED:
		bulletDelegate = new StarBulletSmall(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(32, 48, 160, 176));
		SetBulletColor(RED);
		break;
	case STARSMALL_PURPLE:
		bulletDelegate = new StarBulletSmall(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(64, 80, 160, 176));
		SetBulletColor(PURPLE);
		break;
	case STARSMALL_BLUE:
		bulletDelegate = new StarBulletSmall(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(96, 112, 160, 176));
		SetBulletColor(BLUE);
		break;
	case STARSMALL_TEAL:
		bulletDelegate = new StarBulletSmall(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(128, 144, 160, 176));
		SetBulletColor(TEAL);
		break;
	case STARSMALL_GREEN:
		bulletDelegate = new StarBulletSmall(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(160, 176, 160, 176));
		SetBulletColor(GREEN);
		break;
	case STARSMALL_YELLOW:
		bulletDelegate = new StarBulletSmall(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(192, 208, 160, 176));
		SetBulletColor(YELLOW);
		break;
	case STARSMALL_ORANGE:
		bulletDelegate = new StarBulletSmall(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(224, 240, 160, 176));
		SetBulletColor(ORANGE);
		break;
	case STARSMALL_GREY:
		bulletDelegate = new StarBulletSmall(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(240, 256, 160, 176));
		SetBulletColor(GREY);
		break;
	case POINT_RED:
		bulletDelegate = new PointBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(8, 16, 240, 248));
		SetBulletColor(RED);
		break;
	case POINT_PURPLE:
		bulletDelegate = new PointBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(24, 32, 240, 248));
		SetBulletColor(PURPLE);
		break;
	case POINT_BLUE:
		bulletDelegate = new PointBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(40, 48, 240, 248));
		SetBulletColor(BLUE);
		break;
	case POINT_TEAL:
		bulletDelegate = new PointBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(56, 64, 240, 248));
		SetBulletColor(TEAL);
		break;
	case POINT_GREEN:
		bulletDelegate = new PointBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(8, 16, 248, 256));
		SetBulletColor(GREEN);
		break;
	case POINT_YELLOW:
		bulletDelegate = new PointBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(32, 40, 248, 256));
		SetBulletColor(YELLOW);
		break;
	case POINT_ORANGE:
		bulletDelegate = new PointBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(48, 56, 248, 256));
		SetBulletColor(ORANGE);
		break;
	case POINT_GREY:
		bulletDelegate = new PointBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(56, 64, 248, 256));
		SetBulletColor(GREY);
		break;
	case NEEDLE_RED:
		bulletDelegate = new NeedleBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(32, 48, 96, 112));
		SetBulletColor(RED);
		break;
	case NEEDLE_PURPLE:
		bulletDelegate = new NeedleBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(64, 80, 96, 112));
		SetBulletColor(PURPLE);
		break;
	case NEEDLE_BLUE:
		bulletDelegate = new NeedleBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(96, 112, 96, 112));
		SetBulletColor(BLUE);
		break;
	case NEEDLE_TEAL:
		bulletDelegate = new NeedleBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(128, 144, 96, 112));
		SetBulletColor(TEAL);
		break;
	case NEEDLE_GREEN:
		bulletDelegate = new NeedleBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(160, 176, 96, 112));
		SetBulletColor(GREEN);
		break;
	case NEEDLE_YELLOW:
		bulletDelegate = new NeedleBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(192, 208, 96, 112));
		SetBulletColor(YELLOW);
		break;
	case NEEDLE_ORANGE:
		bulletDelegate = new NeedleBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(224, 240, 96, 112));
		SetBulletColor(ORANGE);
		break;
	case NEEDLE_GREY:
		bulletDelegate = new NeedleBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(240, 256, 96, 112));
		SetBulletColor(GREY);
		break;
	case BACTERIA_RED:
		bulletDelegate = new BacteriaBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(16, 24, 192, 200));
		SetBulletColor(RED);
		break;
	case BACTERIA_PURPLE:
		bulletDelegate = new BacteriaBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(32, 40, 192, 200));
		SetBulletColor(PURPLE);
		break;
	case BACTERIA_BLUE:
		bulletDelegate = new BacteriaBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(48, 56, 192, 200));
		SetBulletColor(BLUE);
		break;
	case BACTERIA_TEAL:
		bulletDelegate = new BacteriaBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(0, 8, 200, 208));
		SetBulletColor(TEAL);
		break;
	case BACTERIA_GREEN:
		bulletDelegate = new BacteriaBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(16, 24, 200, 208));
		SetBulletColor(GREEN);
		break;
	case BACTERIA_YELLOW:
		bulletDelegate = new BacteriaBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(40, 48, 200, 208));
		SetBulletColor(YELLOW);
		break;
	case BACTERIA_GREY:
		bulletDelegate = new BacteriaBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet01);
		SetTexRect(Rect(56, 64, 200, 208));
		SetBulletColor(GREY);
		break;
	case STARBIG_RED:
		bulletDelegate = new StarBulletBig(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(0, 32, 0, 32));
		SetBulletColor(RED);
		break;
	case STARBIG_PURPLE:
		bulletDelegate = new StarBulletBig(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(32, 64, 0, 32));
		SetBulletColor(PURPLE);
		break;
	case STARBIG_BLUE:
		bulletDelegate = new StarBulletBig(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(64, 96, 0, 32));
		SetBulletColor(BLUE);
		break;
	case STARBIG_TEAL:
		bulletDelegate = new StarBulletBig(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(96, 128, 0, 32));
		SetBulletColor(TEAL);
		break;
	case STARBIG_GREEN:
		bulletDelegate = new StarBulletBig(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(128, 160, 0, 32));
		SetBulletColor(GREEN);
		break;
	case STARBIG_YELLOW:
		bulletDelegate = new StarBulletBig(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(160, 192, 0, 32));
		SetBulletColor(YELLOW);
		break;
	case STARBIG_ORANGE:
		bulletDelegate = new StarBulletBig(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(192, 224, 0, 32));
		SetBulletColor(ORANGE);
		break;
	case STARBIG_GREY:
		bulletDelegate = new StarBulletBig(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(224, 256, 0, 32));
		SetBulletColor(GREY);
		break;
	case MIDJADE_RED:
		bulletDelegate = new MidJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(0, 32, 32, 64));
		SetBulletColor(RED);
		break;
	case MIDJADE_PURPLE:
		bulletDelegate = new MidJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(32, 64, 32, 64));
		SetBulletColor(PURPLE);
		break;
	case MIDJADE_BLUE:
		bulletDelegate = new MidJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(64, 96, 32, 64));
		SetBulletColor(BLUE);
		break;
	case MIDJADE_TEAL:
		bulletDelegate = new MidJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(96, 128, 32, 64));
		SetBulletColor(TEAL);
		break;
	case MIDJADE_GREEN:
		bulletDelegate = new MidJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(128, 160, 32, 64));
		SetBulletColor(GREEN);
		break;
	case MIDJADE_YELLOW:
		bulletDelegate = new MidJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(160, 192, 32, 64));
		SetBulletColor(YELLOW);
		break;
	case MIDJADE_ORANGE:
		bulletDelegate = new MidJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(192, 224, 32, 64));
		SetBulletColor(ORANGE);
		break;
	case MIDJADE_GREY:
		bulletDelegate = new MidJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(224, 256, 32, 64));
		SetBulletColor(GREY);
		break;
	case BUTTERFLY_RED:
		bulletDelegate = new ButterflyBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(0, 32, 64, 96));
		SetBulletColor(RED);
		break;
	case BUTTERFLY_PURPLE:
		bulletDelegate = new ButterflyBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(32, 64, 64, 96));
		SetBulletColor(PURPLE);
		break;
	case BUTTERFLY_BLUE:
		bulletDelegate = new ButterflyBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(64, 96, 64, 96));
		SetBulletColor(BLUE);
		break;
	case BUTTERFLY_TEAL:
		bulletDelegate = new ButterflyBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(96, 128, 64, 96));
		SetBulletColor(TEAL);
		break;
	case BUTTERFLY_GREEN:
		bulletDelegate = new ButterflyBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(128, 160, 64, 96));
		SetBulletColor(GREEN);
		break;
	case BUTTERFLY_YELLOW:
		bulletDelegate = new ButterflyBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(160, 192, 64, 96));
		SetBulletColor(YELLOW);
		break;
	case BUTTERFLY_ORANGE:
		bulletDelegate = new ButterflyBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(192, 224, 64, 96));
		SetBulletColor(ORANGE);
		break;
	case BUTTERFLY_GREY:
		bulletDelegate = new ButterflyBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(224, 256, 64, 96));
		SetBulletColor(GREY);
		break;
	case KNIFE_RED:
		bulletDelegate = new KnifeBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(0, 32, 96, 128));
		SetBulletColor(RED);
		break;
	case KNIFE_PURPLE:
		bulletDelegate = new KnifeBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(32, 64, 96, 128));
		SetBulletColor(PURPLE);
		break;
	case KNIFE_BLUE:
		bulletDelegate = new KnifeBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(64, 96, 96, 128));
		SetBulletColor(BLUE);
		break;
	case KNIFE_TEAL:
		bulletDelegate = new KnifeBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(96, 128, 96, 128));
		SetBulletColor(TEAL);
		break;
	case KNIFE_GREEN:
		bulletDelegate = new KnifeBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(128, 160, 96, 128));
		SetBulletColor(GREEN);
		break;
	case KNIFE_YELLOW:
		bulletDelegate = new KnifeBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(160, 192, 96, 128));
		SetBulletColor(YELLOW);
		break;
	case KNIFE_ORANGE:
		bulletDelegate = new KnifeBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(192, 224, 96, 128));
		SetBulletColor(ORANGE);
		break;
	case KNIFE_GREY:
		bulletDelegate = new KnifeBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(224, 256, 96, 128));
		SetBulletColor(GREY);
		break;
	case ELLIPSE_RED:
		bulletDelegate = new EllipseBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(0, 32, 128, 160));
		SetBulletColor(RED);
		break;
	case ELLIPSE_PURPLE:
		bulletDelegate = new EllipseBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(32, 64, 128, 160));
		SetBulletColor(PURPLE);
		break;
	case ELLIPSE_BLUE:
		bulletDelegate = new EllipseBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(64, 96, 128, 160));
		SetBulletColor(BLUE);
		break;
	case ELLIPSE_TEAL:
		bulletDelegate = new EllipseBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(96, 128, 128, 160));
		SetBulletColor(TEAL);
		break;
	case ELLIPSE_GREEN:
		bulletDelegate = new EllipseBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(128, 160, 128, 160));
		SetBulletColor(GREEN);
		break;
	case ELLIPSE_YELLOW:
		bulletDelegate = new EllipseBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(160, 192, 128, 160));
		SetBulletColor(YELLOW);
		break;
	case ELLIPSE_ORANGE:
		bulletDelegate = new EllipseBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(192, 224, 128, 160));
		SetBulletColor(ORANGE);
		break;
	case ELLIPSE_GREY:
		bulletDelegate = new EllipseBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet02);
		SetTexRect(Rect(224, 256, 128, 160));
		SetBulletColor(GREY);
		break;
	case DIDAN_RED:
		bulletDelegate = new DiDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(32, 48, 192, 208));
		SetBulletColor(RED);
		break;
	case DIDAN_PURPLE:
		bulletDelegate = new DiDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(64, 80, 192, 208));
		SetBulletColor(PURPLE);
		break;
	case DIDAN_BLUE:
		bulletDelegate = new DiDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(96, 112, 192, 208));
		SetBulletColor(BLUE);
		break;
	case DIDAN_TEAL:
		bulletDelegate = new DiDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(128, 144, 192, 208));
		SetBulletColor(TEAL);
		break;
	case DIDAN_GREEN:
		bulletDelegate = new DiDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(160, 176, 192, 208));
		SetBulletColor(GREEN);
		break;
	case DIDAN_YELLOW:
		bulletDelegate = new DiDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(192, 208, 192, 208));
		SetBulletColor(YELLOW);
		break;
	case DIDAN_ORANGE:
		bulletDelegate = new DiDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(224, 240, 192, 208));
		SetBulletColor(ORANGE);
		break;
	case DIDAN_GREY:
		bulletDelegate = new DiDan(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(240, 256, 192, 208));
		SetBulletColor(GREY);
		break;
	case HEART_RED:
		bulletDelegate = new HeartBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(0, 32, 0, 32));
		SetBulletColor(RED);
		break;
	case HEART_PURPLE:
		bulletDelegate = new HeartBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(32, 64, 0, 32));
		SetBulletColor(PURPLE);
		break;
	case HEART_BLUE:
		bulletDelegate = new HeartBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(64, 96, 0, 32));
		SetBulletColor(BLUE);
		break;
	case HEART_TEAL:
		bulletDelegate = new HeartBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(96, 128, 0, 32));
		SetBulletColor(TEAL);
		break;
	case HEART_GREEN:
		bulletDelegate = new HeartBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(128, 160, 0, 32));
		SetBulletColor(GREEN);
		break;
	case HEART_YELLOW:
		bulletDelegate = new HeartBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(160, 192, 0, 32));
		SetBulletColor(YELLOW);
		break;
	case HEART_ORANGE:
		bulletDelegate = new HeartBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(192, 224, 0, 32));
		SetBulletColor(ORANGE);
		break;
	case HEART_GREY:
		bulletDelegate = new HeartBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(224, 256, 0, 32));
		SetBulletColor(GREY);
		break;
	case ARROW_RED:
		bulletDelegate = new ArrowBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(0, 32, 32, 64));
		SetBulletColor(RED);
		break;
	case ARROW_PURPLE:
		bulletDelegate = new ArrowBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(32, 64, 32, 64));
		SetBulletColor(PURPLE);
		break;
	case ARROW_BLUE:
		bulletDelegate = new ArrowBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(64, 96, 32, 64));
		SetBulletColor(BLUE);
		break;
	case ARROW_TEAL:
		bulletDelegate = new ArrowBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(96, 128, 32, 64));
		SetBulletColor(TEAL);
		break;
	case ARROW_GREEN:
		bulletDelegate = new ArrowBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(128, 160, 32, 64));
		SetBulletColor(GREEN);
		break;
	case ARROW_YELLOW:
		bulletDelegate = new ArrowBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(160, 192, 32, 64));
		SetBulletColor(YELLOW);
		break;
	case ARROW_ORANGE:
		bulletDelegate = new ArrowBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(192, 224, 32, 64));
		SetBulletColor(ORANGE);
		break;
	case ARROW_GREY:
		bulletDelegate = new ArrowBullet(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet03);
		SetTexRect(Rect(224, 256, 32, 64));
		SetBulletColor(GREY);
		break;
	case BIGJADE_RED:
		bulletDelegate = new BigJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet04);
		SetTexRect(Rect(0, 64, 0, 64));
		SetBulletColor(RED);
		break;
	case BIGJADE_PURPLE:
		bulletDelegate = new BigJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet04);
		SetTexRect(Rect(64, 128, 0, 64));
		SetBulletColor(PURPLE);
		break;
	case BIGJADE_BLUE:
		bulletDelegate = new BigJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet04);
		SetTexRect(Rect(128, 192, 0, 64));
		SetBulletColor(BLUE);
		break;
	case BIGJADE_TEAL:
		bulletDelegate = new BigJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet04);
		SetTexRect(Rect(192, 256, 0, 64));
		SetBulletColor(TEAL);
		break;
	case BIGJADE_GREEN:
		bulletDelegate = new BigJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet04);
		SetTexRect(Rect(0, 64, 64, 128));
		SetBulletColor(GREEN);
		break;
	case BIGJADE_YELLOW:
		bulletDelegate = new BigJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet04);
		SetTexRect(Rect(64, 128, 64, 128));
		SetBulletColor(YELLOW);
		break;
	case BIGJADE_ORANGE:
		bulletDelegate = new BigJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet04);
		SetTexRect(Rect(128, 192, 64, 128));
		SetBulletColor(ORANGE);
		break;
	case BIGJADE_GREY:
		bulletDelegate = new BigJade(this);
		bulletDelegate->Retain();
		SetTexture(stgResources->texBullet04);
		SetTexRect(Rect(192, 256, 64, 128));
		SetBulletColor(GREY);
		break;
	}
}