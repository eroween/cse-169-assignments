#include "springdamper.hpp"
#include "particle.hpp"

SpringDamper::SpringDamper() :
    m_spring_constant(1.0f),
    m_damping_factor(0.05f),
    m_rest_length(1.0f)
{

}

#include "qdebug.h"
void
SpringDamper::compute_force()
{
    QVector3D   e = (m_p1->m_position - m_p0->m_position);
    if (e.length() == 0) {
        e = m_p1->m_position + QVector3D(0.001f, 0.001f, 0.001f) - m_p0->m_position;
    }
    float   x = (m_p1->m_position - m_p0->m_position).length() - m_rest_length;
    float   v = QVector3D::dotProduct(m_p1->m_velocity, e) - QVector3D::dotProduct(m_p0->m_velocity, e);

    if (std::isnan(x) || std::isnan(v) || std::isnan(e.x()) || std::isnan(e.y()) || std::isnan(e.z()))
        return;

    m_p0->add_force((-m_spring_constant * x - m_damping_factor * v) * -e);
    m_p1->add_force((-m_spring_constant * x - m_damping_factor * v) * e);
}
