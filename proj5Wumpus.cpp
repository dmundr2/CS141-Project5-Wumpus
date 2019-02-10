/* prog5Wumpus.cpp
 
 Description: Navigate a maze to kill the Wumpus.
 Implementation of a 1972 game by Gregory Yob.
 
 Results of a program run are shown below:
https://codio.com/dreed/prog5-hunt-the-wumpus/filetree#
      
 */
#include <iostream>
#include <iomanip>   // for setw()
#include <cctype>    // for toupper()
#include <cstdlib>   // for rand() and srand()
#include <ctime>     // to seed random number generator with time(0)
#include <sstream>
#include <string>
using namespace std;

// global constants
#define MAX_LINE_LENGTH 81
#define NUMBER_OF_ROOMS 20

//--------------------------------------------------------------------------------
void displayCave()
{
        cout<< "       ______18______             \n"
            << "      /      |       \\           \n"
            << "     /      _9__      \\          \n"
            << "    /      /    \\      \\        \n"
            << "   /      /      \\      \\       \n"
            << "  17     8        10     19       \n"
            << "  | \\   / \\      /  \\   / |    \n"
            << "  |  \\ /   \\    /    \\ /  |    \n"
            << "  |   7     1---2     11  |       \n"
            << "  |   |    /     \\    |   |      \n"
            << "  |   6----5     3---12   |       \n"
            << "  |   |     \\   /     |   |      \n"
            << "  |   \\       4      /    |      \n"
            << "  |    \\      |     /     |      \n"
            << "  \\     15---14---13     /       \n"
            << "   \\   /            \\   /       \n"
            << "    \\ /              \\ /        \n"
            << "    16---------------20           \n"
            << endl;
}//end displayCave()


//--------------------------------------------------------------------------------
void displayInstructions()
{
    cout<< "Hunt the Wumpus:                                             \n"
        << "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
        << "room has 3 tunnels leading to other rooms.                   \n"
        << "                                                             \n"
        << "Hazards:                                                     \n"
        << "1. Two rooms have bottomless pits in them.  If you go there you fall and die.  \n"
        << "2. Two other rooms have super-bats.  If you go there, the bats grab you and    \n"
        << "   fly you to some random room, which could be troublesome.  Then those bats go\n"
        << "   to a new room different from where they came from and from the other bats.  \n"
        << "3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and   \n"
        << "   is too heavy for bats to lift.  Usually he is asleep.  Two things wake      \n"
        << "   him up: Anytime you shoot an arrow, or you entering his room.  When he      \n"
        << "   wakes he moves if he is in an odd-numbered room, but stays still otherwise. \n"
        << "   After that, if he is in your room, he eats you and you die!                 \n"
        << "                                                                               \n"
        << "Moves:                                                                         \n"
        << "On each move you can do the following, where input can be upper or lower-case: \n"
        << "1. Move into an adjacent room.  To move enter 'M' followed by a space and      \n"
        << "   then a room number.                                                         \n"
        << "2. Shoot your guided arrow through a list of up to three adjacent rooms, which \n"
        << "   you specify.  Your arrow ends up in the final room.                         \n"
        << "   To shoot enter 'S' followed by the number of rooms (1..3), and then the     \n"
        << "   list of the desired number (up to 3) of adjacent room numbers, separated    \n"
        << "   by spaces. If an arrow can't go a direction because there is no connecting  \n"
        << "   tunnel, it ricochets and moves to the lowest-numbered adjacent room and     \n"
        << "   continues doing this until it has traveled the designated number of rooms.  \n"
        << "   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You \n"
        << "   automatically pick up the arrow if you go through a room with the arrow in  \n"
        << "   it.                                                                         \n"
        << "3. Enter 'R' to reset the person and hazard locations, useful for testing.     \n"
        << "4. Enter 'C' to cheat and display current board positions.                     \n"
        << "5. Enter 'D' to display this set of instructions.                              \n"
        << "6. Enter 'P' to print the maze room layout.                                    \n"
        << "7. Enter 'X' to exit the game.                                                 \n"
        << "                                                                               \n"
        << "Good luck!                                                                     \n"
        << " \n"
        << endl;
}//end displayInstructions()

//--------------------------------------------------------------------------------
//assigns the neighbor room values 
// *** Yuwei: you can instead use one array for each room to store its neighbors, for example, neighbors[1]={2,5,8}
// *** Yuwei: which can make this block much shorter
void assignNeighbors(int neighborRooms[][21]){
  neighborRooms[0][1] = 2;
  neighborRooms[1][1] = 5;
  neighborRooms[2][1] = 8;
  neighborRooms[0][2] = 1;
  neighborRooms[1][2] = 3;
  neighborRooms[2][2] = 10;
  neighborRooms[0][3] = 2;
  neighborRooms[1][3] = 4;
  neighborRooms[2][3] = 12;
  neighborRooms[0][4] = 3;
  neighborRooms[1][4] = 5;
  neighborRooms[2][4] = 14;
  neighborRooms[0][5] = 1;
  neighborRooms[1][5] = 4;
  neighborRooms[2][5] = 6;
  neighborRooms[0][6] = 5;
  neighborRooms[1][6] = 7;
  neighborRooms[2][6] = 15;
  neighborRooms[0][7] = 6;
  neighborRooms[1][7] = 8;
  neighborRooms[2][7] = 17;
  neighborRooms[0][8] = 1;
  neighborRooms[1][8] = 7;
  neighborRooms[2][8] = 9;
  neighborRooms[0][9] = 8;
  neighborRooms[1][9] = 10;
  neighborRooms[2][9] = 18;
  neighborRooms[0][10] = 2;
  neighborRooms[1][10] = 9;
  neighborRooms[2][10] = 11;
  neighborRooms[0][11] = 10;
  neighborRooms[1][11] = 12;
  neighborRooms[2][11] = 19;
  neighborRooms[0][12] = 3;
  neighborRooms[1][12] = 11;
  neighborRooms[2][12] = 13;
  neighborRooms[0][13] = 12;
  neighborRooms[1][13] = 14;
  neighborRooms[2][13] = 20;
  neighborRooms[0][14] = 4;
  neighborRooms[1][14] = 13;
  neighborRooms[2][14] = 15;
  neighborRooms[0][15] = 6;
  neighborRooms[1][15] = 14;
  neighborRooms[2][15] = 16;
  neighborRooms[0][16] = 15;
  neighborRooms[1][16] = 17;
  neighborRooms[2][16] = 20;
  neighborRooms[0][17] = 7;
  neighborRooms[1][17] = 16;
  neighborRooms[2][17] = 18;
  neighborRooms[0][18] = 9;
  neighborRooms[1][18] = 17;
  neighborRooms[2][18] = 19;
  neighborRooms[0][19] = 11;
  neighborRooms[1][19] = 18;
  neighborRooms[2][19] = 20;
  neighborRooms[0][20] = 13;
  neighborRooms[1][20] = 16;
  neighborRooms[2][20] = 19;
}

//--------------------------------------------------------------------------------
//checks if the values are neighbors
bool isNeigbor(int valOne, int neighborRoom[][21], int col){
  bool isNeigbor = false;
  for(int i = 0; i < 3; i++){
    if(valOne == neighborRoom[i][col]){
      isNeigbor = true;
    }
  }
  return isNeigbor;
}
//--------------------------------------------------------------------------------
//prints the neighbor rooms
void printNeighbors(int neighborRooms[][21]){
  for(int col = 1; col < 21; col++){
    for(int row = 0; row < 3; row++){
      cout << neighborRooms[row][col] << endl;
    }
    cout << endl;
  }
}

//--------------------------------------------------------------------------------

//assigns the room for each of the objects initially and makes sure the number is random
void makeRandom(int objArray[], int index){
  objArray[index] = rand() % 20 + 1;
  objArray[6] = -1;
  for(int i = 0; i < 7; i++){
    if ((i != index) && (objArray[index] == objArray[i])){
      objArray[index] = rand() % 20 + 1;
      i = 0;
    }
  }
}
//--------------------------------------------------------------------------------
//moves the human to the given room number, changing the corresponding index in the array holding the objects rooms
void moveTo(int roomNum, int roomArray[], int neighborRooms[][21], int& counter){
  bool valid = false;
  for(int i = 0; i < 3; i++){
   if(neighborRooms[i][roomArray[5]] == roomNum){
     counter++;
     roomArray[5] = roomNum;
     valid = true;
   }
 }
  if(valid == false){
    cout << "Invalid move.  Please retry. " << endl;
  }
}
//--------------------------------------------------------------------------------
//prints out the locations of the 7 game objects
void cheatPrint(int roomArray[]){
  cout << "Cheating! Game elements are in the following rooms: " << endl;
  cout << "Player Wumpus Bats1 Bats2 Pit1 Pit2 Arrow" << endl;
  cout << "   " << roomArray[5] << "   " << roomArray[4] << "    " << roomArray[0] << "     "<< roomArray[1] << "    "<< 
    roomArray[2] << "     " << roomArray[3] << "     "<< roomArray[6] <<  endl;
}
//--------------------------------------------------------------------------------
//checks if a wumpus is nearby
void wumpusNear(int roomArray[], int neighborRooms[][21]){
  if(isNeigbor(roomArray[4], neighborRooms, roomArray[5])){
       cout << "You smell a stench.";
     }
}
//check if one of the three rooms
//--------------------------------------------------------------------------------
//check if you entered the wumpus room
void checkWumpus(int roomArray[], int neighborRooms[][21], bool& life){
  if(roomArray[5] == roomArray[4]){
    if((roomArray[5] % 2) != 0){
      roomArray[4] = neighborRooms[0][roomArray[4]];
      cout << "You hear a slithering sound, as the Wumpus slips away." << endl;
      cout << "Whew, that was close!" << endl;
    }
    else{
      cout << "You briefly feel a slimy tentacled arm as your neck is snapped. " << endl;
      cout << "It is over." << endl;
      life = false;
    }
  }
}
//--------------------------------------------------------------------------------
void nearPit(int roomArray[], int neighborRooms[][21]){
  //checks the two pits if the user is in an adjacent room
     if(isNeigbor(roomArray[2], neighborRooms, roomArray[5])){
       cout << "You feel a draft. ";
     }
      
     if(isNeigbor(roomArray[3], neighborRooms, roomArray[5])){
       cout << "You feel a draft. ";
     }

}
//--------------------------------------------------------------------------------
// checks for bats nearby
void nearBats(int roomArray[], int neighborRooms[][21]){
 //checks the two bat rooms if they are adjacent to the person
  if(isNeigbor(roomArray[0], neighborRooms, roomArray[5])){
       cout << "You hear rustling of bat wings. ";
     } 
  if(isNeigbor(roomArray[1], neighborRooms, roomArray[5])){
       cout << "You hear rustling of bat wings. ";
     }
  
}
//--------------------------------------------------------------------------------
//checks for the hazards and displays corresponding message
void checkHazards(int roomArray[], int neighborRooms[][21], bool& life){
  wumpusNear(roomArray, neighborRooms);
  nearPit(roomArray, neighborRooms);
  nearBats(roomArray, neighborRooms);
}
//--------------------------------------------------------------------------------
//checks if the user entered lethal room
void checkPit(int roomArray[], int neighborRooms[][21], bool& life){
  if((roomArray[5] == roomArray[2]) || (roomArray[5] == roomArray[3])){
    cout << "Aaaaaaaaahhhhhh...." << endl;
    cout << "    You fall into a pit and die." << endl;
    life = false;
  }
}
//--------------------------------------------------------------------------------
//checks if user moved into bats
void checkBats(int roomArray[], int neighborRooms[][21]){
 if(roomArray[5] == roomArray[0]){
  int newPerson = rand() % 20 + 1;
  int newBat = rand() % 20 + 1;
  if(newPerson == roomArray[5]){
    newPerson == rand() % 20 + 1;
  }
  if((newBat == roomArray[0]) || (newBat == roomArray[1])){
    newBat = rand() % 20 + 1;
  
  }
  roomArray[5] = newPerson;
  roomArray[0] = newBat;
  cout << "Woah... you're flying!" << endl;
  cout << "You've just been transported by bats to room 10" << endl;
 }
 
  if(roomArray[5] == roomArray[1]){
  int newPerson = rand() % 20 + 1;
  int newBat = rand() % 20 + 1;
  if(newPerson == roomArray[5]){
    newPerson == rand() % 20 + 1;
  }
  if((newBat == roomArray[1]) || (newBat == roomArray[0])){
    newBat = rand() % 20 + 1;
  
  }
  roomArray[5] = newPerson;
  roomArray[1] = newBat;
  cout << "Woah... you're flying!" << endl;
  cout << "You've just been transported by bats to room 10" << endl;
 }
  
  
}
//--------------------------------------------------------------------------------
void resetRooms(int roomArray[]){
  cout << "(Remember arrow value of -1 means it is with the person.)" << endl;
  cout << "Enter the 7 room locations (1..20) for player, wumpus, bats1, bats2, pit1, pit2, and arrow: " << endl;
  cin >> roomArray[5];
  cin >> roomArray[4];
  cin >> roomArray[0];
  cin >> roomArray[1];
  cin >> roomArray[2];
  cin >> roomArray[3];
  cin >> roomArray[6];
}
//--------------------------------------------------------------------------------
//shoot the arrow
int shootArrow(int roomArray[], int neighborRooms[][21], int roomNums, int room1, int room2, int room3, int& counter){
  //check if the user has arrow
  if(roomArray[6] != -1){
    counter++;
    cout << "Sorry, you can't shoot an arrow you don't have.  Go find it." << endl;
  }
  bool isValid = false;
 if(roomArray[6] == -1){
    counter++;
    cout << "Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ";
    cin >> roomNums;
   //if user wants to shoot over one room 
   if(roomNums == 1){
      cin >> room1;
     
     //checks if the target room neighbor is valid and changes the arrays room if so
     if(isNeigbor(room1, neighborRooms, roomArray[5])){
       roomArray[6] = room1;
       isValid = true;
     }
     //checks if ricochets
     if(!isValid){
          cout << "Room 4 is not adjacent.  Arrow ricochets..." << endl;
          roomArray[6] = neighborRooms[0][roomArray[5]];
        }
     //check if the arrow hit a wumpus
     if(roomArray[6] == roomArray[4]){
       cout << "Wumpus has just been pierced by your deadly arrow!" << endl;
       cout << "Congratulations on your victory, you awesome hunter you." << endl;
       cout << "Exiting Program ...";
       exit(-1);
     } 
     //if you do not hit the wumpus, it slithers into the lowest val neighbor
     if(roomArray[6] != roomArray[4]){
       roomArray[4] = neighborRooms[0][roomArray[4]];
     }
    }//end 1 room
   //checks if user wants to shoot two rooms
    if(roomNums == 2){
      cin >> room1;
      cin >> room2;
    //checks if the target room 1 neighbor is valid and changes the arrays room if so
     if(isNeigbor(room1, neighborRooms, roomArray[5])){
       roomArray[6] = room1;
       isValid = true;
     }

    //checks if the target room 2 neighbor is valid and changes the arrays room if so
     if(isNeigbor(room2, neighborRooms, roomArray[6])){
       roomArray[6] = room2;
       isValid = true;
     }
      //check if arrow hit wumpus
      if(roomArray[6] == roomArray[4]){
       cout << "Wumpus has just been pierced by your deadly arrow!" << endl;
       cout << "Congratulations on your victory, you awesome hunter you." << endl;
       cout << "Exiting Program ...";
       exit(-1);
     }
      //if you do not hit the wumpus, it slithers into the lowest val neighbor
      if(roomArray[6] != roomArray[4]){
       roomArray[4] = neighborRooms[0][roomArray[4]];
     }
    }//end 2 room shot
    
   if(roomNums == 3){
     cin >>room1;
     cin >> room2;
     cin >> room3;
    //checks if the target room 1 neighbor is valid and changes the arrays room if so
     if(isNeigbor(room1, neighborRooms, roomArray[5])){
       roomArray[6] = room1;
       isValid = true;
     }
     
      //checks if the target room 2 neighbor is valid and changes the arrays room if so
     if(isNeigbor(room2, neighborRooms, roomArray[6])){
       roomArray[6] = room2;
       isValid = true;
     }
     
     //checks if the target room 3 neighbor is valid and changes the arrays room if so
     if(isNeigbor(room3, neighborRooms, roomArray[6])){
       roomArray[6] = room3;
       isValid = true;
     }

     if(roomArray[6] == roomArray[4]){
       cout << "Wumpus has just been pierced by your deadly arrow!" << endl;
       cout << "Congratulations on your victory, you awesome hunter you." << endl;
       cout << "Exiting Program ...";
       exit(-1);
     }
     //if you do not hit the wumpus, it slithers into the lowest val neighbor
     if(roomArray[6] != roomArray[4]){
       roomArray[4] = neighborRooms[0][roomArray[4]];
     }
   }// end 3 room
  }
 }

//--------------------------------------------------------------------------------
//prints players locations
void myLoc(int roomArray[]){
   cout << "You are in room " << roomArray[5] << ". ";
}
//--------------------------------------------------------------------------------
int main()
{   
    //array for the 6 objects, holding the room they are int
    //index 0 - 7 respectively, human - wumpus - bats1 - bats2 - pit1- pit2- arrow
    int objectRooms[7];
    //used for the main while loop, true until player dies or enters x
    bool isAlive = true;
    //changed when player chooses to move rooms
    int moveRoom;
    //holds input of users desired action ex. m for move, r for reset
    char userInput;
    // holds the valid rooms for the 20 rooms, size 21 so index can line up with room, col 0 blank
    int validRooms[3][21];
    //keeps track of move numbers
    int moveNum = 1;
    //three rooms that the arrows shoot into
    int room1;
    int room2;
    int room3;
    int numRooms;
    //calls functions to assign the array with each rooms valid moves
    assignNeighbors(validRooms);
   
    // Seed the random number generator.  Change seed to time(0) to change output each time.
    // srand(time(0));
    srand(1);   // Use this version in what you turn in
    makeRandom(objectRooms, 0);
    makeRandom(objectRooms, 1);
    makeRandom(objectRooms, 2);
    makeRandom(objectRooms, 3);
    makeRandom(objectRooms, 4);
    makeRandom(objectRooms, 5);
    
    //displayCave();
		//displayInstructions();
    //printNeighbors(validRooms);
		// Lots more code goes here...
		//checks for initial hazards nearby
		
		while(isAlive){
       checkPit(objectRooms, validRooms, isAlive);
       checkWumpus(objectRooms, validRooms, isAlive);
       if(isAlive == false){
         break;
       }
// *** Yuwei: code within the same block should line up
      checkBats(objectRooms, validRooms);
       myLoc(objectRooms);
       wumpusNear(objectRooms, validRooms);
       nearPit(objectRooms, validRooms);
       nearBats(objectRooms, validRooms);
       cout << endl << moveNum <<  ". Enter your move (or 'D' for directions): " << endl;

       //takes user input
          cin >> userInput;
          userInput = toupper(userInput);
      
       //terminates program if user enters x  
       if(userInput == 'X'){
          isAlive = false;
          }
// *** Yuwei: code within the same block should line up
       // prints out the locations of the 7 objects if user enters c for cheat 
     if(userInput == 'C'){
          cheatPrint(objectRooms);
        }
        
      //prints the neigbor rooms
     if(userInput == 'N'){
        printNeighbors(validRooms);
      }

      //lets user reset the values of the rooms if user enters reset
     if(userInput == 'R'){
       resetRooms(objectRooms);
      }
      //moves room to users input if user enters m
     if(userInput == 'M'){
          cin >> moveRoom;
          moveTo(moveRoom, objectRooms, validRooms, moveNum);        
        }
     if(userInput == 'S'){
       shootArrow(objectRooms, validRooms, numRooms, room1, room2, room3, moveNum);
     }
     
    }// end while loop
    
    cout << "\nExiting Program ..." << endl;
}//end main()
