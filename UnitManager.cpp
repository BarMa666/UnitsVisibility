#include "UnitManager.h"
#include "UnitSettings.h"
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
    auto unit = Unit::create(_name, _position, _direction);
    add(std::move(*(unit)));
}

void UnitManager::calcutale()
{
    auto first = m_units.begin();
    while (first != m_units.end())
    {
        auto res = std::count_if(m_units.cbegin(), m_units.cend(), [first, this](auto& _elem)
            {
                if (!(*first == _elem))
                {
                    return checkVisibility(*first, _elem);
                }
                return false;
            });
        first++->setVisibleCount(res);
    }
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
