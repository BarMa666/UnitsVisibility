#pragma once

/*
* Класс Field представляет собой игровое поле, на котором располагаются объекты
*/
#include "FieldView.h"
#include "Types.h"

class FieldView;
class Object;
class Unit;

class Field
{
public:
	using CellT = int;

	Field();

	virtual ~Field();

	// установить объект на его позицию
	void setCell(Object const* _object);
	// освободить позицию
	void freeCell(CellT _x, CellT _y);
	// отобразить поле
	void show() const;

	Field(const Field&) = delete;
	Field& operator=(const Field&) = delete;
	Field(Field&&) = delete;
	Field& operator=(Field&&) = delete;

	// std::vector<Unit const*> getUnits() const;

protected:
	// предотварщаяет выход за пределы поля
	bool checkBorders(CellT _x, CellT _y) const;
	// переход от координат к индексам массива поля
	void convertBorders(OUT CellT& _x, OUT CellT& _y) const;

private:

#ifndef _TEST
	static constexpr CellT FIELD_WIDTH_HALF = 50;
	static constexpr CellT FIELD_HEIGHT_HALF = 50;
#else
	static constexpr CellT FIELD_WIDTH_HALF = 2;
	static constexpr CellT FIELD_HEIGHT_HALF = 2;
#endif
	static constexpr CellT FIELD_WIDTH = FIELD_WIDTH_HALF * 2 + 1;
	static constexpr CellT FIELD_HEIGHT = FIELD_HEIGHT_HALF * 2 + 1;

	Object const* m_field[FIELD_WIDTH][FIELD_HEIGHT];
	friend static void FieldView::show(const Field* _field);
};


