#include <QFile>
#include <QDebug>

#include "skin_loader.hpp"

skin_loader::skin_loader()
{

}

skin_loader::~skin_loader()
{
}

skin *
skin_loader::load(const QString &filename)
{
    QFile   file(filename);

    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "file " << filename << "cannot be opened";
        return 0;
    }
    QTextStream in(&file);
    QString text = in.readAll() + '\0';
    file.close();
    skin *s = new skin();
    this->parse(s, text);
    return s;
}

void
skin_loader::parse(skin *sk, const QString &file)
{
    int index = 0;

    while (file[index] != '\0') {
        const QString &section_name = this->get_string(file, index);
        qDebug() << section_name;
        if (section_name == "positions")
            this->parse_position(sk, file, index);
        else if (section_name == "normals")
            this->parse_normals(sk, file, index);
        else if (section_name == "skinweights")
            this->parse_skinweights(sk, file, index);
        else if (section_name == "triangles")
            this->parse_triangles(sk, file, index);
        else if (section_name == "bindings")
            this->parse_bindings(sk, file, index);
        else if (section_name == "texcoords")
            this->parse_texcoords(sk, file, index);
        else if (section_name == "material")
            this->parse_material(sk, file, index);
        else {
            qDebug() << "file error";
            break;
        }
        this->skip_space(file, index);
    }
}

void
skin_loader::parse_position(skin *sk, const QString &file, int &index)
{
    QVector<float>  positions;
    int pos_number = 0;
    this->parse_int(file, index, pos_number);
    positions.reserve(pos_number * 3);
    this->parse_open_parenthesis(file, index);
    for (int i = 0 ; i < pos_number ; ++i) {
        float x, y, z;
        this->parse_float(file, index, x);
        this->parse_float(file, index, y);
        this->parse_float(file, index, z);
        positions.push_back(x);
        positions.push_back(y);
        positions.push_back(z);
    }
    sk->positions(positions);
    this->parse_close_parenthesis(file, index);
}

void
skin_loader::parse_normals(skin *sk, const QString &file, int &index)
{
    QVector<float>  normals;
    int number = 0;
    this->parse_int(file, index, number);
    normals.reserve(number * 3);
    this->parse_open_parenthesis(file, index);
    for (int i = 0 ; i < number ; ++i) {
        float x, y, z;
        this->parse_float(file, index, x);
        this->parse_float(file, index, y);
        this->parse_float(file, index, z);
        normals.push_back(x);
        normals.push_back(y);
        normals.push_back(z);
    }
    sk->normals(normals);
    this->parse_close_parenthesis(file, index);
}

void
skin_loader::parse_skinweights(skin *sk, const QString &file, int &index)
{
    QVector<float>  weights;
    QVector<unsigned int>  indices;
    int number = 0;

    this->parse_int(file, index, number);
    this->parse_open_parenthesis(file, index);
    weights.reserve(number * 4);
    indices.reserve(number * 4);
    qDebug() << number;
    for (int i = 0 ; i < number ; ++i) {

        int number_joint = 0;
        this->parse_int(file, index, number_joint);


        if (number_joint > 4) {
                    qDebug() << number_joint;
            qDebug() << "number_joint linked is more than 4.";
            exit(0);
        }

        int j;
        for (j = 0 ; j < number_joint ; ++j) {
            int idx = 0;
            float val = 0.0f;
            this->parse_int(file, index, idx);
            this->parse_float(file, index, val);
            weights.push_back(val);
            indices.push_back(idx);
        }
        while (j < 4) {
            weights.push_back(0.0f);
            indices.push_back(42);
            ++j;
        }
    }
    this->parse_close_parenthesis(file, index);
    sk->skin_weights(weights);
    sk->skin_indices(indices);
}

void
skin_loader::parse_triangles(skin *sk, const QString &file, int &index)
{
    QVector<unsigned int>   indices;
    int number = 0;

    this->parse_int(file, index, number);
    this->parse_open_parenthesis(file, index);
    indices.reserve(number * 3);
    for (int i = 0 ; i < number ; ++i) {
        int v1, v2, v3;
        this->parse_int(file, index, v1);
        this->parse_int(file, index, v2);
        this->parse_int(file, index, v3);
        indices.push_back(v1);
        indices.push_back(v2);
        indices.push_back(v3);
    }
    this->parse_close_parenthesis(file, index);
    sk->indices(indices);
}

void
skin_loader::parse_bindings(skin *sk, const QString &file, int &index)
{
    QVector<QMatrix4x4>     m_bindings;
    int number = 0;

    this->parse_int(file, index, number);
    this->parse_open_parenthesis(file, index);
    m_bindings.reserve(number);
    for (int b = 0 ; b < number ; ++b) {
        QMatrix4x4  matrix;
        this->parse_matrix(file, index, matrix);
        m_bindings.push_back(matrix);
    }
    this->parse_close_parenthesis(file, index);
    sk->binding_matrices(m_bindings);
}

void
skin_loader::parse_texcoords(skin *sk, const QString &file, int &index)
{

}

void
skin_loader::parse_material(skin *sk, const QString &file, int &index)
{

}

QString
skin_loader::get_string(const QString &file, int &index)
{
    QString str = "";

    this->skip_space(file, index);
    while (file[index] != ' ' && file[index] != '\t' && file[index] != '\n' && file[index] != '\0')
    {
        str += file[index++];
    }
    return str;
}

void
skin_loader::skip_space(const QString &file, int &index)
{
    while (file[index] == ' ' || file[index] == '\t' || file[index] == '\n') ++index;
}


bool
skin_loader::parse_int(const QString &data, int &index, int &output)
{
    QString str = "";
    int     i = index;

    this->skip_space(data, i);
    if (data[i] == '-' || data[i] == '+') str += data[i++];
    while (data[i].isDigit()) {
        str += data[i];
        ++i;
    }
    index = i;
    output = str.toInt();
    return true;
}

bool
skin_loader::parse_float(const QString &data, int &index, float &output)
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
skin_loader::parse_open_parenthesis(const QString &data, int &index)
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
skin_loader::parse_close_parenthesis(const QString &data, int &index)
{
    int i = index;
    this->skip_space(data, i);
    if (data[i] == '}') {
        index = i + 1;
        return true;
    }
    return false;
}

//a a a
//b b b
//c c c
//d d d

bool
skin_loader::parse_matrix(const QString &file, int &index, QMatrix4x4 &output)
{
    this->get_string(file, index);
    this->parse_open_parenthesis(file, index);
    this->parse_float(file, index, output.data()[0]);
    this->parse_float(file, index, output.data()[1]);
    this->parse_float(file, index, output.data()[2]);
    output.data()[3] = 0;
    this->parse_float(file, index, output.data()[4]);
    this->parse_float(file, index, output.data()[5]);
    this->parse_float(file, index, output.data()[6]);
    output.data()[7] = 0;
    this->parse_float(file, index, output.data()[8]);
    this->parse_float(file, index, output.data()[9]);
    this->parse_float(file, index, output.data()[10]);
    output.data()[11] = 0;
    this->parse_float(file, index, output.data()[12]);
    this->parse_float(file, index, output.data()[13]);
    this->parse_float(file, index, output.data()[14]);
    output.data()[15] = 1;
    output = output.inverted();
    this->parse_close_parenthesis(file, index);
}




