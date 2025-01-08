#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
    static TextureManager &getInstance()
    {
        static TextureManager instance;
        return instance;
    }

    /**
     * @brief Loads a texture from a file and caches it.
     *
     * This function attempts to load a texture from the specified file path.
     * If the texture has already been loaded and cached, it returns the cached texture.
     * Otherwise, it loads the texture from the file, caches it, and then returns it.
     *
     * @param filePath The path to the texture file to be loaded.
     * @return std::shared_ptr<sf::Texture> A shared pointer to the loaded texture.
     * @throws std::runtime_error If the texture cannot be loaded from the specified file path.
     */
    std::shared_ptr<sf::Texture> loadTexture(const std::string &filePath)
    {
        auto it = textures.find(filePath);
        if (it != textures.end())
        {
            return it->second;
        }

        auto texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(filePath))
        {
            throw std::runtime_error("Unable to load texture: " + filePath);
        }
        textures[filePath] = texture;
        return texture;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;

    TextureManager() = default;
    ~TextureManager() = default;

    TextureManager(const TextureManager &) = delete;
    TextureManager &operator=(const TextureManager &) = delete;
};

#endif // TEXTURE_MANAGER_HPP
