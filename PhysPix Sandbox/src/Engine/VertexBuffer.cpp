#include "VertexBuffer.h"

#include "GLCore.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, GLenum usage)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::BufferSubData(int offset, int size, const void* data)
{
    Bind();
    GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data));
}