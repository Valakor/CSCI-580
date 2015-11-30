//
//  PerlinNoise.cpp
//  Game-mac
//
//  Created by Ricardo Sisnett on 11/8/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "PerlinNoise.h"
#include "Math.h"
#include <random>
#include <numeric>
#include <algorithm>
#include "Random.h"

#define FADE(t) ((t) * (t) * (t) * ((t) * ((t) * 6 - 15) + 10))
#define GET_P(i) (mGradients[((i)%256)])
#define MLERP(f, a, b)   Math::Lerp((a), (b), (f))

static double grad(int hash, double x, double y, double z)
{
    int h = hash & 15;
    double u = h<8 ? x : y,
           v = h<4 ? y : h==12||h==14 ? x : z;
    return ((h&1) == 0 ? u : -1*u) + ((h&2) == 0 ? v : -1*v);
}

PerlinNoise::PerlinNoise()
{
    mGradients =  {   151,160,137,91,90,15,
        131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
        190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
        88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
        77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
        102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
        135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
        5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
        223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
        129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
        251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
        49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
        138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
    };
}

PerlinNoise::PerlinNoise(unsigned int seed)
{
    mGradients.resize(256);
    
    // Fill with values from 0 to 255
    std::iota(mGradients.begin(), mGradients.end(), 0);
    
    // Initialize a random engine with seed
    std::default_random_engine engine(seed);
    
    // Suffle  using the above random engine
    std::shuffle(mGradients.begin(), mGradients.end(), engine);
}

double PerlinNoise::Noise(double x, double y, double z)
{
    int X = (int)floor(x) & 255,
        Y = (int)floor(y) & 255,
        Z = (int)floor(z) & 255;
    
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);
    
    double u = FADE(x),
           v = FADE(y),
           w = FADE(z);
    
    int A  = GET_P(X)+Y,
        AA = GET_P(A)+Z,
        AB = GET_P(A+1)+Z;
    
    int B  = GET_P(X+1)+Y,
        BA = GET_P(B)+Z,
        BB = GET_P(B+1)+Z;
    
    double r = MLERP(w, MLERP(v, MLERP(u, grad(GET_P(AA  ), x  , y  , z   ),
                                       grad(GET_P(BA  ), x-1, y  , z   )),
                                 MLERP(u, grad(GET_P(AB  ), x  , y-1, z   ),
                                       grad(GET_P(BB  ), x-1, y-1, z   ))),
                        MLERP(v, MLERP(u, grad(GET_P(AA+1), x  , y  , z-1 ),
                                       grad(GET_P(BA+1), x-1, y  , z-1 )),
                                 MLERP(u, grad(GET_P(AB+1), x  , y-1, z-1 ),
                                       grad(GET_P(BB+1), x-1, y-1, z-1 ))));
    return r;
}

double PerlinNoise::NoiseSample(double x, double y, double z, int octaves, bool ridged)
{
    double pn = 0.0f;
            
    for (int o=0; o < octaves; ++o)
    {
        float add = (0.5 / (1 << o))*Noise(x * (2 << o), y * (2 << o), z * (2 << o));
        pn += ( add );
    }
    
    if (ridged)
    {
        if ( pn > 0)
        {
            pn = -1*pn + 1.0f;
        }
        else
        {
            pn += 1.0f;
        }
    }
    
    pn = fmax(0.0f, fmin(1.0f, pn));
    return pn;
}
