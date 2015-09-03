#version 120

attribute vec4 vPosition;
attribute vec4 vColour;

varying vec4 colour;

uniform mat4 projection;

void main()
{
	colour			= vColour;

	gl_Position 	= projection * vPosition;
}