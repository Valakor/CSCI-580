//
//  IcoGenerator.h
//  Game-windows
//
//  Created by Matthew Pohlmann on 11/14/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "ProceduralMesh.h"
#include <map>

struct IcoGenerator : public MeshGenerator
{
	IcoGenerator(size_t recursions) : mNumRecursions(recursions) { }
	virtual ~IcoGenerator() { }

	virtual void GenerateMesh(std::vector<Vertex>& verts, std::vector<GLuint>& indices, std::vector<TexturePtr>& textures, float& radius) override;

	size_t mNumRecursions;

private:

	GLuint AddVertex(Vertex& vertex);
	GLuint GetMiddlePoint(GLuint p1, GLuint p2);

	GLuint mCurrentIndex;
	std::map<int64_t, GLuint> mMiddlePointIndexCache;

	std::vector<Vertex>* mVerts;
	std::vector<GLuint>* mIndices;
};

