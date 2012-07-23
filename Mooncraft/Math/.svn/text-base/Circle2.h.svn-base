#pragma once

#include "Vector2.h"

namespace phynet{
namespace math{

class Circle2
{
public:
	Circle2()
		:m_radius(0.0f)
		,m_center()
	{
	}
	
	Circle2(const Vector2& i_center, const Real i_radius)
		:m_radius(i_radius)
		,m_center(i_center)
	{
	}

	const Vector2& GetCenter() const
	{
		return m_center;
	}
	
	const Real GetRadius() const
	{
		return m_radius;
	}

	void SetCenter(const Vector2& i_center) 
	{
		m_center = i_center;
	}
	
	void SetRadius(const Real i_radius)
	{
		m_radius = i_radius;
	}

private:
	Vector2 m_center;
	Real m_radius;
};

}} // namespaces

