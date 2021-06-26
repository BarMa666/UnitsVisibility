#pragma once

class Object;

class ObjectView
{
public:
	ObjectView() = default;

	virtual ~ObjectView() = default;

	virtual void show(const Object* _unit) = 0;
};

