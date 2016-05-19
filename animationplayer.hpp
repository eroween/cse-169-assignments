#ifndef ANIMATIONPLAYER_H
#define ANIMATIONPLAYER_H

#include <animation.hpp>
#include "node.hpp"
#include "skeleton.hpp"

class AnimationPlayer
{
public:
    AnimationPlayer(Animation *anim);

    void animate(node *n, skeleton *skel);


public:
    float       m_t;
    Animation   *m_animation;
};

#endif // ANIMATIONPLAYER_H
