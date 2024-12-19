#version 400

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
// FIGV 1
layout (location = 2) in vec2 vTexCoord;
uniform mat4 mViewProjection;
uniform mat4 mModel;

out vec3 position;
out vec3 normal;
// FIGV 2
 out vec2 texCoord;
void main() {
    normal = vec3(mModel * vec4(vNormal, 0.0));
    position = vec3(mModel * vec4(vPosition, 1.0));
    // FIGV 3
    texCoord = vTexCoord;
    gl_Position = (mViewProjection * mModel) * vec4(vPosition, 1.0);
}

