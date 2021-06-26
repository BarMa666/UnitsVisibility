#pragma once

/*
* ����� ������������ ����� ��� ������� ����
* TODO: ��������� ��������
*/
#include <memory>

#include "UnitManager.h"
#include "Object.h"
#include "ObjectView.h"
#include "Types.h"

class Unit : public Object
{
public:

	Unit(const Unit&) = delete;
	Unit& operator=(const Unit&) = delete;
	Unit(Unit&&) = default;
	Unit& operator=(Unit&&) = default;

	void show() const override;
	void setVisibleCount(const VisibleCountT&);
	VisibleCountT getVisibleCount() const;

	// ������ ����� ��� ��������� �� ������ UnitManager, ������ ��� ��� ��������
	const bool checkDirection(const Unit& _other) const;

	virtual ~Unit() = default;

protected:
	Unit(const NameT& _name, const PositionT& _position, const DirectionT& _direction, std::unique_ptr<ObjectView>&& _view);
	const DirectionT& direction() const;
private:
	static Unit* create(const NameT& _name, const PositionT& _position, const DirectionT& _direction);

	DirectionT m_direction;
	VisibleCountT m_visibleUnitsCount;

	friend bool operator==(const Unit& _lhs, const Unit& _rhs);
	friend void UnitManager::createUnit(const NameT& _name, const PositionT& _position, const DirectionT& _direction);
};

bool operator==(const Unit& _lhs, const Unit& _rhs);

