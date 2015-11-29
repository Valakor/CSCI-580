//
//  ShaderCache.cpp
//  Game-mac
//
//  Created by Matthew Pohlmann on 11/23/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#include "ShaderCache.h"
#include "Shader.h"

ShaderPtr ShaderCache::GetShader(const std::string& name) const
{
	auto shaderItr = mCache.find(name);
	if (shaderItr != mCache.end())
	{
		return shaderItr->second;
	}
	return nullptr;
}

bool ShaderCache::RegisterShader(const std::string& name, ShaderPtr shader)
{
	if (mCache.find(name) != mCache.end())
	{
		return false;
	}

	mCache[name] = shader;
	return true;
}
