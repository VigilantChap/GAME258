#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : currentMaterial(Material()) {
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel() {
	OnDestroy();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath__) {
	
	std::ifstream in(objFilePath__.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open OBJ file: " + objFilePath__, "LoadOBJModel.cpp", __LINE__);
			return;
	}

	std::string line;
	while (std::getline(in, line)) {
		//VERTEX DATA
		if (line.substr(0, 2) == "v ") {
			std::istringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));
		}

		//NORMAL DATA
		else if (line.substr(0, 3) == "vn ") {
			std::istringstream v(line.substr(3));
			float x, y, z;
			v >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}

		//TEXTURE COORDINATE DATA
		else if (line.substr(0, 3) == "vt ") {
			std::istringstream v(line.substr(3));
			float x, y;
			v >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}

		//FACE DATA
		else if (line.substr(0, 2) == "f ")
		{
			std::istringstream f(line.substr(2));

			int v, t, n;
			char slash;

			for (int i = 0; i < 3; i++) {
				f >> v >> slash >> t >> slash >> n;

				indices.push_back(v - 1);
				textureIndices.push_back(t - 1);
				normalIndices.push_back(n - 1);
			}
		}

		else if (line.substr(0, 7) == "usemlt ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath__, const std::string& matFilePath_){


	LoadMaterialLibrary(matFilePath_);
	LoadModel(objFilePath__);
	
}

void LoadOBJModel::OnDestroy() {
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}



void LoadOBJModel::PostProcessing() {
	for (int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.texCoords = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}

	SubMesh subMesh;
	subMesh.vertexList = meshVertices;
	subMesh.meshIndices = indices;
	subMesh.material = currentMaterial;
	subMeshes.push_back(subMesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	currentMaterial = Material();
}

void LoadOBJModel::LoadMaterial(const std::string& fileName_) {
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(fileName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_) {
	MaterialLoader::LoadMaterial(matFilePath_);
}