//
//  Foliage.cpp
//  Game-mac
//
//  Created by Shazzy Gustafson on 11/14/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "Rock.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

struct TriIndices
{
    GLuint v1, v2, v3;
    TriIndices(int _v1, int _v2, int _v3) : v1(_v1), v2(_v2), v3(_v3) { }
};


void Rock::GenerateMesh(std::vector<Vertex>& verts, std::vector<GLuint>& indices, std::vector<TexturePtr>& textures, float& radius)
{
    
    mVerts = &verts;
    mIndices = &indices;
    
    
    verts.clear();
    indices.clear();
    mCurrentIndex = 0;
    
    //Bottom of Rock
    AddVertex(Vertex(Vector3(1.0f, 1.0f, 0.0f), Vector2()));
    AddVertex(Vertex(Vector3(1.5 * cos(3.49066f), 1.5 *sin(3.49066f), 0.0f), Vector2()));
    AddVertex(Vertex(Vector3(cos(5.49779f), sin(5.49779f),  0.0f), Vector2()));
    AddVertex(Vertex(Vector3(2 * cos(6.02139f), 2 * sin(6.02139f) ,  0.0f), Vector2()));
    AddVertex(Vertex(Vector3(2.0f, 2.0f, 0.0f), Vector2()));
    
    AddVertex(Vertex(Vector3(0.5 * 1.0f, 0.5 * 1.0f, 1.0f), Vector2()));
    AddVertex(Vertex(Vector3(0.5 * 1.5 * cos(3.49066f), 0.5 * 1.5 *sin(3.49066f), 1.0f), Vector2()));
    AddVertex(Vertex(Vector3(0.5 * cos(5.49779f), 0.5 *  sin(5.49779f),  1.0f), Vector2()));
    AddVertex(Vertex(Vector3(0.5 * 2 * cos(6.02139f),  0.5 * 2 * sin(6.02139f) ,  1.0f), Vector2()));
    AddVertex(Vertex(Vector3(0.5 * 2.0f, 0.5 * 2.0f, 1.0f), Vector2()));

    auto faces = std::vector<std::shared_ptr<TriIndices>>();
    
    
    faces.push_back(std::make_shared<TriIndices>(0, 1, 2));
    faces.push_back(std::make_shared<TriIndices>(0, 2, 4));
    faces.push_back(std::make_shared<TriIndices>(2, 3, 4));
    
    faces.push_back(std::make_shared<TriIndices>(5, 6, 7));
    faces.push_back(std::make_shared<TriIndices>(5, 7, 9));
    faces.push_back(std::make_shared<TriIndices>(7, 8, 9));
    
    faces.push_back(std::make_shared<TriIndices>(0, 1, 6));
    faces.push_back(std::make_shared<TriIndices>(5, 6, 0));
    
    faces.push_back(std::make_shared<TriIndices>(1, 2, 7));
    faces.push_back(std::make_shared<TriIndices>(6, 7, 1));
    
    faces.push_back(std::make_shared<TriIndices>(2, 3, 8));
    faces.push_back(std::make_shared<TriIndices>(7, 8, 2));
    
    faces.push_back(std::make_shared<TriIndices>(3, 4, 9));
    faces.push_back(std::make_shared<TriIndices>(8, 9, 3));
    
    faces.push_back(std::make_shared<TriIndices>(4, 0, 5));
    faces.push_back(std::make_shared<TriIndices>(9, 5, 4));
    
    
    // finalize index buffer
    for (auto tri : faces)
    {
        indices.push_back(tri->v1);
        indices.push_back(tri->v2);
        indices.push_back(tri->v3);
    }


}

GLuint Rock::AddVertex(Vertex vertex)
{
    mVerts->push_back(vertex);
    return mCurrentIndex++;
}

