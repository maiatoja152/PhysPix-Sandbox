#pragma once

#include "GL/glew.h"

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size, GLenum usage);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void BufferSubData(int offset, int size, const void* data);
};