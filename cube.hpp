#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLShaderProgram>

#include "mesh.hpp"

//

class cube : public mesh
{
public:
    cube(const QVector3D &box_min, const QVector3D &box_max, QOpenGLShaderProgram *program);

    void precompute(QOpenGLShaderProgram *) {

    }

public:

    void    render();
};

#endif // CUBE_H
