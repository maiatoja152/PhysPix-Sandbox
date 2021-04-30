#pragma once

#include <memory>

namespace cell
{
	class Cell;
}

class CellGrid;

class CellPlacement
{
private:
	std::unique_ptr<cell::Cell> m_ActiveCell;
	CellGrid* m_CellGrid;
	uint16_t m_PlaceSize;

public:
	CellPlacement(CellGrid* cellGrid);
	~CellPlacement();

	void Place(int32_t x, int32_t y);
};