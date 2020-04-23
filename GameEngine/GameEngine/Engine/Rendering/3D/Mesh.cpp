#include "Mesh.h"

Mesh::Mesh(SubMesh subMesh_, GLuint shaderProgram_)
	: VAO(0), VBO(0), modelLoc(0), viewLoc(0), projLoc(0), textureLoc(0){

	shaderProgram = shaderProgram_;
	subMesh = subMesh_;
	GenerateBuffers();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0) {
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndices.size() > 0) {
		subMesh.meshIndices.clear();
	}

}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4> instances_) {
	glUniform1i(diffuseMapLoc, 0);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);
	//set materials after bind texture

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));


	glUniform3fv(viewPositionLoc, GL_FALSE, glm::value_ptr(camera_->GetPosition()));
	glUniform3fv(lightPosLoc, GL_FALSE, glm::value_ptr(camera_->GetLightSources()[0]->GetPosition()));
	glUniform1f(lightAmbientLoc, camera_->GetLightSources()[0]->GetAmbient());
	glUniform1f(lightDiffuseLoc, camera_->GetLightSources()[0]->GetDiffuse());
	glUniform3fv(lightColourLoc, GL_FALSE, glm::value_ptr(camera_->GetLightSources()[0]->GetColour()));

	glUniform1f(shininessLoc, subMesh.material.shininess);
	glUniform1f(transparencyLoc, subMesh.material.transparency);
	glUniform3fv(ambientLoc, GL_FALSE, glm::value_ptr(subMesh.material.ambient));
	glUniform3fv(diffuseLoc, GL_FALSE, glm::value_ptr(subMesh.material.diffuse));
	glUniform3fv(specularLoc, GL_FALSE, glm::value_ptr(subMesh.material.specular));

	glBindVertexArray(VAO);

	for (int i = 0; i < instances_.size(); i++)
	{
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//TEXTURE COORDS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	//COLOUR
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

	viewPositionLoc = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPosLoc = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightAmbientLoc = glGetUniformLocation(shaderProgram, "light.ambient");
	lightDiffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightColourLoc = glGetUniformLocation(shaderProgram, "light.lightColour");

	shininessLoc = glGetUniformLocation(shaderProgram, "material.shininess");
	transparencyLoc = glGetUniformLocation(shaderProgram, "material.transparency");
	ambientLoc = glGetUniformLocation(shaderProgram, "material.ambient");
	diffuseLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	specularLoc = glGetUniformLocation(shaderProgram, "material.specular");
	diffuseMapLoc = glGetUniformLocation(shaderProgram, "material.diffuseMap");
}