#include "Application.h"
#include "UnitSettings.h"

Application::Application()
	: m_field()
{
}

void Application::loadData()
{
	UnitSettings::instance().loadSettings();
}

void Application::showResult()
{
	UnitManager::instance().calcutale();
	m_field.show();
}
