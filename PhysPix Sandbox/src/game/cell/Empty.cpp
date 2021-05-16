#include "Empty.h"

namespace cell
{
	Empty::Empty()
	{
		m_Color = cell_color::empty;

		m_CellID = cell_id::empty;
	}

	Empty::~Empty()
	{
	}

	void Empty::OnTick()
	{
	}
}