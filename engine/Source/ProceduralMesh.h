//
//  ProceduralMesh.h
//  Game-windows
//
//  Created by Matthew Pohlmann on 11/14/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "Mesh.h"

// Use this as DECL_PROC(SelfClass, SuperClass)
#define DECL_PROC(d,s) typedef s Super; \
		std::shared_ptr<d> ThisPtr() \
		{ \
			return std::static_pointer_cast<d>(shared_from_this()); \
		} \
	public: \
		static std::shared_ptr<d> StaticCreate(MeshGeneratorPtr generator) \
		{ \
			std::shared_ptr<d> ptr = std::make_shared<d>(generator); \
			if (!ptr->Generate()) { return nullptr; } \
			return ptr; \
		} \
		virtual bool Load(const char* fileName, class AssetCache* cache) override { return true; } \
	private: \


struct MeshGenerator
{
	virtual ~MeshGenerator() { }
	virtual void GenerateMesh(std::vector<Vertex>& verts, std::vector<GLuint>& indices, std::vector<TexturePtr>& textures, float& radius);
};
DECL_PTR(MeshGenerator);


class ProceduralMesh : public Mesh
{
	DECL_PROC(ProceduralMesh, Mesh);
	ProceduralMesh() { }

public:
    
	ProceduralMesh(MeshGeneratorPtr generator) : mGenerator(generator) { }
	virtual ~ProceduralMesh() { }

	bool Generate();
	MeshGeneratorPtr GetGenerator() { return mGenerator; }

private:

	MeshGeneratorPtr mGenerator;
    
};

DECL_PTR(ProceduralMesh);
