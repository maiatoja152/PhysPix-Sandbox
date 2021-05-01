#pragma once

#include "Cell.h"

namespace cell
{
	class Empty : public Cell
	{
	public:
		Empty();
		~Empty();

		virtual Empty* clone() const override;
	};
}
