#include "UnitView.h"
#include "UnitSettings.h"
#include "Unit.h"
#include "Object.h"
#include "Types.h"

UnitView::UnitView() : ObjectView()
{}

void UnitView::show(const Object* _object)
{
	const auto _unit = dynamic_cast<const Unit*>(_object);
	if ( _unit)
	{
		auto res = _unit->name() + _T(": видит ") + tostring(_unit->getVisibleCount()) + _T("\n");
		tcout << res;
		UnitSettings::instance() << res;
	}
}
