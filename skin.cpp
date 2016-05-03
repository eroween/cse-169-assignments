#include "skin.hpp"
#include <QOpenGLShaderProgram>

skin::skin() :
    mesh()
{

}

void
skin::precompute(QOpenGLShaderProgram *program)
{
    QVector<float>  vertices;
    int num = this->m_positions.size() / 3;
    vertices.reserve(num * 16 * sizeof(float));

//    qDebug() << num;
    for (int i = 0; i < num ; ++i) {
        vertices.push_back(this->m_positions[i * 3 + 0]);
        vertices.push_back(this->m_positions[i * 3 + 1]);
        vertices.push_back(this->m_positions[i * 3 + 2]);
        vertices.push_back(1.0f);

        vertices.push_back(this->m_normals[i * 3 + 0]);
        vertices.push_back(this->m_normals[i * 3 + 1]);
        vertices.push_back(this->m_normals[i * 3 + 2]);
        vertices.push_back(0.0f);

        vertices.push_back(this->m_skin_weight[i * 4 + 0]);
        vertices.push_back(this->m_skin_weight[i * 4 + 1]);
        vertices.push_back(this->m_skin_weight[i * 4 + 2]);
        vertices.push_back(this->m_skin_weight[i * 4 + 3]);

        vertices.push_back(this->m_skin_indices[i * 4 + 0]);
        vertices.push_back(this->m_skin_indices[i * 4 + 1]);
        vertices.push_back(this->m_skin_indices[i * 4 + 2]);
        vertices.push_back(this->m_skin_indices[i * 4 + 3]);
    }

//    qDebug() << 694 * 16 * sizeof(float) << " " << vertices.size() * sizeof(float);
//    qDebug() << 1236 * 3 * sizeof(int) << " " << this->m_indices.size() * sizeof(int);

    this->m_array_buffer.bind();
    this->m_array_buffer.allocate(vertices.data(), vertices.size() * sizeof(float));
    this->m_index_buffer.bind();
    this->m_index_buffer.allocate(this->m_indices.data(), this->m_indices.size() * sizeof(unsigned int));

    this->m_vao.bind();
    this->m_array_buffer.bind();
    quintptr offset = 0;
    int v_loc = program->attributeLocation("position");
    program->enableAttributeArray(v_loc);
    program->setAttributeBuffer(v_loc, GL_FLOAT, offset, 4, 16 * sizeof(float));

    offset += 4 * sizeof(float);
    v_loc = program->attributeLocation("normal");
    program->enableAttributeArray(v_loc);
    program->setAttributeBuffer(v_loc, GL_FLOAT, offset, 4, 16 * sizeof(float));

    offset += 4 * sizeof(float);
    v_loc = program->attributeLocation("skin_weights");
    program->enableAttributeArray(v_loc);
    program->setAttributeBuffer(v_loc, GL_FLOAT, offset, 4, 16 * sizeof(float));

    offset += 4 * sizeof(float);
    v_loc = program->attributeLocation("skin_indices");
    program->enableAttributeArray(v_loc);
    program->setAttributeBuffer(v_loc, GL_FLOAT, offset, 4, 16 * sizeof(float));

    this->m_index_buffer.bind();
    this->m_vao.release();
}

void
skin::render()
{
    this->m_vao.bind();
    glDrawElements(GL_TRIANGLES, this->m_indices.size(), GL_UNSIGNED_INT, 0);
    this->m_vao.release();
}
