#pragma once

#include "GLCore.h"

#include "glm/gtc/matrix_transform.hpp"

class BatchRenderer
{
private:
	
public:
	static void Init();
	static void Shutdown();

	static void BeginBatch();
	static void EndBatch();
	static void Flush();

	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, uint32_t textureID);

private:
	static void GenerateQuadVerts(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, uint32_t textureID);

public:
	// Stats
	struct Stats
	{
		uint32_t DrawCount = 0;
		uint32_t QuadCount = 0;
	};

	static const Stats& GetStats();
	static void ResetStats();
};

