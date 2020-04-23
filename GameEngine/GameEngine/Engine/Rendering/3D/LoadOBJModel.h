#ifndef LOADOBJMODEL_H
#define LOADOBJMODEL_H


#include "Mesh.h"  
#include "../../Core/Debug.h"
#include "../../FX/MaterialLoader.h"
#include <sstream>
#include "../../Math/BoundingBox.h"

class LoadOBJModel
{
public:
	LoadOBJModel();
	~LoadOBJModel();

	void LoadModel(const std::string& objFilePath__);
	void LoadModel(const std::string& objFilePath__, const std::string& matFilePath_);

	inline BoundingBox GetBoundingBox() { return box; }
	inline std::vector<Vertex> GetVerts() {	return meshVertices; }

	inline std::vector<int> GetIndices() { return indices; }

	inline std::vector<SubMesh> GetSubMeshes() { return subMeshes; }

	void OnDestroy();

private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords;
	std::vector<int> indices;
	std::vector<int> normalIndices;
	std::vector<int> textureIndices;
	std::vector<Vertex> meshVertices;
	std::vector<SubMesh> subMeshes;

	void PostProcessing();
	void LoadMaterial(const std::string& fileName_);
	void LoadMaterialLibrary(const std::string& matFilePath_);


	BoundingBox box;
	Material currentMaterial;
};


#endif // !LOADOBJMODEL_H