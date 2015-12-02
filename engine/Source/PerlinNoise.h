//
//  PerlinNoise.h
//  Game-mac
//
//  Created by Ricardo Sisnett on 11/8/15.
//

#ifndef __Game_mac__PerlinNoise__
#define __Game_mac__PerlinNoise__

#include <stdio.h>
#include <vector>

class PerlinNoise
{
public:
    PerlinNoise();
    PerlinNoise(unsigned int seed);
    double Noise(double x, double y, double z);
    double NoiseSample(double x, double y, double z, int octaves, bool ridged = false);
private:
    std::vector<int> mGradients;
};

#endif /* defined(__Game_mac__PerlinNoise__) */
