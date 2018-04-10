#include "TextureLoader.h"

TextureLoader::TextureLoader() {}

void TextureLoader::loadTextures() {
    current = defaultGroup = new TextureGroup("src/images/spaceship.png",
                                              "src/images/firesprite.png",
                                              "src/images/Explosion.png",
                                              "src/images/mountain2.png",
                                              "src/images/LandingSite.png",
                                              "src/images/Earth.png");
}
