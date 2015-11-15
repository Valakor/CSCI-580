//
//  IcoGenerator.cpp
//  Game-windows
//
//  Created by Matthew Pohlmann on 11/14/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "IcoGenerator.h"

struct TriIndices
{
	GLuint v1, v2, v3;
	TriIndices(int _v1, int _v2, int _v3) : v1(_v1), v2(_v2), v3(_v3) { }
};

void IcoGenerator::GenerateMesh(std::vector<Vertex>& verts, std::vector<GLuint>& indices, std::vector<TexturePtr>& textures, float& radius)
{
	radius = 1.0f;

	mVerts = &verts;
	mIndices = &indices;

	mMiddlePointIndexCache.clear();
	verts.clear();
	indices.clear();
	mCurrentIndex = 0;

	float t = (1.0f + Math::Sqrt(5.0f)) / 2.0f;

	AddVertex(Vertex(Vector3(-1.0f, t, 0.0f), Vector2()));
	AddVertex(Vertex(Vector3(1.0f, t, 0.0f), Vector2()));
	AddVertex(Vertex(Vector3(-1.0f, -t, 0.0f), Vector2()));
	AddVertex(Vertex(Vector3(1.0f, -t, 0.0f), Vector2()));

	AddVertex(Vertex(Vector3(0.0f, -1.0f, t), Vector2()));
	AddVertex(Vertex(Vector3(0.0f, 1.0f, t), Vector2()));
	AddVertex(Vertex(Vector3(0.0f, -1.0f, -t), Vector2()));
	AddVertex(Vertex(Vector3(0.0f, 1.0f, -t), Vector2()));

	AddVertex(Vertex(Vector3(t, 0.0f, -1.0f), Vector2()));
	AddVertex(Vertex(Vector3(t, 0.0f, 1.0f), Vector2()));
	AddVertex(Vertex(Vector3(-t, 0.0f, -1.0f), Vector2()));
	AddVertex(Vertex(Vector3(-t, 0.0f, 1.0f), Vector2()));

	auto faces = std::vector<std::shared_ptr<TriIndices>>();
	faces.push_back(std::make_shared<TriIndices>(0, 11, 5));
	faces.push_back(std::make_shared<TriIndices>(0, 5, 1));
	faces.push_back(std::make_shared<TriIndices>(0, 1, 7));
	faces.push_back(std::make_shared<TriIndices>(0, 7, 10));
	faces.push_back(std::make_shared<TriIndices>(0, 10, 11));

	faces.push_back(std::make_shared<TriIndices>(1, 5, 9));
	faces.push_back(std::make_shared<TriIndices>(5, 11, 4));
	faces.push_back(std::make_shared<TriIndices>(11, 10, 2));
	faces.push_back(std::make_shared<TriIndices>(10, 7, 6));
	faces.push_back(std::make_shared<TriIndices>(7, 1, 8));

	faces.push_back(std::make_shared<TriIndices>(3, 9, 4));
	faces.push_back(std::make_shared<TriIndices>(3, 4, 2));
	faces.push_back(std::make_shared<TriIndices>(3, 2, 6));
	faces.push_back(std::make_shared<TriIndices>(3, 6, 8));
	faces.push_back(std::make_shared<TriIndices>(3, 8, 9));

	faces.push_back(std::make_shared<TriIndices>(4, 9, 5));
	faces.push_back(std::make_shared<TriIndices>(2, 4, 11));
	faces.push_back(std::make_shared<TriIndices>(6, 2, 10));
	faces.push_back(std::make_shared<TriIndices>(8, 6, 7));
	faces.push_back(std::make_shared<TriIndices>(9, 8, 1));

	for (size_t i = 0; i < mNumRecursions; ++i)
	{
		auto faces2 = std::vector<std::shared_ptr<TriIndices>>();
		for (auto tri : faces)
		{
			int a = GetMiddlePoint(tri->v1, tri->v2);
			int b = GetMiddlePoint(tri->v2, tri->v3);
			int c = GetMiddlePoint(tri->v3, tri->v1);

			faces2.push_back(std::make_shared<TriIndices>(tri->v1, a, c));
			faces2.push_back(std::make_shared<TriIndices>(tri->v2, b, a));
			faces2.push_back(std::make_shared<TriIndices>(tri->v3, c, b));
			faces2.push_back(std::make_shared<TriIndices>(a, b, c));
		}

		faces.clear();
		for (size_t j = 0; j < faces2.size(); ++j)
		{
			faces.push_back(faces2[j]);
		}
	}

	for (auto tri : faces)
	{
		indices.push_back(tri->v1);
		indices.push_back(tri->v2);
		indices.push_back(tri->v3);
	}
}

GLuint IcoGenerator::AddVertex(Vertex& vertex)
{
	vertex.mPos.Normalize();
	vertex.mNormal = vertex.mPos;
	mVerts->push_back(vertex);

	return mCurrentIndex++;
}

GLuint IcoGenerator::GetMiddlePoint(GLuint p1, GLuint p2)
{
	bool p1Smaller = p1 < p2;
	int64_t smaller = p1Smaller ? p1 : p2;
	int64_t greater = p1Smaller ? p2 : p1;
	int64_t key = (smaller << 32) + greater;

	auto found = mMiddlePointIndexCache.find(key);
	if (found != mMiddlePointIndexCache.end())
	{
		return found->second;
	}

	Vertex point1 = (*mVerts)[p1];
	Vertex point2 = (*mVerts)[p2];
	Vertex middle = Vertex((point1.mPos + point2.mPos) * 0.5f, point1.mTexCoord);

	GLuint i = AddVertex(middle);
	mMiddlePointIndexCache.insert(std::make_pair(key, i));

	return i;
}