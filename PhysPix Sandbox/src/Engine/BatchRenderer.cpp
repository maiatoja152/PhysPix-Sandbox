#include "BatchRenderer.h"

#include "GLCore.h"
#include "GL/glew.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include <array>
#include <memory>

static const size_t MaxQuadCount = 10000;
static const size_t MaxVertexCount = MaxQuadCount * 4;
static const size_t MaxIndexCount = MaxQuadCount * 6;
static const size_t MaxTextures = 32;

struct Vertex
{
	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec2 TexCoords;
	float TexIndex;
};

//struct RendererData
//{
//	GLuint QuadVA = 0;
//	GLuint QuadVB = 0;
//	GLuint QuadIB = 0;
//
//	GLuint WhiteTexture = 0;
//	uint32_t WhiteTextureSlot = 0;
//
//	uint32_t IndexCount = 0;
//
//	Vertex* QuadBuffer = nullptr;
//	Vertex* QuadBufferPtr = nullptr;
//
//	std::array<uint32_t, MaxTextures> TextureSlots;
//	uint32_t TextureSlotIndex = 1;
//
//	BatchRenderer::Stats RendererStats;
//};

struct RendererData
{
	std::unique_ptr<VertexArray> QuadVA = nullptr;
	std::unique_ptr<VertexBuffer> QuadVB = nullptr;
	std::unique_ptr<VertexBufferLayout> QuadVBL = nullptr;
	std::unique_ptr<IndexBuffer> QuadIB = nullptr;

	GLuint WhiteTexture = 0;
	uint32_t WhiteTextureSlot = 0;

	uint32_t IndexCount = 0;

	Vertex* QuadBuffer = nullptr;
	Vertex* QuadBufferPtr = nullptr;

	//std::array<Texture, MaxTextures> Textures;
	std::array<uint32_t, MaxTextures> TextureSlots;
	uint8_t TextureSlotIndex = 1;

	BatchRenderer::Stats RendererStats;
};

static RendererData s_Data;

void BatchRenderer::Init()
{
	// If the cpu-side buffer is not empty then Init() may have been called more than once which is not allowed
	ASSERT(s_Data.QuadBuffer == nullptr);
	s_Data.QuadBuffer = new Vertex[MaxVertexCount];

	s_Data.QuadVA = std::make_unique<VertexArray>();
	s_Data.QuadVA->Bind();

	s_Data.QuadVB = std::make_unique<VertexBuffer>(MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	s_Data.QuadVB->Bind();

	s_Data.QuadVBL = std::make_unique<VertexBufferLayout>();
	s_Data.QuadVBL->Push<float>(3);
	s_Data.QuadVBL->Push<float>(4);
	s_Data.QuadVBL->Push<float>(2);
	s_Data.QuadVBL->Push<float>(1);

	s_Data.QuadVA->AddBuffer(*s_Data.QuadVB, *s_Data.QuadVBL);

	std::vector<uint32_t> indices(MaxIndexCount);
	uint32_t offset = 0;
	for (uint32_t i = 0; i < MaxIndexCount; i += 6)
	{
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}

	s_Data.QuadIB = std::make_unique<IndexBuffer>(indices.size(), &indices[0], GL_STATIC_DRAW);

	// 1x1 white texture
	glCreateTextures(GL_TEXTURE_2D, 1, &s_Data.WhiteTexture);
	glBindTexture(GL_TEXTURE_2D, s_Data.WhiteTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	uint32_t color = 0xffffffff;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

	s_Data.TextureSlots[s_Data.WhiteTextureSlot] = s_Data.WhiteTexture;
	for (size_t i = 1; i < MaxTextures; i++)
		s_Data.TextureSlots[i] = 0;
}

void BatchRenderer::Shutdown()
{
	glDeleteTextures(1, &s_Data.WhiteTexture);
	delete[] s_Data.QuadBuffer;
}

void BatchRenderer::BeginBatch()
{
	s_Data.QuadBufferPtr = s_Data.QuadBuffer;
}

void BatchRenderer::EndBatch()
{
	GLsizeiptr size = (uint8_t*)s_Data.QuadBufferPtr - (uint8_t*)s_Data.QuadBuffer;
	s_Data.QuadVB->Bind();
	s_Data.QuadVB->BufferSubData(0, size, s_Data.QuadBuffer);
}

void BatchRenderer::Flush()
{
	for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
	{
		GLCall(glBindTextureUnit(i, s_Data.TextureSlots[i]));
	}

	s_Data.QuadVA->Bind();
	GLCall(glDrawElements(GL_TRIANGLES, s_Data.IndexCount, GL_UNSIGNED_INT, nullptr));
	s_Data.RendererStats.DrawCount++;

	s_Data.IndexCount = 0;
	s_Data.TextureSlotIndex = 1;
}

void BatchRenderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	if (s_Data.IndexCount + 6 > MaxIndexCount)
	{
		EndBatch();
		Flush();
		BeginBatch();
	}

	float textureIndex = 0.0f;

	GenerateQuadVerts(position, size, color, textureIndex);

	s_Data.IndexCount += 6;
	s_Data.RendererStats.QuadCount++;
}

void BatchRenderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, uint32_t textureID)
{
	if (s_Data.IndexCount + 6 > MaxIndexCount || s_Data.TextureSlotIndex > 31)
	{
		EndBatch();
		Flush();
		BeginBatch();
	}

	constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// Check if the texture has already been added to TextureSlots
	float textureIndex = 0.0f;
	for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
	{
		if (s_Data.TextureSlots[i] == textureID)
		{
			textureIndex = i;
			break;
		}
	}

	if (textureIndex == 0.0f)
	{
		textureIndex = s_Data.TextureSlotIndex;
		s_Data.TextureSlots[s_Data.TextureSlotIndex] = textureID;
		s_Data.TextureSlotIndex++;
	}

	GenerateQuadVerts(position, size, color, textureIndex);

	s_Data.IndexCount += 6;
	s_Data.RendererStats.QuadCount++;
}

void BatchRenderer::GenerateQuadVerts(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, uint32_t textureID)
{
	s_Data.QuadBufferPtr->Position = { -size.x / 2 + position.x, -size.y / 2 + position.y, 0.0f };
	s_Data.QuadBufferPtr->Color = color;
	s_Data.QuadBufferPtr->TexCoords = { 0.0f, 0.0f };
	s_Data.QuadBufferPtr->TexIndex = textureID;
	s_Data.QuadBufferPtr++;

	s_Data.QuadBufferPtr->Position = { size.x / 2 + position.x, -size.y / 2 + position.y, 0.0f };
	s_Data.QuadBufferPtr->Color = color;
	s_Data.QuadBufferPtr->TexCoords = { 1.0f, 0.0f };
	s_Data.QuadBufferPtr->TexIndex = textureID;
	s_Data.QuadBufferPtr++;

	s_Data.QuadBufferPtr->Position = { size.x / 2 + position.x, size.y / 2 + position.y, 0.0f };
	s_Data.QuadBufferPtr->Color = color;
	s_Data.QuadBufferPtr->TexCoords = { 1.0f, 1.0f };
	s_Data.QuadBufferPtr->TexIndex = textureID;
	s_Data.QuadBufferPtr++;

	s_Data.QuadBufferPtr->Position = { -size.x / 2 + position.x, size.y / 2 + position.y, 0.0f };
	s_Data.QuadBufferPtr->Color = color;
	s_Data.QuadBufferPtr->TexCoords = { 0.0f, 1.0f };
	s_Data.QuadBufferPtr->TexIndex = textureID;
	s_Data.QuadBufferPtr++;
}