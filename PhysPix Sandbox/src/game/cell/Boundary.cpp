#include "Boundary.h"

namespace cell
{
	Boundary::Boundary()
	{
		m_Color = { 1.0f, 0.0f, 0.0f, 1.0f };

		m_CellID = cell_id::boundary;
	}

	Boundary::~Boundary()
	{
	}

	Boundary* Boundary::clone() const
	{
		return new Boundary(*this);
	}
}