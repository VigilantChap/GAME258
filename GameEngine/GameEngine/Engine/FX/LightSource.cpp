#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, float ambient_, float diffuse_, glm::vec3 colour_)
	: position(position_), ambient(ambient_), diffuse(diffuse_), colour(colour_)
{

}

LightSource::~LightSource() {

}