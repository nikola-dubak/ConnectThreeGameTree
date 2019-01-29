#pragma once
#include "Tree.h"

inline int max(int a, int b) {
	return a > b ? a : b;
}

inline int min(int a, int b) {
	return a < b ? a : b;
}

inline void Indent(int indentCount) {
	for (int k = 0; k < 5 * indentCount; k++) cout << " ";
}

class Game {
	int player1Matrix : 25;
	int columnFull : 5;
	int nextPlayer : 2;
	int player2Matrix : 25;
	int state : 2;
	bool gameEnded : 1;
	int Get(int, int) const;
	void Set(int, int, int);
	bool ThreeConnected();
public:
	Game() :nextPlayer(0), columnFull(0), state(-2), player1Matrix(0), player2Matrix(0), gameEnded(false) {}
	void Read();
	int State() const { return state; }
	int Player() const { return nextPlayer; }
	bool GameEnded() const { return gameEnded; }
	void SetState(int state) { this->state = state; }
	void Insert(int);
	bool ColumnFull(int column) const {
		return (columnFull >> column) & 1;
	}
	void Print(int indentCount);
};

int Game::Get(int row, int column) const {
	if ((player1Matrix >> (5 * row + column)) & 1) return 1;
	if ((player2Matrix >> (5 * row + column)) & 1) return -1;
	return 0;
}

void Game::Set(int row, int column, int player) {
	if (player == 1) {
		player1Matrix = player1Matrix | (1 << (5 * row + column));
		return;
	}
	player2Matrix = player2Matrix | (1 << (5 * row + column));
}

bool Game::ThreeConnected() {
	int current1, current2, previous1, previous2;
	bool equal1, equal2;

	for (int i = 0; i < 5; i++) {
		equal1 = equal2 = false;
		for (int j = 1; j < 5; j++) {
			current1 = Get(i, j); previous1 = Get(i, j - 1);
			current2 = Get(j, i); previous2 = Get(j - 1, i);

			if (current1 != previous1)
				equal1 = false;
			else if (current1 != 0) {
				if (equal1) {
					state = current1;
					return true;
				}
				equal1 = true;
			}

			if (current2 != previous2)
				equal2 = false;
			else if (current2 != 0) {
				if (equal2) {
					state = current2;
					return true;
				}
				equal2 = true;
			}
		}
	}

	for (int slice = 2; slice < 7; slice++) {
		equal1 = equal2 = false;
		int z = slice < 5 ? 0 : slice - 4;
		for (int i = z + 1; i <= slice - z; i++) {
			current1 = Get(i,4 - (slice - i));
			previous1 = Get(i - 1, 4 - (slice - (i - 1)));
			current2 = Get(slice - i, i);
			previous2 = Get(slice - (i - 1), i - 1);

			if (current1 != previous1)
				equal1 = false;
			else if (current1 != 0) {
				if (equal1) {
					state = current1;
					return true;
				}
				equal1 = true;
			}

			if (current2 != previous2)
				equal2 = false;
			else if (current2 != 0) {
				if (equal2) {
					state = current2;
					return true;
				}
				equal2 = true;
			}
		}
	}
	return false;
}

void Game::Read() {
	int number, count = 0;
	cout << "Unesite pocetno stanje igre" << endl; // Enter beginning game state
	cout << "Prazno polje: 0, Prvi igrac: 1, Drugi igrac: 2" << endl; // Empty: 0, First player: 1, Second player: 2
	for (int i = 0; i < 5; i++) {
		cout << "Unesite vrstu " << i + 1 << ": "; // Enter row {i+1}
		for (int j = 0; j < 5; j++) {
			cin >> number;
			if (number != 0) {
				Set(i, j, number);
				count++;
				if (i == 0) {
					columnFull = columnFull | (1 << j);
				}
			}
		}
	}
	nextPlayer = count % 2 ? -1 : 1;
	gameEnded = ThreeConnected();
	if (!gameEnded && (columnFull == -1)) {
		gameEnded = true;
		state = 0;
	}
}

void Game::Insert(int column) {
	for (int row = 4; row >= 0; row--) {
		if (!Get(row, column)) {
			Set(row, column, nextPlayer);
			if (row == 0) {
				columnFull = columnFull | (1 << column);
			}
			nextPlayer = -nextPlayer;
			break;
		}
	}
	gameEnded = ThreeConnected();
	if (!gameEnded && (columnFull == -1)) {
		gameEnded = true;
		state = 0;
	}
}

void Game::Print(int indentCount) {
	Indent(indentCount); cout << "Sledeci: " << (nextPlayer > 0 ? 1 : 2) << endl; // Next:
	if (state != -2) {
		Indent(indentCount); cout << "Stanje: " << state << endl; // State:
	}
	int number;
	for (int i = 0; i < 5; i++) {
		Indent(indentCount);
		for (int j = 0; j < 5; j++) {
			number = Get(i, j);
			if (number == -1) cout << 2;
			else cout << number;
		}
		cout << endl;
	}
}

class GameTree : public Tree<Game> {
public:
	GameTree(const Game&);
	void Print();
};

GameTree::GameTree(const Game& startGame):Tree<Game>(5) {
	Insert(startGame);
	Node* current;
	Queue<Node*> queue;
	queue.Insert(root);
	while (!queue.Empty()) {
		current = queue.Delete();
		if (!current->value.GameEnded()) {
			for (int i = 0; i < 5; i++) {
				Node*& child = current->children[i];
				if (!child && !current->value.ColumnFull(i)) {
					child = new Node(current->value, order);
					child->value.Insert(i);
					child->parent = current;
				}
				if (child) {
					queue.Insert(child);
				}
			}
		}
		else {
			Node* child = current;
			Node* parent = current->parent;
			while (parent) {
				if (parent->value.State() == -2) {
					parent->value.SetState(child->value.State());
				}
				else if (parent->value.Player() == 1) {
					parent->value.SetState(max(parent->value.State(), child->value.State()));
				}
				else {
					parent->value.SetState(min(parent->value.State(), child->value.State()));
				}
				child = parent;
				parent = parent->parent;
			}
		}
	}
}

void GameTree::Print() {
	int level = 1;
	Node* current;
	Node* parent = nullptr;
	Queue<Node*> queue;
	queue.Insert(root);
	queue.Insert(nullptr);
	while (queue.Front()) {
		current = queue.Delete();
		for (int i = 0; i < order; i++) {
			if (current->children[i]) {
				queue.Insert(current->children[i]);
			}
		}
		if (current->parent != parent) {
			parent = current->parent;
			cout << endl;
			Indent(level - 2);
			cout << "Deca od ID - " << parent << ':' << endl; // Children from ID - {parent}:
		}
		Indent(level - 1); cout << "ID: " << current << endl; // ID:
		current->value.Print(level - 1);
		cout << endl;
		if (!queue.Front()) {
			queue.Insert(nullptr);
			queue.Delete();
			level++;
		}
	}
	queue.Delete();
	cout << endl;
}