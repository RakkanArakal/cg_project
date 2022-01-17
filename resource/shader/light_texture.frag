
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ambientMap;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float phongShininess;
uniform float blinnShininess;

uniform bool isBlinn;

void main(){
  /*** Ambient **/
  float ambient = 0.50f;

  /*** Diffuse **/
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  float diffuse = max(dot(norm, lightDir), 0.0f);

  /*** Specular **/
  float specular = 0.0f;
  vec3 viewDir = normalize(viewPos - FragPos);
  if(!isBlinn){
    /*** Phong ***/
    vec3 reflectDir = reflect(-lightDir, norm);
    specular = pow(max(dot(viewDir, reflectDir), 0.0f), phongShininess);
  }else{
    /*** Blinn-Phong ***/
    vec3 halfwayDir = normalize(lightDir + viewDir);
    specular = pow(max(dot(norm, halfwayDir), 0.0), blinnShininess);
  }

    FragColor += ambient * texture(ambientMap, TexCoords);
    FragColor += diffuse * texture(ambientMap, TexCoords);
    FragColor += specular * vec4(vec3(0.3f), 1.0f); //假设镜面反光是白光
  //FragColor = (ambient + diffuse) * texture(ambientMap, fs_in.TexCoords) + specular * vec4(vec3(0.8f), 1.0f);
}
