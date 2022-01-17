
#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNor;

uniform mat4 projection;
uniform mat4 view;

uniform mat4 model;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

void main(){
  FragPos = vec3(model * vec4(aPos, 1.0f));
  Normal = mat3(transpose(inverse(model))) * aNor;
  TexCoords = aTex;
  gl_Position = projection * view * model * vec4(aPos, 1.0f);

}
