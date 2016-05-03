#include "mesh.hpp"

mesh::mesh() :
    m_indices(),
    m_index_buffer(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();
    this->m_array_buffer.create();
    this->m_index_buffer.create();
    this->m_vao.create();
}

mesh::~mesh()
{
    this->m_array_buffer.destroy();
    this->m_index_buffer.destroy();
    this->m_vao.destroy();
}
