#pragma once

// TODO вынесты класс Object в отдельный модуль
class Object;

class ObjectView
{
public:
	ObjectView() = default;

	virtual ~ObjectView() = default;

	virtual void show(const Object* _unit) = 0;
};

class UnitView : public ObjectView
{
public:
	UnitView();

	virtual ~UnitView() = default;

	void show(const Object* _unit) override;
};

