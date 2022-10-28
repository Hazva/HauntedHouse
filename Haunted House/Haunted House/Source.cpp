#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <stdio.h>
//#include "MonsterHeader.h"
//#include "RoomHeader.h"
//#include "PlayerHeader.h"
#include "Header.h"

//(process 7856) exited with code -1073741819.
//means that your program was terminated due to an access violation. This error can occur for a variety of reasons, including de-referencing a NULL pointer or referencing an invalid address.
//When it crashes, it always crashes after "Tried to move south." I have a message from myself that shows it crashing after saying that AND the location name though. Either way, that only
//appears in monster move. Speaking of monster move,
//we still have two monster moves. So that might have something to do with it still. I don't remember why we didn't get rid of one of them, there was probably a reason. 

// Driver code
int main()
{   
    int timer = 0;
    srand(time(NULL));
    srKeypad[0] = rand() % 10;
    srKeypad[1] = rand() % 10;
    srKeypad[2] = rand() % 10;
    srKeypad[3] = rand() % 10;
    bool alive = true;
    std::string userInput;
    std::string descriptionInput;
    Player player;
    Monster monster;
    Room* StartRoom = NULL;
    Room* Stairs = NULL;
    Room* Study = NULL;
    Room* Ballroom = NULL;
    Room* Dining = NULL;
    Room* Kitchen = NULL;
    Room* Outdoors = NULL;
    Room* GrandStairs = NULL;
    Room* MasterBedroom = NULL;
    Room* Bedroom = NULL;
    Room* Bathroom = NULL;
    Room* Hallway = NULL;
    Room* HidingSpace = NULL;
    Room* Ladder = NULL;
    Room* Attic = NULL;
    Room* Basement = NULL;

    // allocate 3 nodes in the heap
    StartRoom = new Room();
    Stairs = new Room();
    Ballroom = new Room();
    Study = new Room();
    Dining = new Room();
    Kitchen = new Room();
    Outdoors = new Room();
    GrandStairs = new Room();
    MasterBedroom = new Room();
    Bedroom = new Room();
    Bathroom = new Room();
    Hallway = new Room();
    HidingSpace = new Room();
    Ladder = new Room();
    Attic = new Room();
    Basement = new Room();

    HidingSpace->roomName = "Hidden";
    StartRoom->roomName = "Living Room"; // assign data in first node
    StartRoom->east = Stairs; // Link first node with second
    Stairs->west = StartRoom;
    //remove startroom key at some point. still here for testing purposes.
    //StartRoom->objects[1] = "Key";
    //StartRoom->interacts.push_back("Keypad");

    Stairs->roomName = "Stairs"; // assign data to second node
    Stairs->north = Study;

    Study->roomName = "Study";
    Study->south = Stairs;
    Study->locked = true;
    Study->objects[1] = "OrangePen";
    //Study->objects[2] = "Tire";
    Study->interacts.push_back("Desk");
    Study->interacts.push_back("Clock");

    Ballroom->roomName = "Ballroom"; // assign data in Ballroom node
    StartRoom->north = Ballroom; // Link first node with second
    Ballroom->south = StartRoom;
    Ballroom->north = NULL;
    Ballroom->west = Kitchen; // Link first node with second
    Ballroom->east = GrandStairs;
    Ballroom->objects[1] = "Painting";
    Ballroom->objects[2] = "OrangeVase";

    Kitchen->roomName = "Kitchen"; // assign data in Kitchen node
    Kitchen->south = Dining;
    Kitchen->east = Ballroom;
    Kitchen->objects[1] = "OrangePainting";

    Dining->roomName = "Dining Room"; // assign data in Dining node
    StartRoom->west = Dining; // Link first node with second
    Dining->east = StartRoom;
    Dining->north = Kitchen;
    Dining->west = Outdoors;
    Dining->objects[1] = "Key1";
    Dining->hasKey = true;

    Outdoors->roomName = "Outdoors";
    Outdoors->east = Dining;
    Outdoors->south = Basement;
    Outdoors->interacts.push_back("Car");

    GrandStairs->roomName = "Grand Stairs";
    GrandStairs->west = Ballroom;
    GrandStairs->north = MasterBedroom;
    GrandStairs->south = Bedroom;
    GrandStairs->east = Bathroom;

    MasterBedroom->roomName = "Master Bedroom";
    MasterBedroom->south = GrandStairs;
    MasterBedroom->locked = true;
    MasterBedroom->interacts.push_back("Keypad");
    //MasterBedroom->objects[2] = "Keys";

    Bedroom->roomName = "Bedroom";
    Bedroom->north = GrandStairs;
    Bedroom->east = MasterBedroom;
    Bedroom->objects[2] = "Clock";

    Bathroom->roomName = "Bathroom";
    Bathroom->west = GrandStairs;
    Bathroom->objects[1] = "Key2";
    Bathroom->hasKey = true;

    Hallway->roomName = "Hallway";
    Hallway->east = MasterBedroom;
    MasterBedroom->west = Hallway;
    Hallway->west = Stairs;
    Stairs->east = Hallway;

    Ladder->roomName = "Ladder";
    Hallway->north = Ladder;
    Ladder->south = Hallway;
    Ladder->north = Attic;
    Attic->roomName = "Attic";
    Attic->south = Ladder;
    Attic->objects[1] = "Key3";
    Attic->hasKey = true;

    Basement->roomName = "Basement";
    Basement->north = Outdoors;
    Basement->locked = true;
    Basement->interacts.push_back("Fuse");
    //Basement->objects[1] = "Fuel";


    Room* roomList[13] = {Attic, Dining, Ladder, Hallway, Bedroom, Bathroom, GrandStairs, Ballroom, Outdoors, StartRoom, Kitchen, Stairs};

    
    monster.loc = *Bathroom;
    player.loc = *StartRoom;
    monster.loc.monsterOccupied = true;
    player.loc.playerOccupied = true;
    for (int i = 0; i < 3; i++) {
        lockAns[i] = 1 + rand() % 3;
        //std::cout << lockAns[i];
    }
    for (int i = 0; i < 3; i++) {
        lockAns2[i] = 1 + rand() % 3;
        //std::cout << lockAns2[i];
    }
    for (int i = 0; i < 3; i++) {
        lockAns3[i] = 1 + rand() % 3;
        //std::cout << lockAns3[i];
    }
    //above is testing I think. At least the cout part.
    int monsterDirection = 0;
    int playerLife = 3;
    while (alive) {
        //std::cout << "Monster Location: " << monster.loc.roomName << "\n";
        std::cout << "1: Move\n2: Listen\n3: Hide\n4: Investigate\n5: Inventory\n6: Interact\n7: Description\n";
        std::cin >> userInput;
        if (userInput == "1") {
            //player.playerMove(player, player.loc, monster);
            player.playerMove2(monster);
            timer += 100;
        }
        else if (userInput == "2") {
            std::cout << "You are listening... \n";
            player.Listen(player.loc, 2, monster);
            timer += 50;
        }
        else if (userInput == "3") {
            player.Hide(player, *HidingSpace, monster);
            timer += 50;
        }
        else if (userInput == "4") {
            Investigate(player, player.loc);
            timer += 25;
        }
        else if (userInput == "5") {
            for (int i = 0; i < player.inventory.size(); i++) {
                std::cout << player.inventory.at(i) << "\n";
                timer += 25;
            }
        }
        else if (userInput == "6") {
            bool win = Interact(player, player.loc);
            if (win) {
                std::cout << "You have escaped the haunted house.\nCONGRATULATIONS!\n";
                break;
            }
            timer += 100;
        }
        else if (userInput == "7") {
            for (int i = 0; i < player.inventory.size(); i++) {
                std::cout << player.inventory.at(i) << "\n";
            }
            std::cout << "What do you wish to examine?\n";
            std::cin >> descriptionInput;
            for (int i = 0; i < player.inventory.size(); i++) {
                if (player.inventory.at(i) == descriptionInput) {
                    std::cout << Description(descriptionInput, player) << "\n";
                }
            }
            timer += 25;
        }
        if (player.loc.roomName == monster.loc.roomName) {
            playerLife -= 1;
            std::cout << "The monster has hit you. ";
            if (playerLife <= 0) {
                std::cout << "You died!\n";
                break;
            }
            else if (playerLife == 1) {
                std::cout << "You are now one hit from death.\n";
            }
            else if (playerLife > 1) {
                std::cout << "You have been injured.\n";
            }
            std::cout << "You are running, select your destination.\n";
            player.playerMove2(monster);
        }
        //monster move not working, it double moves and then crashes shortly after. The error code has something to do with "an access violation. This error can occur for a variety of reasons, including 
        //de-referencing a NULL pointer or referencing an invalid address."
        //seperate issue with moving, has had issues when moving into attic and master bedroom no idea what the issue is.
        if (timer >= 100) {
            timer = 0;
            //std::cout << "MONSTER MOVING.\n";
            //can use this / self
            monster.monsterMove();
        
			//source of error? monster moving is still stuck in the same two rooms. monsterMove(monster, *StartRoom);
			
        }
        if (player.loc.roomName == monster.loc.roomName) {
            playerLife -= 1;
            std::cout << "The monster has hit you. ";
            if (playerLife <= 0) {
                std::cout << "You died!\n";
                break;
            }
            else if (playerLife == 1) {
                std::cout << "You are now one hit from death.\n";
            }
            else if (playerLife > 1) {
                std::cout << "You have been injured.\n";
            }
            std::cout << "You are running, select your destination.\n";
            player.playerMove2(monster);
        }
    }
    return 0;
}
