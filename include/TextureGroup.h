#ifndef TEXTUREGROUP_H
#define TEXTUREGROUP_H

#include <Texture.h>
class TextureGroup {
    public:
        TextureGroup(
             char* spaceshipTexturePath,  int spaceshipTextureSteps,
             char* fireTexturePath,       int fireTextureSteps,
             char* explosionTexturePath,  int explosionTextureSteps,
             char* mapTexturePath,        int mapTextureSteps,
             char* landigSiteTexturePath, int landigSiteTextureSteps,
             char* backgroundTexturePath, int backgroundTextureSteps);

        Texture* getSpaceshipTexture()   { return spaceshipTexture; }
        Texture* getFireTexture()        { return fireTexture; }
        Texture* getExplosionTexture()   { return explosionTexture; }
        Texture* getMapTexture()         { return mapTexture; }
        Texture* getLandingSiteTexture() { return landingSiteTexture; }
        Texture* getBackgroundTexture()  { return backgroundTexture; }

    protected:

    private:
        Texture *spaceshipTexture,
                *fireTexture,
                *explosionTexture,
                *mapTexture,
                *landingSiteTexture,
                *backgroundTexture;
};

#endif // TEXTUREGROUP_H
