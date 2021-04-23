#pragma once

class CellGrid;

#include <stdint.h>

namespace cell
{
	class Cell
	{
	protected:
		CellGrid* m_CellGrid;
		int32_t m_PosX, m_PosY;

	public:
		Cell();
		~Cell();

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnTick() {}

		void RemoveCell();
		void MoveCell(uint16_t x, uint16_t y);
	};
}
