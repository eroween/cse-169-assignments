#include "particle.hpp"
#include "cloth.hpp"

Particle::Particle() :
    m_t(0),
    m_velocity(0.0f, 0.0f, 0.0f)
{

}

void
Particle::update(float elapsed)
{
    if (m_fixed == false || m_cloth->m_detach)
    {
        QVector3D   a = (1.0f / m_masse) * m_force;

        m_velocity += a * elapsed;
        m_position += m_velocity * elapsed;
    }
    m_force = QVector3D(0.0f, 0.0f, 0.0f);
}

void
Particle::compute_normal(int width, int height, const QVector<Particle> &)
{
    this->m_normal = QVector3D(0.0f, 0.0f, -1.0f);
}
