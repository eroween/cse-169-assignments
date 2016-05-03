#include "skeleton.hpp"

skeleton::skeleton()
{

}

void
skeleton::render(const QMatrix4x4 &projection, const QMatrix4x4 &view, const QMatrix4x4 &model, QOpenGLShaderProgram *program)
{
    if (this->m_root != 0)
        this->m_root->render(projection, view, model, program);
}
