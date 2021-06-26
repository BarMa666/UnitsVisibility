#include "Application.h"
#include "UnitSettings.h"
#include "UnitVisibilityTester.h"
#include "UnitManager.h"

Application::Application()
	: m_field()
{
#ifdef _TEST
	UnitVisibilityTester::instance();
#endif
}

void Application::loadData()
{
	UnitSettings::instance().loadSettings();
}

void Application::showResult() const
{
	UnitManager::instance().update();
	m_field.show();
	UnitSettings::instance().saveResult();
#ifdef _TEST
	UnitVisibilityTester::instance().test();
#endif
}
