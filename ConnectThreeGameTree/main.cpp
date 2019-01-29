#include <iostream>
#include "Game.h"
using namespace std;

int main() {
	int option;
	Game* game = nullptr;
	GameTree* tree = nullptr;
	while (true) {
		if (!game) {
			cout << "1. Kreirajte pocetnu igru" << endl // Create beginning game state
				<< "0. Napustite program" << endl // Exit
				<< "Unesite redni broj: ";
			cin >> option;

			switch (option) {
			case 0: {
				return 0;
			}
			case 1: {
				game = new Game();
				game->Read();
				break;
			default: continue;
			}
			}
			cout << endl;
		}
		if (!tree) {
			cout << "1. Kreirajte stablo igre" << endl // Create Game Tree
				<< "2. Ispisite pocetnu igru" << endl // Write beginning game state
				<< "3. Obrisite igru" << endl // Delete beginning game state
				<< "0. Napustite program" << endl // Exit
				<< "Unesite redni broj: "; // Enter number:
			cin >> option;
			switch (option) {
			case 0: {
				delete game;
				return 0;
			}
			case 1: {
				tree = new GameTree(*game);
				break;
			}
			case 2: {
				game->Print(0);
				break;
			}
			case 3: {
				delete game; game = nullptr;
				break;
			}
			}
			cout << endl;
		}
		else {
			cout << "1. Ispisite stablo igre" << endl // Write Game Tree
				<< "2. Sirina stabla igre" << endl // Game Tree Width
				<< "3. Ispisite pocetnu igru" << endl // Write beginning game state
				<< "4. Zapocnite novu igru" << endl // Start new game
				<< "0. Napustite program" << endl // Exit
				<< "Unesite redni broj: "; // Enter number:
			cin >> option;
			switch (option) {
			case 0: {
				delete game; delete tree;
				return 0;
			}
			case 1: {
				tree->Print();
				break;
			}
			case 2: {
				cout << "Sirina stabla igre je: " << tree->Width() << endl; // Game Tree width is:
				break;
			}
			case 3: {
				game->Print(0);
				break;
			}
			case 4: {
				delete game; game = nullptr;
				delete tree; tree = nullptr;
				break;
			}
			}
			cout << endl;
		}
		
	}
}