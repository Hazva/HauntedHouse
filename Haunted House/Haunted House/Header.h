#pragma once
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <string>
//#include "PlayerHeader.h"
//BUGS/THINGS TO FIX OR DO BEFORE FINALIZING (That I could find)
//hide still using monstermove old code, can lead to double moving while you are hiding. Done probably (check)
//all locks use the same combination
//not really a bug but get rid of all the testing code
//maybe add descriptions for all items
//make description output your inventory (pass in player)
//maybe just merge description and inventory. 
//IF YOU GET HIT YOU CAN WALK STRAIGHT THROUGH KEY DOORS STILL. I ALMOST FORGOT ABOUT THAT, I'VE KNOWN ABOUT IT FOR SO LONG BUT NEVER BOTHERED TO FIX IT.
//above should be fixed now
//FINAL STUFF. Keypad and Interacts still have test code, and when you get an item from completing a puzzle it should tell you (like fuel or etc)
//interacts, investigate, and everything re-initializes when you enter and exit a room. rooms don't re lock themselves though, so it's localized to only interacts 
//investigate. really strange. It seems like it is playerMove??????? Hiding and then leaving doesn't change anything. Take a look at both hide and playerMove. 
//for interacts: create booleans for each puzzle, set them to true on clear, if they are set to true then the player can no longer interact with them as they have already completed them.
//did above, but currently it treats the player as if they auto-fail rather than they have already done it. It does work though.
//for move: making it more similar to hide, setting player location to the returned new player.loc
//

std::vector<int> lockAns = { 0, 0, 0 };
std::vector<int> lockAns2 = { 0, 0, 0 };
std::vector<int> lockAns3 = { 0, 0, 0 };
int srKeypad[4] = {0, 0, 0, 0};
bool keypadClear = false;
bool clockClear = false;
bool fuseClear = false;
bool deskClear = false;

class Room {
public:
    std::vector<std::string> objects{ "", "", "", "", "" };
    std::string ary[5] = { "1", "2", "3", "4" , "5" };
    std::string roomName;
    bool hasKey = false;
    Room* north;
    Room* east;
    Room* west;
    Room* south;
    std::vector<std::string> interacts;
    //puzzle list: 
    bool playerOccupied;
    bool monsterOccupied;
    bool locked = false;
    Room();
    ~Room();
};

Room::Room() {

}

Room::~Room() {

}

// This function prints contents of linked list
// starting from the given node
void printList(Room* n)
{
    while (n != NULL) {
        std::cout << n->roomName << " ";
        n = n->east;
    }
}

class Monster {
public:
    Room loc;
    void monsterMove();
    Monster();
    ~Monster();
};

Monster::Monster() {

}

Monster::~Monster() {

}

class Player {
public:
    std::vector<std::string> inventory{ "", "", "", "", "" };
    Room loc;
    void Listen(Room r, int d, Monster m);
    void Hide(Player p, Room r, Monster m);
    //void playerMove(Player &p, Room &r, Monster &m);
    void playerMove2(Monster& m);
    Room playerMove3(Monster& m);
    Room previousRoom;
    Player();
    ~Player();
};

Player::Player() {

}

Player::~Player() {

}

void Player::Listen(Room loc, int d, Monster m) {
    d = d - 1;
    std::string foundMonster;
    //std::string northString, southString, eastString, westString;
    //std::cout << "Started listening. \n";
    if (loc.north != NULL && d > 0) {
        //std::cout << "I'm listening north. \n";
        Listen(*loc.north, d, m);
    }

    if (loc.south != NULL && d > 0) {
        //std::cout << "I'm listening south. \n";
        Listen(*loc.south, d, m);
    }

    if (loc.east != NULL && d > 0) {
        //std::cout << "I'm listening east. \n";
        Listen(*loc.east, d, m);
    }

    if (loc.west != NULL && d > 0) {
        //std::cout << "I'm listening west. \n";
        Listen(*loc.west, d, m);
    }
    if (loc.roomName == m.loc.roomName) {
        std::cout << "Found monster in: ";
        std::cout << loc.roomName << "\n";
    }
}

//we may have to use references. Also vector and arrays seems to not be the issue so just use whichever we want
void Investigate(Player &p, Room &r) {
    std::string userInput;
    //std::cout << r.roomName << "\n";
    //std::cout << r.objects.size() << "\n";
    //std::cout << r.roomName << "\n";
    //std::cout << r.objects.at(0) << "\n";
    for (int i = 0; i < r.objects.size(); i++) {
        std::cout << r.objects.at(i) << "\n";
    }
    //std::cout << "Investigated. \n";
    if (r.objects.size() == 0) {
        std::cout << "There was nothing to find. \n";
    }
    else {
        std::cout << "What do you wish to take? \n";
        std::cin >> userInput;
        for (int i = 0; i < r.objects.size(); i++) {
            if (r.objects.at(i) == userInput) {
                if ((userInput == "Key1") || (userInput == "Key2") || (userInput == "Key3")) {
                    p.loc.hasKey = false;
                }
                p.inventory.push_back(r.objects[i]);
                r.objects.erase(r.objects.begin()+i);
            }

        }
        //bool thing = std::find(r->objects.begin(), r->objects.end(), userInput) != r->objects.end();
    }
}

//most puzzles do not actually give the player any reward at this point in time and you can skip basically all of them to complete the game. Most of these should just give you a key or a 
//necessary item and then the player has to do them.
//each lock has the exact same combination
//can't unlock specifically the basement door. EDIT: fixed that. Only move north had the key unlock code. Now only move north and south have it, add it to east / west later. 
bool Puzzle(std::string &puz, Room &r, Player &p) {
    //std::cout << "This is puzzling.\n";
    std::string userLine;
    std::string userLine2;
    int userInput;
    //int srKeypad = 9136;
    int stClock = 113015;
    bool solved = false;
    int placeholder;
    std::vector<int> row1 = {0, 0, 0, 0};
    std::vector<int> row2 = {0, 0, 0, 0};
    std::vector<int> row3 = {0, 0, 0, 0};
    std::vector<int> answer = { 0, 0, 0, 0};
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
    if (puz == "Keypad" && keypadClear != true) {
        std::cout << "This orange keypad has four digits.\nWhat do you type?\n";
        std::stringstream ss;
        ss << srKeypad[0] << srKeypad[1] << srKeypad[2] << srKeypad[3];
        std::string strNum = ss.str();
        //std::cout << strNum << " AAAAAAAAAAAA\n";
        std::cin >> userInput;
        if (userInput == std::stoi(strNum)) {
            std::cout << "The keypad unlocks. You find some Car Keys inside.\n";
            p.inventory.push_back("Keys");
            keypadClear = true;
            return true;
        }
        //stringstream conversion https://www.programiz.com/cpp-programming/string-int-conversion
        //convert srKeypad to string to concatenate to compare userInput that is a string now to this combined randomized string that was originally an int and we also have to turn our userInput
        //into an array and compare it maybe? unsure
    }
    else if (puz == "Clock" && clockClear != true) {
        std::cout << "This clock has stopped. You can adjust the hands manually.\nYou adjust the hour hand, minute hand, and then seconds hand sequentially. What do you change them to?\n";
        std::cin >> userInput;
        if (userInput == stClock) {
            std::cout << "The hands all lock into place, and the clock opens. You take an orange slip of paper from inside.\n";
            //add key to players inventory here, I guess you'll have to pass in player for this
            p.inventory.push_back("OrangePaper");
            clockClear = true;
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
    else if (puz == "Fuse" && fuseClear != true) {
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
                fuseClear = true;
                return true;
            }
        }
    }
    else if (puz == "Desk" && deskClear != true) {
        int pairs = 0;
        int unknown[4][4] = {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}};
        int solution[4][4] = {
            {1,4,8,3},
            {5,2,7,8},
            {6,3,5,1},
            {2,7,6,4}};
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
                    deskClear = true;
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

bool Interact(Player &p, Room &r) {
    std::string userInput;
    bool win;
    if (r.interacts.size() > NULL) {
        for (int i = 0; i < r.interacts.size(); i++) {
            //std::cout << "INTERACTS. \n";
            std::cout << r.interacts.at(i) << "\n";
        }
        std::cout << "What do you want to interact with? \n";
        std::cin >> userInput;
        for (int i = 0; i < r.interacts.size(); i++) {
            if (r.interacts.at(i) == userInput) {
                win = Puzzle(userInput, r, p);
                if (win) {
                    r.interacts.erase(r.interacts.begin() + i);
                    if (p.loc.roomName == "Outdoors") {
                        return true;
                    }
                }
                else {
                    std::cout << "You did not complete the puzzle.\n";
                }
            }

        }
    }
    else {
        std::cout << "There is nothing in this room for you to interact with. \n";
    }
    return false;
}

//may or may not need no spaces for object names? I don't really know. Also make this output your inventory when called. 
//list of items
//fuel, keys, tire, painting
std::string Description(std::string& s, Player &p) {
    //output inventory code. pass in player later. 
    std::stringstream ss;
    if (s == "Key1" || s == "Key2" || s == "Key3") {
        return "An ordinary key. It should unlock something.";
    }
    else if (s == "Clock") {
        return "A formerly wall-mounted clock. It seems to have stopped at 11 hours, 30 minutes, and 15 seconds. \n";
    }
    else if (s == "Fuel") {
        return "A fuel cannister. It could refuel a car. \n";
    }
    else if (s == "Keys") {
        return "It seems to be keys for a car. \n";
    }
    else if (s == "Tire") {
        return "A spare tire, presumably for a car. \n";
    }
    else if (s == "Painting") {
        return "An ordinary painting, there's nothing of note on the front or the back. \n";
    }
    else if (s == "OrangePen") {
        ss << "An Orange pen with a XXX" << srKeypad[3] << "inscribed on it. \n";
        std::string strNum = ss.str();
        return strNum;
    }
    else if (s == "OrangeVase") {
        ss << "An Orange Vase with the number " << srKeypad[0] << "XXX on the side. \n";
        std::string strNum = ss.str();
        return strNum;
    }
    else if (s == "OrangePainting") {
        ss << "A Painting of an Orange with a X" << srKeypad[1] << "XX behind it. \n";
        std::string strNum = ss.str();
        return strNum;
    }
    else if (s == "OrangePaper") {
        ss << "A slip of Paper with an Orange XX" << srKeypad[2] <<"X written on it. \n";
        std::string strNum = ss.str();
        return strNum;
    }
    return "a";
}

void Player::playerMove2(Monster& m) {
    this->previousRoom = this->loc;
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
            if ((std::find(inventory.begin(), inventory.end(), "Key1") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key2") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key3") != inventory.end())) {
                bool win = Puzzle(Lock, this->loc, *this);
                if (win) {
                    for (int i = 0; i < this->inventory.size(); i++) {
                        if ((this->inventory.at(i) == "Key1") || (this->inventory.at(i) == "Key2") || (this->inventory.at(i) == "Key3")) {
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
            *this->loc.south = previousRoom;
            this->loc.playerOccupied = true;

        }
    }
    else if (userInput == "South" || userInput == "south" || userInput == "SOUTH") {
        if (this->loc.south->locked == true) {
            if ((std::find(inventory.begin(), inventory.end(), "Key1") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key2") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key3") != inventory.end())) {
                bool win = Puzzle(Lock, this->loc, *this);
                if (win) {
                    for (int i = 0; i < this->inventory.size(); i++) {
                        if ((this->inventory.at(i) == "Key1") || (this->inventory.at(i) == "Key2") || (this->inventory.at(i) == "Key3")) {
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
            *this->loc.north = previousRoom;
            this->loc.playerOccupied = true;

        }
    }
    else if (userInput == "East" || userInput == "east" || userInput == "EAST") {
        if (this->loc.east->locked == true) {
            if ((std::find(inventory.begin(), inventory.end(), "Key1") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key2") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key3") != inventory.end())) {
                bool win = Puzzle(Lock, this->loc, *this);
                if (win) {
                    for (int i = 0; i < this->inventory.size(); i++) {
                        if ((this->inventory.at(i) == "Key1") || (this->inventory.at(i) == "Key2") || (this->inventory.at(i) == "Key3")) {
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
            *this->loc.west = previousRoom;
            this->loc.playerOccupied = true;

        }
    }
    else if (userInput == "West" || userInput == "west" || userInput == "WEST") {
        if (this->loc.west->locked == true) {
            if ((std::find(inventory.begin(), inventory.end(), "Key1") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key2") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key3") != inventory.end())) {
                bool win = Puzzle(Lock, this->loc, *this);
                if (win) {
                    for (int i = 0; i < this->inventory.size(); i++) {
                        if ((this->inventory.at(i) == "Key1") || (this->inventory.at(i) == "Key2") || (this->inventory.at(i) == "Key3")) {
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
            *this->loc.east = previousRoom;
            this->loc.playerOccupied = true;

        }
    }
}

Room Player::playerMove3(Monster& m) {
    Room previousRoom = this->loc;
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
            if ((std::find(inventory.begin(), inventory.end(), "Key1") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key2") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key3") != inventory.end())) {
                bool win = Puzzle(Lock, this->loc, *this);
                if (win) {
                    for (int i = 0; i < this->inventory.size(); i++) {
                        if ((this->inventory.at(i) == "Key1") || (this->inventory.at(i) == "Key2") || (this->inventory.at(i) == "Key3")) {
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
            if ((std::find(inventory.begin(), inventory.end(), "Key1") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key2") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key3") != inventory.end())) {
                bool win = Puzzle(Lock, this->loc, *this);
                if (win) {
                    for (int i = 0; i < this->inventory.size(); i++) {
                        if ((this->inventory.at(i) == "Key1") || (this->inventory.at(i) == "Key2") || (this->inventory.at(i) == "Key3")) {
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
            if ((std::find(inventory.begin(), inventory.end(), "Key1") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key2") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key3") != inventory.end())) {
                bool win = Puzzle(Lock, this->loc, *this);
                if (win) {
                    for (int i = 0; i < this->inventory.size(); i++) {
                        if ((this->inventory.at(i) == "Key1") || (this->inventory.at(i) == "Key2") || (this->inventory.at(i) == "Key3")) {
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
            if ((std::find(inventory.begin(), inventory.end(), "Key1") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key2") != inventory.end()) || (std::find(inventory.begin(), inventory.end(), "Key3") != inventory.end())) {
                bool win = Puzzle(Lock, this->loc, *this);
                if (win) {
                    for (int i = 0; i < this->inventory.size(); i++) {
                        if ((this->inventory.at(i) == "Key1") || (this->inventory.at(i) == "Key2") || (this->inventory.at(i) == "Key3")) {
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
    return previousRoom;
}


void Monster::monsterMove() {
    int roomChoices[4] = { 0, 0, 0, 0 };
    int roomCounter = 0;
    int monsterDirection = 0;
    //Room placeHolder = Room();
    //std::cout << "MONSTER IS MOVING \n";
    if (this->loc.north != NULL) {
        roomCounter++;
        roomChoices[0] = 1;
        //std::cout << "Monster thought about going north. \n";

    }
    if (this->loc.south != NULL) {
        roomCounter++;
        roomChoices[1] = 2;
        //std::cout << "Monster thought about going south. \n";
        
    }
    if (this->loc.east != NULL) {
        roomCounter++;
        roomChoices[2] = 3;
        //std::cout << "Monster thought about going east. \n";

    }
    if (this->loc.west != NULL) {
        roomCounter++;
        roomChoices[3] = 4;
        //std::cout << "Monster thought about going west. \n";

    }
    int isZero = 0;
    while (isZero == 0) {
        monsterDirection = rand() % 4;
        isZero = roomChoices[monsterDirection];
        //std::cout << isZero << "\n";
    }
    switch (isZero) {
    case 1:
        //std::cout << "Tried to move north. \n";
        this->loc.monsterOccupied = false;
        //std::cout << "Unoccupying \n";
        //std::cout << this->loc.north->roomName;
        this->loc = *this->loc.north;
        //std::cout << "Moved to new room \n";
        this->loc.monsterOccupied = true;
        //std::cout << "Reoccupying \n";

        break;

    case 2:
        //std::cout << "Tried to move south. \n";
        this->loc.monsterOccupied = false;
        //std::cout << "Unoccupying \n";
        //std::cout << this->loc.south->roomName;
        this->loc = *this->loc.south;
        //std::cout << "Moved to new room \n";
        this->loc.monsterOccupied = true;
        //std::cout << "Reoccupying \n";
        break;

    case 3:
        //std::cout << "Tried to move east. \n";
        this->loc.monsterOccupied = false;
        //std::cout << "Unoccupying \n";
        //std::cout << this->loc.east->roomName;
        this->loc = *this->loc.east;
        //std::cout << "Moved to new room \n";
        this->loc.monsterOccupied = true;
        //std::cout << "Reoccupying \n";
        break;

    case 4:
        //std::cout << "Tried to move west. \n";
        this->loc.monsterOccupied = false;
        //std::cout << "Unoccupying \n";
        //std::cout << this->loc.west->roomName;
        this->loc = *this->loc.west;
        //std::cout << "Moved to new room \n";
        this->loc.monsterOccupied = true;
        //std::cout << "Reoccupying \n";
        break;

    default:
        
        std::cout << "default switch case\n";
    }
}
//A LOT OF TESTING COUTS ABOVE


//hide still using monstermove old code, can lead to double moving while you are hiding.
void Player::Hide(Player p, Room r, Monster m) {
    Room lastLoc = p.loc;
    p.loc = r;
    std::string userInput;
    while (p.loc.roomName == "Hidden") {
        std::cout << "Do you wish to Listen or Leave? \n";
        std::cin >> userInput;
        if (userInput == "Listen" || userInput == "listen" || userInput == "LISTEN") {
            std::cout << "You are listening... \n";
            p.Listen(lastLoc, 2, m);
        }
        else if (userInput == "Leave" || userInput == "leave" || userInput == "LEAVE") {
            std::cout << "You are leaving... \n";
            p.loc = lastLoc;
            break;
        }
        //Room placeHolder = Room();
        m.monsterMove();
    }
}