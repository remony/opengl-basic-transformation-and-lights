//Minimal fragment shader
#version 420

in vec4 fcolour;
in vec3 fnormal;
in vec4 fposition;
in mat3 fnormalmatrix;
flat in int femitmode;
in vec4 flightpos;

out vec4 outputColour;


uniform mat4 model, view, projection;

// Light Properties struct for storing data about lights
struct LightProperties {
	vec3 color;
	vec4 position;
};
// The limit of how many lights to have
const int maxLights = 2;
uniform LightProperties Lights[maxLights];

// Shadow colour applied with the specular
vec3 specular_albedo = vec3(0.4, 0.4, 0.4);

// Global colour override, this will change the colour of everything
vec3 global_ambient = vec3(0, 0, 0); 

// Define the shininess our shader will render things; more = darker but more shinyness; less = more light up models but less shinyness
int  shininess = 1;

struct Fog {
	float max_distance;
	float min_distance;
	vec4 colour;
};

Fog fog;


void main()
{

	// Set the light reflective colour to be the colour from the vertex shader
	vec4 light_albedo  = fcolour;
	vec3 ambient = light_albedo.xyz;

	// Create an empty vec4 for the final lighting (for when we have multiple lights)  
	vec4 finalColour = vec4(0);
		
	// Calculate diffuse and specular lighting
	
	mat4 mv_matrix = view * model; // caculate the mv matrix
	vec4 Pos = mv_matrix * fposition;	// Vertex position

	
	vec3 Nor = normalize(fnormalmatrix * fnormal); // Modifying the normals by calculating the normals times the matrix normals
	vec3 L = flightpos.xyz; // Calculate the vector from the light position to the vertex in eye space

	float distanceToLight = length(L); // Calculate the distance

	// Normalised the light position after getting distance
	L = normalize(L);					

	// Calculate the diffuse
	vec3 diffuse = max(0.0, dot(Nor, L))* light_albedo.xyz * 2;


	// Calculate Phong specular reflection
	vec3 V = normalize(-Pos.xyz); //Normalise the negative vertex position (negative: light colour infront; positive: light colour behind models)

	// Calculate the reflection of the negative distance and the combined normals
	vec3 R = reflect(-L, Nor);

	// Speculate calculation


	float specCoefficient = pow(max(0.0, dot(Pos.xyz, reflect(L, Nor))), shininess);

	vec3 specular = specCoefficient * specular_albedo * 0.03; // the power of the dot product of the reflection and normalized vertex positions powered by the shininess factor defined in the global variable then times byt he reflection

	// Calculate the attenuation factor;
	float attenuation = 1.0; 

	// Calculate our output colour
	finalColour = vec4(ambient + attenuation*(diffuse + specular) + global_ambient, 1.0);
	
	// Apply gamma correction
	finalColour = vec4 (
		pow(finalColour.x, 1.0),
		pow(finalColour.y, 1.0),
		pow(finalColour.z, 1.0),
		pow(finalColour.w, 1.0)
	);
	
	outputColour = finalColour;
	
}