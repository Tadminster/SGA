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
    std::cout << "������ ���� [??] [??]\t[??]" << std::endl;
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
        std::cout << "������ ���� ";
        display(cards);

        // Display UI
        std::cout << "�� ������: " << coin;
        std::cout << ", ���� ī��: " << remainingCards << std::endl;

        // Get the player's bet
        int betting{ playerInput(coin) };

        // Reveal the hidden card
        std::cout << std::endl;
        std::cout << "[??] ī���� ���ڴ� [" << cards[2] << "] �Դϴ�." << std::endl;

        // Output the Result
        funcResult(betting, coin, cards);
        std::cout << std::endl;

        // Check the end std::condition
        if (coin == 0)
        {
            std::cout << "��� ���� �Ҿ����ϴ�. �ٽ� �����Ͻðڽ��ϱ�?" << std::endl;
            break;
        }
        else if (remainingCards < 3)
        {
            std::cout << "���� ī�尡 3�� �̸��Դϴ�. �ٽ� �����Ͻðڽ��ϱ�?" << std::endl;
            break;
        }
        else
        {
            std::cout << "����Ϸ��� �ƹ�Ű�� �Է��ϼ���: ";
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
        std::cout << "[1]�����ϱ�, [2]�׸��ϱ�, ���ϴ� �ɼ��� �����ϼ���: ";
        std::cin >> sInput;
        if (sInput == "1") return true;
        else if (sInput == "2") return false;
        else std::cout << "�ùٸ� �ɼ��� �����ϼ���." << std::endl;
    }
}

/* Player input */
int playerInput(int coin)
{
    std::string str;
    int input{ 0 };
    while (1)
    {
        std::cout << "�󸶸� ���� �Ͻðڽ��ϱ�? ";
        std::cin >> str;

        try
        {
            input = stoi(str);
        }
        // std::string checking
        catch (const std::invalid_argument& e)
        {
            std::cout << "[ERROR] '����'�� �ԷµǾ����ϴ�." << std::endl;
            std::cout << std::endl;
            continue;
        }

        //overflow checking
        if (input < MIN_BET) std::cout << "[ERROR] '0��'�̻� �����ؾ� �մϴ�." << std::endl;
        else if (input > coin) std::cout << "[ERROR] ���� ������ ���� ������ �� �����ϴ�." << std::endl;
        else if (input > MAX_BET) std::cout << "[ERROR] �ִ� ���ñݾ��� '5000��'�Դϴ�." << std::endl;
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
        std::cout << "0���� �����߽��ϴ�. �̹� ������ �н��ϰڽ��ϴ�." << std::endl;
    else if (cards[0] < cards[2] && cards[2] < cards[1])
    {
        int payout = betting * 2;
        std::cout << "�����մϴ�. �̹� ���ӿ��� �¸��Ͽ� " << payout << "���� �������ϴ�." << std::endl;
        coin += payout;
    }
    else
    {
        std::cout << "�ƽ��Ե� �̹� ���ӿ��� �й��Ͽ� " << betting << "���� �Ҿ����ϴ�." << std::endl;
        coin = (coin - betting < 0 ? 0 : coin - betting);
    }
}