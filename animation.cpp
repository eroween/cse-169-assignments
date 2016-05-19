#include "animation.hpp"
#include <qdebug.h>

Animation::Animation()
{

}


std::vector<float>
Animation::evaluate(float t)
{
    std::vector<float>  poses;
    poses.reserve(m_channels.size());
    for (int i = 0 ; i < m_channels.size() ; ++i)
    {
        Channel *c = m_channels[i];
        poses.push_back(c->evaluate(t));
    }
    return poses;
}
