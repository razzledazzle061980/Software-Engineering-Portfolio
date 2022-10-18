#version 330 core
out vec4 FragColor;

struct Light {
    vec3 pos;
    vec3 color;
    float intensity;
};

#define NUM_LIGHTS 2

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoords;  

uniform vec3 viewPos;
uniform sampler2D texture1;
uniform Light lights[NUM_LIGHTS];

vec3 CalcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{   vec3 result;
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    for(int i = 0; i < NUM_LIGHTS; i++)
        result += CalcLight(lights[i], norm, FragPos, viewDir);
    
    FragColor = vec4(result, 1.0);
}

vec3 CalcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    // ambient
    float ambientStrength = light.intensity;
    vec3 ambient = light.intensity * light.color * vec3(texture(texture1, TexCoords));
  	
    // diffuse 
    vec3 lightDir = normalize(light.pos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = (diff * light.color * vec3(texture(texture1, TexCoords)));
    
    // specular
    //float theta = dot(lightDir, normalize(-light.direction));
    //float epsilon = light.cutOff - light.outerCutOff;
    //float strength = clamp((theta - light.outerCutOff) / epsilon, )
    float specularStrength = light.intensity;
    
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.intensity * (spec * light.color * vec3(texture(texture1, TexCoords)));  
      

    return (ambient + diffuse + specular);
}