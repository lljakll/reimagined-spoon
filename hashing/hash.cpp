#include <cstdlib>
#include <iostream>
#include <string>

#include "hash.h"

hash::hash(){
	for(int i = 0; i < tableSize; i++){
		HashTable[i] = new item;
		HashTable[i]->name = "empty";
		HashTable[i]->drink = "empty";
		HashTable[i]->next = nullptr;
	}
}

void hash::AddItem(std::string name, std::string drink){
	int index = Hash(name);

	if(HashTable[index]->name == "empty"){
		HashTable[index]->name = name;
		HashTable[index]->drink = drink;
	}
	else{
		item* Ptr = HashTable[index];
		item* newItem = new item;

		newItem->name = name;
		newItem->drink = drink;
		newItem->next = nullptr;

		while(Ptr->next != nullptr){
			Ptr = Ptr->next;
		}

		Ptr->next = newItem;

	}
}

int hash::NumberOfItemsInIndex(int index){
	int count = 0;
	if(HashTable[index]->name == "empty"){
		return 0;
	}
	else{
		count++;
		item* Ptr = HashTable[index];
		while(Ptr->next != nullptr){
			count++;
			Ptr = Ptr->next;
		}
	}
	return count;
}

void hash::PrintTable(){
	int number;
	for(int i = 0; i < tableSize; i++){
		if(HashTable[i]->name =="empty"){
		}
		else{
			number = NumberOfItemsInIndex(i);
			std::cout<<"-----------------------\n";
			std::cout << "index = " << i << std::endl;
			std::cout << HashTable[i]->name << std::endl;
			std::cout << HashTable[i]->drink << std::endl;
			std::cout << "# of items = " << number << std::endl;
			std::cout<<"-----------------------\n";
		}	
	}
}

void hash::PrintItemsInIndex(int index){
	item* Ptr = HashTable[index];

	if(Ptr->name == "empty"){
		std::cout << "index " << index << " is empty" << std::endl;
	}
	else{
		std::cout << "index " << index << " contains: " << std::endl;

		while(Ptr != nullptr){
			std::cout<<"-----------------------\n";	
			std::cout << Ptr->name << std::endl;
			std::cout << Ptr->drink << std::endl;
			std::cout<<"-----------------------\n";
			Ptr = Ptr->next;
		}
	}
}

void hash::PrintDrink(int index){
	std::cout << HashTable[index]->drink;
}

int hash::SearchTable(std::string searchKey){
	int index;

	index = Hash(searchKey);

	return index;
}

int hash::Hash(std::string key){
	
	int hash = 0;
	int index;

	for (int i = 0; i < key.length(); i++){
		hash = (hash + (int)key[i]) * 17;	
	}
		index = abs(hash % tableSize);
		std::cout << "Key:  " << key << " | Hashed is: " << hash << " | Index: " << index << std::endl;

	return index;

}