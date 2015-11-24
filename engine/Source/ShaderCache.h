//
//  ShaderCache.h
//  Game-mac
//
//  Created by Matthew Pohlmann on 11/23/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include <unordered_map>
#include <string>

class Shader;
typedef std::shared_ptr<Shader> ShaderPtr;

class ShaderCache
{
public:

	static ShaderCache& Get()
	{
		static ShaderCache sInstance;
		return sInstance;
	}

	ShaderPtr GetShader(const std::string& name) const;
	bool RegisterShader(const std::string& name, ShaderPtr shader);

private:

	std::unordered_map<std::string, ShaderPtr> mCache;

};

