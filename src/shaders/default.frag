#version 330 core
out vec4 FragColor;
in vec3 fColor;
in vec2 fTexCoord;

uniform sampler2D ourTexture;
void main(){
	// FragColor = vec4(fColor,1.0);
	FragColor = texture(ourTexture,fTexCoord);
}