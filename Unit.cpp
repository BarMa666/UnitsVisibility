#include "Unit.h"
#include "UnitManager.h"
#include "UnitSettings.h"
#include "ObservationSubject.h"
#include <iostream>

Unit::Unit(const NameT& _name, const PositionT& _position, const DirectionT& _direction, std::unique_ptr<ObjectView>&& _view)
	: Object(_position, _name, std::move(_view))
	, m_direction(_direction)
	, m_visibleUnitsCount(0)
{
}

const DirectionT& Unit::direction() const
{
	return m_direction;
}

void Unit::show() const
{
	m_view->show(this);
}

void Unit::setVisibleCount(const VisibleCountT& _count)
{
	m_visibleUnitsCount = _count;
}

const bool Unit::checkDirection(const Unit& _other) const
{
	auto positional_vector = position() - _other.position();
	return direction().angle(positional_vector) <= (UnitSettings::instance().getDegreesVisibility() / 2);
}

Unit* Unit::create(const NameT& _name, const PositionT& _position, const DirectionT& _direction)
{
	return new Unit(_name, _position, _direction, std::make_unique<UnitView>());
}

VisibleCountT Unit::getVisibleCount() const
{
	return m_visibleUnitsCount;
}

bool operator==(const Unit& _lhs, const Unit& _rhs)
{
	return _lhs.m_name == _rhs.m_name;
}
