#include "UnitVisibilityTester.h"
#include "ObservationSubject.h"
#include "Unit.h"
#include <algorithm>

UnitVisibilityTester& UnitVisibilityTester::instance()
{
	static UnitVisibilityTester settings;
	return settings;
}

UnitVisibilityTester::UnitVisibilityTester() : m_test()
{
	ObservationSubject::subscribe(ObservationSubject::UNIT_CREATE, this, [this](Unit const* _unit)
		{
			addTestData(_unit);
		});

	ObservationSubject::subscribe(ObservationSubject::UNIT_DELETE, this, [this](Unit const* _unit)
		{
			removeTestData(_unit);
		});
}

UnitVisibilityTester::~UnitVisibilityTester()
{
	ObservationSubject::unsubscribe(this);
}

void UnitVisibilityTester::add(const TestNameT& _name, const TestValueT& _val)
{
	auto iter = m_test.find(_name);
	if (iter != m_test.end())
	{
		iter->second = _val;
	}
}

void UnitVisibilityTester::addResult(const TestNameT& _name, const tstring& _raw_val)
{
	m_result.emplace(_name, static_cast<unsigned>(std::stoul(_raw_val)));
}

// REFME 
void UnitVisibilityTester::test() const
{
	auto iter_test = m_test.cbegin();
	auto iter_result = m_result.cbegin();
	while (true)
	{
		const auto& found = std::mismatch(iter_test, m_test.cend(), iter_result, m_result.cend(), [](const auto& _lhs, const auto& _rhs)
			{
				if (_lhs.first == _rhs.first)
				{
					return _lhs.second == _rhs.second;
				}
				return true;
			});
		if (found.first == m_test.cend()) break;
		++(iter_test = found.first);
		++(iter_result = found.second);
		tcout << _T("Mismatch found: ") << found.first->first << _T(" expected: ") << found.second->second << _T(" result: ") << found.first->second << _T("\n");
	}
	
}

void UnitVisibilityTester::addTestData(Unit const* _unit)
{
	if (_unit)
	{
		m_test.emplace(_unit->name(), 0);
	}
}

void UnitVisibilityTester::removeTestData(Unit const* _unit)
{
	if (_unit)
	{
		m_test.erase(_unit->name());
	}
}
