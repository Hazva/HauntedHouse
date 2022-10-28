#pragma once
#include <vector>
#include <iostream>
#include "Header.h"
class Player {
public:
    std::vector<std::string> inventory{ "", "", "", "", "" };
    Room loc;
    void Listen(Room r, int d, Monster m);
    void Hide(Player p, Room r, Monster m);
    void playerMove(Monster& m);
    Player();
    ~Player();
};

Player::Player() {

}

Player::~Player() {

}
bool Puzzle(std::string& puz, Room& r, Player& p) {
    //std::cout << "This is puzzling.\n";
    std::string userLine;
    std::string userLine2;
    int userInput;
    //int srKeypad = 9136;
    int stClock = 113015;
    bool solved = false;
    int placeholder;
    std::vector<int> row1 = { 0, 0, 0, 0 };
    std::vector<int> row2 = { 0, 0, 0, 0 };
    std::vector<int> row3 = { 0, 0, 0, 0 };
    std::vector<int> answer = { 0, 0, 0, 0 };
    for (int i = 0; i < 4; i++) {
        row1[i] = rand() % 10;
        //std::cout << "row1: " << row1[i] << "\n";
        row2[i] = rand() % 10;
        //std::cout << "row2: " << row2[i] << "\n";
        row3[i] = rand() % 10;
        //std::cout << "row3: " << row3[i] << "\n";
        answer[i] = row1[i] + row2[i] + row3[i];
        //std::cout << "answer: " << answer[i] << "\n";
    }
    for (int i = 0; i < 12; i++) {
        int randRow = rand() % 4;
        int timesShuffled = rand() % 2;
        if (randRow == 0) {
            for (int i = 0; i <= timesShuffled; i++) {
                std::swap(row1[0], row1[1]);
                std::swap(row1[1], row1[2]);
                std::swap(row1[2], row1[3]);
            }
        }

        else if (randRow == 1) {
            for (int i = 0; i <= timesShuffled; i++) {
                std::swap(row2[0], row2[1]);
                std::swap(row2[1], row2[2]);
                std::swap(row2[2], row2[3]);
            }
        }

        else if (randRow == 2) {
            for (int i = 0; i <= timesShuffled; i++) {
                std::swap(row3[0], row3[1]);
                std::swap(row3[1], row3[2]);
                std::swap(row3[2], row3[3]);
            }
        }

        //std::swap(row1[rand() % 3], row2[rand() % 3]);
        //std::swap(row2[rand() % 3], row3[rand() % 3]);
        //std::swap(row3[rand() % 3], row1[rand() % 3]);
    }
    //std::cout << "SHUFFLED.\n";
    //for (int i = 0; i < 4; i++) {
        //std::cout << "row1: " << row1[i] << "\n";
        //std::cout << "row2: " << row2[i] << "\n";
        //std::cout << "row3: " << row3[i] << "\n";
        //std::cout << "answer: " << answer[i] << "\n";
    //}
    //above is test
    if (puz == "Keypad") {
        std::cout << "This orange keypad has four digits.\nWhat do you type?\n";
        std::stringstream ss;
        ss << srKeypad[0] << srKeypad[1] << srKeypad[2] << srKeypad[3];
        std::string strNum = ss.str();
        //std::cout << strNum << " AAAAAAAAAAAA\n";
        std::cin >> userInput;
        if (userInput == std::stoi(strNum)) {
            std::cout << "The keypad unlocks. You find some Car Keys inside.\n";
            p.inventory.push_back("Keys");
            return true;
        }
        //stringstream conversion https://www.programiz.com/cpp-programming/string-int-conversion
        //convert srKeypad to string to concatenate to compare userInput that is a string now to this combined randomized string that was originally an int and we also have to turn our userInput
        //into an array and compare it maybe? unsure
    }
    else if (puz == "Clock") {
        std::cout << "This clock has stopped. You can adjust the hands manually.\nYou adjust the hour hand, minute hand, and then seconds hand sequentially. What do you change them to?\n";
        std::cin >> userInput;
        if (userInput == stClock) {
            std::cout << "The hands all lock into place, and the clock opens. You take a key from inside.\n";
            //add key to players inventory here, I guess you'll have to pass in player for this
            p.inventory.push_back("Key");
            return true;
        }
    }
    //pass in parameters for the lock combination maybe? right now the lock combination randomizes each time making it really difficult and completely up to chance each time
    //right now this will end up in it resetting every time unless the combination of all 3 is exactly the same I think. EDIT: Tested it, could be what is happening. that or
    //it's thinking "you aren't outdoors and your thing doesn't equal lockAns3," so the lock resets because that else is tied to that. That's probably it actually. 
    else if (puz == "Lock") {
        std::cout << "\n";
        int lockProgression = 0;
        while (!solved) {
            std::cout << "What do you want to try? \n1 - Push\n2 - Jiggle\n3 - Turn\n";
            std::cin >> userInput;
            if ((p.loc.roomName == "Stairs" && userInput == lockAns[lockProgression]) ||
                (p.loc.roomName == "Grand Stairs" || p.loc.roomName == "Hallway" && userInput == lockAns2[lockProgression]) ||
                (p.loc.roomName == "Outdoors" && userInput == lockAns3[lockProgression])) {
                std::cout << "You hear something click inside of the lock.\n";
                lockProgression++;
            }
            else {
                std::cout << "You hear the lock reset.\n";
                return false;
            }
            if (lockProgression > 2) {
                std::cout << "The final pin slides into place, and you have made it through the lock.\n";
                return true;
            }
        }
    }
    else if (puz == "Fuse") {
        while (!solved) {
            std::cout << "row1: \t";
            for (int i = 0; i < 4; i++) {
                std::cout << row1[i] << "\t";
            }
            std::cout << "\nrow2: \t";
            for (int i = 0; i < 4; i++) {
                std::cout << row2[i] << "\t";
            }
            std::cout << "\nrow3: \t";
            for (int i = 0; i < 4; i++) {
                std::cout << row3[i] << "\t";
            }
            std::cout << "\nanswer: ";
            for (int i = 0; i < 4; i++) {
                std::cout << answer[i] << "\t";
            }
            std::cout << "\nThe voltage is controlled by the dials on each of the three rows. Which dial do you wish to adjust? You may also type 0 to exit. \n";
            std::cin >> userInput;
            if (userInput == 1) {
                placeholder = row1[0];
                row1[0] = row1[3];
                row1[3] = row1[2];
                row1[2] = row1[1];
                row1[1] = placeholder;
            }

            else if (userInput == 2) {
                placeholder = row2[0];
                row2[0] = row2[3];
                row2[3] = row2[2];
                row2[2] = row2[1];
                row2[1] = placeholder;
            }

            else if (userInput == 3) {
                placeholder = row3[0];
                row3[0] = row3[3];
                row3[3] = row3[2];
                row3[2] = row3[1];
                row3[1] = placeholder;
            }
            else if (userInput == 0) {
                return false;
            }
            else {
                std::cout << "That isn't a dial.\n";
            }
            if (row1[0] + row2[0] + row3[0] == answer[0] &&
                row1[1] + row2[1] + row3[1] == answer[1] &&
                row1[2] + row2[2] + row3[2] == answer[2] &&
                row1[3] + row2[3] + row3[3] == answer[3]) {
                std::cout << "You solved the puzzle. A small hatch opens, containing a Tire\n";
                p.inventory.push_back("Tire");
                return true;
            }
        }
    }
    else if (puz == "Desk") {
        int pairs = 0;
        int unknown[4][4] = {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0} };
        int solution[4][4] = {
            {1,4,8,3},
            {5,2,7,8},
            {6,3,5,1},
            {2,7,6,4} };
        int reset[4][4] = {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0} };
        while (!solved) {
            std::cout << "  0 1 2 3\n";
            int counter = 0;
            for (int i = 0; i < 4; i++) {
                std::cout << counter << " ";
                counter++;
                for (int j = 0; j < 4; j++) {
                    std::cout << unknown[i][j] << " ";
                }
                std::cout << "\n";

            }
            std::cin >> userLine;
            int found = userLine.find(",");
            //std::cout << "found: " << found << "\n";
            char c = userLine[found - 1];
            char c2 = userLine[found + 1];
            int coordX = (int)c - 48;
            int coordY = (int)c2 - 48;
            std::cout << coordX << "," << coordY << "\n";
            unknown[coordX][coordY] = solution[coordX][coordY];

            //need to update visual here and at the bottom
            std::cout << "  0 1 2 3\n";
            counter = 0;
            for (int i = 0; i < 4; i++) {
                std::cout << counter << " ";
                counter++;
                for (int j = 0; j < 4; j++) {
                    std::cout << unknown[i][j] << " ";
                }
                std::cout << "\n";

            }

            std::cin >> userLine2;
            int found2 = userLine2.find(",");
            //std::cout << "found: " << found2 << "\n";
            char c3 = userLine2[found2 - 1];
            char c4 = userLine2[found2 + 1];
            int coordX2 = (int)c3 - 48;
            int coordY2 = (int)c4 - 48;
            std::cout << coordX2 << "," << coordY2 << "\n";
            unknown[coordX2][coordY2] = solution[coordX2][coordY2];

            std::cout << "  0 1 2 3\n";
            counter = 0;
            for (int i = 0; i < 4; i++) {
                std::cout << counter << " ";
                counter++;
                for (int j = 0; j < 4; j++) {
                    std::cout << unknown[i][j] << " ";
                }
                std::cout << "\n";

            }


            if (solution[coordX][coordY] == solution[coordX2][coordY2]) {
                bool winCheck = true;
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        if (unknown[i][j] != solution[i][j]) {
                            winCheck = false;
                            break;
                        }
                    }
                }
                if (winCheck) {
                    std::cout << "After searching through all the desks, drawers, and various containers, you find a fuel cannister. It seems like it is meant for a car.\n";
                    p.inventory.push_back("Fuel");
                    return true;
                }
            }
            else {
                unknown[coordX][coordY] = reset[coordX][coordY];
                unknown[coordX2][coordY2] = reset[coordX2][coordY2];
            }
        }
    }
    else if (puz == "Car") {
        int carCounter = 0;
        for (int i = 0; i < p.inventory.size(); i++) {
            if (p.inventory.at(i) == "Fuel" || p.inventory.at(i) == "Keys" || p.inventory.at(i) == "Tire") {
                carCounter++;
            }
        }
        if (carCounter >= 3) {
            return true;
        }

    }
    return false;
}

void Player::playerMove(Monster& m) {
    std::string userInput;
    std::string Lock = "Lock";
    std::cout << "Select your destination.\n";
    if (this->loc.north != NULL) {
        std::cout << "North: " << this->loc.north->roomName << "\n";
        //std::cout << "Is the North door locked? " << p.loc.north->locked << "\n";
    }
    if (this->loc.south != NULL) {
        std::cout << "South: " << this->loc.south->roomName << "\n";
    }
    if (this->loc.east != NULL) {
        std::cout << "East: " << this->loc.east->roomName << "\n";
    }
    if (this->loc.west != NULL) {
        std::cout << "West: " << this->loc.west->roomName << "\n";
    }

    std::cin >> userInput;
    if (userInput == "North" || userInput == "north" || userInput == "NORTH") {
        if (this->loc.north->locked == true) {
            if (std::find(inventory.begin(), inventory.end(), "Key") != inventory.end()) {
                bool win = Puzzle(Lock, this->loc, *this);
                if (win) {
                    for (int i = 0; i < this->inventory.size(); i++) {
                        if (this->inventory.at(i) == "Key") {
                            //std::cout << "HERE!!!!! \n";
                            this->inventory.erase(this->inventory.begin() + i);
                        }
                    }
                    this->loc.north->locked = false;
                }
                else {
                    std::cout << "You did not complete the puzzle.\n";
                }
            }
            std::cout << "The " << this->loc.north->roomName << " door is locked.\n";
        }
        else {
            this->loc.playerOccupied = false;
            this->loc = *this->loc.north;
            this->loc.playerOccupied = true;

        }
    }
    else if (userInput == "South" || userInput == "south" || userInput == "SOUTH") {
        if (this->loc.south->locked == true) {
            if (std::find(inventory.begin(), inventory.end(), "Key") != inventory.end()) {
                bool win = Puzzle(Lock, this->loc, *this);
                if (win) {
                    for (int i = 0; i < this->inventory.size(); i++) {
                        if (this->inventory.at(i) == "Key") {
                            //std::cout << "HERE!!!!! \n";
                            this->inventory.erase(this->inventory.begin() + i);
                        }
                    }
                    this->loc.south->locked = false;
                }
                else {
                    std::cout << "You did not complete the puzzle.\n";
                }
            }
            std::cout << "The " << this->loc.south->roomName << " door is locked.\n";
        }
        else {
            this->loc.playerOccupied = false;
            this->loc = *this->loc.south;
            this->loc.playerOccupied = true;

        }
    }
    else if (userInput == "East" || userInput == "east" || userInput == "EAST") {
        if (this->loc.east->locked == true) {
            if (std::find(inventory.begin(), inventory.end(), "Key") != inventory.end()) {
                bool win = Puzzle(Lock, this->loc, *this);
                if (win) {
                    for (int i = 0; i < this->inventory.size(); i++) {
                        if (this->inventory.at(i) == "Key") {
                            //std::cout << "HERE!!!!! \n";
                            this->inventory.erase(this->inventory.begin() + i);
                        }
                    }
                    this->loc.east->locked = false;
                }
                else {
                    std::cout << "You did not complete the puzzle.\n";
                }
            }
            std::cout << "The " << this->loc.east->roomName << " door is locked.\n";
        }
        else {
            this->loc.playerOccupied = false;
            this->loc = *this->loc.east;
            this->loc.playerOccupied = true;

        }
    }
    else if (userInput == "West" || userInput == "west" || userInput == "WEST") {
        if (this->loc.west->locked == true) {
            if (std::find(inventory.begin(), inventory.end(), "Key") != inventory.end()) {
                bool win = Puzzle(Lock, this->loc, *this);
                if (win) {
                    for (int i = 0; i < this->inventory.size(); i++) {
                        if (this->inventory.at(i) == "Key") {
                            //std::cout << "HERE!!!!! \n";
                            this->inventory.erase(this->inventory.begin() + i);
                        }
                    }
                    this->loc.west->locked = false;
                }
                else {
                    std::cout << "You did not complete the puzzle.\n";
                }
            }
            std::cout << "The " << this->loc.west->roomName << " door is locked.\n";
        }
        else {
            this->loc.playerOccupied = false;
            this->loc = *this->loc.west;
            this->loc.playerOccupied = true;

        }
    }
}















void Player::playerMove(Player& p, Room& r, Monster& m) {
    std::string userInput;
    std::string Lock = "Lock";
    std::cout << "Select your destination.\n";
    if (p.loc.north != NULL) {
        std::cout << "North: " << p.loc.north->roomName << "\n";
        //std::cout << "Is the North door locked? " << p.loc.north->locked << "\n";
    }
    if (p.loc.south != NULL) {
        std::cout << "South: " << p.loc.south->roomName << "\n";
    }
    if (p.loc.east != NULL) {
        std::cout << "East: " << p.loc.east->roomName << "\n";
    }
    if (p.loc.west != NULL) {
        std::cout << "West: " << p.loc.west->roomName << "\n";
    }

    std::cin >> userInput;
    if (userInput == "North" || userInput == "north" || userInput == "NORTH") {
        if (p.loc.north->locked == true) {
            if (std::find(inventory.begin(), inventory.end(), "Key") != inventory.end()) {
                bool win = Puzzle(Lock, r, p);
                if (win) {
                    for (int i = 0; i < p.inventory.size(); i++) {
                        if (p.inventory.at(i) == "Key") {
                            //std::cout << "HERE!!!!! \n";
                            p.inventory.erase(p.inventory.begin() + i);
                        }
                    }
                    p.loc.north->locked = false;
                }
                else {
                    std::cout << "You did not complete the puzzle.\n";
                }
            }
            std::cout << "The " << p.loc.north->roomName << " door is locked.\n";
        }
        else {
            p.loc.playerOccupied = false;
            p.loc = *p.loc.north;
            p.loc.playerOccupied = true;

        }
    }
    else if (userInput == "South" || userInput == "south" || userInput == "SOUTH") {
        if (p.loc.south->locked == true) {
            if (std::find(inventory.begin(), inventory.end(), "Key") != inventory.end()) {
                bool win = Puzzle(Lock, r, p);
                if (win) {
                    for (int i = 0; i < p.inventory.size(); i++) {
                        if (p.inventory.at(i) == "Key") {
                            //std::cout << "HERE!!!!! \n";
                            p.inventory.erase(p.inventory.begin() + i);
                        }
                    }
                    p.loc.south->locked = false;
                }
                else {
                    std::cout << "You did not complete the puzzle.\n";
                }
            }
            std::cout << "The " << p.loc.south->roomName << " door is locked.\n";
        }
        else {
            p.loc.playerOccupied = false;
            p.loc = *p.loc.south;
            p.loc.playerOccupied = true;

        }
    }
    else if (userInput == "East" || userInput == "east" || userInput == "EAST") {
        if (p.loc.east->locked == true) {
            if (std::find(inventory.begin(), inventory.end(), "Key") != inventory.end()) {
                bool win = Puzzle(Lock, r, p);
                if (win) {
                    for (int i = 0; i < p.inventory.size(); i++) {
                        if (p.inventory.at(i) == "Key") {
                            //std::cout << "HERE!!!!! \n";
                            p.inventory.erase(p.inventory.begin() + i);
                        }
                    }
                    p.loc.east->locked = false;
                }
                else {
                    std::cout << "You did not complete the puzzle.\n";
                }
            }
            std::cout << "The " << p.loc.east->roomName << " door is locked.\n";
        }
        else {
            p.loc.playerOccupied = false;
            p.loc = *p.loc.east;
            p.loc.playerOccupied = true;

        }
    }
    else if (userInput == "West" || userInput == "west" || userInput == "WEST") {
        if (p.loc.west->locked == true) {
            if (std::find(inventory.begin(), inventory.end(), "Key") != inventory.end()) {
                bool win = Puzzle(Lock, r, p);
                if (win) {
                    for (int i = 0; i < p.inventory.size(); i++) {
                        if (p.inventory.at(i) == "Key") {
                            //std::cout << "HERE!!!!! \n";
                            p.inventory.erase(p.inventory.begin() + i);
                        }
                    }
                    p.loc.west->locked = false;
                }
                else {
                    std::cout << "You did not complete the puzzle.\n";
                }
            }
            std::cout << "The " << p.loc.west->roomName << " door is locked.\n";
        }
        else {
            p.loc.playerOccupied = false;
            p.loc = *p.loc.west;
            p.loc.playerOccupied = true;

        }
    }
}