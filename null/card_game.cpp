#include <iostream>
#include <ctime>
#include <string>

const int DECK_SIZE = 52;
const int INITIAL_COIN = 10000;
const int MIN_BET = 0;
const int MAX_BET = 5000;

void game();
void shuffle(int[]);
bool menuInput();
int playerInput(int);
void display(int[]);
void funcResult(int, int&, int[]);

int main()
{
    std::cout << "월남뽕 게임 [??] [??]\t[??]" << std::endl;
    std::cout << std::endl;
    while (menuInput())
    {
        game();
    }
}

void game()
{
    // Initialize player money
    int coin{ INITIAL_COIN };

    // Initialize the deck
    int deck[DECK_SIZE];
    for (int i = 0; i < DECK_SIZE; i++)
        deck[i] = (i % 13) + 1;

    // Random Seed Initialize
    srand(time(NULL));

    // shuffle
    shuffle(deck);

    // Draw
    int cardIndex = 0;
    int remainingCards = DECK_SIZE;
    while (1)
    {
        // Clear the screen
        system("cls");

        // Draw three cards
        remainingCards -= 3;
        int cards[3] = { deck[cardIndex++], deck[cardIndex++], deck[cardIndex++] };

        // If card A and card B are the same...
        while (cards[0] == cards[1])
        {
            if (cards[1] == 1) cards[1] += 2;
            else cards[1]--;
        }

        // Sort the cards
        if (cards[0] > cards[1])
            std::swap(cards[0], cards[1]);

        // Display the cards
        std::cout << "월남뽕 게임 ";
        display(cards);

        // Display UI
        std::cout << "내 소지금: " << coin;
        std::cout << ", 남은 카드: " << remainingCards << std::endl;

        // Get the player's bet
        int betting{ playerInput(coin) };

        // Reveal the hidden card
        std::cout << std::endl;
        std::cout << "[??] 카드의 숫자는 [" << cards[2] << "] 입니다." << std::endl;

        // Output the Result
        funcResult(betting, coin, cards);
        std::cout << std::endl;

        // Check the end std::condition
        if (coin == 0)
        {
            std::cout << "모든 돈을 잃었습니다. 다시 시작하시겠습니까?" << std::endl;
            break;
        }
        else if (remainingCards < 3)
        {
            std::cout << "남은 카드가 3장 미만입니다. 다시 시작하시겠습니까?" << std::endl;
            break;
        }
        else
        {
            std::cout << "계속하려면 아무키나 입력하세요: ";
            std::string waiting;
            std::cin >> waiting;
        }
    }
}

/* Func to shuffle cards (target array) */
void shuffle(int deck[])
{
    // Shuffle card
    for (int i = 0; i < DECK_SIZE; i++) {
        int j = rand() % DECK_SIZE;
        std::swap(deck[i], deck[j]);
    }
}

/* Menu settings */
bool menuInput()
{
    std::string sInput;
    while (1)
    {
        std::cout << "[1]시작하기, [2]그만하기, 원하는 옵션을 선택하세요: ";
        std::cin >> sInput;
        if (sInput == "1") return true;
        else if (sInput == "2") return false;
        else std::cout << "올바른 옵션을 선택하세요." << std::endl;
    }
}

/* Player input */
int playerInput(int coin)
{
    std::string str;
    int input{ 0 };
    while (1)
    {
        std::cout << "얼마를 배팅 하시겠습니까? ";
        std::cin >> str;

        try
        {
            input = stoi(str);
        }
        // std::string checking
        catch (const std::invalid_argument& e)
        {
            std::cout << "[ERROR] '문자'가 입력되었습니다." << std::endl;
            std::cout << std::endl;
            continue;
        }

        //overflow checking
        if (input < MIN_BET) std::cout << "[ERROR] '0원'이상 배팅해야 합니다." << std::endl;
        else if (input > coin) std::cout << "[ERROR] 가진 돈보다 많이 배팅할 수 없습니다." << std::endl;
        else if (input > MAX_BET) std::cout << "[ERROR] 최대 배팅금액은 '5000원'입니다." << std::endl;
        else break;
        std::cout << std::endl;
    }
    return input;
}

/* Display the cards */
void display(int cards[])
{
    // 1st-card
    if (cards[0] < 10) std::cout << "[ ";
    else std::cout << "[";
    std::cout << cards[0] << "] ";

    // 2nd-card
    if (cards[1] < 10) std::cout << "[ ";
    else std::cout << "[";
    std::cout << cards[1] << "] ";

    // Hidden
    std::cout << "\t[??]" << std::endl;
    std::cout << std::endl;
}

/* result output */
void funcResult(int betting, int &coin, int cards[])
{
    if (betting == 0)
        std::cout << "0원을 배팅했습니다. 이번 게임은 패스하겠습니다." << std::endl;
    else if (cards[0] < cards[2] && cards[2] < cards[1])
    {
        int payout = betting * 2;
        std::cout << "축하합니다. 이번 게임에서 승리하여 " << payout << "원을 벌었습니다." << std::endl;
        coin += payout;
    }
    else
    {
        std::cout << "아쉽게도 이번 게임에서 패배하여 " << betting << "원을 잃었습니다." << std::endl;
        coin = (coin - betting < 0 ? 0 : coin - betting);
    }
}