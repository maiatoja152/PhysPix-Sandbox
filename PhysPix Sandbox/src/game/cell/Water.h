#pragma once

#include "Cell.h"
#include "Fluid.h"

namespace cell
{
	class Water : public Cell, public Fluid
	{
	public:
		Water(CellGrid* cellGrid, int32_t posX, int32_t posY);
		~Water();

		void OnUpdate(float deltaTime) override;
		void OnTick() override;
	};
}