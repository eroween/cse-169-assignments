#ifndef ENTITY_H
#define ENTITY_H

#include <QMatrix4x4>

class   node;

class entity
{
public:
    entity(node *parent_node);
    virtual ~entity(void);

public:
    virtual void    update(void) = 0;
    virtual void    render(const QMatrix4x4 &projection, const QMatrix4x4 &view, const QMatrix4x4 &model) = 0;

protected:

    node    *m_node;
};

#endif // ENTITY_H
