#include "animationloader.hpp"
#include <QFile>
#include <QTextStream>

AnimationLoader::AnimationLoader()
{

}

#include <qdebug.h>

Animation *
AnimationLoader::load(const QString &filename)
{

    QFile   file(filename);

    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "file " << filename << "cannot be opened";
        return 0;
    }
    QTextStream in(&file);
    QString text = in.readAll() + '\0';
    file.close();
    Animation *anim = new Animation;
    this->parse(anim, text);
    return anim;
}

void
AnimationLoader::parse(Animation *anim, const QString &file)
{
    qDebug() << file;
    int index = 0;
    if (this->get_string(file, index) == "animation")
    {
        if (this->parse_open_parenthesis(file, index) == false) {qDebug() << "open para fail"; return;}
        if (this->get_string(file, index) != "range") {qDebug() << "range fail"; return;}
        float min = 0.0f, max = 0.0f;
        if (this->parse_float(file, index, min) == false) {qDebug() << "range min fail"; return;}
        if (this->parse_float(file, index, max) == false) {qDebug() << "range min fail"; return;}
        anim->m_range.setX(min);
        anim->m_range.setY(max);
        qDebug() << "range : " << min << " " << max;
        float numchan;
        if (this->get_string(file, index) != "numchannels") {qDebug() << "numchannels fail"; return;}
        if (this->parse_float(file, index, numchan) == false) {qDebug() << "num chan fail"; return;}
        qDebug() << "numchan : " << (int)numchan;
        for (int nc = 0 ; nc < (int)numchan ; ++nc) {
            Channel *chan = new Channel();
            anim->m_channels.push_back(chan);
            if (this->parse_channel(file, index, chan) == false)
                {qDebug() << "chan parse fail"; return;}
        }
        if (this->parse_close_parenthesis(file, index) == false) {qDebug() << "close para fail"; return;}
    }
}

bool
AnimationLoader::parse_channel(const QString &file, int &index, Channel *out)
{
    if (this->get_string(file, index) != "channel") {qDebug() << "channel name fail"; return false;}
    if (this->parse_open_parenthesis(file, index) == false) {qDebug() << "open para fail"; return false;}

    if (this->get_string(file, index) != "extrapolate") {qDebug() << "extrapolate fail"; return false;}

    int i = index;
    Channel::ExtrapolationType t;
    if (this->get_string(file, (i = index)) == "constant") t = Channel::CONSTANT_EXTRAPOLATION;
    else if (this->get_string(file, (i = index)) == "linear") t = Channel::LINEAR_EXTRAPOLATION;
    else if (this->get_string(file, (i = index)) == "cycle") t = Channel::CYCLE_EXTRAPOLATION;
    else if (this->get_string(file, (i = index)) == "cycle_offset") t = Channel::CYCLE_OFFSET_EXTRAPOLATION;
    else if (this->get_string(file, (i = index)) == "bounce") t = Channel::BOUNCE_EXTRAPOLATION;
    else { qDebug() << "extrapolate in type fail"; return false; }

    index = i;
    out->m_extrapolation_in = t;

    if (this->get_string(file, (i = index)) == "constant") t = Channel::CONSTANT_EXTRAPOLATION;
    else if (this->get_string(file, (i = index)) == "linear") t = Channel::LINEAR_EXTRAPOLATION;
    else if (this->get_string(file, (i = index)) == "cycle") t = Channel::CYCLE_EXTRAPOLATION;
    else if (this->get_string(file, (i = index)) == "cycle_offset") t = Channel::CYCLE_OFFSET_EXTRAPOLATION;
    else if (this->get_string(file, (i = index)) == "bounce") t = Channel::BOUNCE_EXTRAPOLATION;
    else { qDebug() << "extrapolate in type fail => " << this->get_string(file, (i = index)); return false; }

    out->m_extrapolation_out = t;

    index = i;

    if (this->get_string(file, index) != "keys") {qDebug() << "key name fail"; return false;}
    float keynum = 0.0f;
    if (this->parse_float(file, index, keynum) == false) {qDebug() << "keynum fail"; return false;}
    if (this->parse_open_parenthesis(file, index) == false) {qDebug() << "open para fail"; return false;}

    for (int kn = 0 ; kn < keynum ; ++kn) {
        float time = 0.0f;
        if (this->parse_float(file, index, time) == false) {qDebug() << "time keyframe " << kn << " fail"; return false;}
        float value = 0.0f;
        if (this->parse_float(file, index, value) == false) {qDebug() << "value keyframe " << kn << " fail"; return false;}

        Channel::KeyFrame kf;
        kf.m_time = time;
        kf.m_value = value;

        value = 0.0f;
        Channel::KeyFrame::TangentType tt = Channel::KeyFrame::VALUE;

        int j = index;

        if (this->get_string(file, j = index) == "flat") tt = Channel::KeyFrame::VALUE;
        else if (this->get_string(file, j = index) == "linear") tt = Channel::KeyFrame::LINEAR;
        else if (this->get_string(file, j = index) == "smooth") tt = Channel::KeyFrame::SMOOTH;
        else if (this->parse_float(file, j = index, value) == false) {
            qDebug() << "value tt1 keyframe " << kn << " fail"; return false;
        }

        kf.m_tangent_in = tt;
        kf.m_tangent_in_value = value;

        index = j;

        value = 0.0f;
        tt = Channel::KeyFrame::VALUE;

        if (this->get_string(file, j = index) == "flat") tt = Channel::KeyFrame::VALUE;
        else if (this->get_string(file, j = index) == "linear") tt = Channel::KeyFrame::LINEAR;
        else if (this->get_string(file, j = index) == "smooth") tt = Channel::KeyFrame::SMOOTH;
        else if (this->parse_float(file, j = index, value) == false) {
            qDebug() << "value tt2 keyframe " << kn << " fail"; return false;
        }

        kf.m_tangent_out = tt;
        kf.m_tangent_out_value = value;
        index = j;

        out->m_keyframes.push_back(kf);
    }

    if (out->m_keyframes.size() != (unsigned int)keynum) {
        qDebug() << "keyframe number missmatch";
    }
    if (this->parse_close_parenthesis(file, index) == false) {qDebug() << "close para fail"; return false;}

    if (this->parse_close_parenthesis(file, index) == false) {qDebug() << "close para fail"; return false;}
    out->compute();
    return true;
}

QString
AnimationLoader::get_string(const QString &file, int &index)
{
    QString str = "";

    this->skip_space(file, index);
    while (file[index] != ' ' && file[index] != '\t' && file[index] != '\n'&& file[index] != '\r' && file[index] != '\0')
    {
        str += file[index++];
    }
    return str;
}

void
AnimationLoader::skip_space(const QString &file, int &index)
{
    while (file[index] == ' ' || file[index] == '\t' || file[index] == '\n' || file[index] == '\r') ++index;
}


bool
AnimationLoader::parse_float(const QString &data, int &index, float &output)
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
AnimationLoader::parse_open_parenthesis(const QString &data, int &index)
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
AnimationLoader::parse_close_parenthesis(const QString &data, int &index)
{
    int i = index;
    this->skip_space(data, i);
    if (data[i] == '}') {
        index = i + 1;
        return true;
    }
    return false;
}
