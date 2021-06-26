#include "ObservationSubject.h"

std::multimap <ObservationSubject::ActionNameT, std::pair<void*, ObservationSubject::ActionT>> ObservationSubject::m_map;

const ObservationSubject::ActionNameT ObservationSubject::UNIT_CREATE = _T("Unit Create");
const ObservationSubject::ActionNameT ObservationSubject::UNIT_DELETE = _T("Unit Delete");

void ObservationSubject::subscribe(const ActionNameT& _action_name, void* _observer, ActionT _action)
{
	m_map.emplace(std::make_pair(_action_name, std::make_pair(_observer, _action)));
}

void ObservationSubject::unsubscribe(const ActionNameT& _action_name, void* _observer)
{
	for (auto&& it : m_map)
	{
		if (it.second.first && it.first == _action_name && it.second.first == _observer)
		{
			m_map.erase(it.first);
		}
	}
}

void ObservationSubject::unsubscribe(void* _observer)
{
	for (auto iter = m_map.begin(); iter != m_map.end();)
	{
		if (iter->second.first && iter->second.first == _observer)
		{
			iter = m_map.erase(iter);
		}
		else ++iter;
	}
}

void ObservationSubject::invoke(const ActionNameT& _action_name, Unit const* _unit)
{
	for (auto&& it : m_map)
	{
		if (it.second.first && it.first == _action_name)
		{
			it.second.second(_unit);
		}
	}
}
