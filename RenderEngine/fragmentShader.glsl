#version 330 core

out vec4 FragColor;

uniform float variableColorG;

in vec4 vertexColor;

void main()
{
   FragColor = vec4(vertexColor.r, variableColorG, vertexColor.b, vertexColor.a);
}