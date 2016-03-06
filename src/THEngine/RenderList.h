#ifndef RENDERLIST_H
#define RENDERLIST_H

#include "stdafx.h"

template<class type>
class RenderObjectNode{
public:
	type *obj;
	RenderObjectNode<type> *prior;
	RenderObjectNode<type> *next;
};

template<class type>
class RenderList{
public:
	RenderObjectNode<type> *head;
public:
	RenderList();
	~RenderList();
	void Delet(RenderObjectNode<type> *obj);
	void Add(type *obj);
	void Render();
	void Update();
	void Clear();
	type* Get(int index);
};

/////////////////////////////////////////////////////////////////

template<class type>
RenderList<type>::RenderList()
{
	head = new RenderObjectNode<type>;
	head->next = head->prior = NULL;
}

template<class type>
RenderList<type>::~RenderList()
{
	Clear();
	delete head;
}

template<class type>
void RenderList<type>::Delet(RenderObjectNode<type> *obj)
{
	obj->prior->next = obj->next;
	if (obj->next){
		obj->next->prior = obj->prior;
	}
	delete obj->obj;
	delete obj;
}

template<class type>
void RenderList<type>::Add(type *obj)
{
	RenderObjectNode<type> *robj = new RenderObjectNode<type>;
	robj->obj = obj;
	robj->next = head->next;
	robj->prior = head;
	if (robj->next){
		robj->next->prior = robj;
	}
	head->next = robj;
}

template<class type>
void RenderList<type>::Render()
{
	RenderObjectNode<type> *p = head;
	while (p->next){
		p = p->next;
		p->obj->CommonDraw();
	}
}

template<class type>
void RenderList<type>::Update()
{
	RenderObjectNode<type> *p = head;
	RenderObjectNode<type> *q = p->next;
	while (q){
		p = q;
		q = p->next;
		p->obj->CommonUpdate();
		if (p->obj->NeedAutoDelete()){
			Delet(p);
		}
	}
}

template<class type>
void RenderList<type>::Clear()
{
	RenderObjectNode<type> *p, *q;
	q = head->next;
	while (q){
		p = q;
		q = p->next;
		TH_SAFE_DELETE(p->obj);
		delete p;
	}
	head->next = NULL;
}

template<class type>
type* RenderList<type>::Get(int index)
{
	int i = 0;
	RenderObjectNode<type> *p = head->next;
	while (p){
		if (i == index){
			return p->obj;
		}
		i += 1;
		p = p->next;
	}
	return NULL;
}

#endif