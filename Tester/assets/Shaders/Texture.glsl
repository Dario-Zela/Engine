#type vertex
#version 330 core
		
layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec4 aColor;
	
uniform mat4 uViewProjection;

out vec2 vTexCoords;
out vec4 vColor;
void main()
{
	vTexCoords = aTexCoord;
	vColor = aColor;
	gl_Position = uViewProjection * aPosition;
}

#type fragment
#version 330 core
		
layout(location = 0) out vec4 color;

in vec2 vTexCoords;
in vec4 vColor;
//uniform sampler2D uTexture;
//uniform float uTexScale;

void main()
{
	//color = texture(uTexture, vTexCoords * uTexScale) * vColor;
	color = vColor;
}