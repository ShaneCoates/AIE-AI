#version 400

attribute vec4 vPosition;
attribute vec2 vUV;
attribute vec4 vColour;

varying vec4 colour;
varying vec2 uv;

uniform mat4 projection;

void main()
{
	colour			= vColour;
	uv				= vUV;

	gl_Position 	= projection * vPosition;
}