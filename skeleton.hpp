#ifndef SKELETON_H
#define SKELETON_H


#include <QOpenGLShaderProgram>
#include "joint.hpp"
#include "balljoint.hpp"

class skeleton
{
public:
    skeleton(void);
    ~skeleton(void);

public:
    ///
    /// \brief Setter for the root joint skeleton.
    /// \param t_joint The new root joint.
    ///
    void    root_joint(joint *t_joint) {
        this->m_root = t_joint;
    }

    ///
    /// \brief root_joint Get the root joint of the skeleton.
    /// \return the root joint of the skeleton.
    ///
    joint   *root_joint(void) const {
        return this->m_root;
    }

    joint   *search_joint(const QString &name) {
        return this->m_root->search(name);
    }

    QVector<QMatrix4x4> world_matrices(void) const {
        QVector<QMatrix4x4>     res;
        QMatrix4x4 identity;
        identity.setToIdentity();
        this->m_root->world_matrices(res, identity);
        return res;
    }

    QVector<joint *>    joints(void)
    {
        QVector<joint *> res;

        this->m_root->joints(res);
        return res;
    }


public:
    void    render(const QMatrix4x4 &projection, const QMatrix4x4 &view, const QMatrix4x4 &model, QOpenGLShaderProgram *program);

private:
    ///
    /// \brief The root joint of the skeleton.
    ///
    joint   *m_root;
};

#endif // SKELETON_H
