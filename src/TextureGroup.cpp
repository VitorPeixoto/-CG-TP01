#include "TextureGroup.h"
#include <SOIL.h>

TextureGroup::TextureGroup(char* spaceshipTexturePath,
             char* fireTexturePath,
             char* explosionTexturePath,
             char* mapTexturePath,
             char* landigSiteTexturePath,
             char* backgroundTexturePath)
{
    spaceshipTextureId = SOIL_load_OGL_texture(
        spaceshipTexturePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
	fireTextureId = SOIL_load_OGL_texture(
        fireTexturePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
	explosionTextureId = SOIL_load_OGL_texture(
        explosionTexturePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
	mapTextureId = SOIL_load_OGL_texture(
        mapTexturePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
	landingSiteTextureId = SOIL_load_OGL_texture(
        landigSiteTexturePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
	backgroundTextureId = SOIL_load_OGL_texture(
        backgroundTexturePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
}
