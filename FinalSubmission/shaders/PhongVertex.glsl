 #version 330 core
/// @brief the vertex passed in
layout (location = 0) in vec3 inVert;
/// @brief the normal passed in
layout (location = 2) in vec3 inNormal;

// MVP
uniform mat4 M;
uniform mat4 MV;
uniform mat4 MVP;
uniform mat3 normalMatrix;

out vec3 normal;
out vec3 fragPos;
out vec3 viewDir;

void main()
{
    gl_Position = MVP*vec4(inVert,1.0);
    normal = normalize(normalMatrix*inNormal);
    vec4 fragPos = MV*vec4(inVert,1.0);

}
