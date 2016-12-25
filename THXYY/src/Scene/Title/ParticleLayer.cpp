#include "ParticleLayer.h"
#include "SakuraParticle.h"

ParticleLayer::ParticleLayer()
{
	Camera3D* camera = new Camera3D("Main");
	camera->SetPosition(Vector3f(320, 240, -200));
	camera->SetLookAt(Vector3f(320, 240, 0));
	camera->SetUp(Vector3f(0, 1, 0));

	SetCamera(camera);
}

ParticleLayer::~ParticleLayer()
{

}

void ParticleLayer::Update()
{
	Layer::Update();

	frame++;

	
	if (frame == 15)
	{
		frame = 0;

		SakuraParticle* particle = new SakuraParticle(0);

		particle->SetLife(300);
		
		float x = Random(-100, 740);
		float y = Random(240, 500);
		float z = Random(0, 100);

		particle->SetPosition(Vector3f(x, y, z));

		if (x < 320)
		{
			particle->SetDirection(Vector3f(Random(1, 100), Random(-100, 0), 0));
		}
		else
		{
			particle->SetDirection(Vector3f(Random(-100, -1), Random(-100, 0), 0));
		}

		particle->SetRotatingAxis(Vector3f(Random(-100, 100), Random(-100, 100), Random(-100, 100)));
		particle->SetRotatingSpeed(Random(100, 500) / 100.0f);

		particle->SetSpeed(0.5f + Random(0, 100) / 100.0f);

		particle->SetAlpha(0);

		TweenSequence* sequence = new TweenSequence();
		sequence->AddTween(new FadeTo(0.6f, 100, Tweener::EASE_OUT));
		sequence->AddTween(new Delay(100));
		sequence->AddTween(new FadeOut(100, Tweener::EASE_OUT));
		particle->AddTween(sequence);

		AddChild(particle);
	}
}