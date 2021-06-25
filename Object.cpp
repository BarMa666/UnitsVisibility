#include "Object.h"

Object::Object(const PositionT& _pos, const NameT& _name, std::unique_ptr<ObjectView>&& _view)
	: m_position(_pos)
	, m_name(_name)
	, m_view(nullptr)
{
	m_view.swap(_view);
}

const PositionT& Object::position() const
{
	return m_position;
}

const NameT& Object::name() const
{
	return m_name;
}
