#ifndef OPTIONS_MENU_HPP
#define OPTIONS_MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <optional>
#include "client/TcpClient.hpp"
#include "../../server/include/ProceduralLevel.hpp"


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

    std::optional<NmpClient::TcpClient> m_tcpClient;

    std::vector<sf::Text> m_buttons;
    int m_selectedButton;
    sf::Text m_lobbyListText;
    void setupButtons();

    std::string m_lobbyNameInput;
    sf::Text m_lobbyNameText;

    std::string m_ipAddressInput;
    sf::Text m_ipAddressText;
    sf::RectangleShape m_ipAddressInputBorder;

    std::string m_portInput;
    sf::Text m_portText;
    sf::RectangleShape m_portInputBorder;

    bool m_isChatOpen;
    bool m_isChatInputSelected;
    sf::Text m_chatInput;
    std::string m_chatInputString;
    sf::RectangleShape m_chatInputBorder;
    sf::Text m_chatHistoryText;
    std::vector<std::string> m_chatHistory;
    sf::Clock m_chatUpdateClock;

    bool m_cursorVisible;
    sf::Clock m_cursorClock;

    bool m_isConnecting;

    int m_difficulty;
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
    sf::RectangleShape m_optionsBackgrounds;
    sf::RectangleShape m_optionsBorders;
    sf::RectangleShape m_optionsBackgroundd;
    sf::RectangleShape m_optionsBorderd;    

    void createLobby();
    void joinLobby();
    void leaveLobby();
    void listLobbies();
    void sendMessage();
    void getChatHistory();
    void updateChatHistory(const std::string& chatHistory);
    int start_udp(const NmpServer::Difficulty diff, const bool friendlyFire);
};

#endif // OPTIONS_MENU_HPP