#include "TestBatchRendering.h"

#include "Renderer.h"

#include "imgui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"

#include <vector>
#include <cstdlib>

namespace test
{
	TestBatchRendering::TestBatchRendering(float screenWidth, float screenHeight, uint32_t numOfQuads, float quadSize)
		: m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight), m_QuadSize(quadSize),
		m_ModelMatrix(glm::mat4(1.0f)), m_ViewMatrix(glm::mat4(1.0f)), m_ProjectionMatrix(glm::ortho(0.0f, (float)m_ScreenWidth, 0.0f, (float)m_ScreenHeight, -1.0f, 1.0f))
	{
		std::vector<float> batchedVerts;
		std::vector<uint32_t> indices;

		for (uint32_t i = 0; i < numOfQuads; i++)
		{
			// The range of the offsets is designed so that the quads can be up to half way off the screen
			float offsetX = RandomFloatRange(0, m_ScreenWidth);
			float offsetY = RandomFloatRange(0, m_ScreenHeight);

			// Vertex color RGBA values
			float r = RandomFloatRange(0, 1),
				  g = RandomFloatRange(0, 1),
				  b = RandomFloatRange(0, 1),
				  a = 1;

			uint8_t textureIndex = std::rand() % 2;

			float scale = RandomFloatRange(0.25f, 1.75f);

			float quadVerts[] = {
				(-m_QuadSize / 2 + offsetX) * scale, (-m_QuadSize / 2 + offsetY) * scale, r, g, b, a, 0.0f, 0.0f, textureIndex, // 0
				 (m_QuadSize / 2 + offsetX) * scale, (-m_QuadSize / 2 + offsetY) * scale, r, g, b, a, 1.0f, 0.0f, textureIndex, // 1
				 (m_QuadSize / 2 + offsetX) * scale,  (m_QuadSize / 2 + offsetY) * scale, r, g, b, a, 1.0f, 1.0f, textureIndex, // 2
				(-m_QuadSize / 2 + offsetX) * scale,  (m_QuadSize / 2 + offsetY) * scale, r, g, b, a, 0.0f, 1.0f, textureIndex  // 3
			};

			// Add to the batched verts
			batchedVerts.insert(batchedVerts.end(), &quadVerts[0], &quadVerts[sizeof(quadVerts) / sizeof(float)]);

			// The total number of verts currently in the vector of batched verts. Useful for generating indices.
			uint32_t n = i * 4;
			uint32_t quadIndices[] = { n, n + 1, n + 2, n + 2, n + 3, n };

			// Add to the indices
			indices.insert(indices.end(), &quadIndices[0], &quadIndices[sizeof(quadIndices) / sizeof(float)]);
		}

		// Vertex array
		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>((const void*)&batchedVerts[0], 9 * 4 * numOfQuads * sizeof(float));

		m_VertexBufferLayout = std::make_unique<VertexBufferLayout>();
		m_VertexBufferLayout->Push<float>(2); // Position
		m_VertexBufferLayout->Push<float>(4); // Vertex color
		m_VertexBufferLayout->Push<float>(2); // Texture coordinates
		m_VertexBufferLayout->Push<float>(1); // Texture index
		m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

		// Index buffer
		m_IndexBuffer = std::make_unique<IndexBuffer>((const unsigned int*)&indices[0], indices.size());

		// Shader
		m_Shader = std::make_unique<Shader>("res/shaders/BatchTextured.shader");
		m_Shader->Bind();

		// Texture
		m_Texture0 = std::make_unique<Texture>("res/textures/bank.png");
		m_Texture0->Bind();
		m_Texture0->BindTextureUnit(0);

		m_Texture1 = std::make_unique<Texture>("res/textures/cat2.png");
		m_Texture1->Bind();
		m_Texture0->BindTextureUnit(1);

		int samplers[2] = { 0, 1 };
		m_Shader->SetUniform1iv("u_Textures", 2, samplers);

		m_Renderer = std::make_unique<Renderer>();
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
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
	}

	void TestBatchRendering::OnImGuiRender()
	{
	}
}