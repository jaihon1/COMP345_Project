#pragma once
#include "Subject.h"

class Foo : public Subject
{
public:
	Foo() { }
	~Foo() { }

	//TODO: Implement methods

	void foo() { notify(); }
};
