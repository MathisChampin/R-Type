#include "../include/OptionsMenu.hpp"
#include <iostream>
#include <cctype>
#include "../../server/include/Server.hpp"
#include "../../server/include/ProtocolHandler.hpp"
//#include "../../server/include/ProceduralLevel.hpp"

OptionsMenu::OptionsMenu(sf::RenderWindow &window)
    : m_window(window),
      m_font(),
      m_titleText(),
      m_volumeText(),
      m_volumeBarBackground(),
      m_volumeBarForeground(),
      m_volume(50.0f),
      m_music(),
      m_tcpClient(std::nullopt),
      m_buttons(),
      m_selectedButton(0),
      m_lobbyListText(),
      m_lobbyNameInput(""),
      m_lobbyNameText(),
      m_ipAddressInput(""),
      m_ipAddressText(),
      m_ipAddressInputBorder(),
      m_portInput("50000"),
      m_portText(),
      m_portInputBorder(),
      m_isChatOpen(false),
      m_isChatInputSelected(false),
      m_chatInput(),
      m_chatInputString(""),
      m_chatInputBorder(),
      m_chatHistoryText(),
      m_chatHistory(),
      m_chatUpdateClock(),
      m_cursorVisible(false),
      m_cursorClock(),
      m_isConnecting(false),
      m_difficulty(0),
      m_friendlyFire(false),
      m_friendlyFireCheckBoxSelected(false)
{
    // Initialisation de la police
    if (!m_font.loadFromFile("./assets/fonts/ZenDots-Regular.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
    }

    // Configuration de la musique
    m_music.setLoop(true);
    m_music.play();
    m_music.setVolume(m_volume);

    // Initialisation des boutons
    setupButtons();

    // Configuration du texte pour l'adresse IP
    m_ipAddressText.setFont(m_font);
    m_ipAddressText.setString("IP: ");
    m_ipAddressText.setCharacterSize(30);
    m_ipAddressText.setFillColor(sf::Color::White);
    m_ipAddressText.setPosition(m_window.getSize().x / 2.0f - 120, 300);

    // Configuration de la couleur des bordures des inputs
    m_ipAddressInputBorder.setFillColor(sf::Color::Transparent);
    m_ipAddressInputBorder.setOutlineColor(sf::Color::White);
    m_ipAddressInputBorder.setOutlineThickness(2);

    m_portInputBorder.setFillColor(sf::Color::Transparent);
    m_portInputBorder.setOutlineColor(sf::Color::White);
    m_portInputBorder.setOutlineThickness(2);

    // Configuration du texte pour le nom du lobby
    m_lobbyNameText.setFont(m_font);
    m_lobbyNameText.setString("Lobby: ");
    m_lobbyNameText.setCharacterSize(30);
    m_lobbyNameText.setFillColor(sf::Color::White);
    m_lobbyNameText.setPosition(m_window.getSize().x / 2.0f - 120, 400);

    // Configuration de l'input de chat
    m_chatInput.setFont(m_font);
    m_chatInput.setCharacterSize(24);
    m_chatInput.setFillColor(sf::Color::White);
    m_chatInput.setPosition(10, m_window.getSize().y - 50);

    // Configuration de la bordure de l'input de chat
    m_chatInputBorder.setSize(sf::Vector2f(m_window.getSize().x - 20, 40));
    m_chatInputBorder.setPosition(10, m_window.getSize().y - 50);
    m_chatInputBorder.setFillColor(sf::Color::Transparent);
    m_chatInputBorder.setOutlineColor(sf::Color::White);
    m_chatInputBorder.setOutlineThickness(2);

    // Configuration de l'historique du chat
    m_chatHistoryText.setFont(m_font);
    m_chatHistoryText.setCharacterSize(24);
    m_chatHistoryText.setFillColor(sf::Color::White);
    m_chatHistoryText.setPosition(10, 10);

    // Configuration de la liste des lobbies
    m_lobbyListText.setFont(m_font);
    m_lobbyListText.setCharacterSize(25);
    m_lobbyListText.setFillColor(sf::Color::White);
    m_lobbyListText.setPosition(100, 700);

    // Boutons de difficulté
    m_easyButton.setFont(m_font);
    m_easyButton.setString("Easy");
    m_easyButton.setCharacterSize(25);
    m_easyButton.setFillColor(sf::Color::Green);
    m_easyButton.setPosition(m_window.getSize().x / 2.0f - 800, 450);

    m_mediumButton.setFont(m_font);
    m_mediumButton.setString("Medium");
    m_mediumButton.setCharacterSize(25);
    m_mediumButton.setFillColor(sf::Color::White);
    m_mediumButton.setPosition(m_window.getSize().x / 2.0f - 690, 450);

    m_hardButton.setFont(m_font);
    m_hardButton.setString("Hard");
    m_hardButton.setCharacterSize(25);
    m_hardButton.setFillColor(sf::Color::White);
    m_hardButton.setPosition(m_window.getSize().x / 2.0f - 550, 450);

    // Texte et case à cocher pour le friendly fire
    m_friendlyFireText.setFont(m_font);
    m_friendlyFireText.setString("Friendly Fire:");
    m_friendlyFireText.setCharacterSize(25);
    m_friendlyFireText.setFillColor(sf::Color::White);
    m_friendlyFireText.setPosition(m_window.getSize().x / 2.0f - 700, 500);

    m_friendlyFireCheckBox.setSize(sf::Vector2f(20, 20));
    m_friendlyFireCheckBox.setPosition(m_window.getSize().x / 2.0f - 480 , 510);
    m_friendlyFireCheckBox.setFillColor(sf::Color::Transparent);
    m_friendlyFireCheckBox.setOutlineColor(sf::Color::White);
    m_friendlyFireCheckBox.setOutlineThickness(2);
    m_optionsBackground.setSize(sf::Vector2f(400, 200));
    m_optionsBackground.setPosition(m_window.getSize().x / 2.0f - 820, 350);
    m_optionsBackground.setFillColor(sf::Color::Black);

    m_optionsBorder.setSize(sf::Vector2f(400,200));
    m_optionsBorder.setPosition(m_window.getSize().x / 2.0f - 820, 350);
    m_optionsBorder.setFillColor(sf::Color::Transparent);
    m_optionsBorder.setOutlineColor(sf::Color::White);
    m_optionsBorder.setOutlineThickness(2);

    m_optionsText.setFont(m_font);
    m_optionsText.setString("Options :");
    m_optionsText.setCharacterSize(30);
    m_optionsText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = m_optionsText.getLocalBounds();
    m_optionsText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_optionsText.setPosition(m_window.getSize().x / 2.0f - 700 , 410);




    m_optionsBackgrounds.setSize(sf::Vector2f(400, 600));
    m_optionsBackgrounds.setPosition(m_window.getSize().x / 2.0f - 200, 250);
    m_optionsBackgrounds.setFillColor(sf::Color::Black);

    m_optionsBorders.setSize(sf::Vector2f(400,600));
    m_optionsBorders.setPosition(m_window.getSize().x / 2.0f - 200, 250);
    m_optionsBorders.setFillColor(sf::Color::Transparent);
    m_optionsBorders.setOutlineColor(sf::Color::White);
    m_optionsBorders.setOutlineThickness(2);



    m_optionsBackgroundd.setSize(sf::Vector2f(580, 400));
    m_optionsBackgroundd.setPosition(m_window.getSize().x / 2.0f - 900, 600);
    m_optionsBackgroundd.setFillColor(sf::Color::Black);

    m_optionsBorderd.setSize(sf::Vector2f(580,400));
    m_optionsBorderd.setPosition(m_window.getSize().x / 2.0f - 900, 600);
    m_optionsBorderd.setFillColor(sf::Color::Transparent);
    m_optionsBorderd.setOutlineColor(sf::Color::White);
    m_optionsBorderd.setOutlineThickness(2);


}

void OptionsMenu::connectTcpClient(const std::string& ipAddress, const std::string& port)
{
    m_tcpClient.emplace(ipAddress, port);
    std::cout << "Tentative de connexion à " << ipAddress << ":" << port << std::endl;
    if (m_tcpClient.has_value()) {
        std::cout << "Connexion réussie !" << std::endl;
    } else {
        std::cerr << "Échec de la connexion." << std::endl;
    }
}

void OptionsMenu::setupButtons()
{
    std::vector<std::string> buttonLabels = {"Connect", "Create a lobby", "Join a lobby", "Leave the lobby", "List lobbies"};
    float yOffset = 550;

    for (const auto &label : buttonLabels) {
        sf::Text button;
        button.setFont(m_font);
        button.setString(label);
        button.setCharacterSize(30);
        button.setFillColor(sf::Color::White);

        sf::FloatRect textRect = button.getLocalBounds();
        button.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        button.setPosition(m_window.getSize().x / 2.0f, yOffset);

        yOffset += 50;
        m_buttons.push_back(button);
    }

    if (!m_buttons.empty()) {
        m_buttons[0].setFillColor(sf::Color::Cyan);
    }
}

void OptionsMenu::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W) {
            m_isChatOpen = !m_isChatOpen;
            if (m_isChatOpen) {
                getChatHistory();
            }
        }
        if (m_isChatOpen && event.key.code == sf::Keyboard::Enter) {
            if (!m_chatInputString.empty()) {
                sendMessage();
                m_chatInputString.clear();
                m_chatInput.setString("");
            } else {
                m_isChatOpen = false;
            }
        }

        if (m_isConnecting) {
            if (event.key.code == sf::Keyboard::Up) {
                m_selectedButton = (m_selectedButton == -1) ? -2 : -1;
            } else if (event.key.code == sf::Keyboard::Down) {
                m_selectedButton = (m_selectedButton == -1) ? -2 : -1;
            } else if (event.key.code == sf::Keyboard::Tab) {
                if (event.key.shift) {
                    m_selectedButton = (m_selectedButton == -1) ? -2 : -1;
                } else {
                    m_selectedButton = (m_selectedButton == -1) ? -2 : -1;
                }
            } else if (event.key.code == sf::Keyboard::Enter) {
                m_isConnecting = false;
                m_selectedButton = 1;
                m_buttons[1].setFillColor(sf::Color::Cyan);
                m_ipAddressInputBorder.setOutlineColor(sf::Color::White);
                m_portInputBorder.setOutlineColor(sf::Color::White);
                connectTcpClient(m_ipAddressInput, m_portInput);
            }
        } else {
            if (event.key.code == sf::Keyboard::Up) {
                if (m_selectedButton > 0) {
                    m_buttons[m_selectedButton].setFillColor(sf::Color::White);
                    m_selectedButton--;
                    m_buttons[m_selectedButton].setFillColor(sf::Color::Cyan);
                }
            } else if (event.key.code == sf::Keyboard::Down) {
                if (m_selectedButton < static_cast<int>(m_buttons.size()) - 1) {
                    m_buttons[m_selectedButton].setFillColor(sf::Color::White);
                    m_selectedButton++;
                    m_buttons[m_selectedButton].setFillColor(sf::Color::Cyan);
                }
            } else if (event.key.code == sf::Keyboard::Enter && m_isChatOpen == false) {
                if (m_selectedButton == 0) {
                    m_isConnecting = true;
                    m_selectedButton = -1;
                    m_ipAddressInputBorder.setOutlineColor(sf::Color::Cyan);
                    m_buttons[0].setFillColor(sf::Color::White);
                } else if (m_selectedButton >= 1 && m_selectedButton <= 4 && m_tcpClient.has_value()) {
                    switch (m_selectedButton) {
                        case 1: createLobby(); break;
                        case 2: joinLobby(); break;
                        case 3: leaveLobby(); break;
                        case 4: listLobbies(); break;
                    }
                }
            }
        }
    }

    if (event.type == sf::Event::TextEntered) {
        if (m_isConnecting) {
            if (m_selectedButton == -1) {
                if (event.text.unicode < 128) {
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar == '\b' && !m_ipAddressInput.empty()) {
                        m_ipAddressInput.pop_back();
                    } else if (std::isdigit(enteredChar) || enteredChar == '.') {
                        m_ipAddressInput += enteredChar;
                    }
                    m_ipAddressText.setString("IP : " + m_ipAddressInput);
                }
            } else if (m_selectedButton == -2) {
                if (event.text.unicode < 128) {
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar == '\b' && !m_portInput.empty()) {
                        m_portInput.pop_back();
                    } else if (std::isdigit(enteredChar)) {
                        m_portInput += enteredChar;
                    }
                    m_portText.setString("Port : " + m_portInput);
                }
            }
        } else if (m_isChatOpen) {
            if (event.text.unicode < 128) {
                char enteredChar = static_cast<char>(event.text.unicode);
                if (enteredChar == '\b' && !m_chatInputString.empty()) {
                    m_chatInputString.pop_back();
                } else if (std::isprint(enteredChar) && enteredChar != '\b' && enteredChar != '\r') {
                    m_chatInputString += enteredChar;
                }
                m_chatInput.setString(m_chatInputString);
            }
        } else if (!m_isChatOpen && !m_isConnecting) {
            if (event.text.unicode < 128) {
                char enteredChar = static_cast<char>(event.text.unicode);
                if (enteredChar == '\b' && !m_lobbyNameInput.empty()) {
                    m_lobbyNameInput.pop_back();
} else if (std::isalnum(enteredChar) || std::isspace(enteredChar)) {
                    m_lobbyNameInput += enteredChar;
                }
                m_lobbyNameText.setString("Lobby : " + m_lobbyNameInput);
            }
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            for (size_t i = 0; i < m_buttons.size(); ++i) {
                if (m_buttons[i].getGlobalBounds().contains(mousePos)) {
                    if (m_selectedButton != -1) {
                        m_buttons[m_selectedButton].setFillColor(sf::Color::White);
                    }
                    m_selectedButton = static_cast<int>(i);
                    m_buttons[m_selectedButton].setFillColor(sf::Color::Cyan);
                    break;
                }
            }

            if (m_easyButton.getGlobalBounds().contains(mousePos)) {
                m_difficulty = 0;
                m_easyButton.setFillColor(sf::Color::Green);
                m_mediumButton.setFillColor(sf::Color::White);
                m_hardButton.setFillColor(sf::Color::White);
            } else if (m_mediumButton.getGlobalBounds().contains(mousePos)) {
                m_difficulty = 1;
                m_easyButton.setFillColor(sf::Color::White);
                m_mediumButton.setFillColor(sf::Color::Yellow);
                m_hardButton.setFillColor(sf::Color::White);
            } else if (m_hardButton.getGlobalBounds().contains(mousePos)) {
                m_difficulty = 2;
                m_easyButton.setFillColor(sf::Color::White);
                m_mediumButton.setFillColor(sf::Color::White);
                m_hardButton.setFillColor(sf::Color::Red);
            }

            if (m_friendlyFireCheckBox.getGlobalBounds().contains(mousePos)) {
                m_friendlyFire = !m_friendlyFire;
                m_friendlyFireCheckBoxSelected = m_friendlyFire;
            }
        }
    }
}

int OptionsMenu::start_udp(const NmpServer::Difficulty diff, const bool friendlyFire) {
    std::cout << "create udp" << std::endl;

    // Créer un thread pour le serveur
    std::thread serverThread([this, diff, friendlyFire]() {
        NmpServer::Server server(diff, friendlyFire);
        server.run();
    });

    // Détacher le thread pour exécution indépendante
    serverThread.detach();
    std::cout << "ca kill" << std::endl;
    return 0;
}




void OptionsMenu::createLobby()
{
    if (m_tcpClient.has_value()) {
        if (m_lobbyNameInput.empty()) {
            m_lobbyListText.setString("Erreur : lobby name is empty.");
            return;
        }

        std::string lobbyNameCopy = m_lobbyNameInput;
        std::string difficultyStr = std::to_string(m_difficulty);
        std::string friendlyFireStr = m_friendlyFire ? "1" : "0";
        bool ff{false};
        m_tcpClient.value().send("CREATE_LOBBY " + lobbyNameCopy);

        auto response = m_tcpClient.value().receive();
        if (response.has_value()) {
            std::string responseStr = response.value();
            if (responseStr.find("ERROR:") == 0) {
                m_lobbyListText.setString(responseStr);
            } else {
                    m_lobbyListText.setString("Lobby created successfully.");
                    m_lobbyNameInput.clear();
                if (friendlyFireStr == "1")
                    ff = true;
                if (difficultyStr == "Easy")
                    start_udp(NmpServer::Difficulty::Easy, ff);
                else if (difficultyStr == "Meduim")
                    start_udp(NmpServer::Difficulty::Medium, ff);
                else
                    start_udp(NmpServer::Difficulty::Hard, ff);
            }
        } else {
            m_lobbyListText.setString("Error create lobby.");
        }
    } else {
        m_lobbyListText.setString("Error: TCP client not initialized.");
    }
}

void OptionsMenu::joinLobby() {
    if (m_tcpClient.has_value()) {
        if (m_lobbyNameInput.empty()) {
            m_lobbyListText.setString("Erreur : le nom du lobby est vide.");
            return;
        }

        std::string lobbyNameCopy = m_lobbyNameInput;
        m_tcpClient.value().send("JOIN_LOBBY " + lobbyNameCopy);

        auto joinResponse = m_tcpClient.value().receive();
        if (joinResponse.has_value()) {
            std::string joinResponseStr = joinResponse.value();

            if (joinResponseStr.find("ERROR:") == 0) {
                m_lobbyListText.setString(joinResponseStr);
            } else {
                m_lobbyListText.setString("Rejoint le lobby: " + lobbyNameCopy);
                getChatHistory();

                m_tcpClient.value().send("GET_UDP_INFO " + lobbyNameCopy);
                auto udpInfoResponse = m_tcpClient.value().receive();

                if (udpInfoResponse.has_value()) {
                    std::string udpInfoResponseStr = udpInfoResponse.value();

                    if (udpInfoResponseStr.find("ERROR:") == 0) {
                        m_lobbyListText.setString(udpInfoResponseStr);
                    } else {
                        m_lobbyListText.setString("Info UDP : " + udpInfoResponseStr);
                        creatorIp.emplace(udpInfoResponseStr);
                    }
                } else {
                    m_lobbyListText.setString("Erreur en récupérant les informations UDP.");
                }
                m_lobbyNameInput.clear();
            }
        } else {
            m_lobbyListText.setString("Erreur en rejoignant le lobby.");
        }
    } else {
        m_lobbyListText.setString("Error: TCP client not initialized.");
    }
}


void OptionsMenu::leaveLobby()
{
    if(m_tcpClient.has_value()){
        m_tcpClient.value().send("LEAVE_LOBBY");
        auto response = m_tcpClient.value().receive();
        if (response.has_value()) {
        m_lobbyListText.setString("Successfully left the lobby.");
            m_chatHistory.clear();
            m_chatHistoryText.setString("");
        } else {
            m_lobbyListText.setString("Erreur en quittant le lobby.");
        }
    } else {
        m_lobbyListText.setString("Error: TCP client not initialized.");
    }
}

void OptionsMenu::listLobbies()
{
    if(m_tcpClient.has_value()){
        m_tcpClient.value().send("LIST_LOBBIES");
        auto response = m_tcpClient.value().receive();
        if (response.has_value()) {
            std::string responseStr = response.value();
            if (responseStr.find("ERROR:") == 0) {
                m_lobbyListText.setString(responseStr);
            } else {
                m_lobbyListText.setString(response.value());
            }
        } else {
            m_lobbyListText.setString("Erreur en listant les lobbies.");
        }
    } else {
        m_lobbyListText.setString("Error: TCP client not initialized.");;
    }
}

void OptionsMenu::sendMessage()
{
    if(m_tcpClient.has_value()){
        if (!m_chatInputString.empty()) {
            m_tcpClient.value().send("SEND_MESSAGE " + m_chatInputString);
            getChatHistory();
        }
    } else {
        m_lobbyListText.setString("Error: TCP client not initialized.");    }
}

void OptionsMenu::getChatHistory()
{
    if(m_tcpClient.has_value()){
        m_tcpClient.value().send("GET_CHAT_HISTORY");
        auto response = m_tcpClient.value().receive();
        if (response.has_value()) {
            updateChatHistory(response.value());
        }
    } else {
        m_lobbyListText.setString("Error: TCP client not initialized.");    }
}

void OptionsMenu::updateChatHistory(const std::string& chatHistory)
{
    m_chatHistory.clear();

    std::istringstream iss(chatHistory);
    std::string line;
    std::getline(iss, line);

    while (std::getline(iss, line)) {
        m_chatHistory.push_back(line);
    }

    std::string chatHistoryStr;
    for (const auto& message : m_chatHistory) {
        chatHistoryStr += message + "\n";
    }
    m_chatHistoryText.setString(chatHistoryStr);
}

void OptionsMenu::update()
{
    if (m_isChatOpen) {
        if (m_chatUpdateClock.getElapsedTime().asMilliseconds() > 500) {
             getChatHistory();
             m_chatUpdateClock.restart();
        }
    }
    if (m_cursorClock.getElapsedTime().asMilliseconds() > 500) {
        m_cursorVisible = !m_cursorVisible;
        m_cursorClock.restart();
    }

    if (m_isConnecting) {
        m_ipAddressInputBorder.setOutlineColor(m_selectedButton == -1 ? sf::Color::Cyan : sf::Color::White);
        m_portInputBorder.setOutlineColor(m_selectedButton == -2 ? sf::Color::Cyan : sf::Color::White);
    } else {
        m_ipAddressInputBorder.setOutlineColor(sf::Color::White);
        m_portInputBorder.setOutlineColor(sf::Color::White);
    }
}

void OptionsMenu::render()
{
    m_window.draw(m_optionsBackgrounds);
    m_window.draw(m_optionsBorders);
    m_window.draw(m_optionsBackgroundd);
    m_window.draw(m_optionsBorderd);
    m_window.draw(m_ipAddressText);
    m_window.draw(m_lobbyNameText);
    m_window.draw(m_lobbyListText);
    m_window.draw(m_optionsBackground);
    m_window.draw(m_optionsBorder);
    m_window.draw(m_optionsText);


    sf::Vector2f ipPos = m_ipAddressText.getPosition();
    sf::Vector2f portPos = m_portText.getPosition();
    m_ipAddressInputBorder.setPosition(ipPos.x - 10, ipPos.y);
    m_ipAddressInputBorder.setSize(sf::Vector2f(m_ipAddressText.getGlobalBounds().width + 20, 40));
    m_window.draw(m_ipAddressInputBorder);

    if (m_isConnecting && m_cursorVisible) {
        sf::RectangleShape cursor;
        cursor.setSize(sf::Vector2f(2, 30)); 
        cursor.setFillColor(sf::Color::White);

        if (m_selectedButton == -1) {
            cursor.setPosition(ipPos.x + m_ipAddressText.getGlobalBounds().width + 5, ipPos.y + 5);
        } else if (m_selectedButton == -2) {
            cursor.setPosition(portPos.x + m_portText.getGlobalBounds().width + 5, portPos.y + 5);
        }
        m_window.draw(cursor);
    }

    static sf::Clock clock;
    static bool shouldMove = true;
    if (shouldMove && clock.getElapsedTime().asSeconds() > 0.00f) {
        shouldMove = false;
    }

    if (shouldMove) {
        m_titleText.setPosition(m_titleText.getPosition().x + 0, m_titleText.getPosition().y);
    }
    m_window.draw(m_titleText);

    for (auto &button : m_buttons) {
        if (shouldMove) {
            button.setPosition(button.getPosition().x + 0, button.getPosition().y);
        }
        m_window.draw(button);
    }

    m_window.draw(m_chatHistoryText);
    if (m_isChatOpen) {
        m_window.draw(m_chatInputBorder);
        m_window.draw(m_chatInput);
    }

    m_window.draw(m_easyButton);
    m_window.draw(m_mediumButton);
    m_window.draw(m_hardButton);

    m_window.draw(m_friendlyFireText);
    m_window.draw(m_friendlyFireCheckBox);
    if (m_friendlyFireCheckBoxSelected) {
        sf::RectangleShape checkMark;
        checkMark.setSize(sf::Vector2f(10, 10));
        checkMark.setPosition(m_friendlyFireCheckBox.getPosition() + sf::Vector2f(5, 5));
        checkMark.setFillColor(sf::Color::White);
        m_window.draw(checkMark);
    }
}