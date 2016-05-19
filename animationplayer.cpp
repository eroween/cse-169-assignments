
#include <qdebug.h>
#include "animationplayer.hpp"
#include <iostream>

AnimationPlayer::AnimationPlayer(Animation *a) :
    m_animation(a)
{

}

void
AnimationPlayer::animate(node *n, skeleton *skel)
{
    m_t += 0.01f;
    const auto &poses = m_animation->evaluate(m_t);

    transform &t = n->get_transform();
    t.position(QVector3D(poses[0], poses[1], poses[2]));
   // qDebug() << QVector3D(poses[0], poses[1], poses[2]);

    QVector<joint *> jts = skel->joints();
    for (int i = 3 ; i < poses.size() ; i += 3)
    {
        balljoint *bj = dynamic_cast<balljoint *>(jts[i / 3 - 1]);
        bj->m_rotation = QVector3D(poses[i], poses[i + 1], poses[i + 2]);
    }
}
