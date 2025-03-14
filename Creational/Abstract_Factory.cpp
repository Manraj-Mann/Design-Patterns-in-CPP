#include <iostream>
#include <vector>

/*
    Abstract Factory Design Pattern Implementation

    Intent: Provide an interface for creating families of related or dependent objects 
    without specifying their concrete classes. This pattern allows a client to create 
    objects through an abstract interface while keeping the object creation decoupled 
    from the client's code.

    Structure:
    - Abstract Factory (MazeFactory): Declares interface for creating product objects
    - Concrete Factories: Implement factory methods to create concrete products
    - Abstract Products (MapSite, Room, Door, Wall): Declare interfaces for products
    - Concrete Products: Implement specific product interfaces
*/

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

// Complex Product: Maze containing multiple rooms
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
    Abstract Factory: Interface for creating maze components
    Provides creation methods for all products in the family (Maze, Room, Wall, Door)
*/
class MazeFactory {
public:
    virtual ~MazeFactory() = default; // Virtual destructor for proper cleanup
    
    // Factory methods for creating maze components
    virtual Maze* MakeMaze() const { return new Maze; }
    virtual Room* MakeRoom(int n) const { return new Room(n); }
    virtual Wall* MakeWall() const { return new Wall; }
    virtual Door* MakeDoor(Room* r1, Room* r2) const { return new Door(r1, r2); }
};

/*
    Client Code: Creates a maze using components from the provided factory
    This implementation is factory-agnostic - it works with any MazeFactory implementation
*/
Maze* CreateMaze(MazeFactory& factory) {
    // Create maze using factory methods
    Maze* aMaze = factory.MakeMaze();
    Room* r1 = factory.MakeRoom(1);
    Room* r2 = factory.MakeRoom(2);
    Door* aDoor = factory.MakeDoor(r1, r2);
    
    // Build maze structure
    aMaze->AddRoom(r1);
    aMaze->AddRoom(r2);
    
    // Configure room 1 sides
    r1->SetSide(North, factory.MakeWall());
    r1->SetSide(East, aDoor);
    r1->SetSide(South, factory.MakeWall());
    r1->SetSide(West, factory.MakeWall());
    
    // Configure room 2 sides
    r2->SetSide(North, factory.MakeWall());
    r2->SetSide(East, factory.MakeWall());
    r2->SetSide(South, factory.MakeWall());
    r2->SetSide(West, aDoor);
    
    return aMaze;
}

int main() {
    /*
        Usage Example:
        MazeFactory factory;               // Create concrete factory
        Maze* maze = CreateMaze(factory);  // Build maze using factory
        
        For specialized mazes, create a different factory:
        class EnchantedMazeFactory : public MazeFactory { ... };
        EnchantedMazeFactory enchantedFactory;
        Maze* fairyMaze = CreateMaze(enchantedFactory);
    */
    
    return 0;
}
