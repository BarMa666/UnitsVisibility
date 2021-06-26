#pragma once

#include "ObjectView.h"

class UnitView : public ObjectView
{
public:
	UnitView();

	virtual ~UnitView() = default;

	void show(const Object* _unit) override;
};

