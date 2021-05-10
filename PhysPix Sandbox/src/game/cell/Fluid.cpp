#include "Fluid.h"

#include "Cell.h"
#include "CellGrid.h"

#include <iostream>
#include <stdexcept>
#include <string>

namespace cell
{
	Fluid::Fluid()
		: m_FluidDir(0)
	{
	}

	Fluid::~Fluid()
	{
	}

	void Fluid::FluidMove(Cell* cell)
	{
		auto cellGrid = cell->GetCellGrid();
		int32_t posX, posY;
		cell->GetPosition(&posX, &posY);
		auto density = cell->GetDensity();

		// Error handling
		if (m_FluidDir != -1 && m_FluidDir != 1)
		{
			std::string message = std::string("Invalid fluid direction value: ") + std::to_string(m_FluidDir) + ". Fluid direction should be either -1 or 1.";
			std::cout << "[ERROR] " << message << std::endl;
			throw std::logic_error(message.c_str());
		}
		if (density == cell_density::default_density)
		{
			const char* message = "Density of a fluid should not be equal to default density";
			std::cout << "[ERROR] " << message << std::endl;
			throw std::logic_error(message);
		}

		// Multiply the density check by (m_FluidDir == -1) because it should only apply for fluids that move downward.
		// Doing this avoids a pair of if else statements and a lot of repeated code.
		if (cellGrid->GetCell(posX, posY + m_FluidDir)->GetID() == cell_id::empty || (cellGrid->GetCell(posX, posY + m_FluidDir)->GetDensity() < density) * (m_FluidDir == -1))
		{
			cellGrid->DisplaceFluid(posX, posY, posX, posY + m_FluidDir);
			return;
		}
		int8_t dir = cellGrid->GetDir();
		if (cellGrid->GetCell(posX + dir, posY + m_FluidDir)->GetID() == cell_id::empty || (cellGrid->GetCell(posX + dir, posY + m_FluidDir)->GetDensity() < density) * (m_FluidDir == -1))
		{
			cellGrid->DisplaceFluid(posX, posY, posX + dir, posY + m_FluidDir);
		}
		else if (cellGrid->GetCell(posX - dir, posY + m_FluidDir)->GetID() == cell_id::empty || (cellGrid->GetCell(posX - dir, posY + m_FluidDir)->GetDensity() < density) * (m_FluidDir == -1))
		{
			cellGrid->DisplaceFluid(posX, posY, posX - dir, posY + m_FluidDir);
		}
		else if (cellGrid->GetCell(posX + dir, posY)->GetID() == cell_id::empty || (cellGrid->GetCell(posX + dir, posY)->GetDensity() < density) * (m_FluidDir == -1))
		{
			cellGrid->DisplaceFluid(posX, posY, posX + dir, posY);
		}
		else if (cellGrid->GetCell(posX - dir, posY)->GetID() == cell_id::empty || (cellGrid->GetCell(posX - dir, posY)->GetDensity() < density) * (m_FluidDir == -1))
		{
			cellGrid->DisplaceFluid(posX, posY, posX - dir, posY);
		}
	}
}