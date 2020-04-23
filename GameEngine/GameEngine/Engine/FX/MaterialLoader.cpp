#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader() {}

void MaterialLoader::LoadMaterial(std::string filePath_) {
	std::ifstream in(filePath_.c_str(), std::ios::in);

	if (!in) {
		Debug::Error("Cannot open MTL file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}

	std::string line;
	Material m = Material();
	std::string matName = "";

	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}

		//TODO: finish loading the relevant information
		if (line.substr(0, 4) == "\tNs ") {
			std::stringstream Ns(line.substr(4));
			float x;
			Ns >> x;
			m.shininess = x;
		}

		if (line.substr(0, 4) == "\tTr ") {
			std::stringstream Tr(line.substr(4));
			float x;
			Tr >> x;
			m.transparency = x;
		}

		if (line.substr(0, 4) == "\tKa ") {
			std::stringstream ka(line.substr(4));
			float x, y, z;
			ka >> x >> y >> z;
			m.ambient.x = x;
			m.ambient.y = y;
			m.ambient.z = z;
		}

		if (line.substr(0, 4) == "\tKd ") {
			std::stringstream kd(line.substr(4));
			float x, y, z;
			kd >> x >> y >> z;
			m.diffuse.x = x;
			m.diffuse.y = y;
			m.diffuse.z = z;
		}

		if (line.substr(0, 4) == "\tKs ") {
			std::stringstream ks(line.substr(4));
			float x, y, z;
			ks >> x >> y >> z;
			m.specular.x = x;
			m.specular.y = y;
			m.specular.z = z;
		}
	}

	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}

	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_) {
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);

	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName_, "./Resources/Textures/" + fileName_ + ".JPG");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}