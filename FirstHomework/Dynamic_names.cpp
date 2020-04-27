#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>
//#include <type_traits>

using namespace std;

static const string players_File = "players.dat";
static const string cards_File = "cards.dat";
static const string decks_File = "decks.dat";

static int next_card_id = 0;
static int next_player_id = 0;
static int all_decks = 0;

bool all_files_created()
{
	bool result = true;
	ofstream players_file;
	players_file.open(players_File, ios::binary | ios::trunc);
	ofstream cards_file;
	cards_file.open(cards_File, ios::binary | ios::trunc);
	ofstream decks_file;
	decks_file.open(decks_File, ios::binary | ios::trunc);
	if (!players_file || !cards_file || !decks_file)
	{
		cout << "One or more .dat file doesn't exist" << endl;
		result = false;
	}
	players_file.close();
	cards_file.close();
	decks_file.close();
	return result;
}

struct Player {
	int id;
	char* name;
	int name_size;

};
struct Card {
	int id;
	char color[8];
	char* name;
	int name_size;

};
struct Deck {
	int player_id;
	char color[8];
	int cards_ids[60];
};

//Player read_File_Player(ifstream& in, string name_of_file) //returning the first Player
//{
//	Player player;
//	in.open(name_of_file);
//	if (!in)
//	{
//		cout << "Something went wrong" << endl;
//		in.close();
//		return player = { 0,nullptr,0 };
//	}
//	else {
//
//		in.read((char*)&player, sizeof(Player));
//	}
//	in.close();
//	return player;
//}
Player read_File_Player(int index) // returning the Player on index
{
	ifstream in;
	Player player = { -1,0,0 };
	in.open(players_File, ios::binary);
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

Card read_File_Card(int index)
{
	ifstream in;
	Card card = {-1,"",0,0};
	in.open(cards_File, ios::binary);
	for (size_t i = 0; i <= index; i++)
	{
		in.read((char*)&card, sizeof(Card));
	}
	in.close();
	return card;
}

string color_of_the_card(int index)
{
	Card card = read_File_Card(index);;
	return card.color;
}
string color_of_the_card(string name)
{
	string result;
	ifstream in;
	in.open(cards_File, ios::binary);
	for (size_t i = 0; i <= next_card_id; i++)
	{
		//maybe
		Card card = read_File_Card(i);
		if (string(card.name, card.name_size) == name)
		{
			in.close();
			return card.color;
		}
	}
	in.close();
	return "";
}

template <typename T>
void write_File(string name_of_file, T& object) //writes struct player to the file
{
	ofstream out;
	out.open(name_of_file, ios::app | ios::binary);
	out.write((char*)&object, sizeof(T));
	out.close();
}

int player_exist(Player& player)
{
	ifstream in;
	in.open(players_File, ios::binary);
	Player curr_player = {-1,0,0};
	string player_name = string(player.name, player.name_size);
	while (in)
	{
		in.read((char*)&curr_player, sizeof(Player));
		if (player_name == string(curr_player.name, curr_player.name_size))
		{
			in.close();
			return curr_player.id;
		}


	}
	in.close();
	return -1;
}
int card_exists(Card& card)
{
	ifstream in;
	Card curr_card = {-1,"",0,0};
	in.open(cards_File, ios::binary);
	string card_name = string(card.name, card.name_size);
	while (in)
	{
		in.read((char*)&curr_card, sizeof(Card));
		if (card_name == string(curr_card.name, curr_card.name_size))
		{

			in.close();
			return curr_card.id;
		}
	}
	in.close();
	return -1;

}

bool all_cards_exist(int* cards_ids)
{
	for (size_t i = 0; i < 60; i++)
	{
		Card card = {-1,"",0,0};

		string name;
		getline(cin, name); //input name
		card.name_size = name.size();
		card.name = new char[card.name_size+1];
		strcpy_s(card.name, card.name_size+1, name.c_str());

		int result = card_exists(card);
		if (result >= 0)
		{
			cards_ids[i] = result;
		}
		else {
			cout << ">Card \"" << card.name << "\"" << " doesn't exist" << endl;
			return false;
		}
		delete[] card.name;
	}
	return true;
}
string color_of_the_deck(int* cards_id)
{
	string color;
	unordered_map<string, int> colors;
	vector < string> ordered_colors;
	colors["Red"] = 0;
	ordered_colors.push_back("Red");
	colors["Black"] = 0;
	ordered_colors.push_back("Black");
	colors["Blue"] = 0;
	ordered_colors.push_back("Blue");
	colors["White"] = 0;
	ordered_colors.push_back("White");
	colors["Green"] = 0;
	ordered_colors.push_back("Green");

	for (size_t i = 0; i < 60; i++)
	{
		string curr_color = color_of_the_card(cards_id[i]);
		colors[curr_color]++;
	}
	int max_count = 0;
	for (int i = 0; i < ordered_colors.size(); ++i)
	{
		if (colors[ordered_colors[i]] > max_count)
		{
			max_count = colors[ordered_colors[i]];
			color = ordered_colors[i];
		}
	}
	return color;
}
string print_deck(Deck& deck)
{
	string result = "";
	Player player = read_File_Player(deck.player_id);
	Card first_card = read_File_Card(deck.cards_ids[0]);
	result.append("\t");
	result.append("Owner: ");
	result.append(string(player.name, player.name_size));
	result.append(" Card: ");
	result.append(string(first_card.name, first_card.name_size));
	result.append(" Color: ");
	result.append(first_card.color);
	result.append("\n");
	return result;

}
string print_all_decks_by_color(string color)
{
	ifstream in;
	string result = "";
	in.open(decks_File, ios::binary);
	int it = 0;
	/*while (in)
	{
		Deck deck;
		in.read((char*)&deck, sizeof(deck));
		if (deck.color==color)
		{
			it++;
			result.append(print_deck(deck));
		}
	}*/
	//poslenia zapis vinagi izlizashe dva puti
	for (size_t i = 0; i < all_decks; i++)
	{
		Deck deck;
		in.read((char*)&deck, sizeof(deck));
		if (deck.color == color)
		{
			it++;
			result.append(print_deck(deck));
		}
	}
	in.close();
	return result;
}

string print_most_used_card()
{
	unordered_map<string, int> cards;

	ifstream in_decks;
	ifstream in_cards;
	string result;
	in_cards.open(cards_File, ios::binary);
	in_decks.open(decks_File, ios::binary);
	for (size_t i = 0; i < all_decks; i++)
	{
		Deck deck;
		in_decks.read((char*)&deck, sizeof(deck));
		for (size_t i = 0; i < 60; i++)
		{
			Card card;
			card = read_File_Card(deck.cards_ids[i]);
			string card_name = string(card.name, card.name_size);
			if (cards.find(card_name) != cards.end())//found
			{
				cards[card_name]++;
			}
			//not found
			else
			{
				cards.insert(pair<string, int>(card_name, 1));
			}
		}
	}
	int currentMax = 0;
	string name_of_max = "";
	for (auto it = cards.cbegin(); it != cards.cend(); ++it)
	{
		if (it->second >= currentMax)
		{
			name_of_max = it->first;
			currentMax = it->second;
		}
	}

	result.append("Most common card: ");
	result.append(name_of_max);
	result.append(" Color:");
	result.append(color_of_the_card(name_of_max));
	return result;
}

void create_player()
{

	Player curr_player = {next_player_id,0,0};

	string name;
	getline(cin, name); //name input

	curr_player.name_size = name.size();
	curr_player.name = new char[curr_player.name_size+1];

	strcpy_s(curr_player.name, curr_player.name_size+1, name.c_str()); //setting player's name
	if (player_exist(curr_player) != -1) //checks if player already exists 
	{
		std::cout << "Player \"" << name << "\" already exists" << endl;
	}
	else {
		write_File<Player>(players_File, curr_player); //writes the player to the file
		next_player_id++;
		std::cout << ">Player \"" << name << "\"" << " created" << endl;
	}
}
void create_card()
{

	Card curr_card={ next_card_id,"",0,0 };

	string color;
	string name;

	cin >> color; //input color
	cin.ignore(1); //ignores the space between color and name
	getline(cin, name); //input name

	curr_card.name_size = name.size();
	curr_card.name = new char[curr_card.name_size+1];

	strcpy_s(curr_card.name,curr_card.name_size+1, name.c_str()); //setting card's name
	strcpy_s(curr_card.color, color.size()+1,color.c_str()); // setting card's color

	if (card_exists(curr_card) != -1)//checks if card already exists
	{
		cout << ">Card \"" << name << "\" already exists" << endl;
	}
	else
	{
		write_File<Card>(cards_File, curr_card); //writes the struct to the file
		next_card_id++;
		cout << ">Card \"" << name << "\"" << " created" << endl;
	}


}
void create_deck()
{
	Deck curr_deck;
	Player player = { -1,0,0 };

	string name;
	getline(cin, name);

	player.name_size = name.size();
	player.name = new char[player.name_size+1];

	strcpy_s(player.name, player.name_size+1, name.c_str());

	int result = player_exist(player);//finds out if player exists
	if (result == -1)
	{
		cout << ">Player \"" << name << "\" doesn't exist" << endl;
		return;
	}
	else 
		curr_deck.player_id=result;
	

	//all cards exists
	int* cards_ids = new int[60];
	if (all_cards_exist(cards_ids))
	{
		
		for (size_t i = 0; i < 60; i++)
		{
			curr_deck.cards_ids[i] = cards_ids[i];
		}
	}
	else
	{
		cout << ">Not all cards exist" << endl;
		return;
	}

	string deck_color = color_of_the_deck(cards_ids);

	strcpy_s(curr_deck.color,deck_color.size()+1, deck_color.c_str());

	write_File<Deck>(decks_File, curr_deck);
	cout << ">Deck created for player \"" << name << "\"" << endl;

	all_decks++;

	delete[] player.name;
	delete[] cards_ids;
}
void report()
{
	ofstream out;
	out.open("report.txt", ios::trunc);
	//map orders the keys alphabetically *THE MORE YOU KNOW*
	unordered_map<string, int> colors;
	vector < string> ordered_colors;
	colors["Red"] = 0;
	ordered_colors.push_back("Red");
	colors["Black"] = 0;
	ordered_colors.push_back("Black");
	colors["Blue"] = 0;
	ordered_colors.push_back("Blue");
	colors["White"] = 0;
	ordered_colors.push_back("White");
	colors["Green"] = 0;
	ordered_colors.push_back("Green");

	//poslednata teste go vzima 2 puti ako e s while(out)

	for (int i = 0; i < ordered_colors.size(); ++i)
	{
		out << ordered_colors[i] << endl;
		out << print_all_decks_by_color(ordered_colors[i]);
	}
	out << print_most_used_card();
	cout << ">report generated" << endl;
	out.close();



}

int main()
{
	string line;
	if (!all_files_created())
		return 0;

	while (true)
	{
		/*cout << ">";*/
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
			report();

		}
		else
		{
			cout << ">command \"" << line << "\" not recognized - exiting" << endl;
			break;
		}
	}


}



