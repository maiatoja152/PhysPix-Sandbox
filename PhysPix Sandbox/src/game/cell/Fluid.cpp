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
		uint16_t posX, posY;
		cell->GetPosition(&posX, &posY);
		auto density = cell->GetDensity();

		// Error handling
		CheckValidFluidDir(m_FluidDir);

		if (density == cell_density::default_density)
		{
			const char* message = "Density of a fluid should not be equal to default density";
			std::cout << "[ERROR] " << message << std::endl;
			throw std::logic_error(message);
		}

		// Movement checks
		Cell* currCell = cellGrid->GetCell(posX, posY + m_FluidDir);
		if (currCell->GetID() == cell_id::empty || IsValidFluidDisplacement(density, currCell->GetDensity(), m_FluidDir))
		{
			cellGrid->DisplaceFluid(posX, posY, posX, posY + m_FluidDir, m_FluidDir);
			return;
		}
		int8_t dir = cellGrid->GetDir();
		currCell = cellGrid->GetCell(posX + dir, posY + m_FluidDir);
		if (currCell->GetID() == cell_id::empty || IsValidFluidDisplacement(density, currCell->GetDensity(), m_FluidDir))
		{
			cellGrid->DisplaceFluid(posX, posY, posX + dir, posY + m_FluidDir, m_FluidDir);
			return;
		}
		currCell = cellGrid->GetCell(posX - dir, posY + m_FluidDir);
		if (currCell->GetID() == cell_id::empty || IsValidFluidDisplacement(density, currCell->GetDensity(), m_FluidDir))
		{
			cellGrid->DisplaceFluid(posX, posY, posX - dir, posY + m_FluidDir, m_FluidDir);
			return;
		}
		currCell = cellGrid->GetCell(posX + dir, posY);
		if (currCell->GetID() == cell_id::empty || IsValidFluidDisplacement(density, currCell->GetDensity(), m_FluidDir))
		{
			cellGrid->DisplaceFluid(posX, posY, posX + dir, posY, m_FluidDir);
			return;
		}
		currCell = cellGrid->GetCell(posX - dir, posY);
		if (currCell->GetID() == cell_id::empty || IsValidFluidDisplacement(density, currCell->GetDensity(), m_FluidDir))
		{
			cellGrid->DisplaceFluid(posX, posY, posX - dir, posY, m_FluidDir);
			return;
		}
	}

	// Check if a fluid may displace another fluid based on their relative densities
	bool Fluid::IsValidFluidDisplacement(uint8_t cellDensity, uint8_t destCellDensity, int8_t fluidDir /*= -1*/)
	{
		// Not a fluid
		if (destCellDensity == cell_density::default_density)
			return false;

		if (fluidDir == -1)
			return destCellDensity < cellDensity;
		else
			return destCellDensity > cellDensity;
	}

	void Fluid::CheckValidFluidDir(int8_t fluidDir)
	{
		if (fluidDir != -1 && fluidDir != 1)
		{
			std::string message = std::string("Invalid fluid direction value: ") + std::to_string(fluidDir) + ". Fluid direction should be either -1 or 1.";
			std::cout << "[ERROR] " << message << std::endl;
			throw std::logic_error(message.c_str());
		}
	}
}