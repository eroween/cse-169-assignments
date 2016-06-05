#ifndef FLUIDSYSTEM_H
#define FLUIDSYSTEM_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QVector>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

#include "entity.hpp"

class FluidSystem : public entity, protected QOpenGLExtraFunctions
{
public:
    FluidSystem(node *parent_node, std::size_t max_particle_number, QOpenGLShaderProgram *program);
    ~FluidSystem(void);

public:

    virtual void    update(float elapsed);
    virtual void    render(const QMatrix4x4 &projection, const QMatrix4x4 &view, const QMatrix4x4 &model);

private:
    float               m_rest_density;
    float               m_stiffness;

    float               m_particle_masse;
    float               m_particle_radius;
    float               m_velocity_max;

    std::size_t         m_particle_number;
    std::size_t         m_max_particle_number;
    QVector<float>  m_particle_positions;
    QVector<float>  m_particle_velocities;
    QVector<float>  m_particle_forces;
    QVector<float>  m_particle_pressure;
    QVector<float> m_particle_densities;

    QOpenGLShaderProgram *m_program;
    QOpenGLVertexArrayObject    m_vao;
    QOpenGLBuffer               m_position_buffer;
    QOpenGLBuffer               m_velocity_buffer;
    QOpenGLBuffer               m_array_buffer;
    QOpenGLBuffer               m_index_buffer;

    QVector3D                   m_box_max;
    QVector3D                   m_box_min;

    float                       m_width;
    float                       m_height;
    float                       m_depth;

    struct container
    {
        QVector<std::size_t>    m_particles;
    };

    QVector<QVector<std::size_t>>   m_particle_neighboors;
    QVector<QVector<QVector<container>>> m_grid;
};

#endif // FLUIDSYSTEM_H
