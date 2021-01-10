#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D u_texture;

void main()
{
   //FragColor = vec4(0.1f, 0.5f, 0.9f, 1.0f);
   //FragColor = texture(u_texture, TexCoord);

   vec4 texColor = texture(u_texture, TexCoord);
   if(texColor.a <= 0.1 )
        discard;
   
   FragColor = texColor;
}