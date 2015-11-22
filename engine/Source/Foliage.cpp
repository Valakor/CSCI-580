//
//  Foliage.cpp
//  Game-mac
//
//  Created by Shazzy Gustafson on 11/14/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "Foliage.h"

struct TriIndices
{
    GLuint v1, v2, v3;
    TriIndices(int _v1, int _v2, int _v3) : v1(_v1), v2(_v2), v3(_v3) { }
};


void Foliage::GenerateMesh(std::vector<Vertex>& verts, std::vector<GLuint>& indices, std::vector<TexturePtr>& textures, float& radius)
{
    
    mVerts = &verts;
    mIndices = &indices;
    

    verts.clear();
    indices.clear();
    mCurrentIndex = 0;
    
    if(mFoliageType == 1) {
       createBranch(indices);
    }

    else if(mFoliageType == 2) {
       createEverGreen(indices);

    }


    

    



}

GLuint Foliage::AddVertex(Vertex vertex)
{
    mVerts->push_back(vertex);
    return mCurrentIndex++;
}

void Foliage::createBranch(std::vector<GLuint>& indices)
{
    //Pentagon
    float bx = .3f;
    float by = .3f;
    float bz = 0.0f;
    //Base
    AddVertex(Vertex(Vector3(bx * cos(0.0f), by * sin(0.0f), bz * 0.0f), Vector2()));
    AddVertex(Vertex(Vector3(bx * cos(1.25664f), by * sin(1.25664f), bz * 0.0f), Vector2()));
    AddVertex(Vertex(Vector3(bx * cos(2.51327f), by * sin(2.51327f),bz * 0.0f), Vector2()));
    AddVertex(Vertex(Vector3(bx * cos(3.76991f), by * sin(3.76991f), bz * 0.0f), Vector2()));
    AddVertex(Vertex(Vector3(bx * cos(5.02665f), by * sin(5.02665f), bz * 0.0f), Vector2()));
    
    float tx = .2f;
    float ty = .2f;
    float tz = 3.0f;
    //Top
    AddVertex(Vertex(Vector3(tx * cos(0.0f), ty * sin(0.0f), tz), Vector2()));
    AddVertex(Vertex(Vector3(tx * cos(1.25664f), ty * sin(1.25664f),tz), Vector2()));
    AddVertex(Vertex(Vector3(tx * cos(2.51327f), ty * sin(2.51327f),tz), Vector2()));
    AddVertex(Vertex(Vector3(tx * cos(3.76991f), ty * sin(3.76991f),tz), Vector2()));
    AddVertex(Vertex(Vector3(tx * cos(5.02665f), ty * sin(5.02665f),tz), Vector2()));
    
    auto faces = std::vector<std::shared_ptr<TriIndices>>();
    //Bottom
    faces.push_back(std::make_shared<TriIndices>(0, 1, 2));
    faces.push_back(std::make_shared<TriIndices>(0, 2, 3));
    faces.push_back(std::make_shared<TriIndices>(0, 3, 4));
    //Top
    faces.push_back(std::make_shared<TriIndices>(5, 6, 7));
    faces.push_back(std::make_shared<TriIndices>(5, 7, 8));
    faces.push_back(std::make_shared<TriIndices>(5, 8, 9));
    //Trunk
    faces.push_back(std::make_shared<TriIndices>(3, 9, 8));
    faces.push_back(std::make_shared<TriIndices>(3, 9, 4));
    
    faces.push_back(std::make_shared<TriIndices>(4, 5, 9));
    faces.push_back(std::make_shared<TriIndices>(4, 5, 0));
    
    faces.push_back(std::make_shared<TriIndices>(0, 6, 5));
    faces.push_back(std::make_shared<TriIndices>(0, 6, 1));
    
    faces.push_back(std::make_shared<TriIndices>(2, 6, 7));
    faces.push_back(std::make_shared<TriIndices>(2, 6, 1));
    
    faces.push_back(std::make_shared<TriIndices>(2, 7, 8));
    faces.push_back(std::make_shared<TriIndices>(2, 7, 3));
    
    // finalize index buffer
    for (auto tri : faces)
    {
        indices.push_back(tri->v1);
        indices.push_back(tri->v2);
        indices.push_back(tri->v3);
    }
    
}

void Foliage::createEverGreen(std::vector<GLuint>& indices) {
    
    int lvl = 6;
    for(int i  = 0; i < lvl; i++) {
        createPyramid(indices,  (1.7 + (i/10.0f)),  float(lvl - i), (i * 5));
    }
    
    
    
    
}

void Foliage::createPyramid(std::vector<GLuint>& indices, float scale, float pos, int offset) {
    
    float x = 1.0f * scale;
    float y = 1.0f * scale;
    float midPtX = ((-x + x) / 2.0);
    float midPtY = ((-y + y) / 2.0);
    float midPtZ = 2.0f;
    
    AddVertex(Vertex(Vector3(-x, y, pos), Vector2()));
    AddVertex(Vertex(Vector3(x, y, pos), Vector2()));
    AddVertex(Vertex(Vector3(x, -y, pos), Vector2()));
    AddVertex(Vertex(Vector3(-x, -y, pos), Vector2()));
    AddVertex(Vertex(Vector3(midPtX, midPtY, pos + midPtZ), Vector2()));
    
    auto faces = std::vector<std::shared_ptr<TriIndices>>();
    //Plane
    faces.push_back(std::make_shared<TriIndices>(0 + offset, 1 + offset, 3 + offset));
    faces.push_back(std::make_shared<TriIndices>(1 + offset, 3 + offset, 2 + offset));
    //TreeTop
    faces.push_back(std::make_shared<TriIndices>(0 + offset, 1 + offset, 4 + offset));
    faces.push_back(std::make_shared<TriIndices>(1 + offset, 2 + offset, 4 + offset));
    faces.push_back(std::make_shared<TriIndices>(2 + offset, 3 + offset, 4 + offset));
    faces.push_back(std::make_shared<TriIndices>(3 + offset, 0 + offset, 4 + offset));
    
    for (auto tri : faces)
    {
        indices.push_back(tri->v1);
        indices.push_back(tri->v2);
        indices.push_back(tri->v3);
    }
    
}

