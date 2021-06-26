#pragma once

/*
* Базовый класс-интерфейс для игровых объектов, 
* пригодится в случае добавления новых объектов кроме юнитов
*/
#include "UnitView.h"
#include "Types.h"

class Object
{
public:
	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;
	Object(Object&&) = default;
	Object& operator=(Object&&) = default;

	virtual void show() const = 0;
	const PositionT& position() const;
	const NameT& name() const;

	virtual ~Object() = default;

protected:
	Object(const PositionT&, const NameT&, std::unique_ptr<ObjectView>&& _view);

	PositionT m_position;
	NameT m_name;

	std::unique_ptr<ObjectView> m_view;
};

