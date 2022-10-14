#include "Geometry.hpp"
#include <assert.h>
#include <iostream>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/glm.hpp"

// Constructor
Geometry::Geometry(){

}

// Destructor
Geometry::~Geometry(){

}


// Adds a vertex and associated texture coordinate.
// Will also add a and a normal
void Geometry::AddVertex(float x, float y, float z){
	m_vertexPositions.push_back(x);
	m_vertexPositions.push_back(y);
	m_vertexPositions.push_back(z);
}

// Allows for adding one index at a time manually if 
// you know which vertices are needed to make a triangle.
void Geometry::AddIndex(unsigned int i){
    // Simple bounds check to make sure a valid index is added.
    if(i >= 0 && i <= m_vertexPositions.size()/3){
        m_indices.push_back(i);
    }else{
        std::cout << "(Geometry.cpp) ERROR, invalid index\n";
    }
}

// Retrieves a pointer to our data.
float* Geometry::GetBufferDataPtr(){
	return m_bufferData.data();
}

// Retrieves the size of our data 
unsigned int Geometry::GetBufferDataSize(){
	return m_bufferData.size();
}

// Retrieves the number of bytes of our data
unsigned int Geometry::GetBufferSizeInBytes(){
	return m_bufferData.size()*sizeof(float);
}

// Create all data
// The idea here is that we are pshing all of our data from
// each individual vertex into a single vector.
// This makes it relatively easy to then fill in a buffer
// with the corresponding vertices
void Geometry::Gen(){
	int coordsPos =0;
	for(int i =0; i < m_vertexPositions.size()/3; ++i){
	// First vertex
		// vertices
		m_bufferData.push_back(m_vertexPositions[i*3+ 0]);
		m_bufferData.push_back(m_vertexPositions[i*3+ 1]);
		m_bufferData.push_back(m_vertexPositions[i*3+ 2]);
	}
}

// The big trick here, is that when we make a triangle
// We also need to update our m_normals, tangents, and bi-tangents.
void Geometry::MakeTriangle(unsigned int vert0, unsigned int vert1, unsigned int vert2){
	m_indices.push_back(vert0);	
	m_indices.push_back(vert1);	
	m_indices.push_back(vert2);	

	// Look up the actual vertex positions
	glm::vec3 pos0(m_vertexPositions[vert0*3 +0], m_vertexPositions[vert0*3 + 1], m_vertexPositions[vert0*3 + 2]); 
	glm::vec3 pos1(m_vertexPositions[vert1*3 +0], m_vertexPositions[vert1*3 + 1], m_vertexPositions[vert1*3 + 2]); 
	glm::vec3 pos2(m_vertexPositions[vert2*3 +0], m_vertexPositions[vert2*3 + 1], m_vertexPositions[vert2*3 + 2]); 

	// Now create an edge
	// With two edges
	// This section is inspired by: https://learnopengl.com/Advanced-Lighting/Normal-Mapping
	glm::vec3 edge0 = pos1 - pos0;
	glm::vec3 edge1 = pos2 - pos0;
}

// Retrieves the number of indices that we have.
unsigned int Geometry::GetIndicesSize(){
	return m_indices.size();
}

// Retrieves a pointer to the indices that we have
unsigned int* Geometry::GetIndicesDataPtr(){
	return m_indices.data();
}
