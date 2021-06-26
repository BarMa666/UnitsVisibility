#pragma once

#include "Types.h"

class Unit;

class UnitVisibilityTester
{
public:
	using TestNameT = tstring;
	using TestValueT = unsigned;
	using TestTypeT = std::map<TestNameT, TestValueT>;

	static UnitVisibilityTester& instance();

	virtual ~UnitVisibilityTester();

	UnitVisibilityTester(const UnitVisibilityTester&) = delete;
	UnitVisibilityTester& operator=(const UnitVisibilityTester&) = delete;
	UnitVisibilityTester(UnitVisibilityTester&&) = delete;
	UnitVisibilityTester& operator=(UnitVisibilityTester&&) = delete;

	void add(const TestNameT& _name, const TestValueT& _val);
	void addResult(const TestNameT& _name, const tstring& _raw_val);
	void test() const;

private:
	UnitVisibilityTester();

	void addTestData(Unit const* _unit);
	void removeTestData(Unit const* _unit);

	TestTypeT m_test;
	TestTypeT m_result;
};

