#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

class Character {
public:
    string name;
    int health;
    int attackPower;

    Character(string n, int h, int a) : name(n), health(h), attackPower(a) {}

    // Attack method
    void attack(Character& target) {
        int damage = rand() % attackPower + 1; // Random damage between 1 and attackPower
        cout << name << " attacks " << target.name << " for " << damage << " damage!" << endl;
        cout << "\n";
        sleep(3);
        target.health -= damage;
    }

    // Check if character is alive
    bool isAlive() {
        return health > 0;
    }
};

int main() {
    srand(time(0)); // Seed for random number generation

    // Create characters (example: Akame and Tatsumi)
    Character akame("Akame", 100, 30);  // Akame with 100 health and 30 attack power
    Character tatsumi("Tatsumi", 120, 25); // Tatsumi with 120 health and 25 attack power

    cout << "Battle starts!" << endl;
    cout << "\n";

    // Simulate battle
    while (akame.isAlive() && tatsumi.isAlive()) {
        akame.attack(tatsumi);
        if (!tatsumi.isAlive()) {
            cout << tatsumi.name << " has been defeated!" << endl;
            cout << "\n";
            break;
        }

        tatsumi.attack(akame);
        if (!akame.isAlive()) {
            cout << akame.name << " has been defeated!" << endl;
            cout << "\n";
            break;
        }
    }

    // Announce winner
    if (akame.isAlive()) {
        cout << akame.name << " wins!" << endl;
        cout << "\n";
    } else {
        cout << tatsumi.name << " wins!" << endl;
        cout << "\n";
    }

    return 0;
}

