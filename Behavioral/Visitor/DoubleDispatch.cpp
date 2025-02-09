#include <iostream>
#include <memory>
#include <vector>

// shapes
class Circle;
class Square;

// shape visitor
class ShapeVisitor
{
    public:
    
    virtual ~ShapeVisitor() = default;
    
    virtual void visit( Circle const &) const = 0;
    virtual void visit( Square const &) const = 0;
};

class Shape 
{
    public:
    
    Shape() = default;
    virtual ~Shape() = default;
    
    virtual void accept( ShapeVisitor const &) = 0;
};


class Circle : public Shape
{
    public:
    
    explicit Circle( double rad) : _radius{rad} {}
    
    void exclusiveCircleWork()
    {
        std::cout<<"Pure Circle work"<<std::endl;
    }
    
    void accept( ShapeVisitor const & v) override
    {
        v.visit(*this);
    }
    
    private:
    
    double _radius;
};

class Square : public Shape
{
    
    public:
    
    explicit Square( double s) : _side{s} {}
    
    void exclusiveSquareWork()
    {
        std::cout<<"Pure Square work"<<std::endl;
    }
    
    void accept( ShapeVisitor const & v) override
    {
        v.visit(*this);
    }
    
    private:
    
    double _side;
};



class Rotate : public ShapeVisitor
{
    void visit( Circle const &) const override
    {
        std::cout<<"Do Some Rotation on Circle"<<std::endl;
    }
    
    void visit( Square const &) const override
    {
        std::cout<<"Do Some Rotation on Square"<<std::endl;
    }
};


class Draw : public ShapeVisitor
{
    void visit( Circle const &) const override
    {
        std::cout<<"Drawing Circle"<<std::endl;
    }
    
    void visit( Square const &) const override
    {
        std::cout<<"Drawing Square"<<std::endl;
    }
};

void drawAllShapes( std::vector<std::unique_ptr<Shape>> const& shapes )
{
     for( auto const& s : shapes )
     {
        s->accept( Draw{} );
     }
}

int main()
{
     using Shapes = std::vector<std::unique_ptr<Shape>>;
     
     // Creating some shapes
     Shapes shapes;
     shapes.emplace_back( std::make_unique<Circle>( 2.0 ) );
     shapes.emplace_back( std::make_unique<Square>( 1.5 ) );
     shapes.emplace_back( std::make_unique<Circle>( 4.2 ) );
     
     // Drawing all shapes
     drawAllShapes( shapes );
}
