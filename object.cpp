#include "object.hpp"
#include "skeleton.hpp"
#include "node.hpp"
#include "mesh.hpp"
#include "skin.hpp"

object::object(QOpenGLShaderProgram *prg1, QOpenGLShaderProgram *prg2, node *parent_node) :
    entity(parent_node),
    m_skel_shader_program(prg1),
    m_skeleton(0),
    m_skin_shader_program(prg2),
    m_mesh(0)
{
}

object::~object()
{
}


void
object::update(float elapsed)
{
}

void
object::render(const QMatrix4x4 &projection, const QMatrix4x4 &view, const QMatrix4x4 &model)
{
    if (this->m_skeleton != 0)
        this->m_skeleton->render(projection, view, model, this->m_skel_shader_program);
    if (this->m_mesh != 0) {


        this->m_skin_shader_program->bind();
        this->m_skin_shader_program->setUniformValue("mvp", projection * view * model);
        this->m_skin_shader_program->setUniformValue("v", view);
        this->m_skin_shader_program->setUniformValue("m", model);

        this->m_skin_shader_program->setUniformValue("lights[0].position", QVector3D(3.0, 0.0, -3.0));
        this->m_skin_shader_program->setUniformValue("lights[1].position", QVector3D(-3.0, 0.0, -3.0));
        this->m_skin_shader_program->setUniformValue("lights[0].ambient", QVector3D(0.1, 0.0, 0.0));
        this->m_skin_shader_program->setUniformValue("lights[1].ambient", QVector3D(0.0, 0.1, 0.0));
        this->m_skin_shader_program->setUniformValue("lights[0].diffuse", QVector3D(0.5, 0.0, 0.0));
        this->m_skin_shader_program->setUniformValue("lights[1].diffuse", QVector3D(0.0, 0.5, 0.0));
        this->m_skin_shader_program->setUniformValue("lights[0].specular", QVector3D(1.0, 1.0, 1.0));
        this->m_skin_shader_program->setUniformValue("lights[1].specular", QVector3D(1.0, 1.0, 1.0));

        if (this->m_skeleton != 0) {
            skin *sk = dynamic_cast<skin *>(this->m_mesh);
            if (sk == 0) qDebug() << "something bad";
            this->m_skin_shader_program->setUniformValueArray("binding_matrices", sk->binding_matrices().data(), sk->binding_matrices().size());
            const QVector<QMatrix4x4> &wm = this->m_skeleton->world_matrices();
            this->m_skin_shader_program->setUniformValueArray("world_matrices", wm.data(), wm.size());
        }
        this->m_mesh->render();
    }
}
