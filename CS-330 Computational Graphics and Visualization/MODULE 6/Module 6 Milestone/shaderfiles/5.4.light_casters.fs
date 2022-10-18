#version 330 core
out vec4 FragColor;

#define NUM_OF_LIGHTS 4

// Direction Light
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// pointLights
struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

// SpotLight
struct SpotLight {
    vec3 direction;
    vec3 position;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};



in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoords;  

uniform vec3 viewPos;
uniform vec3 lightColor;
uniform float shininess;
uniform sampler2D texture1;
uniform PointLight pointLights[NUM_OF_LIGHTS];
uniform DirLight dirLight;
uniform SpotLight spotLight;


vec3 CreateDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CreatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CreateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = CreateDirLight( dirLight, norm, viewDir);

    for (int i = 0; i < NUM_OF_LIGHTS; i++) {
        result += CreatePointLight(pointLights[i], norm, FragPos, viewDir);
    }

    result += CreateSpotLight( spotLight, norm, FragPos, viewDir);
   
    FragColor = vec4(result, 1.0) * texture(texture1, TexCoords);
}

// Function for creating directional light
vec3 CreateDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize( -light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect( -lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    vec3 ambient = light.ambient * lightColor;
    vec3 diffuse = light.diffuse * diff * lightColor;
    vec3 specular = light.specular * spec * lightColor;

    return (ambient + diffuse + specular);
}

// Function for creating positional lighting
vec3 CreatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize( -light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect( -lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * lightColor;
    vec3 diffuse = light.diffuse * diff * lightColor;
    vec3 specular = light.specular * spec * lightColor;
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}
vec3 CreateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize( -light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect( -lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * (distance * distance));

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient = light.ambient * lightColor;
    vec3 diffuse = light.diffuse * diff * lightColor;
    vec3 specular = light.specular * spec * lightColor;
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}


