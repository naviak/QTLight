#version 330

in vec3 posAttr;
in vec3 normAttr;
in vec2 texAttr;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 normalMatrix;

uniform vec3 lightPos;

out vec3 lightDir;
out vec2 texCoord;
out vec3 fragPos;
out vec3 N;
out vec3 T;
out vec3 B;

void main()
{
  N = normalize(mat3(normalMatrix) * normAttr);
  T = normalize(cross(N, vec3(1.f, 1.f, 1.f)));
  B = normalize(cross(N, T));

  fragPos = vec3(model * vec4(posAttr, 1.0f));
  lightDir = normalize(lightPos);

  gl_Position = projection * view * model * vec4(posAttr, 1.0f);
  texCoord = texAttr;
}
