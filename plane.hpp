#ifndef PLANE_H
#define PLANE_H

#include "mesh.hpp"

class Plane : public mesh
{
public:
    Plane(const QVector3D &box_min, const QVector3D &box_max, QOpenGLShaderProgram *program);

    void precompute(QOpenGLShaderProgram *) {

    }

public:
    void    render();
};

#endif // PLANE_H
