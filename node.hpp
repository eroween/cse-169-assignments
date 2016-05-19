#ifndef NODE_H
#define NODE_H

#include <QOpenGLFunctions>


#include    "transform.hpp"
#include    "entity.hpp"

class   animation;
class   AnimationPlayer;

class node : protected QOpenGLFunctions
{
public:
    ///
    /// \brief Default constructor.
    /// \param parent The parent node, 0 by default.
    ///
    node(node *parent = 0);

    ///
    /// \brief Destructor.
    ///
    ~node(void);

public:
    ///
    /// \brief name Change the name of the node
    /// \param name The new name for the node.
    ///
    void    name(const QString &name)
    {
        this->m_name = name;
    }

    ///
    /// \brief entity Add an entity to the node
    /// \param entity The new entity used in this node.
    ///
    void    set_entity(entity *entity)
    {
        if (this->m_entity != 0)
            delete this->m_entity;
        this->m_entity = entity;
    }

    void    animation_player(AnimationPlayer *ap)
    {
        this->m_animation_player = ap;
    }

    AnimationPlayer *m_animation_player;

public:
    ///
    /// \brief name Getter for the node name.
    /// \return The name of the node
    ///
    const QString   &name(void) const
    {
        return this->m_name;
    }

    transform   &get_transform(void) {
        return this->m_transform;
    }

    entity *get_entity(void) {
        return this->m_entity;
    }

public:
    ///
    /// \brief update the node and the node childrens.
    ///
    void    update(float elapsed);

    ///
    /// \brief render the node and the node childrens.
    /// \param projection the projection used to draw the node.
    ///
    void    render(const QMatrix4x4 &projection, const QMatrix4x4 &view);

public:
    ///
    /// \brief add_child add a node in the children list of the node.
    /// \param child the new child of the node.
    ///
    void    add_child(node *child)
    {
        child->m_parent = this;
        this->m_childrens.append(child);
    }

    node    *search(const QString &name)
    {
        if (this->m_name == name)
            return this;
        foreach (node *child, this->m_childrens) {
            node *res = child->search(name);
            if (res != 0) return res;
        }
        return 0;
    }

    const QList<node*>  &childrens(void) const {
        return this->m_childrens;
    }

public:
    ///
    /// \brief m_name The name of the node.
    ///
    QString m_name;

    ///
    /// \brief m_parent The parent node.
    ///
    node    *m_parent;

    ///
    /// \brief m_childrens The childrens of the node.
    ///
    QList<node *>   m_childrens;

    ///
    /// \brief m_entity The entity applied to this node.
    ///
    entity  *m_entity;

    ///
    /// \brief m_transform The transform applied to the node.
    ///
    transform   m_transform;
};

#endif // NODE_H
