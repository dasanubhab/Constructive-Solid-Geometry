// ====================================================
#version 330 core

// ======================= uniform ====================
// Our light sources
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float ambientIntensity;
// Used for our specular highlights
uniform mat4 view;
// If we have texture coordinates, they are stored in this sampler.
uniform sampler2D u_DiffuseMap; 
uniform vec3 color;
// ======================= IN =========================
in vec3 myNormal; // Import our normal data
in vec2 v_texCoord; // Import our texture coordinates from vertex shader
in vec3 FragPos; // Import the fragment position

// ======================= out ========================
// The final output color of each 'fragment' from our fragment shader.
out vec4 FragColor;

// ======================= Globals ====================
// We will have another constant for specular strength
float near = 0.1;
float far = 10.0;
void main()
{
    float z_ndc = gl_FragCoord.z * 2.0 - 1.0;
    float depth = (2.0*near*far) / (far + near - z_ndc * (far -  near));
    depth/=far;
    FragColor = vec4(depth*vec3(0.5, 0.0, 0.5),1.0);
}
// ==================================================================
