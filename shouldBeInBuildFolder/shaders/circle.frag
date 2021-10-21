#version 420

out vec4 fragColor;

uniform vec3 color;
uniform vec2 center;
uniform int  radius;
uniform bool isFilled;
uniform float thickness;

float linearstep(float low, float high, float x) {
    return (clamp(x, low, high) - low ) / (high - low);
}

void main() {
    // gl_FragCoord is not normalized coords and starts at bottom left
    // expects center to be sent after conversion to bottom left coord system
    vec2 displacement = center - vec2(gl_FragCoord.xy);
    float dist_squared = dot(displacement, displacement);
    if (isFilled) {
        if (dist_squared <= radius * radius)
            fragColor = mix(vec4(color, 1.0f), gl_FragColor, smoothstep(380.25, 420.25, dist_squared));
        else
            fragColor = vec4(0.3f, 0.45f, 0.87f, 1.0f);
    } else {
        if (abs(sqrt(dist_squared) - radius) < thickness) 
            fragColor = mix(vec4(color, 1.0f), gl_FragColor, smoothstep(380.25, 420.25, dist_squared));
        else
            fragColor = vec4(0.3f, 0.45f, 0.87f, 1.0f);
    }
}