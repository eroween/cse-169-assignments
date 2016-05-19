#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <QVector2D>
#include <channel.hpp>

class Animation
{
public:
    Animation();

public:
    std::vector<float>  evaluate(float t);

public:
    QVector2D               m_range;
    std::vector<Channel *>    m_channels;
};

#endif // ANIMATION_H
