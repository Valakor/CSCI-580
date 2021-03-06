//
//  IcoGenerator.h
//  Game-windows
//
//  Created by Matthew Pohlmann on 11/14/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//  Adapted from http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
//

#pragma once

#include "ProceduralMesh.h"
#include <map>
#include <functional>

typedef std::function<void(std::vector<Vertex>&)> DeformationFunction;

struct IcoGenerator : public MeshGenerator
{
	IcoGenerator(size_t recursions) : mNumRecursions(recursions), mTexturePath("Textures/Default.png") { }
    IcoGenerator(size_t recursions, DeformationFunction defFunc) : mNumRecursions(recursions), mDeformationFunction(defFunc), mTexturePath("Textures/Default.png") { }
    IcoGenerator(size_t recursions, DeformationFunction defFunc, std::string texturePath) : mNumRecursions(recursions), mDeformationFunction(defFunc), mTexturePath(texturePath) { }
	virtual ~IcoGenerator() { }

	virtual void GenerateMesh(std::vector<Vertex>& verts, std::vector<GLuint>& indices, std::vector<TexturePtr>& textures, float& radius) override;

	size_t mNumRecursions;

private:

	GLuint AddVertex(Vertex& vertex);
	GLuint AddVertex(Vertex&& vertex);
	GLuint GetMiddlePoint(GLuint p1, GLuint p2);

	GLuint mCurrentIndex;
	std::map<int64_t, GLuint> mMiddlePointIndexCache;

	std::vector<Vertex>* mVerts;
	std::vector<GLuint>* mIndices;

    DeformationFunction mDeformationFunction = nullptr;

    std::string mTexturePath;
};

