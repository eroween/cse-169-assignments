uniform mat4 mvp;
uniform mat4 v;
uniform mat4 m;

attribute vec4 position;
attribute vec4 normal;

varying vec4 frag_color;
varying vec3 frag_normal;
varying vec3 vertPos;

void main()
{
    frag_normal = m * normal;
    frag_color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec4 vertPos4 = m * position;
    vertPos = vec3(vertPos4) / vertPos4.w;
    gl_Position = mvp * position;
}
