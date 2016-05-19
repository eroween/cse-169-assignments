#ifndef CLOTH_H
#define CLOTH_H

#include "environment.hpp"
#include "particle.hpp"
#include "springdamper.hpp"
#include "triangle.hpp"
#include "entity.hpp"
#include "node.hpp"

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QVector>
#include <QOpenGLShaderProgram>

class Cloth : public entity, protected QOpenGLFunctions
{
public:
    Cloth(QOpenGLShaderProgram *prog, node *parent_node);
    ~Cloth();

public:

    void    init(int height, int width, float distance);

    virtual void    update(float elapsed);
    virtual void    render(const QMatrix4x4 &projection, const QMatrix4x4 &view, const QMatrix4x4 &model);

public:
    int                     m_width;
    int                     m_height;
    QVector<Particle>       m_particles;
    QVector<SpringDamper>   m_spring_dampers;
    QVector<Triangle>       m_triangles;
    QOpenGLBuffer           m_buffer;
    QOpenGLBuffer           m_buffer_index;
    QOpenGLVertexArrayObject   m_vao;
    QOpenGLShaderProgram    *m_prog;

    bool                    m_detach;
};
#endif // CLOTH_H
