#include "node.hpp"
#include "entity.hpp"

node::node(node *t_parent) :
    m_name("uninitialised"),
    m_parent(t_parent),
    m_childrens(),
    m_entity(0),
    m_transform()
{
}

node::~node(void)
{

}

void
node::update()
{
    if (this->m_parent != 0)
        this->m_transform.compute_world_matrix(this->m_parent->m_transform);
    if (this->m_entity != 0)
        this->m_entity->update();
    foreach (node *child, this->m_childrens) {
        child->update();
    }
}

void
node::render(const QMatrix4x4 &projection, const QMatrix4x4 &view)
{
    if (this->m_entity != 0)
        this->m_entity->render(projection, view, this->m_transform.world_matrix());
    foreach (node *child, this->m_childrens) {
        child->render(projection, view);
    }
}
