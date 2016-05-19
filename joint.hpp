

#ifndef JOINT_H
#define JOINT_H

#include <QVector2D>
#include <QVector3D>
#include <QList>
#include <QOpenGLShaderProgram>

class joint
{
public:
    joint(void);
    virtual ~joint(void);

public:

    QString   &name(void) {
        return this->m_name;
    }

    joint   *search(const QString &name) {
        if (this->m_name == name)
            return this;
        foreach (joint *child, this->m_childrens)
        {
            joint *res = child->search(name);
            if (res != 0) return res;
        }
        return 0;
    }

    void    joints(QVector<joint *> &res)
    {
        res.push_back(this);
        foreach (joint *child, this->m_childrens)
        {
            child->joints(res);
        }
    }

public:

    void    add_child(joint *child) {
        child->m_parent = this;
        this->m_childrens.append(child);
    }

    virtual void    world_matrices(QVector<QMatrix4x4> &matrices, const QMatrix4x4 &parent) = 0;


public:

    void    offset(const QVector3D &t_offset) {
        this->m_position = t_offset;
    }

    void    box_min(const QVector3D &t_box_min) {
        this->m_box_min = t_box_min;
    }

    void    box_max(const QVector3D &t_box_max) {
        this->m_box_max = t_box_max;
    }

public:

    const QList<joint *>  &childrens(void) const {
        return this->m_childrens;
    }

public:

    virtual void    render(const QMatrix4x4 &projection, const QMatrix4x4 &view, const QMatrix4x4 &model, QOpenGLShaderProgram *program) = 0;

public:
    QString m_name;
    joint *m_parent;
    QList<joint *> m_childrens;

    QVector3D   m_position;
    QVector3D   m_box_min;
    QVector3D   m_box_max;
};

#endif // JOINT_H
