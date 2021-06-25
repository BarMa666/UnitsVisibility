#include "UnitView.h"
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
		auto c = _unit->getVisibleCount();
		auto res = _unit->name() + _T(": видит ") + std::to_wstring(_unit->getVisibleCount()) + _T("\n");
		std::wcout << res;
	}
}
