#ifndef PARTICLE_H
#define PARTICLE_H

#include <qvector3d.h>
class Cloth;

class Particle
{
public:
    Particle();

public:

    void    update(float elapsed);
    void    add_force(const QVector3D &f)
    {
        this->m_force += f;
    }

public:

    void    compute_normal(int width, int height, const QVector<Particle> &);

public:
    Cloth       *m_cloth;
    bool        m_fixed;
    QVector3D   m_position;
    QVector3D   m_normal;
    unsigned int m_index;

    float       m_masse;
    QVector3D   m_force;
    QVector3D   m_velocity;
    float       m_t;
};

#endif // PARTICLE_H
