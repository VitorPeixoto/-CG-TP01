#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <Texture.h>
#include <SOIL/SOIL.h>
#include <TextureGroup.h>

class TextureLoader {
    public:
        TextureLoader();
        void loadTextures();
        Texture* getSpaceshipTexture()   { return current->getSpaceshipTexture(); }
        Texture* getFireTexture()        { return current->getFireTexture(); }
        Texture* getExplosionTexture()   { return current->getExplosionTexture(); }
        Texture* getMapTexture()         { return current->getMapTexture(); }
        Texture* getLandingSiteTexture() { return current->getLandingSiteTexture(); }
        Texture* getBackgroundTexture()  { return current->getBackgroundTexture(); }
    protected:

    private:
        TextureGroup *defaultGroup, *catGroup;
        TextureGroup *current;
};
#endif // TEXTURELOADER_H
