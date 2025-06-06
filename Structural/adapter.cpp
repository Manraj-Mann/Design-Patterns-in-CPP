#include <iostream>

using Coord = float;

class Point {
public:
    Point(Coord x = 0, Coord y = 0) : _x(x), _y(y) {}
private:
    Coord _x, _y;
};

class Manipulator {};
class Shape;

class TextManipulator : public Manipulator 
{
public:
    TextManipulator(const Shape* shape) {}
};

// Target interface (expected interface)
class Shape {
public:
    virtual ~Shape() = default;
    virtual void BoundingBox(Point& bottomLeft, Point& topRight) const = 0;
    virtual Manipulator* CreateManipulator() const = 0;
};

// Existing class (Adaptee)
class TextView {
public:
    TextView() {}
    void GetOrigin(Coord& x, Coord& y) const { x = 0; y = 0; }
    void GetExtent(Coord& width, Coord& height) const { width = 100; height = 50; }
    virtual bool IsEmpty() const { return false; }
};


/*
    - Intent : Convert the interface of a class into another interface clients expect. Adapter lets classes work together that couldn't otherwise because of incompatible interfaces. Al.so known as Wrapper.
    
    - Structure : 
    
        1. A class adapter uses multiple inheritance to adapt one interface to another.
        
        2. An object adapter relies on object composition.
      
    - Consequences

        1.  A class adapter : 
        
            - adapts Adaptee to Target by committing to a concrete Adaptee class. As a consequence, a class adapter won't work when we want to adapt a classand all its subclasses.
            
            -  lets Adapter override some ofAdaptee'sbehavior, since Adapter is a subclass of Adaptee.
            
            - introduces only one object, and no additional pointer indirection is needed to get to the adaptee.
            
        2. An object adapter : 
        
            - lets a single Adapter work with many Adaptees—that is, the Adaptee itself and all of its subclasses (if any). The Adapter can also add functionality to all Adaptees at once.
            
            - makes it harder to override Adaptee behavior. It will require subclassing Adaptee and making Adapter refer to the subclass rather than the Adaptee itself.
        
        3. Issues to consider : 
        
            - How much adapting does Adapter do?Adapters vary in the amount ofwork they do to adapt Adaptee to the Target interface.
            
            - Pluggable adapters : Interface adaptation lets us incorporate our class into existing systems that might expect different interfaces to the class. The term pluggable adapter to describe classes with built-in interface adaptation.
            
            - Using two-way adapters to provide transparency : Two-way adapters can provide transparency. A two-way adapter is a design pattern that allows a class to be used in two different systems that expect different interfaces.
            
        4. Implementation : 
        
            - In a C++ implementation of a class adapter, Adapter would inherit publicly from Target and privately from Adaptee. Thus Adapter would be a subtype of Target but not of Adaptee.
            
            - Pluggable adapters : The first step, which is common to all three ofthe implementations discussed here, is to find a "narrow" interface for Adaptec, that is, the smallest subset of operations that lets us do the adaptation. A narrow interface consisting of only a couple of operations is easier to adapt than an interface with dozens of operations. The narrow interface leads to three implementation approaches:
            
                1. Using abstract operations : This approach defines an interface with abstract methods that concrete adapters must implement : 
                
                    // Target interface
                    class Target {
                    public:
                        virtual void request() = 0;  // Abstract operation
                        virtual ~Target() = default;
                    };
                    
                    // Adaptee (the class we need to adapt)
                    class Adaptee {
                    public:
                        void specificRequest() {
                            std::cout << "Adaptee's specificRequest() called\n";
                        }
                    };
                    
                    // Adapter using Abstract Operations
                    class Adapter : public Target {
                    public:
                        void request() override {
                            adaptee.specificRequest();  // Adapting to Adaptee's method
                        }
                    
                    private:
                        Adaptee adaptee;
                    };
                    
                    int main() {
                        Target* adapter = new Adapter();
                        adapter->request();
                        delete adapter;
                        return 0;
                    }

                
                2. Using delegate objects : This approach uses composition where the adapter holds a reference to the adaptee.
                
                    // Target interface
                    class Target {
                    public:
                        virtual void request() = 0;
                        virtual ~Target() = default;
                    };
                    
                    // Adaptee (the class we need to adapt)
                    class Adaptee {
                    public:
                        void specificRequest() {
                            std::cout << "Adaptee's specificRequest() called\n";
                        }
                    };
                    
                    // Adapter using Delegation
                    class Adapter : public Target {
                    private:
                        Adaptee& adaptee;  // Reference to adaptee object
                    
                    public:
                        Adapter(Adaptee& a) : adaptee(a) {}
                    
                        void request() override {
                            adaptee.specificRequest();  // Delegating the call
                        }
                    };
                    
                    int main() {
                        Adaptee adaptee;
                        Adapter adapter(adaptee);
                        adapter.request();
                        return 0;
                    }
                
                3. Parameterized adapters : Use parameterized approach to reduce subclassing.
                
        5. Related Patterns: 
        
            - Bridge has a structure similar to an object adapter, but Bridge has a different intent.
            
            - Decorator (175) enhances another object without changing its interface.Decorator is thus more transparent to the application than an adapter is.
            
            - Proxy (207)defines a representative or surrogate for another object and does not change its interface.

*/

/*1. Using Multiple Inheritance*/

// Adapter class (adapts TextView to Shape)
class TextShape : public Shape, private TextView {
public:
    void BoundingBox(Point& bottomLeft, Point& topRight) const override {
        Coord x, y, width, height;
        GetOrigin(x, y);
        GetExtent(width, height);
        bottomLeft = Point(x, y);
        topRight = Point(x + width, y + height);
    }

    Manipulator* CreateManipulator() const override {
        return new TextManipulator(this);
    }
    
    bool IsEmpty() const {
        return TextView::IsEmpty();
    }
};

int main() {
    TextShape textShape;
    
    Point bottomLeft, topRight;
    textShape.BoundingBox(bottomLeft, topRight);
    
    std::cout << "Bounding box calculated." << std::endl;
    std::cout << "Is empty: " << textShape.IsEmpty() << std::endl;
    
    Manipulator* manipulator = textShape.CreateManipulator();
    delete manipulator;
    
    return 0;
}

/*
2. Using Object Composition

class TextShape : public Shape {
public:
    TextShape(TextView* textView) : _textView(textView) {}

    void BoundingBox(Point& bottomLeft, Point& topRight) const override {
        Coord x, y, width, height;
        _textView->GetOrigin(x, y);
        _textView->GetExtent(width, height);
        bottomLeft = Point(x, y);
        topRight = Point(x + width, y + height);
    }

    Manipulator* CreateManipulator() const override {
        return new TextManipulator(this);
    }
    
    bool IsEmpty() const {
        return _textView->IsEmpty();
    }

private:
    TextView* _textView;
};

int main() {
    
    TextView textView;
    TextShape textShape(&textView);
    
    Point bottomLeft, topRight;
    textShape.BoundingBox(bottomLeft, topRight);
    
    std::cout << "Bounding box calculated." << std::endl;
    std::cout << "Is empty: " << textShape.IsEmpty() << std::endl;
    
    Manipulator* manipulator = textShape.CreateManipulator();
    delete manipulator;
    
    return 0;
}
*/
