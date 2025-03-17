#include <iostream>
#include <vector>
#include <memory> // For potential smart pointer use

/*
    Intent : Specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype.
    
    Consequences : 
    
    - Adding and removing products at run-time.
    -  Reduced subclassing.
    - Configuring an application with classes dynamically.
    - The main liability of the Prototype pattern isthat each subclass of Prototype must implement the Clone operation, which may be difficult.
    
    Implementation : 
    
    - Using a prototype manager : Clients won't manageprototypes themselves but will store and retrieve them from the registry. A client will ask the registry for a prototype before cloning it. We call this registry a prototype manager.
    
    - Implementing the Clone operation : cloning prototypes with complex structures usually requires a deep copy, because the clone and the original must be independent. Therefore you must ensure that the clone's components are clones of the prototype's components. Cloning forces you to decide what if anything will be shared.
    
    Related Patterns : 

    - Prototype and Abstract Factory (87)are competing patterns in some ways, as we discuss at the end of this chapter. They can also be used together, however. An Abstract Factory might store a set of prototypes from which to clone and return product objects. 
    - Designs that makeheavy use ofthe Composite and Decorator patterns often can benefit from Prototype as well.

    

*/

// Enum to represent directions for room sides
enum Direction { North, South, East, West };

// Abstract Prototype: Interface for cloneable maze components
class MapSite {
public:
    virtual void Enter() = 0;
    virtual MapSite* Clone() const = 0;  // Prototype method
    virtual ~MapSite() = default;
};

// Concrete Prototype: Room component with deep copy
class Room : public MapSite {
public:
    Room(int roomNumber) : _roomNumber(roomNumber) {}
    Room() = default;

    // Deep copy constructor
    Room(const Room& other) : _roomNumber(other._roomNumber) {
        for (int i = 0; i < 4; ++i) {
            if (other._sides[i]) {
                _sides[i] = other._sides[i]->Clone();  // Deep copy sides
            } else {
                _sides[i] = nullptr;
            }
        }
    }

    // Clone method using copy constructor
    Room* Clone() const override { return new Room(*this); }

    void SetRoomNumber(int number) { _roomNumber = number; }
    MapSite* GetSide(Direction direction) const { return _sides[direction]; }
    
    void SetSide(Direction direction, MapSite* site) {
        _sides[direction] = site;
    }

    void Enter() override {}

private:
    MapSite* _sides[4] = {};
    int _roomNumber;
};

// Concrete Prototype: Door component with deep copy
class Door : public MapSite {
public:
    Door() = default;
    Door(Room* r1, Room* r2) { Initialize(r1, r2); }
    
    // Deep copy constructor (initialization done later)
    Door(const Door& other) : _room1(nullptr), _room2(nullptr) {}

    void Initialize(Room* r1, Room* r2) {
        _room1 = r1;
        _room2 = r2;
    }

    Door* Clone() const override { return new Door(*this); }
    void Enter() override {}

    Room* OtherSideFrom(Room* r) const {
        return _room1 == r ? _room2 : _room1;
    }

private:
    Room* _room1 = nullptr;
    Room* _room2 = nullptr;
};

// Concrete Prototype: Wall component (trivial deep copy)
class Wall : public MapSite {
public:
    Wall() = default;
    Wall(const Wall&) = default;
    Wall* Clone() const override { return new Wall(*this); }
    void Enter() override {}
};

// Concrete Prototype: Maze container with deep copy
class Maze {
public:
    Maze() = default;
    
    // Deep copy constructor
    Maze(const Maze& other) {
        for (Room* room : other._rooms) {
            _rooms.push_back(room->Clone());
        }
    }

    Maze* Clone() const { return new Maze(*this); }
    
    void AddRoom(Room* room) { _rooms.push_back(room); }
    Room* RoomNo(int roomNumber) const { return _rooms[roomNumber]; }

private:
    std::vector<Room*> _rooms;
};

// Factories
class MazeFactory {
public:
    virtual Maze* MakeMaze() const { return new Maze; }
    virtual Wall* MakeWall() const { return new Wall; }
    virtual Room* MakeRoom(int n) const { return new Room(n); }
    virtual Door* MakeDoor(Room* r1, Room* r2) const { return new Door(r1, r2); }
    virtual ~MazeFactory() = default;
};



// Prototype Factory
class MazePrototypeFactory : public MazeFactory {
public:
    MazePrototypeFactory(Maze* m, Wall* w, Room* r, Door* d)
        : _prototypeMaze(m), _prototypeWall(w), _prototypeRoom(r), _prototypeDoor(d) {}

    Maze* MakeMaze() const override { return _prototypeMaze->Clone(); }
    
    Wall* MakeWall() const override { return _prototypeWall->Clone(); }
    
    Door* MakeDoor(Room* r1, Room* r2) const override {
        Door* door = _prototypeDoor->Clone();
        door->Initialize(r1, r2);
        return door;
    }
    
    Room* MakeRoom(int n) const override {
        Room* room = _prototypeRoom->Clone();
        room->SetRoomNumber(n);
        return room;
    }

private:
    Maze* _prototypeMaze;
    Wall* _prototypeWall;
    Room* _prototypeRoom;
    Door* _prototypeDoor;
};


/* Key Prototype Pattern Roles:
    - Prototype (MapSite): Declares clone interface
    - Concrete Prototype (Room/Door/Wall/Maze): Implements cloning
    - Client (MazeGame): Creates objects through prototypes
    - Prototype Factory: Manages prototype instances and cloning
*/

class MazeGame 
{
public:
    Maze* CreateMaze(MazePrototypeFactory& factory) {
        Maze* maze = factory.MakeMaze();
        Room* r1 = factory.MakeRoom(1);
        Room* r2 = factory.MakeRoom(2);
        Door* door = factory.MakeDoor(r1, r2);

        maze->AddRoom(r1);
        maze->AddRoom(r2);

        r1->SetSide(North, factory.MakeWall());
        r1->SetSide(East, door);
        r1->SetSide(South, factory.MakeWall());
        r1->SetSide(West, factory.MakeWall());

        r2->SetSide(North, factory.MakeWall());
        r2->SetSide(East, factory.MakeWall());
        r2->SetSide(South, factory.MakeWall());
        r2->SetSide(West, door);

        return maze;
    }
};
int main() 
{
    // Create prototype instances
    Wall basicWall;
    Room basicRoom;
    Door basicDoor;
    Maze basicMaze;

    // Configure factory with prototypes
    MazePrototypeFactory factory(
        &basicMaze, 
        &basicWall,
        &basicRoom,
        &basicDoor
    );

    // Build maze using prototypes
    MazeGame game;
    Maze* maze = game.CreateMaze(factory);
    
    return 0;
}
