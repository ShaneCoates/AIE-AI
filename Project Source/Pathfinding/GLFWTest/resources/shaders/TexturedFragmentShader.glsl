##version 400

varying vec4 colour;
varying vec2 uv;

uniform sampler2D texture;

void main()
{
	gl_FragColor = texture2D(texture, uv) * colour;
}