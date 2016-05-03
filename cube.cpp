#include "cube.hpp"


struct VertexData
{
    QVector3D position;
};

cube::cube(const QVector3D &box_min, const QVector3D &box_max, QOpenGLShaderProgram *program) :
    mesh()
{

    QVector3D   v1(box_min.x(), box_min.y(), box_min.z()),
            v2(box_max.x(), box_min.y(), box_min.z()),
            v3(box_min.x(), box_max.y(), box_min.z()),
            v4(box_max.x(), box_max.y(), box_min.z()),
            v5(box_min.x(), box_min.y(), box_max.z()),
            v6(box_max.x(), box_min.y(), box_max.z()),
            v7(box_min.x(), box_max.y(), box_max.z()),
            v8(box_max.x(), box_max.y(), box_max.z());

    VertexData vertices[] = {
        // Vertex data for face 0
        {v5},  // v0
        {v6}, // v1
        {v7},  // v2
        {v8}, // v3

        // Vertex data for face 1
        {v6}, // v4
        {v2}, // v5
        {v8},  // v6
        {v4}, // v7

        // Vertex data for face 2
        {v2}, // v8
        {v1},  // v9
        {v4}, // v10
        {v3},  // v11

        // Vertex data for face 3
        {v1}, // v12
        {v5},  // v13
        {v3}, // v14
        {v7},  // v15

        // Vertex data for face 4
        {v1}, // v16
        {v2}, // v17
        {v5}, // v18
        {v6}, // v19

        // Vertex data for face 5
        {v7}, // v20
        {v8}, // v21
        {v3}, // v22
        {v4}  // v23
    };
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };
    this->m_array_buffer.bind();
    this->m_array_buffer.allocate(vertices, 24 * sizeof(VertexData));
    this->m_index_buffer.bind();
    this->m_index_buffer.allocate(indices, 34 * sizeof(GLushort));

    this->m_vao.bind();

    this->m_array_buffer.bind();
    quintptr offset = 0;
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
    this->m_index_buffer.bind();

    this->m_vao.release();
}

void
cube::render()
{
    this->m_vao.bind();
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
    this->m_vao.release();
}
