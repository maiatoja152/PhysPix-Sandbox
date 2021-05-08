#include "Empty.h"

namespace cell
{
	Empty::Empty()
	{
		m_Color = { 0.8f, 0.7f, 0.7f, 1.0f };

		m_CellID = cell_id::empty;
	}

	Empty::~Empty()
	{
	}

	void Empty::OnUpdate(float deltaTime)
	{
	}

	void Empty::OnTick()
	{
	}
}