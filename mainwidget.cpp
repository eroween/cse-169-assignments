/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QMouseEvent>
#include <math.h>

#include "animation.hpp"
#include "animationloader.hpp"
#include "animationplayer.hpp"
#include "mainwidget.h"
#include "node.hpp"
#include "entity.hpp"
#include "object.hpp"
#include "skeleton_loader.hpp"
#include "skeleton.hpp"
#include "skin_loader.hpp"
#include "balljoint.hpp"
#include "fluidsystem.hpp"
#include <iostream>

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    m_node(new node()),
    m_projection(),
    m_timer(),
    m_load(false)
{
    this->m_node->name("root_node");
}

MainWidget::~MainWidget()
{
}

#include <QTime>

void MainWidget::timerEvent(QTimerEvent *) {
    QTime   time;
    time.start();
    if (this->m_node != 0)
        this->m_node->update(0.012f);
    this->update();
//    std::cout << "update time : " << time.elapsed() << std::endl;
}

#include "cloth.hpp"
#include "plane.hpp"

void MainWidget::initializeGL() {
    initializeOpenGLFunctions();
    program.create();
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl")) close();
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl")) close();
    if (!program.link()) close();
    if (!program.bind()) close();
    program2.create();
    if (!program2.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/anim_vertex.glsl")) close();
    if (!program2.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl")) close();
    if (!program2.link()) close();
    if (!program2.bind()) close();

    program3.create();
    if (!program3.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/instanced.vert")) close();
    if (!program3.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl")) close();
    if (!program3.link()) close();
    if (!program3.bind()) close();


    glClearColor(0.5, 0.5, 0.5, 1);
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
    this->m_timer.start(12, this);
    qDebug() << "gl initialised";

    node *child = new node();
//    child->name("cloth");
//    child->get_transform().translate(QVector3D(0, 2, 0));
//    child->get_transform().rotate(45, QVector3D(0, 1, 0));
//    Cloth *c = new Cloth(&program, child);
//    c->init(10, 10, 0.2);
//    child->set_entity(c);
//    this->m_node->add_child(child);

//    child = new node();
    child->name("ground");
    object *obj = new object(&this->program, &this->program, child);
    obj->set_mesh(new Plane(QVector3D(-10, -2, -10), QVector3D(10, -2, 10), &program));
    child->set_entity(obj);
    this->m_node->add_child(child);

    child = new node();
    child->name("fluidsystem");
//    child->get_transform().translate(QVector3D(0, 3, 0));
    FluidSystem *fs = new FluidSystem(child, 1000, &this->program3);
    child->set_entity(fs);
    this->m_node->add_child(child);

    this->update_tree();
}

void MainWidget::resizeGL(int w, int h) {
    qDebug() << "initialised";
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.01, zFar = 1000.0, fov = 45.0;
    this->m_projection.setToIdentity();
    this->m_projection.perspective(fov, aspect, zNear, zFar);
    this->m_view.setToIdentity();
    this->m_view.lookAt(QVector3D(0, 0, 2), QVector3D(0,0,0), QVector3D(0,1,0));
}

void MainWidget::paintGL() {
    QTime   time;
    time.start();


    if (m_load) {
        this->load(skel_name, skin_name, anim_name);
        m_load = false;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (this->m_node != 0)
        this->m_node->render(this->m_projection, this->m_view);
//    std::cout << "render time : " << time.elapsed() << std::endl;
}

void MainWidget::load(const QString &skel_file, const QString &skin_file, const QString &anim_file) {
    skeleton_loader skel_loader;
    skin_loader s_loader;
    AnimationLoader     anim_loader;

    node *child = new node();
    child->name(skin_file);
    object *obj = new object(&this->program, &this->program2, child);
    obj->set_skeleton(skel_loader.load(skel_file));

    mesh *m = s_loader.load(skin_file);
    m->precompute(&this->program2);
    obj->set_mesh(m);
    child->set_entity(obj);

    child->animation_player(new AnimationPlayer(anim_loader.load(anim_file)));

    this->m_node->add_child(child);

    this->update_tree();
}

#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void
MainWidget::update_tree(void) {
    this->m_mw->ui->treeWidget->clear();
    this->m_mw->ui->treeWidget->setColumnCount(1);
    this->fill_tree(0, this->m_node);
    this->m_mw->ui->treeWidget->expandAll();
}

void
MainWidget::fill_tree(QTreeWidgetItem *wi_parent, node *parent) {
    QTreeWidgetItem     *item;
    if (wi_parent == 0)
        item = new QTreeWidgetItem(this->m_mw->ui->treeWidget);
    else
        item = new QTreeWidgetItem(wi_parent);
    item->setText(0, parent->name());
    foreach (node *child, parent->childrens()) {
        fill_tree(item, child);
    }
}
