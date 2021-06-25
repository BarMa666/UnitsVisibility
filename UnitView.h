#pragma once

// TODO ������� ����� Object � ��������� ������
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

