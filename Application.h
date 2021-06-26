#pragma once
#include "Field.h"

static const int RETURN_OK = 0;
static const int RETURN_FAILED = 1;

class Application
{
public:
	Application();
	void loadData();
	void showResult() const;
private:
	Field m_field;
};

