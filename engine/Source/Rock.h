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

struct Rock : public MeshGenerator
{
    Rock(size_t rockType) : mRockType(rockType) { }
    virtual ~Rock() { }
    
    virtual void GenerateMesh(std::vector<Vertex>& verts, std::vector<GLuint>& indices, std::vector<TexturePtr>& textures, float& radius) override;
    
    size_t mRockType;
    
private:
    GLuint AddVertex(Vertex vertex);
    std::vector<Vertex>* mVerts;
    std::vector<GLuint>* mIndices;
    GLuint mCurrentIndex;
   };
