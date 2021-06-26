#include "FieldView.h"
#include "Field.h"
#include "Object.h"

void FieldView::show(const Field* _field)
{
	for (auto w = 0; w < _field->FIELD_WIDTH; ++w)
	{
		for (auto h = 0; h < _field->FIELD_HEIGHT; ++h)
		{
			if (_field->m_field[w][h])
			{
				_field->m_field[w][h]->show();
			}
		}
	}
}
