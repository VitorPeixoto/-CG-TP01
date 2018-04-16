#include "TextureLoader.h"
#include <stdlib.h>
#define NUM_GROUPS 3
TextureLoader::TextureLoader() {}

void TextureLoader::loadTextures() {
    defaultGroup = new TextureGroup("../../src/images/spaceship.png", 1,
                                    "../../src/images/firesprite.png", 16,
                                    "../../src/images/Explosion.png", 6,
                                    "../../src/images/mountain2.png", 1,
                                    "../../src/images/LandingSite.png", 1,
                                    "../../src/images/Earth.png", 1);

    catGroup = new TextureGroup("../../src/images/nyancat.png", 6,
                                "../../src/images/RainbowAnimation.png", 11,
                                "../../src/images/NyanExplosion.png", 6,
                                "../../src/images/stripes.png", 1,
                                "../../src/images/LandingSite.png", 1,
                                "../../src/images/Cat.png", 1);

    dogGroup = new TextureGroup("../../src/images/doge.png", 6,
                                "../../src/images/DogeAnimation.png", 10,
                                //"../../src/images/firesprite.png", 16,
                                "../../src/images/DoggoExplosion.png", 6,
                                "../../src/images/grass.png", 1,
                                "../../src/images/LandingSite.png", 1,
                                "../../src/images/Doggo.png", 1);

    current = defaultGroup;//dogGroup;//catGroup;
}

void TextureLoader::randomizeTexture() {
    int group = (rand() % NUM_GROUPS);

    switch(group) {
        case 0:
            current = defaultGroup;
            return;
        case 1:
            current = catGroup;
            return;
        case 2:
            current = dogGroup;
            return;
    }
}
