#version 400

// Define the vertex attributes
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec3 normal;

// This is the output vertex colour sent to the rasterizer
out vec4 fcolour;

// These are the uniforms that are defined in the application
uniform mat4 model, view, projection;
uniform mat3 normalmatrix;
uniform uint colourmode, emitmode;
uniform vec4 lightpos;

// Global constants (for this vertex shader)
vec3 specular_albedo = vec3(1.0, 0.8, 0.6);
vec3 global_ambient = vec3(0.05, 0.05, 0.05);
int  shininess = 100;

void main() {
	vec4 position_h = vec4(position, 1.0);	

	vec4 diffuse_colour;

	if (colourmode == 1)
		diffuse_colour = colour;
	else
		diffuse_colour = vec4(0.0, 1.0, 0, 1.0);

	// Define the vertex colour
	fcolour = diffuse_colour;


	//fcolour = vec4(attenuation*(ambient + diffuse + specular) + emissive + global_ambient, 1.0);
	gl_Position = (projection * view * model) * position_h;
}

