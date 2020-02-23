#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;


struct Player{
    int id;
    char name[128]; 
};
struct Card{
    int id;
    char color[6];
    char name[64];

};
struct Deck{
    int player_id;
    char color[6];    
    int cards_ids[60];
};

Player read_File(ifstream& in,string name_of_file) //returning the first Player
{
    Player player;
    in.open(name_of_file);
    if (!in)
    {
        cout<<"Something went wrong"<<endl;
    }
    in.read((char*)&player,sizeof(Player));
    in.close();
    return player;
}

Player read_File(ifstream& in,string name_of_file,int index) // returning the Player on index
{
    Player player;
    in.open(name_of_file);
    if (!in)
    {
        cout<<"Something went wrong"<<endl;
    }
    for (size_t i = 0; i <= index; i++)
    {
        in.read((char*)&player,sizeof(Player));
    }

    in.close();
    return player;
}

void writer_File(ofstream& out,string name_of_file,Player& player) //writes struct player to the file
{
    out.open(name_of_file,ios::app);
    if (!out)
    {
        cout<<"Something went wrong"<<endl;
    }
    out.write((char*)&player,sizeof(Player));
    out.close(); 
}
void writer_File(ofstream& out,string name_of_file,Card& card) //writes struct card to the file
{
    out.open(name_of_file,ios::app);
    if (!out)
    {
        cout<<"Something went wrong"<<endl;
    }
    out.write((char*)&card,sizeof(Card));
    out.close(); 
}
void print_Player(Player& player)
{
    cout<<player.id<<"::"<<player.name<<endl;
}

int main()
{
    ofstream out; 
    ifstream in;

    Player player = {1,"Damian"};
    Player player1 = {2,"Ivan"};
    Player pla;
    Card card= {1,"Ace","Black"};

    //writer_File(out,"test.dat",player);
    //writer_File(out,"test.dat",player1);
    //writer_File(out,"cards.dat",card);
    
    Player curr=read_File(in,"test.dat",0);
    print_Player(curr);
    curr=read_File(in,"test.dat",1);
    print_Player(curr);
}