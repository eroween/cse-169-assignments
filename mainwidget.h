
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "geometryengine.h"
#include "mainwindow.h"

#include <QMatrix4x4>
#include <QOpenGLWidget>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QTreeWidgetItem>

class node;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget(void);

protected:
    void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

public:

    void    set_mainwindow(MainWindow *mw) {
        this->m_mw = mw;
    }



private:
    MainWindow *m_mw;

public:

    ///
    /// \brief load a skel file
    /// \param filename the filename of the file that will be loaded.
    ///
    void    load(const QString &skel_file, const QString &skin_file, const QString &anim_file);

public:
    void    load_async(const QString &skel_file, const QString &skin_file, const QString &anim_file) {
        skin_name = skin_file;
        anim_name = anim_file;
        skel_name = skel_file;
        m_load = true;
    }

    void update_tree(void);
    void fill_tree(QTreeWidgetItem *wi_parent, node *parent);

    node *root_node(void) {
        return this->m_node;
    }

private:
    ///
    /// \brief The parent node of the graph.
    ///
    node    *m_node;

    ///
    /// \brief The projection used to display the content (perspective)
    ///
    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;

    ///
    /// \brief The timer in order to update the scene.
    ///
    QBasicTimer m_timer;

    /// Totally dumb, but I don't have a lot of time to do something great.
    QOpenGLShaderProgram    program;
    QOpenGLShaderProgram    program2;
    QOpenGLShaderProgram    program3;


    bool m_load;
    QString     skin_name;
    QString     anim_name;
    QString     skel_name;
};



#endif // MAINWIDGET_H
