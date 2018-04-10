#include "TextureGroup.h"
#include <SOIL.h>
#include <stdio.h>

TextureGroup::TextureGroup(
     char* spaceshipTexturePath,
       int spaceshipTextureSteps,
     char* fireTexturePath,
       int fireTextureSteps,
     char* explosionTexturePath,
       int explosionTextureSteps,
     char* mapTexturePath,
       int mapTextureSteps,
     char* landingSiteTexturePath,
       int landingSiteTextureSteps,
     char* backgroundTexturePath,
       int backgroundTextureSteps)
{
    int spaceshipTextureId = SOIL_load_OGL_texture(
        spaceshipTexturePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
	if (!spaceshipTextureId) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }
	int fireTextureId = SOIL_load_OGL_texture(
        fireTexturePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
	if (!fireTextureId) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }
	int explosionTextureId = SOIL_load_OGL_texture(
        explosionTexturePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
	if (!explosionTextureId) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }
	int mapTextureId = SOIL_load_OGL_texture(
        mapTexturePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
	if (!mapTextureId) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }
	int landingSiteTextureId = SOIL_load_OGL_texture(
        landingSiteTexturePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
	if (!landingSiteTextureId) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }
	int backgroundTextureId = SOIL_load_OGL_texture(
        backgroundTexturePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
	if (!backgroundTextureId) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    mapTexture         = new Texture(mapTextureId, mapTextureSteps);
    fireTexture        = new Texture(fireTextureId, fireTextureSteps);
    spaceshipTexture   = new Texture(spaceshipTextureId, spaceshipTextureSteps);
    explosionTexture   = new Texture(explosionTextureId, explosionTextureSteps);
    backgroundTexture  = new Texture(backgroundTextureId, backgroundTextureSteps);
    landingSiteTexture = new Texture(landingSiteTextureId, landingSiteTextureSteps);
}
