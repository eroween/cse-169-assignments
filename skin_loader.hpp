#ifndef SKIN_LOADER_H
#define SKIN_LOADER_H

#include <QMatrix4x4>
#include "skin.hpp"

class skin_loader
{
public:
    skin_loader();
    ~skin_loader(void);


public:

    skin    *load(const QString &filename);

private:
    void    parse(skin *sk, const QString &file);

    void    parse_position(skin *sk, const QString &file, int &index);
    void    parse_normals(skin *sk, const QString &file, int &index);
    void    parse_skinweights(skin *sk, const QString &file, int &index);
    void    parse_triangles(skin *sk, const QString &file, int &index);
    void    parse_bindings(skin *sk, const QString &file, int &index);
    void    parse_texcoords(skin *sk, const QString &file, int &index);
    void    parse_material(skin *sk, const QString &file, int &index);

private:

    QString     get_string(const QString &file, int &index);
    bool    parse_int(const QString &data, int &index, int &output);
    bool    parse_float(const QString &data, int &index, float &output);
    bool    parse_matrix(const QString &data, int &index, QMatrix4x4 &output);
    bool    parse_open_parenthesis(const QString &data, int &index); // OK
    bool    parse_close_parenthesis(const QString &data, int &index); // OK

    void    skip_space(const QString &file, int &index);

};

#endif // SKIN_LOADER_H
