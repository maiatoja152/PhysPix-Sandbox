#pragma once

#include "Cell.h"

namespace cell
{
	class Empty : public Cell
	{
	public:
		Empty();
		~Empty();

		void OnUpdate(float deltaTime) override;
		void OnTick() override;
	};
}
