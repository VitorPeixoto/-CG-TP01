#include "Texture.h"

Texture::Texture(int _id, int _steps) {
    id          = _id;
    steps       = _steps;
    currentStep = 0;
}
