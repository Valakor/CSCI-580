#include "VertexArray.h"
#include <SDL/SDL.h>

VertexArrayPtr VertexArray::Create(const Vertex* verts, size_t vertCount, const GLuint* indices, size_t indexCount)
{
	return std::make_shared<VertexArray>(verts, vertCount, indices, indexCount);
}

VertexArray::VertexArray(const Vertex* verts, size_t vertCount, const GLuint* indices, size_t indexCount)
{
	mVerts.assign(verts, verts + vertCount);
	mIndices.assign(indices, indices + indexCount);
    

    calculateNormals(mVerts, mIndices);
    mVertexCount = mVerts.size();//vertCount;
    mIndexCount = mIndices.size();//indexCount;
    vertCount= mVertexCount;
    indexCount = mIndexCount;

	// Create vertex array
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// Create vertex buffer
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(Vertex), mVerts.data(), GL_STATIC_DRAW);

	// Create index buffer
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);

	// Specify the vertex attributes
	// Position is 3 floats starting at offset 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// Normal is 3 floats starting at offset of mNormal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		reinterpret_cast<void*>(offsetof(Vertex, mNormal)));

	// Color is 3 floats starting at offset of mNormal
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		reinterpret_cast<void*>(offsetof(Vertex, mColor)));

	// TexCoord is 2 floats starting at offset of mColor
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		reinterpret_cast<void*>(offsetof(Vertex, mTexCoord)));
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
}

void VertexArray::calculateNormals(std::vector<Vertex>  & verts, std::vector<GLuint>  & indices)
{
    std::vector<Vertex> newVerts;
    std::vector<GLuint> newIndices;
    newVerts.reserve(indices.size());
    newIndices.reserve(indices.size());
    
    for (int i = 0; i < indices.size(); i += 3)
    {
        Vertex v1 = verts[indices[i]];
        Vertex v2 = verts[indices[i+1]];
        Vertex v3 = verts[indices[i+2]];
        
        Vector3 v12 = v2.mPos - v1.mPos;
        Vector3 v13 = v3.mPos - v1.mPos;
        
        Vector3 n = Cross(v12, v13);
        n.Normalize();
        
        v1.mNormal = n;
        v2.mNormal = n;
        v3.mNormal = n;
        
        newVerts.push_back(v1);
        newVerts.push_back(v2);
        newVerts.push_back(v3);
        newIndices.push_back(i);
        newIndices.push_back(i+1);
        newIndices.push_back(i+2);
    }
    
    verts = std::move(newVerts);
    indices = std::move(newIndices);
    
    
}

