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
uniform float fft;

in vec2 texCoord;

void main()
{
  //vec4 color = vec4((A * cos(B * uTime + C1) / D + K) * 0.5, (A * cos(B * uTime + C2) + K) * .1, (A * cos(B * uTime + C3) + K) * 1.0, 1.);
  vec2 newCoord = vec2(texCoord.x + (floor(cos(uTime) * 16) / 16), texCoord.y + (floor(sin(uTime) * 16) / 16));
  //vec2 newCoord = vec2(texCoord.x + cos(uTime), texCoord.y + sin(uTime));
  FragColor = texture(sample0, texCoord);// + color;
}