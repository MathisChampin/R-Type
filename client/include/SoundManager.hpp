#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <iostream>
#include <memory>
#include <vector>

class SoundManager {
public:
    SoundManager() = default;

    // Load a music file
    bool loadMusic(const std::string& key, const std::string& musicFile) {
        auto music = std::make_shared<sf::Music>();
        if (!music->openFromFile(musicFile)) {
            std::cerr << "Error loading music from file: " << musicFile << std::endl;
            return false;
        }
        _musics[key] = music;
        return true;
    }

    // Play a music track
    bool playMusic(const std::string& key, bool loop = false) {
        auto it = _musics.find(key);
        if (it != _musics.end()) {
            auto& music = it->second;
            if (music->getStatus() == sf::Music::Playing) {
                music->stop(); // Ensure the music restarts if it's already playing
            }
            music->setLoop(loop);
            music->play();
            return true;
        } else {
            std::cerr << "Music key not found: " << key << std::endl;
            return false;
        }
    }

    // Pause a specific music track
    void pauseMusic(const std::string& key) {
        auto it = _musics.find(key);
        if (it != _musics.end() && it->second->getStatus() == sf::Music::Playing) {
            it->second->pause();
        } else {
            std::cerr << "Cannot pause. Music key not found or not playing: " << key << std::endl;
        }
    }

    // Stop a specific music track
    void stopMusic(const std::string& key) {
        auto it = _musics.find(key);
        if (it != _musics.end()) {
            it->second->stop();
        } else {
            std::cerr << "Music key not found: " << key << std::endl;
        }
    }

    // Stop all music tracks
    void stopAllMusic() {
        for (auto& [key, music] : _musics) {
            if (music->getStatus() == sf::Music::Playing) {
                music->stop();
            }
        }
    }

    // Set volume for a specific music track
    void setMusicVolume(const std::string& key, float volume) {
        auto it = _musics.find(key);
        if (it != _musics.end()) {
            it->second->setVolume(volume);
        } else {
            std::cerr << "Music key not found: " << key << std::endl;
        }
    }

    // Set volume for all music tracks
    void setAllMusicVolume(float volume) {
        for (auto& [key, music] : _musics) {
            music->setVolume(volume);
        }
    }

    // Load a sound buffer
    bool loadSound(const std::string& key, const std::string& soundFile) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(soundFile)) {
            std::cerr << "Error loading sound from file: " << soundFile << std::endl;
            return false;
        }
        _soundBuffers[key] = buffer;
        return true;
    }

    // Play a sound
    bool playSound(const std::string& key, bool loop = false) {
        auto it = _soundBuffers.find(key);
        if (it != _soundBuffers.end()) {
            _activeSounds.emplace_back();
            sf::Sound& sound = _activeSounds.back();
            sound.setBuffer(it->second);
            sound.setLoop(loop);
            sound.play();
            return true;
        } else {
            std::cerr << "Sound key not found: " << key << std::endl;
            return false;
        }
    }

    // Stop all sounds
    void stopAllSounds() {
        for (auto& sound : _activeSounds) {
            sound.stop();
        }
        _activeSounds.clear();
    }

    // Clean up finished sounds
    void cleanupSounds() {
        _activeSounds.erase(
            std::remove_if(
                _activeSounds.begin(),
                _activeSounds.end(),
                [](sf::Sound& sound) { return sound.getStatus() == sf::Sound::Stopped; }
            ),
            _activeSounds.end()
        );
    }

private:
    std::map<std::string, std::shared_ptr<sf::Music>> _musics;
    std::map<std::string, sf::SoundBuffer> _soundBuffers;
    std::vector<sf::Sound> _activeSounds;
};
