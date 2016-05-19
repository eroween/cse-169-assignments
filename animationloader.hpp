#ifndef ANIMATIONLOADER_H
#define ANIMATIONLOADER_H

#include <QString>
#include "animation.hpp"

class AnimationLoader
{
public:
    AnimationLoader();

public:
    Animation   *load(const QString &filename);

public:
    void    parse(Animation *anim, const QString &file);
    bool    parse_channel(const QString &data, int &index, Channel *out);

public:
    bool    parse_float(const QString &data, int &index, float &output); // OK
    void    skip_space(const QString &data, int &index); // OK
    bool    parse_open_parenthesis(const QString &data, int &index); // OK
    bool    parse_close_parenthesis(const QString &data, int &index); // OK
    QString     get_string(const QString &file, int &index);

};

#endif // ANIMATIONLOADER_H
