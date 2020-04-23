#include "TextureHandler.h"

std::unique_ptr<TextureHandler> TextureHandler::textureInstance = nullptr;
std::vector<Texture*> TextureHandler::textures = std::vector<Texture*>();

TextureHandler::TextureHandler() {
	textures.reserve(10);
}

TextureHandler::~TextureHandler() {
	OnDestroy();
}

void TextureHandler::OnDestroy() {
	if (textures.size() > 0) {
		for (auto t : textures) {
			glDeleteTextures(sizeof(GLuint), &t->textureID);
			delete t;
			t = nullptr;
		}
	}

	textures.clear();
}

TextureHandler* TextureHandler::GetInstance() {
	if (textureInstance.get() == nullptr) {
		textureInstance.reset(new TextureHandler);
	}

	return textureInstance.get();
}

void TextureHandler::CreateTexture(const std::string& textureName_, const std::string& textureFilePath_) {
	Texture* t = new Texture();
	SDL_Surface* surface = nullptr;
	surface = IMG_Load(textureFilePath_.c_str());
	if (surface == nullptr) {
		Debug::Error("Surface failed to load " + textureName_, "TextureHandler.cpp", __LINE__);
		delete t;
		t = nullptr;
		return;
	}

	glGenTextures(1, &t->textureID);
	glBindTexture(GL_TEXTURE_2D, t->textureID);

	//if the format of surface has 4 bytes, then mode = GL_RGBA. Else it's GL_RGB
	//- value ----------- condition --------------- if true -- if false ---
	int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	t->width = surface->w;
	t->height = surface->h;
	t->textureName = textureName_;
	textures.push_back(t);

	SDL_FreeSurface(surface);
	surface = nullptr;
}

const GLuint TextureHandler::GetTexture(const std::string& textureName_) {
	for (auto t : textures) {
		if (t->textureName == textureName_) return t->textureID;
	}

	return 0;
}

const Texture* TextureHandler::GetTextureData(const std::string& textureName_) {
	for (auto t : textures) {
		if (t->textureName == textureName_) return t;
	}

	return 0;
}