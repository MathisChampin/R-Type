#ifndef OPTIONS_MENU_HPP
#define OPTIONS_MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <optional>
#include "client/TcpClient.hpp"

class OptionsMenu
{
public:
    OptionsMenu(sf::RenderWindow &window);

    void handleEvent(const sf::Event &event);
    void update();
    void render();
    void connectTcpClient(const std::string& ipAddress, const std::string& port);

    std::optional<std::string> creatorIp;

private:
    sf::RenderWindow &m_window;
    sf::Font m_font;
    sf::Text m_titleText;
    sf::Text m_volumeText;
    sf::RectangleShape m_volumeBarBackground;
    sf::RectangleShape m_volumeBarForeground;
    float m_volume;
    sf::Music m_music;

    // Client TCP (maintenant optionnel)
    std::optional<NmpClient::TcpClient> m_tcpClient;

    // Lobby Management
    std::vector<sf::Text> m_buttons;
    int m_selectedButton;
    sf::Text m_lobbyListText;
    void setupButtons();

    // Lobby Name Input
    std::string m_lobbyNameInput;
    sf::Text m_lobbyNameText;

    // IP Address Input
    std::string m_ipAddressInput;
    sf::Text m_ipAddressText;
    sf::RectangleShape m_ipAddressInputBorder;

    // Port Input
    std::string m_portInput;
    sf::Text m_portText;
    sf::RectangleShape m_portInputBorder;

    // Chat
    bool m_isChatOpen;
    bool m_isChatInputSelected;
    sf::Text m_chatInput;
    std::string m_chatInputString;
    sf::RectangleShape m_chatInputBorder;
    sf::Text m_chatHistoryText;
    std::vector<std::string> m_chatHistory;
    sf::Clock m_chatUpdateClock;

    // Pour la gestion du curseur
    bool m_cursorVisible;
    sf::Clock m_cursorClock;

    // Etat de la connexion
    bool m_isConnecting;

    // Lobby configuration
    int m_difficulty; // 0: Easy, 1: Medium, 2: Hard
    bool m_friendlyFire;
    sf::Text m_easyButton;
    sf::Text m_mediumButton;
    sf::Text m_hardButton;
    sf::Text m_friendlyFireText;
    sf::RectangleShape m_friendlyFireCheckBox;
    bool m_friendlyFireCheckBoxSelected;
    sf::RectangleShape m_optionsBackground;
    sf::RectangleShape m_optionsBorder;   
    sf::Text m_optionsText;         

    // Network Actions
    void createLobby();
    void joinLobby();
    void leaveLobby();
    void listLobbies();
    void sendMessage();
    void getChatHistory();
    void updateChatHistory(const std::string& chatHistory);
    int start_udp();
};

#endif // OPTIONS_MENU_HPP