uniform mat4 mvp;

attribute vec4 position;

varying vec4 frag_color;

void main()
{
    frag_color = vec4(0.2f, 0.2f, 0.2f, 0.2f);
    gl_Position = mvp * position;
}
