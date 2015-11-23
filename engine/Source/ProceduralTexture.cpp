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
    
    mWidth = 600;
    mHeight = 450;
    int channels = 3;
    int octaves = 8;
    unsigned char image[mWidth*mHeight*channels];
    
    int kk = 0;
    for (int y=0; y < mHeight; y++)
    {
        for (int x=0; x < mWidth; x++)
        {
            double pn = 0.0f;
            double x_f = double(x) / mWidth;
            double y_f = double(y) / mHeight;
            
            for (int o=0; o < octaves; ++o)
            {
                float add = PerlinNoise::Noise(4*x_f * (1 << o), 4*y_f * (1 << o), 0.8 * ( 1 << o));
                
                if ( add > 0)
                {
                    add = -1*add + 1.0f;
                }
                else
                {
                    add += 1.0f;
                }
                
                pn += ( add / (1 << o));
                
            }
            unsigned char color = (unsigned char) (floor(255 * pn));
            for (int c=0; c < channels; c++)
            {
                image[kk++] = color;
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
