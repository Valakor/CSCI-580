//
//  PerlinNoise.h
//  Game-mac
//
//  Created by Ricardo Sisnett on 11/8/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#ifndef __Game_mac__PerlinNoise__
#define __Game_mac__PerlinNoise__

#include <stdio.h>


class PerlinNoise
{
public:
    static double Noise(double x, double y, double z);
};

#endif /* defined(__Game_mac__PerlinNoise__) */
