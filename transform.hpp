#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QVector3D>
#include <QMatrix4x4>

class transform
{
public:
    ///
    /// \brief transform constructor.
    ///
    transform(void);

    ///
    /// \brief Destructor.
    ///
    ~transform(void);

public:
    ///
    /// \brief local_matrix Getter for the local matrix.
    /// \return the local matrix of the tranform.
    ///
    const QMatrix4x4    &local_matrix(void) const
    {
        return this->m_local_matrix;
    }

    ///
    /// \brief world_matrix Getter for the world matrix.
    /// \return the world matrix of the transform.
    ///
    const QMatrix4x4    &world_matrix(void) const
    {
        return this->m_world_matrix;
    }

public:

    const QVector3D     position(void) const
    {
        return QVector3D(m_local_matrix.column(3));
    }

    const QVector3D     scale(void) const
    {
        QVector3D x = QVector3D(m_local_matrix.row(0));
        QVector3D y = QVector3D(m_local_matrix.row(1));
        QVector3D z = QVector3D(m_local_matrix.row(2));
        return QVector3D(x.length(), y.length(), z.length());
    }


    void    position(const QVector3D &vector)
    {
        this->m_local_matrix.setColumn(3, QVector4D(vector, 1.0f));
    }

    void    translate(const QVector3D &vector)
    {
        this->m_local_matrix.translate(vector);
    }

    void    rotate(float angle, const QVector3D &vector)
    {
        this->m_local_matrix.rotate(angle, vector);
    }

    ///
    /// \brief scale the transform by the vector value.
    /// \param vector the value in x,y, z to scale the transform.
    ///
    void    scale(const QVector3D &vector)
    {
        this->m_local_matrix.scale(vector);
    }

public:
    ///
    /// \brief compute_world_matrix This method is used to compute the world matrix from the parent transform.
    /// \param parent
    ///
    void    compute_world_matrix(const transform &parent)
    {
        this->m_world_matrix = parent.world_matrix() * this->m_local_matrix;
    }

public:
    ///
    /// \brief The local matrix of the transform.
    ///
    QMatrix4x4   m_local_matrix;

    ///
    /// \brief The world matrix of the transform.
    ///
    QMatrix4x4   m_world_matrix;
};

#endif // TRANSFORM_H
