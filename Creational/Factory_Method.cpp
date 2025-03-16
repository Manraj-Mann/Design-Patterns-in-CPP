#include <iostream>
#include <vector>
// Enum to represent directions for room sides
enum Direction { North, South, East, West };

// Abstract Product: Base class for all maze components
class MapSite {
public:
    virtual void Enter() = 0; // Pure virtual interface method
    virtual ~MapSite() = default; // Virtual destructor for proper cleanup
};

// Concrete Product: Room component
class Room : public MapSite {
public:
    Room(int roomNumber) : _roomNumber(roomNumber) {}
    
    // Get a side of the room based on direction
    MapSite* GetSide(Direction direction) const {
        return _sides[direction];
    }
    
    // Set a side of the room
    void SetSide(Direction direction, MapSite* site) {
        _sides[direction] = site;
    }
    
    void Enter() override {} // Implementation of interface method

private:
    MapSite* _sides[4] = {}; // Array to hold room's sides (4 directions)
    int _roomNumber;         // Room identifier
};

// Concrete Product: Door component connecting two rooms
class Door : public MapSite {
public:
    Door(Room* r1, Room* r2) : _room1(r1), _room2(r2) {}
    
    // Get the room on the other side of the door
    Room* OtherSideFrom(Room* room) {
        return (room == _room1) ? _room2 : _room1;
    }
    
    void Enter() override {} // Implementation of interface method

private:
    Room* _room1;  // First connected room
    Room* _room2;  // Second connected room
    bool _isOpen;  // Door state
};

// Concrete Product: Wall component
class Wall : public MapSite {
public:
    Wall() = default;
    void Enter() override {} // Implementation of interface method
};


class Maze {
public:
    Maze() = default;
    
    // Add a room to the maze
    void AddRoom(Room* room) { _rooms.push_back(room); }
    
    // Get a room by number
    Room* RoomNo(int roomNumber) const { return _rooms[roomNumber]; }

private:
    std::vector<Room*> _rooms; // Collection of rooms in the maze
};

/*
    Intent : Define an interface for creating an object, but let subclasses decide which class to instantiate. Factory Method lets a class defer instantiation to subclasses.
    
    Consequences : 
    
    - Provides hooks for subclasses.
    - Connects parallel class hierarchies. Parallel class hierarchies result when a class delegates some ofits responsibilities to a separate class.
    
    Implementation : 
    
    - Factory methods in C++ are always virtual functions and are often pure virtual. Justbe careful not to call factory methods in the Creator's constructor— the factory method in the ConcreteCreatorwon't be available yet.
    - Instead of creating the product in the constructor,the constructor merely initializes it to 0. The accessor returns the product. Butfirst it checksto make sure the product exists, and if it doesn't, the accessor creates it. This technique is sometimes called lazy initialization. 
    - Using templates to avoid subclassing
    
    Related Patterns : 
    
    - Abstract Factory is often implemented with factory methods. 
    - Factory methods are usually called within Template Methods.
    - Prototypes don't require subclassing Creator. However, they often require an Initialize operation on the Product class.Creator uses Initialize to initialize the object. Factory Method doesn't require such an operation.
*/

class MazeGame 
{
    public:
    Maze* CreateMaze();
    
    // factory methods:
    virtual Maze* MakeMaze() const
    { return new Maze; }
    
    virtual Room* MakeRoom(int n) const
    { return new Room(n); }
    
    virtual Wall* MakeWall() const
    { return new Wall; }
    
    virtual Door* MakeDoor(Room* rl, Room* r2) const
    { return new Door(rl, r2); }
};

Maze* MazeGame::CreateMaze () 
{
    Maze* aMaze = MakeMaze ();
    Room* r1 = MakeRoom (1);
    Room* r2 = MakeRoom(2);
    Door* theDoor = MakeDoor(r1, r2);
    aMaze->AddRoom(r1);
    aMaze->AddRoom(r2);
    r1->SetSide(North, MakeWall());
    r1->SetSide(East, theDoor);
    r1->SetSide(South, MakeWall());
    r1->SetSide(West, MakeWall());
    r2->SetSide(North, MakeWall());
    r2->SetSide(East, MakeWall());
    r2->SetSide(South, MakeWall());
    r2->SetSide(West, theDoor);
    return aMaze;
}

/*
New concrete class

class BombedMazeGame : public MazeGame 
{
    public:
    BombedMazeGame();
    virtual Wall* MakeWall() const
    { return new BombedWall; }
    virtual Room* MakeRoom(int n) const
    { return new RoomWithABomb(n); }
};

*/

int main() {
   
   MazeGame game;
   game.CreateMaze();

    return 0;
}
