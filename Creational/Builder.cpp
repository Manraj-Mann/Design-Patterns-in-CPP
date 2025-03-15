#include <iostream>
#include <vector>

/* Ignore the Below code from previous Abstract Factory */

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

    // Get the room number
    int GetRoomNumber() const { return _roomNumber; }
    
    void Enter() override {} // Implementation of interface method

private:
    MapSite* _sides[4] = {}; // Array to hold room's sides (4 directions)
    int _roomNumber;         // Room identifier
};

// Concrete Product: Door component connecting two rooms
class Door : public MapSite {
public:
    Door(Room* r1, Room* r2) : _room1(r1), _room2(r2), _isOpen(false) {}
    
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

// Product: Represents the complex object under construction
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
    Intent : Separate the construction of a complex object from its representation so that the same construction process can create different representations.
    
    Consequences : 
    
    - It lets you vary a product's internal representation.
    - It isolates code for construction and representation.
    - It gives you finer control over the construction process.
    
    Implementation : 
    
    - Builder generally build step by setp.
    - Why no abstract class for products? Because products generally vary alot. May or may not have anything in common.
    - Empty methods as default in Builder.

    Builder Design Pattern Components:
    
    - Builder: Abstract interface for creating maze components.
    - ConcreteBuilder: Implements the Builder interface to construct and assemble parts.
    - Director: Constructs the maze using the Builder interface.
    - Product: The final maze object composed of rooms, doors, and walls.

    Related Patterns : Abstract Factory and Composite
    
    - The primary difference isthat the Builder pattern focuseson constructing a complex object step by step. 
    - Abstract Factory's emphasis is on families of product objects (either simple or complex). Builder returns the product as a final step, but as far as the AbstractFactorypattern is concerned, the product gets returned immediately.
    - A Composite is what the builder often builds.


*/

// Builder: Abstract interface for constructing maze components
class MazeBuilder 
{
public:
    virtual void BuildMaze() { }
    virtual void BuildRoom(int room) { }
    virtual void BuildDoor(int roomFrom, int roomTo) { }
    virtual Maze* GetMaze() { return nullptr; }
    virtual ~MazeBuilder() = default; // Virtual destructor for polymorphic deletion

protected:
    MazeBuilder() = default; // Protected constructor to prevent instantiation
};

// ConcreteBuilder: Implements MazeBuilder to construct a standard maze
class StandardMazeBuilder : public MazeBuilder {
public:
    StandardMazeBuilder() : _currentMaze(nullptr) {}
    
    void BuildMaze() override {
        _currentMaze = new Maze();
    }
    
    void BuildRoom(int room) override {
        if (!_currentMaze->RoomNo(room)) {
            Room* newRoom = new Room(room);
            _currentMaze->AddRoom(newRoom);
            // Initialize all sides with walls
            newRoom->SetSide(North, new Wall());
            newRoom->SetSide(South, new Wall());
            newRoom->SetSide(East, new Wall());
            newRoom->SetSide(West, new Wall());
        }
    }
    
    void BuildDoor(int roomFrom, int roomTo) override {
        Room* r1 = _currentMaze->RoomNo(roomFrom);
        Room* r2 = _currentMaze->RoomNo(roomTo);
        Door* door = new Door(r1, r2);
        
        // Determine common wall direction and set the door
        Direction r1Side = CommonWall(r1, r2);
        Direction r2Side = CommonWall(r2, r1);
        r1->SetSide(r1Side, door);
        r2->SetSide(r2Side, door);
    }
    
    Maze* GetMaze() override {
        return _currentMaze;
    }

private:
    // Determines the direction of the common wall between two rooms
    Direction CommonWall(Room* r1, Room* r2) {
        // Simple heuristic: assumes rooms are ordered and adjacent east-west
        return (r1->GetRoomNumber() < r2->GetRoomNumber()) ? East : West;
    }

    Maze* _currentMaze;
};

// Director: Constructs the maze using the builder's interface
class MazeGame {
public:
    Maze* CreateMaze(MazeBuilder& builder) {
        builder.BuildMaze();
        builder.BuildRoom(1);
        builder.BuildRoom(2);
        builder.BuildDoor(1, 2);
        return builder.GetMaze();
    }
};

int main() {
    MazeGame game;
    StandardMazeBuilder builder; // ConcreteBuilder
    Maze* maze = game.CreateMaze(builder); // Director constructs the maze
    
    // Cleanup (assuming ownership is handled here; in real code, use smart pointers)
    delete maze;
    
    return 0;
}
