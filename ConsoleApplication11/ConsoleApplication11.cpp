#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>

using namespace std;

// Структура для представления карты
struct Card {
    char color; // цвет карты
    int value;  // достоинство карты
};

// Функция для раздачи карт
void dealCards(int n, int numPlayers, vector<vector<Card>>& playersCards) {
    // Создаем колоду карт
    vector<Card> deck;
    for (char c : {'R', 'G', 'B', 'W'}) {
        for (int v = 1; v <= 10; v++) {
            deck.push_back({ c, v });
        }
    }

    // Перемешиваем колоду
    random_device rd;
    mt19937 g(rd());
    shuffle(deck.begin(), deck.end(), g);

    // Раздаем карты игрокам
    int cardIndex = 0;
    for (int i = 0; i < numPlayers; i++) {
        vector<Card> playerCards;
        for (int j = 0; j < n; j++) {
            playerCards.push_back(deck[cardIndex++]);
        }
        playersCards.push_back(playerCards);
    }
}

// Функция для получения карт игрока
void getCards(int playerNum, const vector<vector<Card>>& playersCards) {
    if (playerNum < 1 || playerNum > playersCards.size()) {
        cout << "Ошибка: игрок с номером " << playerNum << " не существует" << endl;
        return;
    }
    const vector<Card>& playerCards = playersCards[playerNum - 1];
    cout << playerNum << " ";
    for (const Card& card : playerCards) {
        cout << card.color << card.value << " ";
    }
    cout << endl;
}

int main() {
    vector<vector<Card>> playersCards; // хранение карт игроков

    while (true) {
        string input;
        getline(cin, input);

        stringstream ss(input);
        string command;
        ss >> command;

        if (command == "start") {
            int n, numPlayers;
            ss >> n >> numPlayers;
            if (n <= 0 || numPlayers <= 0) {
                cout << "Ошибка: некорректные аргументы команды start" << endl;
                continue;
            }
            if (n * numPlayers > 40) { // максимальное кол-во карт в колоде
                cout << "Ошибка: невозможно раздать такое количество карт" << endl;
                continue;
            }
            dealCards(n, numPlayers, playersCards);
        }
        else if (command == "get-cards") {
            int playerNum;
            ss >> playerNum;
            getCards(playerNum, playersCards);
        }
        else {
            cout << "Ошибка: неизвестная команда" << endl;
        }
    }

    return 0;
}