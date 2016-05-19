#ifndef SPRINGDAMPER_H
#define SPRINGDAMPER_H

class Particle;

class SpringDamper
{
public:
    SpringDamper();

    void    compute_force();

public:
    Particle    *m_p0;
    Particle    *m_p1;

    float m_spring_constant;
    float m_damping_factor;
    float m_rest_length;
};

#endif // SPRINGDAMPER_H
