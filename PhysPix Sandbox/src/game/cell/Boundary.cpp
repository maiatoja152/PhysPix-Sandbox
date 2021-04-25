#include "Boundary.h"

namespace cell
{
	Boundary::Boundary()
	{
		m_Color = { 1.0f, 0.0f, 0.0f, 1.0f };

		m_CellID = 255;
	}

	Boundary::~Boundary()
	{
	}
}