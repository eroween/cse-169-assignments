#ifndef BALLJOINT_H
#define BALLJOINT_H

#include <QVector2D>
#include <QVector3D>

#include "joint.hpp"

class balljoint : public joint
{
public:
    balljoint(void);
    ~balljoint(void);

public:

    void    limit_rotation_x(const QVector2D &lrx) {
        this->m_limit_rotation_x = lrx;
    }

    void    limit_rotation_y(const QVector2D &lry) {
        this->m_limit_rotation_y = lry;
    }

    void    limit_rotation_z(const QVector2D &lrz) {
        this->m_limit_rotation_z = lrz;
    }

    void    pose(const QVector3D &pose) {
        this->m_rotation = pose;
    }

    void    render(const QMatrix4x4 &projection, const QMatrix4x4 &view, const QMatrix4x4 &model, QOpenGLShaderProgram *program);

public:

    QMatrix4x4    matrix(void);

    void    world_matrices(QVector<QMatrix4x4> &matrices, const QMatrix4x4 &parent) {
        QMatrix4x4 local = parent * this->matrix();
        matrices.push_back(local);
        foreach (joint *child, this->m_childrens)
        {
            child->world_matrices(matrices, local);
        }
    }

public:

    QVector2D   m_limit_rotation_x;
    QVector2D   m_limit_rotation_y;
    QVector2D   m_limit_rotation_z;

    QVector3D   m_rotation;
};

#endif // BALLJOINT_H
