#include "IndexBuffer.h"

#include "GLCore.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count, GLenum usage)
    : m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, usage));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::BufferSubData(int offset, int size, const void* data)
{
    Bind();
    GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data));
}