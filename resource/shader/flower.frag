 
#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
 
uniform sampler2D ambientMap;
 
void main(){
  vec4 texColor = texture2D(ambientMap, TexCoords);
  if(texColor.a < 0.1f)
    discard;
 
  FragColor = texColor;
}