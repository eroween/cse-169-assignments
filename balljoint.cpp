#include <QtMath>

#include "balljoint.hpp"
#include "mesh.hpp"
#include "cube.hpp"

balljoint::~balljoint()
{

}

balljoint::balljoint() :
    m_limit_rotation_x(-100000, 100000),
    m_limit_rotation_y(-100000, 100000),
    m_limit_rotation_z(-100000, 100000),
    m_rotation(0, 0, 0)
{

}

QMatrix4x4
balljoint::matrix(void)
{
    QMatrix4x4  res;
    res.setToIdentity();
    res.translate(this->m_position);
    res.rotate(qRadiansToDegrees(qBound(this->m_limit_rotation_z.x(), this->m_rotation.z(), this->m_limit_rotation_z.y())), QVector3D(0, 0, 1));
    res.rotate(qRadiansToDegrees(qBound(this->m_limit_rotation_y.x(), this->m_rotation.y(), this->m_limit_rotation_y.y())), QVector3D(0, 1, 0));
    res.rotate(qRadiansToDegrees(qBound(this->m_limit_rotation_x.x(), this->m_rotation.x(), this->m_limit_rotation_x.y())), QVector3D(1, 0, 0));
    return res;
}

void
balljoint::render(const QMatrix4x4 &projection, const QMatrix4x4 &view, const QMatrix4x4 &parent_model, QOpenGLShaderProgram *program)
{
    QMatrix4x4  model = parent_model * this->matrix();
    foreach (joint *child, this->m_childrens)
    {
        child->render(projection, view, model, program);
    }
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    mesh    *c = new cube(this->m_box_min, this->m_box_max, program);
    program->bind();
    program->setUniformValue("mvp", projection * view * model);
    c->render();
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
    delete c;
}
