#version 400

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;

uniform mat4 mViewProjection;
uniform mat4 mModel;

out vec3 normal;

void main() {
    
    normal = vec3(mModel * vec4(vNormal, 0.0));
    gl_Position = (mViewProjection * mModel) * vec4(vPosition, 1.0);
}

