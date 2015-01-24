#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;

uniform mat4 P;
uniform mat4 V;

void main(){	
	gl_Position =  P * V * vec4(vertex,1);
}

