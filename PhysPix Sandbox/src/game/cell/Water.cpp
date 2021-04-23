#include "Water.h"

#include "CellGrid.h"

#include "Empty.h"

namespace cell
{
	Water::Water(int32_t posX, int32_t posY)
	{
		m_PosX = posX;
		m_PosY = posY;
	}

	Water::~Water()
	{
	}

	void Water::OnUpdate(float deltaTime)
	{
	}

	void Water::OnTick()
	{
		Empty* empty = new Empty();
		
		if (m_CellGrid->GetCell(m_PosX, m_PosY + 1) == empty)
		{
			MoveCell(m_PosX, m_PosY + 1);
		}
		else if (m_CellGrid->GetCell(m_PosX + 1, m_PosY + 1) == empty)
		{
			MoveCell(m_PosX + 1, m_PosY + 1);
		}
		else if (m_CellGrid->GetCell(m_PosX - 1, m_PosY + 1) == empty)
		{
			MoveCell(m_PosX - 1, m_PosY + 1);
		}
		else
		{
			delete empty;
		}
	}
}