#pragma once
#include <string>
#include "MGDTexture.h"

#ifndef TEXTUREMANAGEMENT_H // include guard
#define TEXTUREMANAGEMENT_H
class TextureManagement
{
public:
	/*
		@brief
		create the Texture Management
		@param _AllThePaths the path of all the textures
		@param _AllTheDefaultNames the names of the textures
		@param numberOfTextures the number of the textures
	*/
	TextureManagement(std::string* _AllThePaths, std::string* _AllTheDefaultNames, int numberOfTextures);
	/*
		@brief
		delete all the textures 
	*/
	~TextureManagement();
	/*
		@brief
		delete all the textures and change with the new values
		@param other the other texture manager
	*/
	TextureManagement& operator=(TextureManagement& other);
	/*
		@brief
		return the texture based on a name
		@param name the name of the texture
		@return the texture
	*/
	MGDTexture* getTheTexture(std::string name);
	/*
		@brief
		return all the textures
		@return all the textures
	*/
	MGDTexture** GetAllTheTexture();
private:
	MGDTexture** _AllTheTexture;
	std::string* _AllTheNames;
	int numberOfTextures;
};
#endif
