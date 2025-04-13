
#include <iostream>

/*

    Intent : Decouple an abstraction from its implementation so that the two can vary independently.
    
    
    - The Bridgepattern addresses these problems by putting the Abstraction and its implementation in separate class hierarchies. Call it a bridge,because it bridges the abstraction and its implementation, letting them vary independently.
    
    - Applicability : 
    
        1. When the implementation must be selected or switched at run-time.
        
        2. both the abstractions and their implementations should be extensible by subclassing. In this case, the Bridge pattern lets you combine the different abstractions and implementations and extend them independently.
        
        3. Changes in the implementation of an abstraction should have no impact on clients; that is, their code should not have to be recompiled.
        
        4. You want toshare animplementationamongmultiple objects(perhaps using reference counting), and this fact should be hidden from the client

    - Consequences : 
    
        1. Decoupling interface and implementation : Decoupling Abstraction and Implementor also eliminates compile-time dependencies on the implementation. Changing an implementation class doesn't require recompiling the Abstraction class and its clients. This property is essential when you must ensure binary compatibility between different versions of a class library.
        
        2. Improved extensibility. You can extend the Abstraction and Implementor hierarchies independently.
        
        3. Hiding implementation details from clients. You can shield clients from implementation details, like the sharing of implementor objects and the accompanying reference count mechanism (if any).
        
    - Implementation : 
    
        1. Only one Implementor: In situations where there's only one implementation, creating an abstract Implementor class isn't necessary.
        
        2. Creating the right Implementor object : How, when, and where do you decide which Implementor classto instantiate when there's more than one?
        
            - If Abstraction knows about all Concretelmplementor classes, then it can instantiate one of them in its constructor; it can decide between them based on parameters passed to its constructor.
            
            - Another approach is to choose a default implementation initially and change it later according to usage.
            
        3. Sharing implementors : Handle/Body idiom in C++ can be used to share implementations among several objects. The Body stores a reference count that the Handle class increments and decrements. The code for assigning handles with shared bodies has the following general form:
        
            Handle& Handle::operator= (const Handle& other) {
                other._body->Ref(); // add count of other's body since its shared
                _body->Unref(); // undo the ref of current' body
                if (_body->RefCount() == 0)  // if it's free clean it
                {
                delete _body;
                }
                _body = other._body; // start pointing to new implementation
                return *this;
            }
            
            
            // General Structure of Handle/Body Idiom : 
            
            class A {  // Handle class delegating to its body
              public:
                A();  // defined later
                virtual ~A() { delete body; }
                virtual void f1() { body->f1(); }
                virtual void f2() { body->f2(); }
              private: A* body;
              protected: A(int dummy);  // used by body
            };
            
            class BodyOfA: public A { 
              public:
                BodyOfA();
                void f1()  { cout << "A::f1() "; f2(); }
                void f2()  { cout << "A::f2()" << endl; }
            };
  
        4. Using multiple inheritance : You can use multiple inheritance in C++ to combine an interface with its implementation. . For example, a class can inherit publicly from Abstraction and privately from a Concretelmplementor. But because this approach relies on static inheritance, it binds an implementation permanently to its interface. Therefore you can't implement a true Bridge with multiple inheritance—at least not in C++.
        
            // Implementation Interface
            class Renderer {
            public:
                virtual ~Renderer() = default;
                virtual void render_circle(float x, float y, float radius) = 0;
            };
            
            // Concrete Implementations
            class VectorRenderer : public Renderer {
            public:
                void render_circle(float x, float y, float radius) override {
                    std::cout << "Vector: Circle at (" << x << "," << y 
                             << ") with radius " << radius << "\n";
                }
            };
            
            // Shape Interface
            class Shape {
            public:
                virtual ~Shape() = default;
                virtual void draw() = 0;
                virtual void resize(float factor) = 0;
            };
            
            // Concrete Shape using multiple inheritance
            class Circle : public Shape, private VectorRenderer {  // Static binding!
            public:
                Circle(float x, float y, float r) : x(x), y(y), radius(r) {}
                
                void draw() override {
                    render_circle(x, y, radius);  // Directly calls VectorRenderer
                }
                
                void resize(float factor) override {
                    radius *= factor;
                }
            
            private:
                float x, y, radius;
            };
        
    - Related Patterns
        
        1. An AbstractFactory (87)can create and configure a particularBridge.

        2. The Adapter (139) pattern is geared toward making unrelated classes work togeather. It is usually applied to systems after they're designed. Bridge, on the other hand, is used up-front in a design to let abstractions and implementations vary independently.
*/

// Abstract Implementation
class WindowImp 
{
protected:
    WindowImp() {}
public:
    virtual ~WindowImp() = default;
    virtual void DrawRect(int x0, int y0, int x1, int y1) = 0;
};

// Concrete Implementation
class XWindowImp : public WindowImp {
public:
    XWindowImp() = default;
    void DrawRect(int x0, int y0, int x1, int y1) override {
        std::cout << "XWindowImp: Drawing rectangle ["
                  << x0 << "," << y0 << "]-["
                  << x1 << "," << y1 << "]\n";
    }
};

// Concrete Implementation
class PMWindowImp : public WindowImp {
public:
    PMWindowImp() = default;
    void DrawRect(int x0, int y0, int x1, int y1) override {
        std::cout << "PMWindowImp: Drawing rectangle ["
                  << x0 << "," << y0 << "]-["
                  << x1 << "," << y1 << "]\n";
    }
};


// Abstract Factory 
class WindowSystemFactory {
public:
virtual WindowImp* CreateWindowImp()
{
    return new XWindowImp();
}

static WindowSystemFactory * getInstance()
{
    if(!_instance)
    {
        _instance = new WindowSystemFactory();
    }
    return _instance;
}
protected:
WindowSystemFactory() {}
static WindowSystemFactory * _instance;
};

WindowSystemFactory* WindowSystemFactory::_instance = nullptr;

// Abstract Interface Class
class Window {
protected:
    WindowImp* GetWindowImp() {
        if (!_imp) {
            // Typically determined by environment or configuration
            // Here we'll default to XWindowImp for demonstration
            _imp = WindowSystemFactory::getInstance()->CreateWindowImp();
        }
        return _imp;
    }
    
private:
    WindowImp* _imp = nullptr;

public:
    virtual ~Window() {
        delete _imp;
    }
    virtual void Draw() = 0;
};

// Concrete Interface Class 
class ApplicationWindow : public Window {
public:
    void Draw() override {
        WindowImp* imp =  GetWindowImp();
        std::cout << "ApplicationWindow: ";
        imp->DrawRect(0, 0, 100, 150);
    }
};

// Concrete Interface Class 
class IconWindow : public Window {
public:
    void Draw() override {
        WindowImp* imp = GetWindowImp();
        std::cout << "IconWindow: ";
        imp->DrawRect(0, 0, 50, 50);
    }
};

int main() {
    ApplicationWindow appWin;
    appWin.Draw();

    IconWindow iconWin;
    iconWin.Draw();

    return 0;
}
