//
//  Sound.h
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/2/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "Asset.h"

class Sound : public Asset
{
    DECL_ASSET(Sound, Asset);
    
    struct Mix_Chunk* mData;
    
public:
    
    Sound();
    virtual ~Sound();
    
    struct Mix_Chunk* GetData() { return mData; }
    
protected:
    
    virtual bool Load(const char* fileName, class AssetCache* cache) override;
    
};

DECL_PTR(Sound);
