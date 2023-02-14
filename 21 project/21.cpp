// 21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <vector>

using namespace std;

list<int> ShuffleDeck()
{
    /* initialize random seed: */
    srand(time(NULL));

    list<int> deck;
    deck.clear();
    for (int i = 0; i < 52; i++) 
    {
        list<int>::iterator pos = deck.begin();
        int addSpot = (floor(rand() % (deck.size() + 1)));
        for (int j = 0; j < addSpot; j++)
            pos++;
        deck.emplace(pos, i);
    }
    return deck;
}

string NameCard(int card) 
{
    int value = card % 13;
    int suit = card / 13;

    string valueStr;
    switch (value)
    {
    case 0:
        valueStr = "Ace";
        break;
    case 1:
        valueStr = "Two";
        break;
    case 2:
        valueStr = "Three";
        break;
    case 3:
        valueStr = "Four";
        break;
    case 4:
        valueStr = "Five";
        break;
    case 5:
        valueStr = "Six";
        break;
    case 6:
        valueStr = "Seven";
        break;
    case 7:
        valueStr = "Eight";
        break;
    case 8:
        valueStr = "Nine";
        break;
    case 9:
        valueStr = "Ten";
        break;
    case 10:
        valueStr = "Jack";
        break;
    case 11:
        valueStr = "Queen";
        break;
    case 12:
        valueStr = "King";
        break;
    }

    string suitStr;
    switch (suit)
    {
    case 0:
        suitStr = "Spades";
        break;
    case 1:
        suitStr = "Hearts";
        break;
    case 2:
        suitStr = "Diamonds";
        break;
    case 3:
        suitStr = "Clubs";
        break;
    }

    string midStr = " of ";

    return valueStr + midStr + suitStr;
}

int GetValue(vector<int> hand)
{
    int noAces = 0;
    int value = 0;
    for (int i = 0; i < hand.size(); i++) 
    {
        int cardValue = hand[i] % 13;
        if (cardValue == 0)
            noAces++;
        else
        {
            if (cardValue > 9)
                value += 10;             //Picture cards are worth 10
            else
                value += cardValue + 1;  //+ 1 because the card is zero indexed
        }

    }

    //Handle aces
    if (noAces > 0)
    {
        if (value + noAces + 10 <= 21) //Max one ace can be 11 without being bust
        {
            value += noAces + 10;
        }
        else
            value += noAces;
    }

    cout << "Your current hand: " << value << endl;
    return value;
}

void PrintDeck(list<int> deck)
{
    cout << "Current deck is: ";
    std::list<int>::iterator it = deck.begin();
    cout << NameCard(*it);
    it++;
    for (; it != deck.end(); ++it)
        std::cout << ", " << NameCard(*it);
    cout << endl;
}

int DrawCard(list<int> &deck) {
    int card = *deck.begin();
    deck.pop_front();
    return card;
}

bool Play21() 
{
    cout << "Welcome to 21!\n";
    list<int> deck = ShuffleDeck();
    vector<int> hand;
    //PrintDeck(deck);

    int card1 = DrawCard(deck);
    cout << "Your first card was the " << NameCard(card1) << endl;
    int card2 = DrawCard(deck);
    cout << "Your second card was the " << NameCard(card2) << endl;
    hand.push_back(card1);
    hand.push_back(card2);

    int value = GetValue(hand);

    bool ended = false;
    if (value == 21)
    {
        cout << "Wow, blackjack! Congratulations!" << endl;
        ended = true;
    }

    while (!ended)
    {
        cout << "Stick (Press s) or Twist (press t)?";
        bool valid = false;
        while (!valid)
        {
            string input;
            cin >> input;
            if (input == "s")
            {
                valid = true;
                ended = true;
                cout << "You stuck on " << value << endl;
            }
            else if (input == "t")
            {
                valid = true;
                int newCard = DrawCard(deck);
                cout << "You drew the " << NameCard(newCard) << endl;
                hand.push_back(newCard);
                value = GetValue(hand);
                if (value == 21)
                {
                    cout << "21! You win!" << endl;
                    ended = true;
                }
                else if (value > 21)
                {
                    cout << "Bust! You lose..." << endl;
                    ended = true;
                }
            }
            else
            {
                cout << "Please enter s or t" << endl;
            }
        }
    }

    cout << "Play again? (y/n)" << endl;
    bool valid = false;
    while (1)
    {
        string input;
        cin >> input;
        if (input == "y")
        {
            return true;
        }
        else if (input == "n")
        {
            return false;
        }
        else
        {
            cout << "Please enter y or n" << endl;
        }
    }
}

int main()
{
    while(Play21())
    {
        cout << endl;
    }
}

