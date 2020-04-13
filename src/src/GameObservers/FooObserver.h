#pragma once
#include "Observer.h"
#include "Foo.h"

class FooObserver : public Observer
{
public:
	FooObserver(Foo* foo) : foo(foo)
	{
		foo->attach(this);
	}
	~FooObserver()
	{
		foo->detach(this);
	}

	//TODO: Implement update

	void update() override { }

private:
	Foo* foo;
};
