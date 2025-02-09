#include <iostream>
#include <memory>
#include <vector>
#include <variant>

// Concrete shapes
class Circle
{
public:
    explicit Circle(double rad) : _radius{rad} {}

    void exclusiveCircleWork() const
    {
        std::cout << "Pure Circle work" << std::endl;
    }

    double radius() const { return _radius; }

private:
    double _radius; // Radius of the circle
};

class Square
{
public:
    explicit Square(double s) : _side{s} {}

    void exclusiveSquareWork() const
    {
        std::cout << "Pure Square work" << std::endl;
    }

    double side() const { return _side; }

private:
    double _side; // Side length of the square
};

// Define a variant type for shapes
using Shape = std::variant<Circle, Square>;

// Visitor for drawing shapes
struct Draw
{
    void operator()(Circle const& c) const
    {
        std::cout << "Drawing Circle with radius " << c.radius() << std::endl;
    }

    void operator()(Square const& s) const
    {
        std::cout << "Drawing Square with side " << s.side() << std::endl;
    }
};

// Visitor for rotating shapes
struct Rotate
{
    void operator()(Circle const& c) const
    {
        std::cout << "Rotating Circle with radius " << c.radius() << std::endl;
    }

    void operator()(Square const& s) const
    {
        std::cout << "Rotating Square with side " << s.side() << std::endl;
    }
};

// Function to draw all shapes in a collection
void drawAllShapes(std::vector<Shape> const& shapes)
{
    for (auto const& s : shapes)
    {
        // Use std::visit to apply the Draw visitor
        std::visit(Draw{}, s);
    }
}

int main()
{
    // Creating some shapes
    std::vector<Shape> shapes;
    shapes.emplace_back(Circle{2.0}); // Add a Circle
    shapes.emplace_back(Square{1.5}); // Add a Square
    shapes.emplace_back(Circle{4.2}); // Add another Circle

    // Drawing all shapes using std::visit
    drawAllShapes(shapes);

    // Rotating all shapes using std::visit
    for (auto const& s : shapes)
    {
        std::visit(Rotate{}, s);
    }

    return 0;
}
