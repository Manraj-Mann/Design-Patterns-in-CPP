#include <iostream>
#include <memory>
#include <vector>

// Forward declarations for concrete shapes
class Circle;
class Square;

// Visitor Interface
// Defines the operations that can be performed on shapes.
class ShapeVisitor
{
public:
    virtual ~ShapeVisitor() = default;

    // Overloads for visiting each concrete shape type
    virtual void visit(Circle const&) const = 0;
    virtual void visit(Square const&) const = 0;
};

// Base class for all shapes
class Shape
{
public:
    Shape() = default;
    virtual ~Shape() = default;

    // Accept a visitor (part of the Visitor Pattern)
    // This method allows the visitor to "visit" the shape.
    virtual void accept(ShapeVisitor const&) = 0;
};

// Concrete shape: Circle
class Circle : public Shape
{
public:
    explicit Circle(double rad) : _radius{rad} {}

    // Example of a method specific to Circle
    void exclusiveCircleWork()
    {
        std::cout << "Pure Circle work" << std::endl;
    }

    // Implementation of the accept method for Circle
    // Calls the visitor's visit method with *this (a Circle).
    void accept(ShapeVisitor const& v) override
    {
        v.visit(*this); // Double dispatch: Circle + Visitor
    }

private:
    double _radius; // Radius of the circle
};

// Concrete shape: Square
class Square : public Shape
{
public:
    explicit Square(double s) : _side{s} {}

    // Example of a method specific to Square
    void exclusiveSquareWork()
    {
        std::cout << "Pure Square work" << std::endl;
    }

    // Implementation of the accept method for Square
    // Calls the visitor's visit method with *this (a Square).
    void accept(ShapeVisitor const& v) override
    {
        v.visit(*this); // Double dispatch: Square + Visitor
    }

private:
    double _side; // Side length of the square
};

// Concrete Visitor: Rotate
// Implements the rotation operation for each shape type.
class Rotate : public ShapeVisitor
{
public:
    void visit(Circle const&) const override
    {
        std::cout << "Do Some Rotation on Circle" << std::endl;
    }

    void visit(Square const&) const override
    {
        std::cout << "Do Some Rotation on Square" << std::endl;
    }
};

// Concrete Visitor: Draw
// Implements the drawing operation for each shape type.
class Draw : public ShapeVisitor
{
public:
    void visit(Circle const&) const override
    {
        std::cout << "Drawing Circle" << std::endl;
    }

    void visit(Square const&) const override
    {
        std::cout << "Drawing Square" << std::endl;
    }
};

// Function to draw all shapes in a collection
// Uses the Visitor Pattern to perform the drawing operation.
void drawAllShapes(std::vector<std::unique_ptr<Shape>> const& shapes)
{
    for (auto const& s : shapes)
    {
        // Accept the Draw visitor to perform the drawing operation
        s->accept(Draw{});
    }
}

int main()
{
    using Shapes = std::vector<std::unique_ptr<Shape>>;

    // Creating some shapes
    Shapes shapes;
    shapes.emplace_back(std::make_unique<Circle>(2.0)); // Add a Circle
    shapes.emplace_back(std::make_unique<Square>(1.5)); // Add a Square
    shapes.emplace_back(std::make_unique<Circle>(4.2)); // Add another Circle

    // Drawing all shapes using the Visitor Pattern
    drawAllShapes(shapes);

    return 0;
}
