#pragma once

#include "Cell.h"
#include "Fluid.h"
#include "Flammable.h"

namespace cell
{
	class Poison : public Cell, public Fluid, public Flammable
	{
	public:
		Poison(CellGrid* cellGrid, int32_t posX, int32_t posY);
		~Poison();

		void OnTick() override;

	private:
		void Spread();
	};
}