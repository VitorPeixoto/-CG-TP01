#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <SOIL/SOIL.h>
#include <TextureGroup.h>

class TextureLoader {
    public:
        TextureLoader();
        void loadTextures();
        int getSpaceshipTexture()   { return current->getSpaceshipTextureId(); }
        int getFireTexture()        { return current->getFireTextureId(); }
        int getExplosionTexture()   { return current->getExplosionTextureId(); }
        int getMapTexture()         { return current->getMapTextureId(); }
        int getLandingSiteTexture() { return current->getLandingSiteTextureId(); }
        int getBackgroundTexture()  { return current->getBackgroundTextureId(); }
    protected:

    private:
        TextureGroup* defaultGroup;
        TextureGroup* current;
};
#endif // TEXTURELOADER_H
