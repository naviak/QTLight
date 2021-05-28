#pragma once
#include <string>

#include "mesh.h"
#include "vertex.h"
class MeshLoader
{
public:
	static bool loadMesh(const std::string& path, std::vector<Mesh>& vec);
};

