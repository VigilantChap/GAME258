#include "Model.h"
Model::Model(const std::string& objFilePath_, const std::string& matFilePath_, GLuint shaderProgram_) : subMeshes(std::vector<Mesh*>()), shaderProgram(0)
, modelInstances(std::vector<glm::mat4>()) {

	subMeshes.reserve(10);
	shaderProgram = shaderProgram_;
	modelInstances.reserve(5);
	obj = new LoadOBJModel();
	obj->LoadModel(objFilePath_, matFilePath_);
	LoadModel();
}

Model::~Model() {
	if (subMeshes.size() > 0) {
		for (auto m : subMeshes)
		{
			delete m;
			m = nullptr;
		}
		subMeshes.clear();
	}
}

void Model::Render(Camera* camera_) {

	for (auto m : subMeshes) {
		m->Render(camera_, modelInstances);
	}
}

void Model::AddMesh(Mesh* mesh_) {
	subMeshes.push_back(mesh_);
}

glm::mat4 Model::GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const {
	glm::mat4 model;
	
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_, rotation_);
	model = glm::scale(model, scale_);

	return model;
}

int Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) {
	modelInstances.push_back(GetTransform(position_, angle_, rotation_, scale_));
	return modelInstances.size() - 1;
}


void Model::UpdateInstance(int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) {
	modelInstances[index_] = GetTransform(position_, angle_, rotation_, scale_);
}

glm::mat4 Model::GetTransform(int index_) const {
	return modelInstances[index_];
}

void Model::LoadModel() {
	for (int i = 0; i < obj->GetSubMeshes().size(); i++) {
		subMeshes.push_back(new Mesh(obj->GetSubMeshes()[i], shaderProgram));
	}

	box = obj->GetBoundingBox();

	delete obj;
	obj = nullptr;
}