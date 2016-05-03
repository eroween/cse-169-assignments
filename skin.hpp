#ifndef SKIN_H
#define SKIN_H

#include <QMatrix4x4>
#include    "mesh.hpp"
#include <QVector>
#include <QOpenGLShaderProgram>

class skin : public mesh
{
public:
    skin();

public:
    virtual void precompute(QOpenGLShaderProgram *prog);
    virtual void    render();

    void    skin_weights(const QVector<float> &skin_weight) {
        this->m_skin_weight = skin_weight;
    }

    void    skin_indices(const QVector<unsigned int> &skin_indices) {
        this->m_skin_indices = skin_indices;
    }

    void    binding_matrices(const QVector<QMatrix4x4> &binding_matrices) {
        this->m_matrices_bindings = binding_matrices;
    }

public:

    const QVector<QMatrix4x4>   &binding_matrices(void) const {
        return this->m_matrices_bindings;
    }

private:
    QVector<float>  m_skin_weight;
    QVector<unsigned int>  m_skin_indices;
    QVector<QMatrix4x4>     m_matrices_bindings;
};

#endif // SKIN_H
