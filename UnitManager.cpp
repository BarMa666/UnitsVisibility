#include "UnitManager.h"
#include "UnitSettings.h"
#include "UnitVisibilityTester.h"
#include "ObservationSubject.h"
#include "Unit.h"
#include <algorithm>

UnitManager::UnitManager() : m_units()
{
}

UnitManager& UnitManager::instance()
{
    static UnitManager manager;
    return manager;
}

void UnitManager::createUnit(const NameT& _name, const PositionT& _position, const DirectionT& _direction)
{
    add(std::move(*(Unit::create(_name, _position, _direction))));
}

void UnitManager::update()
{
    std::for_each(m_units.begin(), m_units.end(), [this](auto& _unit)
        {
            auto res = std::count_if(m_units.cbegin(), m_units.cend(), [&_unit, this](auto& _elem)
                {
                    if (!(_unit == _elem))
                    {
                        return checkVisibility(_unit, _elem);
                    }
                    return false;
                });
            _unit.setVisibleCount(res);
#ifdef _TEST
            UnitVisibilityTester::instance().add(_unit.name(), res);
#endif             
        });
}

bool UnitManager::checkVisibility(const Unit& _lhs, const Unit& _rhs) const
{
    return checkDistance(_lhs, _rhs) && _lhs.checkDirection(_rhs);
}

bool UnitManager::checkDistance(const Unit& _lhs, const Unit& _rhs) const
{
    return (_lhs.position() - _rhs.position()).modulo() <= UnitSettings::instance().getDistanceVisibility();
}

void UnitManager::add(Unit&& _unit)
{
    m_units.emplace_back(std::move(_unit));
    ObservationSubject::invoke(ObservationSubject::UNIT_CREATE, &m_units.back());
}

UnitManager::~UnitManager()
{
    for (auto& it : m_units)
    {
        ObservationSubject::invoke(ObservationSubject::UNIT_DELETE, &m_units.back());
    }
}
