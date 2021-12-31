#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform float uTime;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float fft;
uniform int pos;

out vec2 texCoord;

void main()
{
  //gl_Position = vec4(aPos.x * (sin(uTime) / 2.0 + 0.5 + 1.0), aPos.y * (sin(uTime) / 2.0 + 0.5 + 1.0), aPos.z, 1.0);
  float newX = abs(aPos.x) > aPos.x ? aPos.x + log(pos+1) : log(pos+2);
  gl_Position = projection * view * model * vec4(newX, aPos.y + fft / 300.0, aPos.z, 1.);
  texCoord = aTexCoord;
}