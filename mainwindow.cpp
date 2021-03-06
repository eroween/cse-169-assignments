#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwidget.h"
#include "balljoint.hpp"
#include "node.hpp"
#include "entity.hpp"
#include "object.hpp"
#include "skeleton.hpp"
#include <QtMath>
#include "environment.hpp"

MainWindow::MainWindow(int argc, char *argv[], QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ac(argc),
    av(argv)
{
    ui->setupUi(this);

    ui->openGLWidget->set_mainwindow(this);

    connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(change_select(QTreeWidgetItem*,QTreeWidgetItem*)));
    connect(ui->treeWidget_2, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(skel_change_select(QTreeWidgetItem*,QTreeWidgetItem*)));

    connect(ui->limitxmin, SIGNAL(valueChanged(double)), this, SLOT(on_limitxmin_changed(double)));
    connect(ui->limitymin, SIGNAL(valueChanged(double)), this, SLOT(on_limitymin_changed(double)));
    connect(ui->limitzmin, SIGNAL(valueChanged(double)), this, SLOT(on_limitzmin_changed(double)));

    connect(ui->limitxmax, SIGNAL(valueChanged(double)), this, SLOT(on_limitxmax_changed(double)));
    connect(ui->limitymax, SIGNAL(valueChanged(double)), this, SLOT(on_limitymax_changed(double)));
    connect(ui->limitzmax, SIGNAL(valueChanged(double)), this, SLOT(on_limitzmax_changed(double)));

    connect(ui->positionx, SIGNAL(valueChanged(double)), this, SLOT(on_positionx_changed(double)));
    connect(ui->positiony, SIGNAL(valueChanged(double)), this, SLOT(on_positiony_changed(double)));
    connect(ui->positionz, SIGNAL(valueChanged(double)), this, SLOT(on_positionz_changed(double)));

    connect(ui->rotationx, SIGNAL(valueChanged(double)), this, SLOT(on_rotationx_changed(double)));
    connect(ui->rotationy, SIGNAL(valueChanged(double)), this, SLOT(on_rotationy_changed(double)));
    connect(ui->rotationz, SIGNAL(valueChanged(double)), this, SLOT(on_rotationz_changed(double)));

    ui->positionx_4->setValue(Environment::gravity.x());
    ui->positiony_4->setValue(Environment::gravity.y());
    ui->positionz_4->setValue(Environment::gravity.z());

    ui->positionx_3->setValue(Environment::wind.x());
    ui->positiony_3->setValue(Environment::wind.y());
    ui->positionz_3->setValue(Environment::wind.z());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::on_limitxmax_changed(double val) {
    if (ui->treeWidget->selectedItems().empty() == true) return;
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    const QString &joint_name = ui->joint_name->text();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    object *obj = dynamic_cast<object *>(n->get_entity());
    if (obj == 0 || obj->get_skeleton() == 0) return;
    balljoint *bj = dynamic_cast<balljoint *>(obj->get_skeleton()->root_joint()->search(joint_name));
    bj->m_limit_rotation_x.setY(val);
}

void
MainWindow::on_limitymax_changed(double val) {
    if (ui->treeWidget->selectedItems().empty() == true) return;
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    const QString &joint_name = ui->joint_name->text();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    object *obj = dynamic_cast<object *>(n->get_entity());
    if (obj == 0 || obj->get_skeleton() == 0) return;
    balljoint *bj = dynamic_cast<balljoint *>(obj->get_skeleton()->root_joint()->search(joint_name));
    bj->m_limit_rotation_y.setY(val);
}

void
MainWindow::on_limitzmax_changed(double val) {
    if (ui->treeWidget->selectedItems().empty() == true) return;
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    const QString &joint_name = ui->joint_name->text();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    object *obj = dynamic_cast<object *>(n->get_entity());
    if (obj == 0 || obj->get_skeleton() == 0) return;
    balljoint *bj = dynamic_cast<balljoint *>(obj->get_skeleton()->root_joint()->search(joint_name));
    bj->m_limit_rotation_z.setY(val);
}

void
MainWindow::on_limitxmin_changed(double val) {
    if (ui->treeWidget->selectedItems().empty() == true) return;
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    const QString &joint_name = ui->joint_name->text();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    object *obj = dynamic_cast<object *>(n->get_entity());
    if (obj == 0 || obj->get_skeleton() == 0) return;
    balljoint *bj = dynamic_cast<balljoint *>(obj->get_skeleton()->root_joint()->search(joint_name));
    bj->m_limit_rotation_x.setX(val);
}

void
MainWindow::on_limitymin_changed(double val) {
    if (ui->treeWidget->selectedItems().empty() == true) return;
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    const QString &joint_name = ui->joint_name->text();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    object *obj = dynamic_cast<object *>(n->get_entity());
    if (obj == 0 || obj->get_skeleton() == 0) return;
    balljoint *bj = dynamic_cast<balljoint *>(obj->get_skeleton()->root_joint()->search(joint_name));
    bj->m_limit_rotation_y.setX(val);
}

void
MainWindow::on_limitzmin_changed(double val) {
    if (ui->treeWidget->selectedItems().empty() == true) return;
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    const QString &joint_name = ui->joint_name->text();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    object *obj = dynamic_cast<object *>(n->get_entity());
    if (obj == 0 || obj->get_skeleton() == 0) return;
    balljoint *bj = dynamic_cast<balljoint *>(obj->get_skeleton()->root_joint()->search(joint_name));
    bj->m_limit_rotation_z.setX(val);
}


void
MainWindow::on_positionx_changed(double val) {
    if (ui->treeWidget->selectedItems().empty() == true) return;
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    const QString &joint_name = ui->joint_name->text();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    object *obj = dynamic_cast<object *>(n->get_entity());
    if (obj == 0 || obj->get_skeleton() == 0) return;
    balljoint *bj = dynamic_cast<balljoint *>(obj->get_skeleton()->root_joint()->search(joint_name));
    bj->m_position.setX(val);
}

void
MainWindow::on_positiony_changed(double val) {
    if (ui->treeWidget->selectedItems().empty() == true) return;
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    const QString &joint_name = ui->joint_name->text();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    object *obj = dynamic_cast<object *>(n->get_entity());
    if (obj == 0 || obj->get_skeleton() == 0) return;
    balljoint *bj = dynamic_cast<balljoint *>(obj->get_skeleton()->root_joint()->search(joint_name));
    bj->m_position.setY(val);
}

void
MainWindow::on_positionz_changed(double val) {
    if (ui->treeWidget->selectedItems().empty() == true) return;
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    const QString &joint_name = ui->joint_name->text();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    object *obj = dynamic_cast<object *>(n->get_entity());
    if (obj == 0 || obj->get_skeleton() == 0) return;
    balljoint *bj = dynamic_cast<balljoint *>(obj->get_skeleton()->root_joint()->search(joint_name));
    bj->m_position.setZ(val);
}

void
MainWindow::on_rotationx_changed(double val) {
    if (ui->treeWidget->selectedItems().empty() == true) return;
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    const QString &joint_name = ui->joint_name->text();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    object *obj = dynamic_cast<object *>(n->get_entity());
    if (obj == 0 || obj->get_skeleton() == 0) return;
    balljoint *bj = dynamic_cast<balljoint *>(obj->get_skeleton()->root_joint()->search(joint_name));
    bj->m_rotation.setX(qDegreesToRadians(val));
}

void
MainWindow::on_rotationy_changed(double val) {
    if (ui->treeWidget->selectedItems().empty() == true) return;
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    const QString &joint_name = ui->joint_name->text();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    object *obj = dynamic_cast<object *>(n->get_entity());
    if (obj == 0 || obj->get_skeleton() == 0) return;
    balljoint *bj = dynamic_cast<balljoint *>(obj->get_skeleton()->root_joint()->search(joint_name));
    bj->m_rotation.setY(qDegreesToRadians(val));
}

void
MainWindow::on_rotationz_changed(double val) {
    if (ui->treeWidget->selectedItems().empty() == true) return;
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    const QString &joint_name = ui->joint_name->text();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    object *obj = dynamic_cast<object *>(n->get_entity());
    if (obj == 0 || obj->get_skeleton() == 0) return;
    balljoint *bj = dynamic_cast<balljoint *>(obj->get_skeleton()->root_joint()->search(joint_name));
    bj->m_rotation.setZ(qDegreesToRadians(val));
}

void MainWindow::on_actionTest_triggered()
{
    ui->openGLWidget->load_async("wasp.skel", "wasp.skin", "wasp.anim");
}

void
MainWindow::change_select(QTreeWidgetItem*item,QTreeWidgetItem*) {

    if (item == 0) return;

    qDebug() << "selection changed : " << item->data(0, Qt::DisplayRole);

    QVariant val = item->data(0, Qt::DisplayRole);
    const QString &name = val.toString();
    qDebug() << name;
    node *node = ui->openGLWidget->root_node()->search(name);
    if (node != 0) {
        entity *ent = node->get_entity();
        object *obj = dynamic_cast<object*>(ent);
        if (obj != 0) {
            qDebug() << "found object !";
            this->display_obj(obj);
        }
            else {
            ui->treeWidget_2->clear();
            qDebug() << "found smthg else";
        }

        QVector3D   pos = node->get_transform().position();

        ui->positionx_2->setValue(pos.x());
        ui->positiony_2->setValue(pos.y());
        ui->positionz_2->setValue(pos.z());

        // display node data



    }


}

void
MainWindow::display_obj(object *obj) {
    skeleton *skel = obj->get_skeleton();
    ui->treeWidget_2->clear();
    ui->treeWidget_2->setColumnCount(1);
    if (skel != 0) {
        joint* jt = skel->root_joint();
        this->fill_skel_tree(0, jt);
        ui->treeWidget_2->expandAll();
    }
}

void
MainWindow::fill_skel_tree(QTreeWidgetItem *wi_parent, joint *parent) {
    QTreeWidgetItem     *item;
    if (wi_parent == 0)
        item = new QTreeWidgetItem(ui->treeWidget_2);
    else
        item = new QTreeWidgetItem(wi_parent);
    item->setText(0, parent->name());
    foreach (joint *child, parent->childrens()) {
        fill_skel_tree(item, child);
    }
}

void MainWindow::on_actionTube_triggered()
{
//    ui->openGLWidget->load_async("tube.skel", "smooth_tube.skin");
}

void
MainWindow::skel_change_select(QTreeWidgetItem *item, QTreeWidgetItem *) {
    qDebug() << "change select";
    if (item == 0) return;

    QVariant val = item->data(0, Qt::DisplayRole);
    const QString &name = val.toString();
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    node *n = ui->openGLWidget->root_node()->search(node_name);
//    n->get_entity()->
    ui->joint_name->setText(name);
    object *obj = dynamic_cast<object *>(n->get_entity());
    joint *j = obj->get_skeleton()->root_joint()->search(name);
    balljoint *bj = dynamic_cast<balljoint *>(j);

    ui->limitxmin->setValue(bj->m_limit_rotation_x.x());
    ui->limitxmax->setValue(bj->m_limit_rotation_x.y());
    ui->limitymin->setValue(bj->m_limit_rotation_y.x());
    ui->limitymax->setValue(bj->m_limit_rotation_y.y());
    ui->limitzmin->setValue(bj->m_limit_rotation_z.x());
    ui->limitzmax->setValue(bj->m_limit_rotation_z.y());
    ui->rotationx->setValue(qRadiansToDegrees(bj->m_rotation.x()));
    ui->rotationy->setValue(qRadiansToDegrees(bj->m_rotation.y()));
    ui->rotationz->setValue(qRadiansToDegrees(bj->m_rotation.z()));
    ui->positionx->setValue(bj->m_position.x());
    ui->positiony->setValue(bj->m_position.y());
    ui->positionz->setValue(bj->m_position.z());
}

#include "cloth.hpp"

void MainWindow::on_pushButton_clicked()
{
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    Cloth *c = dynamic_cast<Cloth *>(n->get_entity());
    if (c != 0) {
        c->m_detach = true;
    }
}

void MainWindow::on_positionx_3_valueChanged(double arg1)
{
    Environment::wind.setX(arg1);
}

void MainWindow::on_positionx_3_valueChanged(const QString &)
{

}

void MainWindow::on_positiony_3_valueChanged(double arg1)
{
    Environment::wind.setY(arg1);
}

void MainWindow::on_positionz_3_valueChanged(double arg1)
{
    Environment::wind.setZ(arg1);
}

void MainWindow::on_positionx_4_valueChanged(double arg1)
{
    Environment::gravity.setX(arg1);
}

void MainWindow::on_positiony_4_valueChanged(double arg1)
{
    Environment::gravity.setY(arg1);
}

void MainWindow::on_positionz_4_valueChanged(double arg1)
{
    Environment::gravity.setZ(arg1);
}

void MainWindow::on_scalex_valueChanged(double arg1)
{
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    // node node
}

void MainWindow::on_positionx_2_valueChanged(double arg1)
{
    if (ui->treeWidget->selectedItems().empty()) return;
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    const QVector3D p = n->get_transform().position();
    n->get_transform().position(QVector3D(arg1, p.y(), p.z()));
}

void MainWindow::on_positiony_2_valueChanged(double arg1)
{
    if (ui->treeWidget->selectedItems().empty()) return;
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    const QVector3D p = n->get_transform().position();
    n->get_transform().position(QVector3D(p.x(), arg1, p.z()));
}

void MainWindow::on_positionz_2_valueChanged(double arg1)
{
    if (ui->treeWidget->selectedItems().empty()) return;
    const QString &node_name = ui->treeWidget->selectedItems().first()->data(0, Qt::DisplayRole).toString();
    node *n = ui->openGLWidget->root_node()->search(node_name);
    if (n == 0) return;
    const QVector3D p = n->get_transform().position();
    n->get_transform().position(QVector3D(p.x(), p.y(), arg1));
}
