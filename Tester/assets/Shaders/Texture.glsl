#type vertex
#version 330 core
		
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
		
uniform mat4 uTransform;
uniform mat4 uViewProjection;

out vec2 vTexCoords;

void main()
{
	vTexCoords = aTexCoord;
	gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
}

#type fragment
#version 330 core
		
layout(location = 0) out vec4 color;

in vec2 vTexCoords;
		
uniform sampler2D uTexture;
		
void main()
{
	color = texture(uTexture, vTexCoords);
}