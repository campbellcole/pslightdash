#version 330 core
#define PI 3.1415926535

#define A 0.5
#define B 2.0
#define D 2.0
#define K 0.5
#define C1 0
#define C2 0//((2.0 * PI) / 3.0)
#define C3 0//((4.0 * PI) / 3.0)

out vec4 FragColor;

uniform float uTime;
uniform sampler2D sample0;

in vec3 vertexColor;
in vec2 texCoord;

void main()
{
	vec4 color = vec4((A * cos(B * uTime + C1) / D + K) * vertexColor.x, (A * cos(B * uTime + C2) + K) * vertexColor.y, (A * cos(B * uTime + C3) + K) * vertexColor.z, 1.);
  FragColor = texture(sample0, texCoord * ((sin(uTime) + 1.0) / 2.0 * 5 + 1)) + color;
}