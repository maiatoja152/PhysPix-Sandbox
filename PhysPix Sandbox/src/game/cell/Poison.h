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

		void OnUpdate(float deltaTime) override;
		void OnTick() override;

	private:
		void Spread();

		virtual void Burn() override;
	};
}