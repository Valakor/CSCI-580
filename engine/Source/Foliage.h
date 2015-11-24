//
//  Foliage.h
//  Game-mac
//
//  Created by Shazzy Gustafson on 11/14/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "ProceduralMesh.h"
#include <map>

struct Foliage : public MeshGenerator
{
    Foliage(size_t foliageType) : mFoliageType(foliageType) { }
    virtual ~Foliage() { }
    
    virtual void GenerateMesh(std::vector<Vertex>& verts, std::vector<GLuint>& indices, std::vector<TexturePtr>& textures, float& radius) override;
    
    size_t mFoliageType;
    
private:
    GLuint AddVertex(Vertex vertex);
    std::vector<Vertex>* mVerts;
    std::vector<GLuint>* mIndices;
    GLuint mCurrentIndex;
    
    void createBranch(std::vector<GLuint>& indices);
    void createEverGreen(std::vector<GLuint>& indices);
    //void create
    void createPyramid(std::vector<GLuint>& indices, float scale, Vector3 pos, float height, int offset);
    void createGrassCluster(std::vector<GLuint>& indices);
};
