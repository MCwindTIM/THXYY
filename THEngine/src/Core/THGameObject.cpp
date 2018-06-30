#include "THGameObject.h"
#include "THDataStack.h"
#include <Tween\THTweenManager.h>

namespace THEngine
{
	GameObject::GameObject()
	{
		needRemove = false;

		Matrix::Identity(&this->rotation3D);

		tweenManager = Ptr<TweenManager>::New();
	}

	GameObject::GameObject(const GameObject& object) : EngineObject(object), children(object.children)
	{
		position = object.position;
		color = object.color;
		alpha = object.alpha;
		scale = object.scale;
		rotation3D = object.rotation3D;

		tweenManager = Ptr<TweenManager>::New(*object.tweenManager.Get());
		needRemove = false;
	}

	GameObject::~GameObject()
	{
	}

	Ptr<Object> GameObject::Clone() const
	{
		return Ptr<GameObject>::New(*this).Get();
	}

	void GameObject::OnLoad(Ptr<AsyncInfo> info)
	{
		EngineObject::OnLoad(info);

		Iterator<Ptr<GameObject>>* iter = children.GetIterator();
		while (iter->HasNext())
		{
			iter->Next()->OnLoad(info);
		}
	}

	void GameObject::AddChild(Ptr<GameObject> obj)
	{
		children.Add(obj);
	}

	void GameObject::Visit()
	{
		auto iter = children.GetIterator();

		SendToRenderQueue();

		WriteRenderData();
		PushDataStack();

		OnVisit();
		while (iter->HasNext())
		{
			iter->Next()->Visit();
		}
		PopDataStack();
	}

	void GameObject::SendToRenderQueue()
	{
	}

	void GameObject::WriteRenderData()
	{
		auto dataStack = DataStack::GetInstance();

		Matrix world;
		GetWorldMatrix(&world);
		this->finalWorldTransform = world * dataStack->worldTransform.top();
	}

	void GameObject::PushDataStack()
	{
		auto dataStack = DataStack::GetInstance();

		dataStack->worldTransform.push(this->finalWorldTransform);
	}

	void GameObject::PopDataStack()
	{
		auto dataStack = DataStack::GetInstance();

		dataStack->worldTransform.pop();
	}

	void GameObject::Update()
	{
		EngineObject::Update();

		tweenManager->Update();

		auto iter = children.GetIterator();
		while (iter->HasNext())
		{
			auto obj = iter->Next();
			if (obj->IsPaused())
			{
				continue;
			}
			if (obj->needRemove)
			{
				obj->OnDestroy();
				iter->Remove();
			}
			else
			{
				obj->Update();
			}
		}
	}

	void GameObject::Draw()
	{
	}

	void GameObject::DrawShadowMap()
	{
	}

	void GameObject::DrawGeometry()
	{
	}

	void GameObject::GetWorldMatrix(Matrix* world)
	{
		Matrix::Identity(world);

		Matrix temp;
		Matrix::Scale(&temp, GetScale().x, GetScale().y, GetScale().z);
		*world *= temp;

		*world *= this->rotation3D;

		Matrix::Translate(&temp, position.x, position.y, position.z);
		*world *= temp;
	}

	void GameObject::OnDestroy()
	{
		RemoveAllChildren();
	}

	void GameObject::RemoveChild(Ptr<GameObject> child)
	{
		auto iter = children.GetIterator();
		while (iter->HasNext())
		{
			auto curChild = iter->Next();
			if (curChild == child)
			{
				iter->Remove();
				return;
			}
			curChild->RemoveChild(child);
		}
	}

	void GameObject::RemoveChildAt(int index)
	{
		children.RemoveAt(index);
	}

	void GameObject::RemoveAllChildren()
	{
		auto iter = children.GetIterator();
		while (iter->HasNext())
		{
			auto child = iter->Next();
			child->OnDestroy();
			iter->Remove();
		}
	}

	void GameObject::AddTween(Ptr<Tween> tween)
	{
		tweenManager->AddTween(tween);
		tween->Bind(this);
	}

	void GameObject::KillTween(Ptr<Tween> tween)
	{
		tweenManager->KillTween(tween);
	}

	void GameObject::ClearTweens()
	{
		tweenManager->ClearTweens();
	}

	void GameObject::SetRotationByAxis(const Vector3f& axis, float rotation)
	{
		Quaternion quat;
		Quaternion::RotateAngleAxis(&quat, Vector3f(axis.x, axis.y, axis.z), rotation);
		Matrix::RotateQuarternion(&this->rotation3D, quat);
	}

	void GameObject::SetRotationByAxis(const Vector3f& axis, const Vector3f& rotatingCenter, float rotation)
	{
		Matrix::Translate(&this->rotation3D, -rotatingCenter.x, -rotatingCenter.y, -rotatingCenter.z);

		Quaternion rot;
		Quaternion::RotateAngleAxis(&rot, axis, rotation);
		this->rotation3D *= rot;

		Matrix translationBack;
		Matrix::Translate(&translationBack, rotatingCenter.x, rotatingCenter.y, rotatingCenter.z);
		this->rotation3D *= translationBack;
	}
}