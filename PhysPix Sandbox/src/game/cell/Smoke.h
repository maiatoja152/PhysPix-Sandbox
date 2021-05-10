#pragma once

#include "Cell.h"
#include "Fluid.h"

namespace cell
{
	class Smoke : public Cell, public Fluid
	{
	public:
		Smoke(CellGrid* cellGrid, int32_t posX, int32_t posY);
		~Smoke();

		void OnUpdate(float deltaTime) override;
		void OnTick() override;
	};
}
