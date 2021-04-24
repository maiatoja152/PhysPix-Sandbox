#pragma once

#include "GL/glew.h"

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(unsigned int count, const unsigned int* data, GLenum usage);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	void BufferSubData(int offset, int size, const void* data);

	inline unsigned int GetCount() const { return m_Count; }
};