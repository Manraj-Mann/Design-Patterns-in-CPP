#include <iostream>
#include <memory>
#include <vector>
#include <any>

// CRTP Base Class
template <typename Derived>
class ShapeCRTP {
public:
    void draw() const {
        static_cast<Derived const*>(this)->draw();
    }
};

// Derived class: Circle
class Circle : public ShapeCRTP<Circle> {
public:
    void draw() const {
        std::cout << "Drawing Circle" << std::endl;
    }
};

// Derived class: Square
class Square : public ShapeCRTP<Square> {
public:
    void draw() const {
        std::cout << "Drawing Square" << std::endl;
    }
};

// Type-erased wrapper
class ShapeWrapper {
public:
    template <typename T>
    ShapeWrapper(T shape) : _shape{std::make_unique<Model<T>>(std::move(shape))} {}

    void draw() const {
        _shape->draw();
    }

private:
    struct Concept {
        virtual ~Concept() = default;
        virtual void draw() const = 0;
    };

    template <typename T>
    struct Model : Concept {
        Model(T shape) : _shape{std::move(shape)} {}
        void draw() const override {
            _shape.draw();
        }
        T _shape;
    };

    std::unique_ptr<Concept> _shape;
};

int main() {
    std::vector<ShapeWrapper> shapes;
    shapes.emplace_back(Circle{});
    shapes.emplace_back(Square{});

    for (auto const& s : shapes) {
        s.draw(); // Type-erased call
    }

    return 0;
}
