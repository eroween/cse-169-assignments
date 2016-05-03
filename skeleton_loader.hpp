#ifndef SKELETON_LOADER_H
#define SKELETON_LOADER_H

#include <QString>

class   balljoint;
class   joint;
class   skeleton;

class skeleton_loader
{
public:
    skeleton_loader(void);
    ~skeleton_loader(void);

public:

    ///
    /// \brief load a skeleton file into a root node tree.
    /// \param filename the skeleton filename.
    /// \return The root node of the file.
    ///
    skeleton  *load(const QString &filename);

private:

    balljoint  *create_joint(const QString &joint_type);

    joint   *parse_joint(const QString &data, int &index); // OK
    bool    parse_open_parenthesis(const QString &data, int &index); // OK
    bool    parse_close_parenthesis(const QString &data, int &index); // OK

    bool    parse_informations(const QString &data, int &index, balljoint *t_joint);

    bool    parse_offset(const QString &data, int &index, balljoint *t_joint);
    bool    parse_box_min(const QString &data, int &index, balljoint *t_joint);
    bool    parse_box_max(const QString &data, int &index, balljoint *t_joint);
    bool    parse_rotxlimit(const QString &data, int &index, balljoint *t_joint);
    bool    parse_rotylimit(const QString &data, int &index, balljoint *t_joint);
    bool    parse_rotzlimit(const QString &data, int &index, balljoint *t_joint);
    bool    parse_pose(const QString &data, int &index, balljoint *t_joint);

    void    skip_space(const QString &data, int &index); // OK

    bool    parse_string(const QString &data, int &index, QString &output); // OK
    bool    parse_float(const QString &data, int &index, float &output); // OK
};

#endif // SKELETON_LOADER_H
