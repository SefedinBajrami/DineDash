#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform vec3 skyColor;

void main()
{
    // Simple gradient sky without cubemap texture
    vec3 topColor = skyColor * 1.2;
    vec3 bottomColor = skyColor * 0.6;
    float gradient = (TexCoords.y + 1.0) * 0.5;
    vec3 color = mix(bottomColor, topColor, gradient);
    FragColor = vec4(color, 1.0);
}
