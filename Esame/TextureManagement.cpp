#include "TextureManagement.h"

// create an array with all the textures
TextureManagement::TextureManagement(std::string* _AllThePaths, std::string* _AllTheDefaultNames, int numberOfTextures)
	:_AllTheNames(_AllTheDefaultNames), numberOfTextures(numberOfTextures){

	_AllTheTexture = new MGDTexture*[numberOfTextures];
	for (int i = 0; i < numberOfTextures; ++i) {
		_AllTheTexture[i] = new MGDTexture(_AllThePaths[i]);
	}
}
// calls the free for each textures and delete the array of names
TextureManagement::~TextureManagement() {
	for (int i = 0; i < numberOfTextures; ++i) {
		delete _AllTheTexture[i];
		_AllTheTexture[i] = nullptr;
	}
	delete[] _AllTheTexture;
	_AllTheTexture = nullptr;
}
TextureManagement& TextureManagement::operator=(TextureManagement& other)
{
	if (this != &other) {
		for (int i = 0; i < numberOfTextures; ++i) {
			_AllTheTexture[i];
		}
		delete[] _AllTheTexture;
		_AllTheTexture = other.GetAllTheTexture();
	}
	return *this;
}
MGDTexture* TextureManagement::getTheTexture(std::string name) {
	MGDTexture* r = nullptr;
	for (int i = 0; i < numberOfTextures; ++i) {
		if (_AllTheNames[i] == name) {
			r = _AllTheTexture[i];
		}
	}
	return r;
}
MGDTexture** TextureManagement::GetAllTheTexture() {
	return _AllTheTexture;
}