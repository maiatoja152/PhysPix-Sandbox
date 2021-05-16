#pragma once

class CellGrid;

#include "glm/gtc/matrix_transform.hpp"

#include <stdint.h>

namespace cell
{
	class Cell
	{
	protected:
		CellGrid* m_CellGrid;
		bool m_IsTicked;
		uint16_t m_PosX, m_PosY;
		uint8_t m_CellID;

		glm::vec4 m_Color;

		bool m_IsFluid;
		uint8_t m_Density;

		bool m_BurnsSurroudings;

	public:
		Cell();
		~Cell();

		virtual void OnTick() = 0;

		void RemoveCell();

		void UpdatePosition(uint16_t posX, uint16_t posY);

		inline CellGrid* GetCellGrid() { return m_CellGrid; }
		void SetTickState(bool state) { m_IsTicked = state; }
		inline bool IsTicked() { return m_IsTicked; }
		inline void GetPosition(uint16_t* x, uint16_t* y) { *x = m_PosX; *y = m_PosY; }
		inline uint8_t GetID() { return m_CellID; }
		inline glm::vec4 GetColor() { return m_Color; }

		inline bool IsFluid() { return m_IsFluid; }
		inline uint8_t GetDensity() { return m_Density; }
		inline bool BurnsSurroudings() { return m_BurnsSurroudings; }
	};
}

namespace cell_id
{
	static constexpr uint8_t default_id = 0;
	static constexpr uint8_t empty = 1;
	static constexpr uint8_t water = 2;
	static constexpr uint8_t poison = 3;
	static constexpr uint8_t lava = 4;
	static constexpr uint8_t sand = 5;
	static constexpr uint8_t stone = 6;
	static constexpr uint8_t smoke = 7;
	static constexpr uint8_t fire = 8;
	static constexpr uint8_t steam = 9;
	static constexpr uint8_t oil = 10;
	static constexpr uint8_t boundary = 255;
}

namespace cell_density
{
	static constexpr uint8_t default_density = 255;
	static constexpr uint8_t fire = 0;
	static constexpr uint8_t steam = 99;
	static constexpr uint8_t smoke = 100;
	static constexpr uint8_t oil = 126;
	static constexpr uint8_t water = 127;
	static constexpr uint8_t poison = 127;
	static constexpr uint8_t lava = 129;
}

namespace cell_color
{
	static constexpr glm::vec4 default_color = { 1.0f, 0.0f, 1.0f, 1.0f };
	static constexpr glm::vec4 empty = { 0.8f, 0.7f, 0.7f, 1.0f };
	static constexpr glm::vec4 water = { 0.1f, 0.3f, 0.8f, 1.0f };
	static constexpr glm::vec4 poison = { 0.0f, 0.6f, 0.1f, 1.0f };
	static constexpr glm::vec4 lava = { 1.0f, 0.45f, 0.2f, 1.0f };
	static constexpr glm::vec4 sand = { 0.95f, 0.92f, 0.33f, 1.0f };
	static constexpr glm::vec4 stone = { 0.5f, 0.5f, 0.53f, 1.0f };
	static constexpr glm::vec4 smoke = { 0.2f, 0.2f, 0.2f, 1.0f };
	static constexpr glm::vec4 fire = { 0.8f, 0.1f, 0.1f, 1.0f };
	static constexpr glm::vec4 steam = { 0.8f, 0.8f, 0.8f, 1.0f };
	static constexpr glm::vec4 oil = { 0.08f, 0.08f, 0.08f, 1.0f };
	static constexpr glm::vec4 boundary = { 1.0f, 0.0f, 0.0f, 1.0f };
}