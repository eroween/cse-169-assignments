uniform mat4 mvp;
uniform mat4 v;
uniform mat4 m;

uniform float radius;
uniform float velocity_max;

attribute vec4 position;
attribute vec4 normal;

attribute vec4 offset_position;
attribute vec3 velocity;

varying vec4 frag_color;
varying vec3 frag_normal;
varying vec3 vertPos;

void main()
{
    frag_normal = m * normal;
    float val = length(velocity) / velocity_max;
    frag_color = mix(vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), val);
    vec4 vertPos4 = m * position;
    vertPos = vec3(vertPos4) / vertPos4.w;

    position.xyz *= radius;
    gl_Position = vec4(mvp * (position + offset_position));
}
