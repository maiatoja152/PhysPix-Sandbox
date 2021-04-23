#pragma once

#include "GL/glew.h"

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count, GLenum usage);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	void BufferSubData(int offset, int size, const void* data);

	inline unsigned int GetCount() const { return m_Count; }
};