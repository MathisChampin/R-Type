#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }

    std::shared_ptr<sf::Texture> loadTexture(const std::string& filePath) {
        auto it = textures.find(filePath);
        if (it != textures.end()) {
            return it->second;
        }

        auto texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(filePath)) {
            throw std::runtime_error("Unable to load texture: " + filePath);
        }
        textures[filePath] = texture;
        return texture;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;

    TextureManager() = default;
    ~TextureManager() = default;

    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
};

#endif // TEXTURE_MANAGER_HPP
