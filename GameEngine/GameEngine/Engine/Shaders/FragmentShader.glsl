#version 450 core


struct Light{
    vec3 lightPos;
    float ambient;
    float diffuse;
    vec3 lightColour;
};

struct Material{
	float shininess;
	float transparency;
	vec3 ambient; 
	vec3 diffuse; 
	vec3 specular; 
	sampler2D diffuseMap;
};


in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

out vec4 fColour;

uniform Material material;
uniform Light light;
uniform vec3 viewPosition;

void main(){
  
	// Ambient
	vec3 ambient = light.ambient * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;

	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff*material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;

	//Specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPosition - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * material.specular) * light.lightColour;

	vec3 result = ambient + diffuse + specular;
	fColour = vec4(result, material.transparency);

}