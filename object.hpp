#ifndef OBJECT_H
#define OBJECT_H

#include "entity.hpp"
#include <QOpenGLShaderProgram>

class   skeleton;
class   mesh;

class object : public entity
{
public:
    object(QOpenGLShaderProgram *prg1, QOpenGLShaderProgram *prg2, node *parent_node);
    virtual ~object(void);

public:
    virtual void    update(void);
    virtual void    render(const QMatrix4x4 &projection, const QMatrix4x4 &view, const QMatrix4x4 &model);

public:

    void    set_skeleton(skeleton *skel) {
        this->m_skeleton = skel;
    }

    skeleton    *get_skeleton(void) {
        return this->m_skeleton;
    }

    void    set_mesh(mesh *m) {
        this->m_mesh = m;
    }

    mesh   *get_mesh(void) {
       return this->m_mesh;
    }

private:

    // should be a mesh.

    QOpenGLShaderProgram    *m_skel_shader_program;
    skeleton    *m_skeleton;

    QOpenGLShaderProgram    *m_skin_shader_program;
    mesh        *m_mesh;

};

#endif // OBJECT_H
