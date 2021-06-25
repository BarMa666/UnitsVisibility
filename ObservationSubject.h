#pragma once
#include "Types.h"
#include <map>
#include <functional>

class Unit;

class ObservationSubject
{
public:
	using ActionNameT = std::wstring;
	using ActionT = std::function<void(Unit const*)>;

	static void subscribe(const ActionNameT& _action_name, void* _observer, ActionT _action);
	static void unsubscribe(const ActionNameT& _action_name, void* _observer);
	static void unsubscribe(void* _observer);

	static void invoke(const ActionNameT& _action_name, Unit const* _unit);

private:
	static std::multimap <ActionNameT, std::pair<void*, ActionT>> m_map;

public:
	static const ActionNameT UNIT_CREATE;
	static const ActionNameT UNIT_DELETE;
};

