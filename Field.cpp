#include "Field.h"
#include "Unit.h"
#include "FieldView.h"
#include "ObservationSubject.h"
#include <algorithm>

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

// TODO возможная оптимизация - создание отдельного вектора с указателями на юниты, 
// при запросе возвращать его, а не создавать новый
std::vector<Unit const*> Field::getUnits() const
{
	std::vector<Unit const*> res;
	for (auto w = 0; w < FIELD_WIDTH; ++w)
	{
		for (auto h = 0; h < FIELD_HEIGHT; ++h)
		{
			if (auto unit = dynamic_cast<Unit const*>(m_field[w][h]))
			{
				res.push_back(unit);
			}
		}
	}
	auto func = [](auto const& _lhs, auto const& _rhs)
	{
		return _lhs->name() < _rhs->name();
	};
	sort(res.begin(), res.end(), func);
	return res;
}

void Field::show()
{
	// UNDONE вынести отображение в отдельный класс FieldView
	for (auto w = 0; w < FIELD_WIDTH; ++w)
	{
		for (auto h = 0; h < FIELD_HEIGHT; ++h)
		{
			if (auto unit = dynamic_cast<const Unit*>(m_field[w][h]))
			{
				unit->show();
			}
		}
	}
}

bool Field::checkBorders(CellT _x, CellT _y) const
{
	return _x <= FIELD_WIDTH_HALF  && _x >= (-1) * FIELD_WIDTH_HALF 
		&& _y <= FIELD_HEIGHT_HALF && _y >= (-1) * FIELD_HEIGHT_HALF;
}

void Field::convertBorders(OUT CellT& _x, OUT CellT& _y)
{
	_x += FIELD_WIDTH_HALF;
	_y += FIELD_HEIGHT_HALF;
}

