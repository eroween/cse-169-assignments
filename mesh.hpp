#ifndef MESH_H
#define MESH_H

#include <QVector>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

class mesh : protected QOpenGLFunctions
{
public:
    mesh();
    virtual ~mesh(void);

public:
    virtual void    render() = 0;

    virtual void precompute(QOpenGLShaderProgram *prog) = 0;

public:

    void    indices(const QVector<unsigned int> &indices) {
        this->m_indices = indices;
    }

    void    positions(const QVector<float> &positions) {
        this->m_positions = positions;
    }

    void    normals(const QVector<float> &normals) {
        this->m_normals = normals;
    }

protected:

    QVector<unsigned int>   m_indices;


    QVector<float>          m_positions;
    QVector<float>          m_normals;


    QOpenGLBuffer   m_array_buffer;
    QOpenGLBuffer   m_index_buffer;
    QOpenGLVertexArrayObject    m_vao;

};

#endif // MESH_H
