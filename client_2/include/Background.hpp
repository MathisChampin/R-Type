#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "./Sprite.hpp"

class Background {
    public:
        Background() = default;
        ~Background() = default;

        void initMoveParallax(Sprite &obj, Sprite &objDuplicate, float x);
        void reloadParallax(Sprite &obj, Sprite &objDuplicate, float textureWidth);
        void moveParallax();
        void drawParallax(sf::RenderWindow &w);

    private:
        // Ajout des duplicatas pour chaque sprite
        Sprite _oneBack{"./assets/background1.png", 0, 0};
        Sprite _oneBackDuplicate{"./assets/background1.png", 1920, 0};

        Sprite _twoBack{"./assets/background2.png", 0, 0};
        Sprite _twoBackDuplicate{"./assets/background2.png", 1920, 0};

        Sprite _threeBack{"./assets/background3.png", 0, 0};
        Sprite _threeBackDuplicate{"./assets/background3.png", 1920, 0};

        Sprite _fourBack{"./assets/background4.png", 0, 0};
        Sprite _fourBackDuplicate{"./assets/background4.png", 1920, 0};

        Sprite _fiveBack{"./assets/background5.png", 0, -58};
        Sprite _fiveBackDuplicate{"./assets/background5.png", 1920, -58};
};
