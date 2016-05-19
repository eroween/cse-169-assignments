attribute vec4 position;
attribute vec4 normal;
attribute vec4 skin_weights;
attribute vec4 skin_indices;

varying vec4 frag_color;
varying vec3 frag_normal;
varying vec3 vertPos;


uniform mat4 mvp;
uniform mat4 m;
uniform mat4 binding_matrices[32];
uniform mat4 world_matrices[32];



void main(void)
{
    ivec4 idx = ivec4(skin_indices);
    vec4 pos = vec4(0);
    vec4 nrml = vec4(0);

    if (skin_indices.x < 32) {
        pos += skin_weights.x
                * world_matrices[idx.x]
                * binding_matrices[idx.x]
                * position;
        nrml += skin_weights.x
                * world_matrices[idx.x]
                * binding_matrices[idx.x]
                * normal;
    }
    if (skin_indices.y < 32) {
        pos += skin_weights.y
                * world_matrices[idx.y]
                * binding_matrices[idx.y]
                * position;
        nrml += skin_weights.y
                * world_matrices[idx.y]
                * binding_matrices[idx.y]
                * normal;

    }
    if (skin_indices.z < 32) {
        pos += skin_weights.z
                * world_matrices[idx.z]
                * binding_matrices[idx.z]
                * position;
        nrml += skin_weights.z
                * world_matrices[idx.z]
                * binding_matrices[idx.z]
                * normal;

    }
    if (skin_indices.w < 32) {
        pos += skin_weights.w
                * world_matrices[idx.w]
                * binding_matrices[idx.w]
                * position;
        nrml += skin_weights.w
                * world_matrices[idx.w]
                * binding_matrices[idx.w]
                * normal;
    }
    frag_color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    frag_normal = m * nrml;
    vertPos = m * pos;
    gl_Position = mvp * pos;
}
