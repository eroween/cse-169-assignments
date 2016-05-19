#include "triangle.hpp"
#include "particle.hpp"

Triangle::Triangle()
{

}

void
Triangle::compute_normal(void)
{
    QVector3D   AB = (this->m_p1->m_position - this->m_p0->m_position).normalized();
    QVector3D   AC = (this->m_p2->m_position - this->m_p0->m_position).normalized();
    QVector3D   n = QVector3D::crossProduct(AB, AC);
    this->m_p0->m_normal += n;
    this->m_p1->m_normal += n;
    this->m_p2->m_normal += n;
}

#include <qdebug.h>

void
Triangle::compute_aero(const QVector3D &w)
{
    float       c = 0.10f;
    float       p = 1.225f; // air

    QVector3D   tv = (m_p0->m_velocity + m_p1->m_velocity + m_p2->m_velocity) / 3.0f; // triangle velocity
    tv -= w; // relative velocity
    if (tv.length() == 0) return;
    QVector3D   tn = QVector3D::crossProduct(m_p1->m_position - m_p0->m_position, m_p2->m_position - m_p0->m_position);
    float l = tn.length();
    if (l == 0) return;
    tn /= l;
    float   a0 = 0.5f * l;
    float   ta = a0 * QVector3D::dotProduct(tv, tn) / tv.length();
    QVector3D   faero = - 0.5f * p * tv.lengthSquared() * c * ta * tn;

    if (std::isnan(faero.x()) || std::isnan(faero.y()) || std::isnan(faero.z()))
        return;

    m_p0->add_force(faero / 3.0f);
    m_p1->add_force(faero / 3.0f);
    m_p2->add_force(faero / 3.0f);
}
