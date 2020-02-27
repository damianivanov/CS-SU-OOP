// Cards.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <regex> 

using namespace std;


struct Player {
    int id;
    char name[128];
};
enum Color
{
    Red=1,
    Black,
    Blue,
    White,
    Green
};
struct Card {
    int id;
    Color color;
    char name[64];

};
struct Deck {
    int player_id;
    Color color;
    int cards_ids[60];
};

Player read_File(ifstream& in, string name_of_file) //returning the first Player
{
    Player player;
    in.open(name_of_file);
    if (!in)
    {
        cout << "Something went wrong" << endl;
    }
    in.read((char*)&player, sizeof(Player));
    in.close();
    return player;
}
Player read_File(ifstream& in, string name_of_file, int index) // returning the Player on index
{
    Player player;
    in.open(name_of_file);
    if (!in)
    {
        cout << "Something went wrong" << endl;
    }
    for (size_t i = 0; i <= index; i++)
    {
        in.read((char*)&player, sizeof(Player));
    }

    in.close();
    return player;
}


void write_File(ofstream& out, string name_of_file, Player& player) //writes struct player to the file
{
    out.open(name_of_file, ios::app);
    if (!out)
    {
        cout << "Something went wrong" << endl;
    }
    out.write((char*)&player, sizeof(Player));
    out.close();
}
void write_File(ofstream& out, string name_of_file, Card& card) //writes struct card to the file
{
    out.open(name_of_file, ios::app);
    if (!out)
    {
        cout << "Something went wrong" << endl;
    }
    out.write((char*)&card, sizeof(Card));
    out.close();
}

void print_Player(Player& player)
{
    cout << player.id << "::" << player.name << endl;
}
void print_Card(Card& card)
{
    cout << card.id << "::" << card.color<< "::" <<card.name << endl;
}

unsigned int id_cards()
{
    ifstream out;
    Card card;
    out.open("cards.dat", ios::binary);
    if (!out)
    {
        cout << "Something went wrong" << endl;
    }
    while (out)
    {
        out.read((char*)&card, sizeof(Card));
    }
    out.close();
    return card.id == 0 ? 0 : card.id + 1;
}
unsigned int id_players()
{
    ifstream out;
    Player player = { -1,"" };
    out.open("players.dat", ios::binary);
    if (!out)
    {
        cout << "Something went wrong" << endl;
    }
    while (out)
    {
        out.read((char*)&player, sizeof(Player));
    }
    out.close();
    return player.id + 1;
}
unsigned int id_decks()
{
    ifstream out;
    Deck deck;
    out.open("decks.dat", ios::binary);
    if (!out)
    {
        cout << "Something went wrong" << endl;
    }
    while (out)
    {
        out.read((char*)&deck, sizeof(Deck));
    }
    out.close();
    return deck.player_id == 0 ? 0 : deck.player_id + 1;
}

int unique_Id(string file_name)
{
    ifstream out;
    int result = 0;
    if (file_name == "cards")
    {
        result = id_cards();
    }
    else if (file_name == "players")
    {
        result = id_players();
    }
    else if (file_name == "decks")
        result = id_decks();
    return result;
}


void create_player()
{
    ofstream out;
    int unique_id = unique_Id("players");
    char* name=new char[128];
    cin.getline(name,127);
    Player curr_player;
    curr_player.id = unique_id;
    strncpy(curr_player.name,name,128);
    write_File(out, "players.dat", curr_player);
    out.close();
}
void create_card()
{
    ofstream out;
    int unique_id = unique_Id("cards");
    char* name = new char[64];
    cin.getline(name, 64);
    Card curr_card;
    curr_card.id = unique_id;
    strncpy(curr_card.name, name, 64);
    write_File(out, "cards.dat", curr_card);
    out.close();
}


int main()
{
    ofstream out;
    ifstream in;

    string line;
    while (true)
    {
        cout << ">";
        getline(cin, line);
        if (line == "cp")//create player
        {
            create_player();
        }
        else if (line == "cc")//create card
        {
        }
        else if (line == "cd")//create deck
        {
            
        }
        else if (line == "report")
        {
            
        }
        else
            break;
    }
}