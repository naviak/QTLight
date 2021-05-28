#include "meshLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "textureLoader.h"


bool MeshLoader::loadMesh(const std::string& name, std::vector<Mesh>& vec)
{
    
    Assimp::Importer import;
    const auto* scene = import.ReadFile(std::string("Meshes/" + name + ".obj"), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        return false;
    }
    for (auto i = 0; i < scene->mNumMeshes; i++)
    {
        auto* mesh = scene->mMeshes[i];
        Mesh tmesh;
        tmesh.initialize();
        //TextureLoader::loadTexture(std::string(
        // "Textures/" + name + ".jpg"), tmesh.texture, QOpenGLTexture::Nearest);
        //TextureLoader::loadTexture(std::string(
        //   "Textures/" + name + "_NormalMap.jpg"), tmesh.normalMap, QOpenGLTexture::Nearest);
    	
        Vertices tmver;
        Indices tmin;
        for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
            Vertex vertex{};
            vertex.pos = { mesh->mVertices[j].x,
                           mesh->mVertices[j].y,
                           mesh->mVertices[j].z };

            vertex.normal = { mesh->mNormals[j].x,
                              mesh->mNormals[j].y,
                              mesh->mNormals[j].z };

            if (mesh->mTextureCoords[0]) {
                vertex.texCoord = { mesh->mTextureCoords[0][j].x,
                                    mesh->mTextureCoords[0][j].y };
            }
            tmver.push_back(vertex);
        }

        for (unsigned int t = 0; t < mesh->mNumFaces; t++) {
            const auto face = mesh->mFaces[t];
            for (unsigned int p = 0; p < face.mNumIndices; p++)
                tmin.push_back(face.mIndices[p]);
        }
        tmesh.vertices = tmver;
        tmesh.indices = tmin;
    	vec.emplace_back(tmesh);
    }

    return true;
}



