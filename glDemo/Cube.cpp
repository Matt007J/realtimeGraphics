#include "Cube.h"


using namespace std;
using namespace glm;


// Example data for cube model

// Packed vertex buffer for cube
static float positionArray[] = {

		// Front face (red)
		-1.0f, 1.0f, 1.0f, 1.0f,  // Vertex 0
		-1.0f, -1.0f, 1.0f, 1.0f, // Vertex 1
		1.0f, -1.0f, 1.0f, 1.0f,  // Vertex 2
		1.0f, 1.0f, 1.0f, 1.0f,   // Vertex 3

		// Back face (green)
		-1.0f, 1.0f, -1.0f, 1.0f,  // Vertex 4
		-1.0f, -1.0f, -1.0f, 1.0f, // Vertex 5
		1.0f, -1.0f, -1.0f, 1.0f,  // Vertex 6
		1.0f, 1.0f, -1.0f, 1.0f,   // Vertex 7

		// Left face (blue)
		-1.0f, 1.0f, 1.0f, 1.0f,  // Vertex 0
		-1.0f, -1.0f, 1.0f, 1.0f, // Vertex 1
		-1.0f, -1.0f, -1.0f, 1.0f, // Vertex 5
		-1.0f, 1.0f, -1.0f, 1.0f,  // Vertex 4

		// Right face (yellow)
		1.0f, 1.0f, 1.0f, 1.0f,   // Vertex 3
		1.0f, -1.0f, 1.0f, 1.0f,  // Vertex 2
		1.0f, -1.0f, -1.0f, 1.0f, // Vertex 6
		1.0f, 1.0f, -1.0f, 1.0f,  // Vertex 7

		// Top face (cyan)
		-1.0f, 1.0f, 1.0f, 1.0f,   // Vertex 0
		-1.0f, 1.0f, -1.0f, 1.0f,  // Vertex 4
		1.0f, 1.0f, -1.0f, 1.0f,   // Vertex 7
		1.0f, 1.0f, 1.0f, 1.0f,    // Vertex 3

		// Bottom face (magenta)
		-1.0f, -1.0f, 1.0f, 1.0f,  // Vertex 1
		-1.0f, -1.0f, -1.0f, 1.0f, // Vertex 5
		1.0f, -1.0f, -1.0f, 1.0f,  // Vertex 6
		1.0f, -1.0f, 1.0f, 1.0f    // Vertex 2
	};



// Packed colour buffer for principle axes model
// Modified colourArray with different colors for each face of the cube
static float colourArray[] = {

	// Front face (Red)
	1.0f, 0.0f, 0.0f, 1.0f,   // Vertex 0
	1.0f, 0.0f, 0.0f, 1.0f,   // Vertex 1
	1.0f, 0.0f, 0.0f, 1.0f,   // Vertex 2
	1.0f, 0.0f, 0.0f, 1.0f,   // Vertex 3

	// Back face (Green)
	0.0f, 1.0f, 0.0f, 1.0f,   // Vertex 4
	0.0f, 1.0f, 0.0f, 1.0f,   // Vertex 5
	0.0f, 1.0f, 0.0f, 1.0f,   // Vertex 6
	0.0f, 1.0f, 0.0f, 1.0f,   // Vertex 7

	// Left face (Blue)
	0.0f, 0.0f, 1.0f, 1.0f,   // Vertex 0
	0.0f, 0.0f, 1.0f, 1.0f,   // Vertex 4
	0.0f, 0.0f, 1.0f, 1.0f,   // Vertex 7
	0.0f, 0.0f, 1.0f, 1.0f,   // Vertex 3

	// Right face (Yellow)
	1.0f, 1.0f, 0.0f, 1.0f,   // Vertex 1
	1.0f, 1.0f, 0.0f, 1.0f,   // Vertex 5
	1.0f, 1.0f, 0.0f, 1.0f,   // Vertex 6
	1.0f, 1.0f, 0.0f, 1.0f,   // Vertex 2

	// Top face (Cyan)
	0.0f, 1.0f, 1.0f, 1.0f,   // Vertex 3
	0.0f, 1.0f, 1.0f, 1.0f,   // Vertex 2
	0.0f, 1.0f, 1.0f, 1.0f,   // Vertex 6
	0.0f, 1.0f, 1.0f, 1.0f,   // Vertex 7

	// Bottom face (Magenta)
	1.0f, 0.0f, 1.0f, 1.0f,   // Vertex 0
	1.0f, 0.0f, 1.0f, 1.0f,   // Vertex 1
	1.0f, 0.0f, 1.0f, 1.0f,   // Vertex 5
	1.0f, 0.0f, 1.0f, 1.0f    // Vertex 4
};



// Line list topology to render principle axes
static unsigned int indexArray[] = {

	// Top face
	2, 1, 0,  
	3, 2, 0,

	// Bottom face
	5, 6, 4, 
	6, 7, 4,

	// Right face
	3, 7, 2, 
	7, 6, 2,

	// Front face
	0, 4, 3,
	4, 7, 3,

	// Left face
	0, 1, 5,
	4, 0, 5,
	
	// Back face
	2, 6, 1,
	6, 5, 1
};



Cube::Cube() {

	m_numFaces = 6 * 2;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// setup vbo for position attribute
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(float), positionArray, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	// setup vbo for colour attribute
	glGenBuffers(1, &m_colourBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(float), colourArray, GL_STATIC_DRAW); 
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(4);

	// setup vbo for cube) index buffer
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), indexArray, GL_STATIC_DRAW);

	glBindVertexArray(0);
}


Cube::~Cube() {

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_colourBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
}


void Cube::render() {
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_numFaces * 3 , GL_UNSIGNED_INT, (const GLvoid*)0);
}
