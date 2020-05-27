// Alchemistry.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "File.h"
#include "Alchemic.h"
int main()
{
    File file;
    file.Open("Book.txt");

    Book book(file.get_content());

    Alchemic alchemic;
    alchemic.set_book(book);
    if (!alchemic.get_philosopher_stone())
    {
        cout << "There is no formula for Philosopher's Stone" << endl;
        return 0;
    }
    else
    {
        alchemic.Fill_Inventory();
        alchemic.Magic();
    }
}


