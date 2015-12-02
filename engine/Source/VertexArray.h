// VertexArray.h
// This is a helper class to wrap OpenGL's
// Vertex array objects
// You shouldn't have to edit this file!

#pragma once
#include "Math.h"
#include <memory>
#include <vector>
#include <GL/glew.h>

// For simplicity, we assume a set vertex format
// This isn't generally a realistic assumption
struct Vertex
{
	// Position of vertex
	Vector3 mPos;
	// Vertex normal
	Vector3 mNormal;
	// Vertex color
	Vector3 mColor;
	// Texture coordinate of vertex
	Vector2 mTexCoord;

	Vertex(float x, float y, float z, float u, float v)
		:mPos(x, y, z)
		,mNormal(0.f, 0.f, 0.f)
		,mColor(Vector3(1.0f, 1.0f, 1.0f))
		,mTexCoord(u,v)
	{}

	Vertex(const Vector3& pos, const Vector2& texcoord)
		:mPos(pos)
		,mNormal(0.f, 0.f, 0.f)
		,mColor(Vector3(1.0f, 1.0f, 1.0f))
		,mTexCoord(texcoord)
	{}

	Vertex(const Vector3& pos, const Vector3& normal, const Vector2& texcoord)
		:mPos(pos)
		,mNormal(normal)
		,mColor(Vector3(1.0f, 1.0f, 1.0f))
		,mTexCoord(texcoord)
	{}
};

typedef std::shared_ptr<class VertexArray> VertexArrayPtr;

class VertexArray
{
public:
	static VertexArrayPtr Create(const Vertex* verts, size_t vertCount, const GLuint* indices, size_t indexCount);
	VertexArray(const Vertex* verts, size_t vertCount, const GLuint* indices, size_t indexCount);
    void calculateNormals(std::vector<Vertex>  & verts, std::vector<GLuint>  & indices);
public:
	~VertexArray();
	void SetActive();

	GLuint GetVertexCount() const { return static_cast<GLuint>(mVertexCount); }
	GLuint GetIndexCount() const { return static_cast<GLuint>(mIndexCount); }
	GLuint GetVertexBuffer() const { return mVertexBuffer; }
	GLuint GetIndexBuffer() const { return mIndexBuffer; }
	GLuint GetVertexArray() const { return mVertexArray; }
	const std::vector<Vertex>& GetVerts() const { return mVerts; }
	const std::vector<GLuint>& GetIndices() const { return mIndices; }
private:
	size_t mVertexCount;
	size_t mIndexCount;
	GLuint mVertexBuffer;
	GLuint mIndexBuffer;
	GLuint mVertexArray;

	std::vector<Vertex> mVerts;
	std::vector<GLuint> mIndices;
};
