#include "TextureLoader.h"

TextureLoader::TextureLoader() {}

void TextureLoader::loadTextures() {
    defaultGroup = new TextureGroup("src/images/spaceship.png", 1,
                                    "src/images/firesprite.png", 16,
                                    "src/images/Explosion.png", 6,
                                    "src/images/mountain2.png", 1,
                                    "src/images/LandingSite.png", 1,
                                    "src/images/Earth.png", 1);

    catGroup = new TextureGroup("src/images/nyancat.png", 6,
                                "src/images/firesprite.png", 16,
                                "src/images/Explosion.png", 6,
                                "src/images/mountain2.png", 1,
                                "src/images/LandingSite.png", 1,
                                "src/images/Cat.png", 1);

    current = defaultGroup;
}
