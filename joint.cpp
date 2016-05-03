#include "joint.hpp"

joint::joint() :
    m_name("uninitialised"),
    m_parent(0),
    m_childrens(),
    m_position(0, 0, 0),
    m_box_min(-0.1f, -0.1f, -0.1f),
    m_box_max(0.1f, 0.1f, 0.1f)
{

}

joint::~joint()
{

}


