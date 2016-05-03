#include "transform.hpp"

transform::transform()
{
    this->m_world_matrix.setToIdentity();
    this->m_local_matrix.setToIdentity();
}

transform::~transform()
{
    // nothing to do atm.
}

