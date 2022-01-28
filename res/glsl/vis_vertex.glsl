#version 330 core

precision mediump float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform float uTime;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float fft;
uniform int bands;
uniform int pos;

out vec2 texCoord;

float scaleFFT() {
  if (abs(aPos.y) > aPos.y) return 0.0;
  float scaledFFT = min(pow(100 * (float(pos)/float(bands)), 1.0 / 15.0), 1) * fft;
  //float scaledFFT = min(sqrt(2 * (float(pos)/float(bands))) + 1.0, 1) * fft;
  float scale = aPos.y + scaledFFT / 50;
  //scale += pow(scale, 2.0);
  return scale;
}

void main()
{
  //gl_Position = vec4(aPos.x * (sin(uTime) / 2.0 + 0.5 + 1.0), aPos.y * (sin(uTime) / 2.0 + 0.5 + 1.0), aPos.z, 1.0);
  float newX = abs(aPos.x) > aPos.x ? log(float(pos+1)) * 3 : log(float(pos+2)) * 3;
  gl_Position = projection * view * model * vec4(newX, scaleFFT(), aPos.z, 1.);
  texCoord = aTexCoord;
}