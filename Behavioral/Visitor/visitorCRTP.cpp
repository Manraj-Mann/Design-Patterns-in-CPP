#include <iostream>
#include <memory>
#include <vector>

// Visitor Interface (generic, not tied to CRTP)
template <typename Derived>
class ShapeCRTP {
public:
    template <typename Visitor>
    void accept(Visitor&& v) {
        v.visit(static_cast<Derived&>(*this)); // Static dispatch via CRTP
    }
};

// Concrete shapes using CRTP
class Circle : public ShapeCRTP<Circle> {
public:
    explicit Circle(double rad) : _radius{rad} {}

    void exclusiveCircleWork() const {
        std::cout << "Pure Circle work" << std::endl;
    }

    double radius() const { return _radius; }

private:
    double _radius;
};

class Square : public ShapeCRTP<Square> {
public:
    explicit Square(double s) : _side{s} {}

    void exclusiveSquareWork() const {
        std::cout << "Pure Square work" << std::endl;
    }

    double side() const { return _side; }

private:
    double _side;
};

// Visitors
struct Draw {
    void visit(Circle const& c) const {
        std::cout << "Drawing Circle with radius " << c.radius() << std::endl;
    }

    void visit(Square const& s) const {
        std::cout << "Drawing Square with side " << s.side() << std::endl;
    }
};

struct Rotate {
    void visit(Circle const& c) const {
        std::cout << "Rotating Circle with radius " << c.radius() << std::endl;
    }

    void visit(Square const& s) const {
        std::cout << "Rotating Square with side " << s.side() << std::endl;
    }
};

// Function to draw all shapes (using type-erasure)
void drawAllShapes(std::vector<std::unique_ptr<void, void(*)(void*)>> const& shapes) {
    for (auto const& s : shapes) {
        // Requires type-erasure to work (non-trivial here; omitted for brevity).
        // Example: Assume we stored a function to dispatch the visitor.
    }
}

int main() {
    // Example usage (simplified without type-erasure):
    Circle c{2.0};
    Square s{1.5};

    c.accept(Draw{}); // Output: Drawing Circle with radius 2
    s.accept(Rotate{}); // Output: Rotating Square with side 1.5
    
    return 0;
}
