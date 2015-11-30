//
//  PerlinNoise.h
//  Game-mac
//
//  Created by Ricardo Sisnett on 11/8/15.
//

#ifndef __Game_mac__PerlinNoise__
#define __Game_mac__PerlinNoise__

#include <stdio.h>


class PerlinNoise
{
public:
    static double Noise(double x, double y, double z);
    static double NoiseSample(double x, double y, double z, int octaves, bool ridged = false);
};

#endif /* defined(__Game_mac__PerlinNoise__) */
