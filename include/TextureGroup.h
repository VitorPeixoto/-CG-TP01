#ifndef TEXTUREGROUP_H
#define TEXTUREGROUP_H


class TextureGroup {
    public:
        TextureGroup(char* spaceshipTexturePath,
                     char* fireTexturePath,
                     char* explosionTexturePath,
                     char* mapTexturePath,
                     char* landigSiteTexturePath,
                     char* backgroundTexturePath);

        int getSpaceshipTextureId()   { return spaceshipTextureId; }
        int getFireTextureId()        { return fireTextureId; }
        int getExplosionTextureId()   { return explosionTextureId; }
        int getMapTextureId()         { return mapTextureId; }
        int getLandingSiteTextureId() { return landingSiteTextureId; }
        int getBackgroundTextureId()  { return backgroundTextureId; }

    protected:

    private:
        int spaceshipTextureId,
            fireTextureId,
            explosionTextureId,
            mapTextureId,
            landingSiteTextureId,
            backgroundTextureId;
};

#endif // TEXTUREGROUP_H
