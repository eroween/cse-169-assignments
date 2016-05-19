#ifndef CHANNEL_H
#define CHANNEL_H

#include <vector>

class Channel
{
public:
    Channel();


public:
    enum    ExtrapolationType
    {
        CONSTANT_EXTRAPOLATION,
        LINEAR_EXTRAPOLATION,
        CYCLE_EXTRAPOLATION,
        CYCLE_OFFSET_EXTRAPOLATION,
        BOUNCE_EXTRAPOLATION
    };

    void    compute();
    float   evaluate(float t);

public:

    class KeyFrame
    {
    public:
        KeyFrame() {

        }

        ~KeyFrame() {

        }

    public:
        enum TangentType
        {
            FLAT,
            LINEAR,
            SMOOTH,
            VALUE
        };

    public:
        float           m_time;
        float           m_value;
        TangentType     m_tangent_in;
        TangentType     m_tangent_out;
        float           m_tangent_in_value;
        float           m_tangent_out_value;
        float           m_a;
        float           m_b;
        float           m_c;
        float           m_d;
    };

public:

public:
    ExtrapolationType       m_extrapolation_in;
    ExtrapolationType       m_extrapolation_out;
    std::vector<KeyFrame>    m_keyframes;
};

#endif // CHANNEL_H
