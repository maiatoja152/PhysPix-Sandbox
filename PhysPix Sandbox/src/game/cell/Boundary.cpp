#include "Boundary.h"

namespace cell
{
	Boundary::Boundary()
	{
		m_Color = cell_color::boundary;

		m_CellID = cell_id::boundary;
	}

	Boundary::~Boundary()
	{
	}

	void Boundary::OnTick()
	{
	}
}