#pragma once

#include "Test.h"

#include "Shader.h"
#include "Texture.h"

#include <memory>
#include <vector>

namespace test
{
	class TestBatchRendering : public Test
	{
	public:
		TestBatchRendering(float screenWidth, float screenHeight, uint32_t numOfQuads, float quadSize, std::string* texPaths, uint8_t count);
		~TestBatchRendering();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_ScreenWidth, m_ScreenHeight, m_QuadSize;

		std::unique_ptr<Shader> m_Shader;
		std::vector<Texture> m_Textures;

		glm::mat4 m_ModelMatrix, m_ViewMatrix, m_ProjectionMatrix;

		float RandomFloatRange(float begin, float end);
	};
}