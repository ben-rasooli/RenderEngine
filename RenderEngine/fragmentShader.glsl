#version 330 core

out vec4 FragColor;

struct Light {
    vec3 position;
    vec3 diffuse;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform Light light;
uniform sampler2D texture1;
uniform vec3 viewPos;

vec3 calcPositionalLight(Light light);

void main()
{
    FragColor = texture(texture1, TexCoord) * vec4(calcPositionalLight(light), 1.0);
}

vec3 calcPositionalLight(Light light)
{
    float ambientStrength = 0.1;
    float specularStrength = 0.5;

    vec3 ambient = ambientStrength * light.diffuse;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse;

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    vec3 specular = specularStrength * spec * light.diffuse;

    return (ambient + diffuse + specular);
}