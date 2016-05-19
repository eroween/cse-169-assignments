#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "QVector3D"
class Particle;

class Triangle
{
public:
    Triangle();

public:
    void    compute_normal(void);
    void    compute_aero(const QVector3D &w);

public:
    Particle    *m_p0;
    Particle    *m_p1;
    Particle    *m_p2;
};

#endif // TRIANGLE_H
