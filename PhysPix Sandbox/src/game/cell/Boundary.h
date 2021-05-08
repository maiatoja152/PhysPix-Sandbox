#pragma once

#include "Cell.h"

namespace cell
{
	class Boundary : public Cell
	{
	public:
		Boundary();
		~Boundary();

		void OnUpdate(float deltaTime) override;
		void OnTick() override;
	};
}