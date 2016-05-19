#include "node.hpp"
#include "entity.hpp"
#include "animationplayer.hpp"
#include "object.hpp"

node::node(node *t_parent) :
    m_animation_player(0),
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
node::update(float elapsed)
{

    object *obj = dynamic_cast<object *>(this->m_entity);

    if (this->m_animation_player != 0 && obj != 0)
        this->m_animation_player->animate(this, obj->get_skeleton());
    if (this->m_parent != 0)
        this->m_transform.compute_world_matrix(this->m_parent->m_transform);
    if (this->m_entity != 0)
        this->m_entity->update(elapsed);
    if (this->m_parent != 0)
        this->m_transform.compute_world_matrix(this->m_parent->m_transform);
    foreach (node *child, this->m_childrens) {
        child->update(elapsed);
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
