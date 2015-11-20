//
//  ProceduralTexture.cpp
//  Game-mac
//
//  Created by Ricardo Sisnett on 11/18/15.
//

#include <stdio.h>
#include "ProceduralTexture.h"
#include "PerlinNoise.h"
#include "Math.h"

bool ProceduralTexture::Load(const char* fileName, class AssetCache* cache)
{
    
    mWidth = 512;
    mHeight = 512;
    int channels = 3;
    int octaves = 8;
    unsigned char image[mWidth*mHeight*channels];
    
    for (int y=0; y < mHeight; y++)
    {
        for (int x=0; x < mWidth; x++)
        {
            double pn = 0.0f;
            double x_f = double(x) / mWidth;
            double y_f = double(y) / mHeight;
            
            pn += (PerlinNoise::Noise(x_f*50, y_f*50, 0));
            
            
            unsigned char color = (unsigned char) (255 * pn);
            for (int c=0; c < channels; c++)
            {
                image[y*mWidth*channels+x*channels+c] = color;
            }
        }
    }
    
    int mode = GL_RGB;
    
    // Generate a GL texture
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, mWidth, mHeight, 0, mode,
                 GL_UNSIGNED_BYTE, image);
    
    // Use linear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Generate mip maps, just in case
    glGenerateMipmap(GL_TEXTURE_2D);
    
    return true;
}
