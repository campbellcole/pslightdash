#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform float uTime;

out vec3 vertexColor;
out vec2 texCoord;

void main()
{
  gl_Position = vec4(aPos.x * (sin(uTime) / 2.0 + 0.5 + 1.0), aPos.y * (sin(uTime) / 2.0 + 0.5 + 1.0), aPos.z, 1.0);
	vertexColor = aColor;
  texCoord = aTexCoord;
}