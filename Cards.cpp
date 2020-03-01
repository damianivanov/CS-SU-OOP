// Cards.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <type_traits>
using namespace std;
static const string players_File= "players.dat";
static const string cards_File = "cards.dat";
static const string decks_File = "decks.dat";

struct Player {
    int id;
    char name[128];
};
struct Card {
    int id;
    char color[10];
    char name[64];

};
struct Deck {
    int player_id;
    char color[10];
    int cards_ids[60];
};

Player read_File_Player(ifstream& in, string name_of_file) //returning the first Player
{
    Player player;
    in.open(name_of_file);
    if (!in)
    {
        cout << "Something went wrong" << endl;
        in.close();
        return player = {0,""};
    }
    else {

        in.read((char*)&player, sizeof(Player));
    }
    in.close();
    return player;
}
Player read_File_Player(ifstream& in, string name_of_file, int index) // returning the Player on index
{
    Player player;
    in.open(name_of_file);
    if (!in)
    {
        cout << "Something went wrong" << endl;
       
    }
    else
    {
        for (size_t i = 0; i <= index; i++)
        {
            in.read((char*)&player, sizeof(Player));
        }
    }
    in.close();
    return player;
}

Card read_File_Card(ifstream& in, string name_of_file, int index)
{
    Card card;
    in.open(name_of_file);
    if (!in)
    {
        cout << "Something went wrong" << endl;

    }
    else
    {
        for (size_t i = 0; i <= index; i++)
        {
            in.read((char*)&card, sizeof(Card));
        }
    }
    in.close();
    return card;
}

template <typename T>
void write_File(ofstream& out, string name_of_file, T& object) //writes struct player to the file
{
    out.open(name_of_file, ios::out|ios::app);
    if (!out)
    {
        cout << "Something went wrong" << endl;
    }
    else
        out.write((char*)&object, sizeof(T));
    out.close();
}

//void write_File(ofstream& out, string name_of_file, Card& card) //writes struct card to the file
//{
//    out.open(name_of_file, ios::app);
//    if (!out)
//    {
//        cout << "Something went wrong" << endl;
//    }
//    out.write((char*)&card, sizeof(Card));
//    out.close();
//}

void print_Player(Player& player)
{
    if (player.name!="")
    {
        cout << player.id << "::" << player.name << endl;
    
    }
}
void print_Card(Card& card)
{
    cout << card.id << "::" << card.color<< "::" <<card.name << endl;
}

unsigned int id_cards()
{
    ifstream out;
    Card card={ -1,"","" };
    out.open(cards_File, ios::binary);
    if (!out)
    {
        cout << "Something went wrong" << endl;
    }
    else {
        while (out)
        {
            out.read((char*)&card, sizeof(Card));
        }
    }
    out.close();
    return card.id+1;
}
unsigned int id_players()
{
    ifstream out;
    Player player = { -1,"" };
    out.open(players_File, ios::binary);
    if (!out)
    {
        cout << "Something went wrong" << endl;
    }
    else {
        while (out)
        {
            out.read((char*)&player, sizeof(Player));
        }
    }
    out.close();
    return player.id + 1;
}
//unsigned int id_decks()
//{
//    ifstream out;
//    Deck deck;
//    out.open(decks_File, ios::binary);
//    if (!out)
//    {
//        cout << "Something went wrong" << endl;
//    }
//    else {
//        while (out)
//        {
//            out.read((char*)&deck, sizeof(Deck));
//        }
//    }
//    out.close();
//    return deck.player_id == 0 ? 0 : deck.player_id + 1;
//}



template<typename T>
int unique_Id()
{
    ifstream out;
    int result = 0;
    
    if (is_same_v<T,Card>)
        result = id_cards();
    else if (is_same_v<T, Player>)
        result = id_players();
    /*else if (is_same_v<T, Deck>)
        result = id_decks();*/
    return result;
}


void create_player()
{
    ofstream out;
    Player curr_player;

    int unique_id = unique_Id<Player>(); //finds the next valid Id
    curr_player.id = unique_id; // setting player's Id

    char* name=new char[128];

    cin.getline(name,127); //name input
    strncpy(curr_player.name,name,128); //setting player's name

    write_File(out,players_File, curr_player); //writes the player to the file

    delete[] name;
    out.close();
}
void create_card()
{

    ofstream out;
    Card curr_card;

    int unique_id = unique_Id<Card>(); //finds the next valid Id
    curr_card.id = unique_id; //setting card's id

    char* color_input = new char[10];
    char* name = new char[64];
    
    cin>>color_input; //input color
    cin.ignore(1); //ignores the space between color and name
    cin.getline(name, 64); //input name
    
    strncpy(curr_card.name, name, 64); //setting card's name 
    strncpy(curr_card.color, color_input, 10); // setting card's color
    
    write_File(out,cards_File, curr_card); //writes the struct to the file
    
    delete[] color_input;
    delete[] name;
    
    out.close();
}
void create_deck()
{
    ofstream out;
    Deck curr_deck;

    //finds out if player exists
    //all cards exists
    //color of the deck is most frequent color 
    //if all are true 
    //creates the deck
    
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
        if (line == "cp")//creates player
        {
            create_player();
        }
        else if (line == "cc")//creates card
        {
            create_card();
        }
        else if (line == "cd")//create deck
        {
            create_deck();
        }
        else if (line == "report")
        {
            
        }
        else
            break;
    }
    
    Card card = read_File_Card(in, cards_File, 1);
    print_Card(card);

    //Player player = read_File_Player(in, players_File, 1);
    //print_Player(player);

}