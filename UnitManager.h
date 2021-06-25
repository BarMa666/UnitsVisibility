#pragma once

/*
* Класс UnitManager отвечает за взаимодействие между юнитами(проверяет видимость напр.)
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

	void calcutale();

	void add(Unit&& _unit);

	~UnitManager();

protected:
	UnitManager();

	// проверяет видимость между двумя юнитами
	bool checkVisibility(const Unit& _lhs, const Unit& _rhs) const;
	// проверяет дистанцию между двумя юнитами
	bool checkDistance(const Unit& _lhs, const Unit& _rhs) const;

public:
	UnitCollectionT m_units;
};

