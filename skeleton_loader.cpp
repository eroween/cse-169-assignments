#include <QFile>
#include <QDebug>

#include "skeleton_loader.hpp"
#include "skeleton.hpp"
#include "joint.hpp"
#include "balljoint.hpp"

skeleton_loader::skeleton_loader()
{

}

skeleton_loader::~skeleton_loader()
{

}

skeleton *
skeleton_loader::load(const QString &filename)
{
    QFile   file(filename);

    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "file " << filename << "cannot be opened";
        return 0;
    }
    QTextStream in(&file);
    QString text = in.readAll() + '\0';
    int index = 0;
    skeleton *skel = new skeleton();
    skel->root_joint(this->parse_joint(text, index));
    file.close();
    return skel;
}

balljoint *
skeleton_loader::create_joint(const QString &joint_type)
{
//    qDebug() << joint_type;
    if (joint_type == "balljoint")
        return new balljoint();
    return 0;
}

joint *
skeleton_loader::parse_joint(const QString &t_data, int &t_index)
{
    QString joint_type = "";
    if (this->parse_string(t_data, t_index, joint_type) == false)
        return 0;
    balljoint   *j = this->create_joint(joint_type);
    if (this->parse_string(t_data, t_index, j->name()) == false)
        return 0;
//    qDebug() << "joint_name : " << j->name();
    if (this->parse_open_parenthesis(t_data, t_index) == false)
        return 0;
    while (this->parse_informations(t_data, t_index, j) != false)
    {
        int i = t_index;
        if (this->parse_close_parenthesis(t_data, t_index) == true) {
            return j;
        }
        t_index = i;
    }
    if (this->parse_close_parenthesis(t_data, t_index) == false)
        return 0;
    return j;
}

bool
skeleton_loader::parse_informations(const QString &data, int &index, balljoint *t_joint)
{
    int i = index;
    if (this->parse_offset(data, index = i, t_joint) == true) return true;
    if (this->parse_box_max(data, index = i, t_joint) == true) return true;
    if (this->parse_box_min(data, index = i, t_joint) == true) return true;
    if (this->parse_rotxlimit(data, index = i, t_joint) == true) return true;
    if (this->parse_rotylimit(data, index = i, t_joint) == true) return true;
    if (this->parse_rotzlimit(data, index = i, t_joint) == true) return true;
    if (this->parse_pose(data, index = i, t_joint) == true) return true;
    joint *child = 0;
    if ((child = this->parse_joint(data, index = i)) != 0) {
        t_joint->add_child(child);
        return true;
    }
    delete child;
    return false;
}

bool
skeleton_loader::parse_rotxlimit(const QString &data, int &index, balljoint *t_joint)
{
    int i = index;
    QString name = "";
    this->parse_string(data, i, name);
    if (name != "rotxlimit") {
        return false;
    }
    float real1, real2;
    if (this->parse_float(data, i, real1) && this->parse_float(data, i, real2))
    {
        index = i;
        t_joint->limit_rotation_x(QVector2D(real1 ,real2));
//        qDebug() << "rotxlimit : " << real1 << " " << real2 << " ";
        return true;
    }
    return false;
}

bool
skeleton_loader::parse_rotylimit(const QString &data, int &index, balljoint *t_joint)
{
    int i = index;
    QString name = "";
    this->parse_string(data, i, name);
    if (name != "rotylimit") {
        return false;
    }
    float real1, real2;
    if (this->parse_float(data, i, real1) && this->parse_float(data, i, real2))
    {
        index = i;
        t_joint->limit_rotation_y(QVector2D(real1, real2));
//        qDebug() << "rotylimit : " << real1 << " " << real2 << " ";
        return true;
    }
    return false;
}

bool
skeleton_loader::parse_rotzlimit(const QString &data, int &index, balljoint *t_joint)
{
    int i = index;
    QString name = "";
    this->parse_string(data, i, name);
    if (name != "rotzlimit") {
        return false;
    }
    float real1, real2;
    if (this->parse_float(data, i, real1) && this->parse_float(data, i, real2))
    {
        index = i;
        t_joint->limit_rotation_z(QVector2D(real1, real2));
//        qDebug() << "rotzlimit : " << real1 << " " << real2 << " ";
        return true;
    }
    return false;
}


bool
skeleton_loader::parse_offset(const QString &data, int &index, balljoint *t_joint)
{
    int i = index;
    QString name = "";
    this->parse_string(data, i, name);
    if (name != "offset") {
        return false;
    }
    float real1, real2, real3;
    if (this->parse_float(data, i, real1) && this->parse_float(data, i, real2) && this->parse_float(data, i, real3))
    {
        index = i;
        t_joint->offset(QVector3D(real1, real2, real3));
//        qDebug() << "offset : " << real1 << " " << real2 << " " << real3;
        return true;
    }
    return false;
}

bool
skeleton_loader::parse_pose(const QString &data, int &index, balljoint *t_joint)
{
    int i = index;
    QString name = "";
    this->parse_string(data, i, name);
    if (name != "pose") {
        return false;
    }
    float real1, real2, real3;
    if (this->parse_float(data, i, real1) && this->parse_float(data, i, real2) && this->parse_float(data, i, real3))
    {
        index = i;
        t_joint->pose(QVector3D(real1, real2, real3));
//        qDebug() << "poses : " << real1 << " " << real2 << " " << real3;
        return true;
    }
    return false;
}


bool
skeleton_loader::parse_box_min(const QString &data, int &index, balljoint *t_joint)
{
    int i = index;
    QString name = "";
    this->parse_string(data, i, name);
    if (name != "boxmin") {
        return false;
    }
    float real1, real2, real3;
    if (this->parse_float(data, i, real1) && this->parse_float(data, i, real2) && this->parse_float(data, i, real3))
    {
        index = i;
        t_joint->box_min(QVector3D(real1, real2, real3));
//        qDebug() << "box_min : " << real1 << " " << real2 << " " << real3;
        return true;
    }
    return false;
}

bool
skeleton_loader::parse_box_max(const QString &data, int &index, balljoint *t_joint)
{
    int i = index;
    QString name = "";
    this->parse_string(data, i, name);
    if (name != "boxmax") {
        return false;
    }
    float real1, real2, real3;
    if (this->parse_float(data, i, real1) && this->parse_float(data, i, real2) && this->parse_float(data, i, real3))
    {
        index = i;
        t_joint->box_max(QVector3D(real1 ,real2, real3));
//        qDebug() << "box_max : " << real1 << " " << real2 << " " << real3;
        return true;
    }
    return false;
}


bool
skeleton_loader::parse_float(const QString &data, int &index, float &output)
{
    QString str = "";
    int     i = index;

    this->skip_space(data, i);
    if (data[i] == '-' || data[i] == '+') str += data[i++];
    while (data[i].isDigit()) {
        str += data[i];
        ++i;
    }
    if (data[i] == '.') str += data[i++];
    while (data[i].isDigit()) {
        str += data[i];
        ++i;
    }
    index = i;
    output = str.toFloat();
    return true;
}

bool
skeleton_loader::parse_string(const QString &data, int &index, QString &output)
{
    int     i = index;
    this->skip_space(data, i);
    output = "";
    while (data[i] != ' ' && data[i] != '\0') {
        output += data[i];
        ++i;
    }
    index = i;
    return true;
}

bool
skeleton_loader::parse_open_parenthesis(const QString &data, int &index)
{
    int     i = index;
    this->skip_space(data, i);
    if (data[i] == '{') {
        index = i + 1;
        return true;
    }
    return false;
}

bool
skeleton_loader::parse_close_parenthesis(const QString &data, int &index)
{
    int i = index;
    this->skip_space(data, i);
    if (data[i] == '}') {
        index = i + 1;
        return true;
    }
    return false;
}

void
skeleton_loader::skip_space(const QString &data, int &index)
{
    while (data[index] == ' ' || data[index] == '\n' || data[index] == '\t') ++index;
}
