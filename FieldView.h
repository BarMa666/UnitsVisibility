#pragma once

/*
* Класс FieldView является визуальным представлением Field
*/

class Field;

class FieldView
{
public:
	// отображает всех юнитов на поле
	static void show(Field* _field);
};

