#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform bool isTextured;

void main()
{
    if(isTextured) {
        // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.4);
        FragColor = texture(texture2, TexCoord);
    }
    else {
        FragColor = vec4(ourColor, 1.0);
    }
}