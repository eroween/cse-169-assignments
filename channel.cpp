#include "channel.hpp"
#include <qdebug.h>

Channel::Channel()
{

}

void
Channel::compute()
{
    static int debug = 0;

    debug++;

    for (int i = 0 ; i < m_keyframes.size() ; ++i)
    {
        Channel::KeyFrame   &curr = m_keyframes[i];
        Channel::KeyFrame   &next = i + 1 >= m_keyframes.size() ? curr : m_keyframes[i + 1];
        Channel::KeyFrame   &prev = i == 0 ? curr : m_keyframes[i - 1];

        if (curr.m_tangent_in == Channel::KeyFrame::FLAT)
            curr.m_tangent_in_value = 0.0f;
        else if (&curr != &prev && curr.m_tangent_in == Channel::KeyFrame::LINEAR)
            curr.m_tangent_in_value = (curr.m_time - prev.m_time) == 0 ? 0.0f : (curr.m_value - prev.m_value) / (curr.m_time - prev.m_time);
        else if (&curr != &prev && curr.m_tangent_in == Channel::KeyFrame::SMOOTH)
            curr.m_tangent_in_value = (next.m_time - prev.m_time) == 0 ? 0.0f : (next.m_value - prev.m_value) / (next.m_time - prev.m_time);

        if (curr.m_tangent_out == Channel::KeyFrame::FLAT)
            curr.m_tangent_out_value = 0.0f;
        else if (&curr != &next && curr.m_tangent_out == Channel::KeyFrame::LINEAR)
            curr.m_tangent_out_value = (curr.m_time - prev.m_time) == 0 ? 0.0f : (next.m_value - curr.m_value) / (next.m_time - curr.m_time);
        else if (&curr != &next && curr.m_tangent_out == Channel::KeyFrame::SMOOTH)
            curr.m_tangent_out_value = (next.m_time - prev.m_time) == 0 ? 0.0f : (next.m_value - prev.m_value) / (next.m_time - prev.m_time);

        if (&curr == &prev && (curr.m_tangent_in == Channel::KeyFrame::LINEAR || curr.m_tangent_in == Channel::KeyFrame::SMOOTH))
            curr.m_tangent_in_value = curr.m_tangent_out_value;
        if (&curr == &next && (curr.m_tangent_out == Channel::KeyFrame::LINEAR || curr.m_tangent_out == Channel::KeyFrame::SMOOTH))
            curr.m_tangent_out_value = curr.m_tangent_in_value;
    }
    for (int i = 0 ; i < m_keyframes.size() - 1 ; ++i)
    {
        Channel::KeyFrame   &curr = m_keyframes[i];
        Channel::KeyFrame   &next = m_keyframes[i + 1];

        float tangent_in = next.m_tangent_in_value * (next.m_time - curr.m_time);
        float tangent_out = curr.m_tangent_out_value * (next.m_time - curr.m_time);

        curr.m_a = 2.0f * curr.m_value - 2.0f * next.m_value + tangent_out + tangent_in;
        curr.m_b = -3.0f * curr.m_value + 3.0f * next.m_value - 2.0f * tangent_out - tangent_in;
        curr.m_c = tangent_out;
        curr.m_d = curr.m_value;
    }
}

float
Channel::evaluate(float t)
{
    Channel::KeyFrame   &first = m_keyframes.front();
    Channel::KeyFrame   &last = m_keyframes.back();
    float offset = 0.0f;
    float duration = last.m_time - first.m_time;
    int happened = duration == 0.0f ? 0 : (t - first.m_time) / duration;

    if (t < first.m_time)
    {
        happened -= 1;
        switch (m_extrapolation_in)
        {
        case CONSTANT_EXTRAPOLATION: // return the first value
            return first.m_value;
        case LINEAR_EXTRAPOLATION:
            return first.m_tangent_out_value * (t - first.m_time) + first.m_value;
        case CYCLE_EXTRAPOLATION:
            t = std::fmod(t - (first.m_time + duration * happened), duration) + first.m_time; // cyclic t
            break;
        case CYCLE_OFFSET_EXTRAPOLATION:
            t = std::fmod(t - (first.m_time + duration * happened), duration) + first.m_time; // cyclic t
            offset = happened * (last.m_value - first.m_value); // happenned * offset per cycle
            break;
        case BOUNCE_EXTRAPOLATION:
            t = std::fmod(t - (first.m_time + duration * happened), duration) + first.m_time; // cyclic t
            if (!(abs(happened) % 2)) t = last.m_time - std::fmod(t - (first.m_time + duration * happened), duration); // reverse cyclic
            break;
        }
    }
    else if (t > last.m_time)
    {
        switch (m_extrapolation_out)
        {
        case CONSTANT_EXTRAPOLATION: // return the first value
            return last.m_value;
        case LINEAR_EXTRAPOLATION:
            return last.m_tangent_out_value * (t - last.m_time) + last.m_value;
        case CYCLE_EXTRAPOLATION:
            t = std::fmod(t - first.m_time, duration) + first.m_time; // cyclic t
            break;
        case CYCLE_OFFSET_EXTRAPOLATION:
            t = std::fmod(t - first.m_time, duration) + first.m_time; // cyclic t
            offset = happened * (last.m_value - first.m_value); // happenned * offset per cycle
            break;
        case BOUNCE_EXTRAPOLATION:
            t = std::fmod(t - first.m_time, duration) + first.m_time; // cyclic t
            if (abs(happened) % 2 == 1) t = last.m_time - std::fmod(t - first.m_time, duration); // reverse cyclic
            break;
        }
    }
    for (int i = 0 ; i < m_keyframes.size() ; ++i)
    {
        Channel::KeyFrame   &curr = m_keyframes[i];
        Channel::KeyFrame   &next = i + 1 < m_keyframes.size() ? m_keyframes[i + 1] : curr;

        // case only 1 keyframe
        if (&curr == &next) return curr.m_value;

        // until we found the good keyframe
        if (t < curr.m_time || t >= next.m_time) continue;

        float u = next.m_time - curr.m_time == 0.0f ? 0.0f : (t - curr.m_time) / (next.m_time - curr.m_time);
        return ((curr.m_a * u + curr.m_b) * u + curr.m_c) * u + curr.m_d + offset;
    }
    return 0.0f;
}
