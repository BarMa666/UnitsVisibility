#pragma once

/*
* ����� Field ������������ ����� ������� ����, �� ������� ������������� �������
*/
#include <memory>
#include <vector>

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

	// ���������� ������ �� ��� �������
	void setCell(Object const* _object);
	// ���������� �������
	void freeCell(CellT _x, CellT _y);
	// ���������� ����
	void show();

	Field(const Field&) = delete;
	Field& operator=(const Field&) = delete;
	Field(Field&&) = delete;
	Field& operator=(Field&&) = delete;

	std::vector<Unit const*> getUnits() const;

protected:
	// �������������� ����� �� ������� ����
	bool checkBorders(CellT _x, CellT _y) const;
	// ������� �� ��������� � �������� ������� ����
	void convertBorders(OUT CellT& _x, OUT CellT& _y);

private:
	static constexpr CellT FIELD_WIDTH_HALF = 50;
	static constexpr CellT FIELD_HEIGHT_HALF = 50;

	static constexpr CellT FIELD_WIDTH = FIELD_WIDTH_HALF * 2 + 1;
	static constexpr CellT FIELD_HEIGHT = FIELD_HEIGHT_HALF * 2 + 1;

	Object const* m_field[FIELD_WIDTH][FIELD_HEIGHT];
	friend static void FieldView::show(Field* _field);
};


