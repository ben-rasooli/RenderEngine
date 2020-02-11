#version 330 core

out vec4 FragColor;

uniform float variableColorG;
uniform float variableColorB;

in vec4 vertexColor;

void main()
{
   FragColor = vec4(vertexColor.r, variableColorG, variableColorB, vertexColor.a);
}