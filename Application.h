#pragma once
#include "UnitManager.h"
#include "Field.h"
#include "Types.h"

static const int RETURN_OK = 0;
static const int RETURN_FAILED = 1;

class Application
{
public:
	Application();
	void loadData();
	void showResult();
private:
	Field m_field;
};

