#include "TestBatchRendering.h"

#include "GLCore.h"
#include "GL/glew.h"

#include "BatchRenderer.h"

#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"

#include <cstdlib>
#include <array>

namespace test
{
	TestBatchRendering::TestBatchRendering(float screenWidth, float screenHeight, uint32_t numOfQuads, float quadSize, std::string* texturePaths, uint8_t count)
		: m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight), m_QuadSize(quadSize),
		m_ModelMatrix(glm::mat4(1.0f)), m_ViewMatrix(glm::mat4(1.0f)), m_ProjectionMatrix(glm::ortho(0.0f, (float)m_ScreenWidth, 0.0f, (float)m_ScreenHeight, -1.0f, 1.0f))
	{
		// Make sure the number of textures passed is less than or equal to the max number of textures available to the fragment shader
		int maxTexUnits;
		GLCall(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTexUnits));
		ASSERT(count <= maxTexUnits - 1);

		// Texture
		std::vector<int> samplers;

		for (uint8_t i = 0; i < count; i++)
		{
			m_Textures[i] = std::make_unique<Texture>(texturePaths[i]);
			m_Textures[i]->Bind(i);

			samplers.push_back(i + 1);
		}

		// Shader
		m_Shader = std::make_unique<Shader>("res/shaders/BatchTextured.shader");
		m_Shader->Bind();

		m_Shader->SetUniform1iv("u_Textures", samplers.size(), &samplers[0]);

		BatchRenderer::BeginBatch();
		for (uint32_t i = 0; i < numOfQuads; i++)
		{
			// The range of the offsets is set so that the quads can be up to half way off the screen
			float offsetX = RandomFloatRange(0.0f, m_ScreenWidth);
			float offsetY = RandomFloatRange(0.0f, m_ScreenHeight);

			// Vertex color RGBA values
			float r = RandomFloatRange(0.1f, 1.0f),
				  g = RandomFloatRange(0.1f, 1.0f),
				  b = RandomFloatRange(0.1f, 1.0f),
				  a = 1;

			uint8_t textureIndex = std::rand() % count;

			float randScale = RandomFloatRange(0.5f, 1.5f);

			BatchRenderer::DrawQuad({ offsetX, offsetY }, { m_QuadSize * randScale, m_QuadSize * randScale }, m_Textures[textureIndex]->GetRendererID());
		}
		BatchRenderer::EndBatch();
	}

	TestBatchRendering::~TestBatchRendering()
	{
	}

	float TestBatchRendering::RandomFloatRange(float begin, float end)
	{
		return begin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (end - begin)));
	}

	void TestBatchRendering::OnUpdate(float deltaTime)
	{
	}

	void TestBatchRendering::OnRender()
	{
		glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
	}

	void TestBatchRendering::OnImGuiRender()
	{
	}
}