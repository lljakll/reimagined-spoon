

#include <cstdlib>
#include <iostream>
#include <string>

#include "hash.h"

int main(int argc, char** argv) {

    hash Hashy;


    Hashy.AddItem("Jackie", "Mocha");
    Hashy.AddItem("Jimmy", "Rip-it");
    Hashy.AddItem("Timmy", "Coke");
    Hashy.AddItem("Jessica", "Tequilla");
    Hashy.AddItem("Jasmine", "Vodka");
    Hashy.AddItem("Ashley", "Coffee");
    Hashy.AddItem("Amy", "Latte");
    Hashy.AddItem("Annabelle", "Tea");
    Hashy.AddItem("Kelly", "Jameson");

//    Hashy.PrintTable();

    char choice;
    std::string name;

    while(choice != 'Q'){
        std::cout << std::endl << "S)earch " << std::endl;
        std::cin >> choice;
        choice = toupper(choice);

        switch(choice){
            case 'S':
                std::cout << "Search for a person: ";
                std::cin >> name;
                std::cout << std::endl << name << " Loves to Drink: ";
                int index = Hashy.SearchTable(name);
                Hashy.PrintDrink(index);
                std::cout << std::endl << std::endl;
            break;
        }
    }

    return 0;
}