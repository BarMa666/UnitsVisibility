#include "Field.h"
#include "Unit.h"
#include "FieldView.h"
#include "ObservationSubject.h"

Field::Field()
{
	for (auto w = 0; w < FIELD_WIDTH; ++w)
	{
		for (auto h = 0; h < FIELD_HEIGHT; ++h)
		{
			m_field[w][h] = nullptr;
		}
	}
	ObservationSubject::subscribe(ObservationSubject::UNIT_CREATE, this, [this](Unit const* _unit)
		{
			setCell(_unit);
		});

	ObservationSubject::subscribe(ObservationSubject::UNIT_DELETE, this, [this](Unit const* _unit)
		{
			freeCell(static_cast<int>(_unit->position().x()), static_cast<int>(_unit->position().y()));
		});
}

Field::~Field()
{
	ObservationSubject::unsubscribe(this);
}

void Field::setCell(Object const* _object)
{
	CellT x = static_cast<int>(_object->position().x());
	CellT y = static_cast<int>(_object->position().y());
	if (checkBorders(x, y))
	{
		convertBorders(x, y);
		m_field[x][y] = _object;
	}
}

void Field::freeCell(CellT _x, CellT _y)
{
	if (checkBorders(_x, _y))
	{
		convertBorders(_x, _y);
		m_field[_x][_y] = nullptr;
	}
}

void Field::show() const
{
	FieldView::show(this);
}

bool Field::checkBorders(CellT _x, CellT _y) const
{
	return _x <= FIELD_WIDTH_HALF  && _x >= (-1) * FIELD_WIDTH_HALF 
		&& _y <= FIELD_HEIGHT_HALF && _y >= (-1) * FIELD_HEIGHT_HALF;
}

void Field::convertBorders(OUT CellT& _x, OUT CellT& _y) const
{
	_x += FIELD_WIDTH_HALF;
	_y += FIELD_HEIGHT_HALF;
}

