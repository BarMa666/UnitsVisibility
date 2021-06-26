#pragma once

/*
* ����� �������� �� �������������� ����� �������(��������� ��������� ��� ������������ ����.)
*/

#include "Types.h"

#include <memory>
#include <vector>

class Unit;

class UnitManager
{
public:
	using UnitT = Unit;
	using UnitCollectionT = std::list<UnitT>;

	static UnitManager& instance();

	void createUnit(const NameT& _name, const PositionT& _position, const DirectionT& _direction);

	UnitManager(const UnitManager&) = delete;
	UnitManager& operator=(const UnitManager&) = delete;
	UnitManager(UnitManager&&) = delete;
	UnitManager& operator=(UnitManager&&) = delete;

	void update();

	~UnitManager();

protected:
	UnitManager();

	// ��������� ��������� ����� ����� �������
	bool checkVisibility(const Unit& _lhs, const Unit& _rhs) const;
	// ��������� ��������� ����� ����� �������
	bool checkDistance(const Unit& _lhs, const Unit& _rhs) const;

	void add(Unit&& _unit);

public:
	UnitCollectionT m_units;
};

