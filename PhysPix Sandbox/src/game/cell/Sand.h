#pragma once

#include "Cell.h"
#include "Powder.h"

namespace cell
{
	class Sand : public Cell, public Powder
	{
	public:
		Sand(CellGrid* cellGrid, int32_t posX, int32_t posY);
		~Sand();

		void OnUpdate(float deltaTime) override;
		void OnTick() override;
	};
}