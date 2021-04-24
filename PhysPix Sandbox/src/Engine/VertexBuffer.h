#pragma once

#include "GL/glew.h"

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(unsigned int size, const void* data, GLenum usage);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void BufferData(int size, const void* data, GLenum usage);
	void BufferSubData(int offset, int size, const void* data);
};