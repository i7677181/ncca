#version 330 core
/// @brief output color calculation
in vec3 normal;
in vec3 fragPos;

out vec4 colour;

struct Lights
{
  vec4 position;
  vec4 diffuse;
  float constantAttenuation;
  float spotCosCutoff;
  float quadraticAttenuation;
  float linearAttenuation;
};

uniform Lights light;
uniform vec4 Colour;
uniform vec3 viewerPos;

void main()
{
    vec3 lightDir = normalize(light.position.xyz - fragPos.xyz);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(viewerPos - fragPos);
    float diffuseStr = dot(normal, lightDir);
    vec4 diffuse = diffuseStr*light.diffuse*Colour;

     colour = diffuse ;
}

