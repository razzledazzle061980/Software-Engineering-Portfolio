#version 440 core
out vec4 FragColor;

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic
};

#define NUM_LIGHTS 3

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoords;  

uniform vec3 viewPos;
uniform Light Light
uniform sampler2D texture1;
uniform float reflective;

void main()

    // Ambient
    // --------------------------------------------
    vec3 ambient = light.ambient * texture(texture1, TexCoords).rgb;

    // Diffuse
    // --------------------------------------------
    vec3 norm = nomralize(Normal);
    vec3 lightDir = nomralize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff;

    // Specular
    // --------------------------------------------
    vec3 viewDir = nomralize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), reflective);
    vec3 specular = light.specular * spec;

    // Spotlight (Edges)
    // --------------------------------------------
    float theta = dot(lightDir, nomralize(-light.direction));
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;

    // Attenuation
    // --------------------------------------------
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 results = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

}


