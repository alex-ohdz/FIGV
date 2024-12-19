#version 400

in vec3 normal;

uniform bool scaled;

layout (location = 0) out vec4 fragColor;

void main() {
    
    vec3 n = normalize(normal);
    
    vec3 color;
    if (scaled) {
        color = (n + 1) / 2;
    } else {
        color = clamp(n, 0.0, 1.0);
    }
    
    fragColor = vec4(color, 1.0);
}

