#version 330

uniform sampler2D Texture;
uniform sampler2D normalMap;

uniform vec4 diffCol;
uniform vec4 specCol;

uniform vec3 viewPos;

in vec2 texCoord;
in vec3 lightDir;
in vec3 fragPos;

in vec3 N;
in vec3 T;
in vec3 B;

uniform int isLighter;

vec3 normal()
{
  vec3 normal = texture2D(normalMap, texCoord).rgb;
  normal = normalize(normal * 2.f - 1.f);
  vec3 result = normalize(normal.x * T + normal.y * B + normal.z * N);
  return result;
}

vec4 lightning()
{
  vec3 norm = normal();

  float ka = 0.7f;
  vec4 ambCol = vec4(0, 0, 0.5f, 0.f);
  vec4 ambient = ka * ambCol;

  float diff = 2 * max(dot(norm, lightDir), 0.f);
  vec4 diffuse = diff * diffCol;

  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = 2 * pow(max(dot(viewDir, reflectDir), 0.0), 10);
  vec4 specular = spec * specCol;

  return vec4(isLighter == 0, isLighter == 0, isLighter == 0, 0.f) * (ambient + diffuse + specular)
    + vec4(isLighter, isLighter, isLighter, 0.f);
}

void main(void)
{
  gl_FragColor = lightning() * texture2D(Texture, texCoord);
}
