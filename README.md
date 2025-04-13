# **What are Design Patterns?**

Design patterns are **reusable solutions** to common problems in software design. They are not ready-made code, but rather **templates** or **best practices** that help developers structure their code in a way that is:

1. **Efficient**: Solves recurring problems without reinventing the wheel.
2. **Scalable**: Makes code easier to extend and maintain.
3. **Reusable**: Promotes code reuse across projects.
4. **Readable**: Provides a common vocabulary for developers to communicate design ideas.

Design patterns are categorized into three main types based on their intent:

1. **Creational Patterns**: Deal with object creation mechanisms (e.g., Singleton, Factory Method).
2. **Structural Patterns**: Focus on object composition and relationships (e.g., Adapter, Decorator).
3. **Behavioral Patterns**: Handle communication between objects (e.g., Observer, Strategy).

By using design patterns, developers can write **cleaner**, **more maintainable**, and **robust code** while avoiding common pitfalls in software design.

---

# 0. Important UML Concepts

![image](https://github.com/user-attachments/assets/70169a71-86fc-4959-97e5-ac47e8b42e10)

**Differences Between Association, Aggregation, and Composition !**

1. **Association** : A general relationship where two classes are connected but independent. Example: A Teacher interacts with a Student, but both can exist independently.

   ```cpp
    // Teacher knows a Student, but no ownership:
    class Student; // Forward declaration

    class Teacher {
    public:
        void setStudent(Student* s) { student = s; }
    private:
        Student* student; // Simple pointer (no ownership)
    };
   ```

2. **Aggregation** : A "has-a" relationship where the part can exist without the whole. Example: A Classroom contains Students, but deleting the Classroom doesn’t delete the Students. Class A does not control lifetime of object of class B , object B may live after A is destroyed.

   ```cpp
    // Classroom has Students, but they exist independently
    class Student; // Forward declaration

    class Classroom {
    public:
        void addStudent(Student* s) { students.push_back(s); }
    private:
        std::vector<Student*> students; // Students can exist outside
    };
   ```

3. **Composition** : A stricter "has-a" relationship where the part cannot exist without the whole. Example: A Car owns an Engine; destroying the Car also destroys the Engine.

   ```cpp
    // Car owns an Engine (lifetime controlled by Car)
    class Engine {
    public:
        void start() { /*...*/ }
    };
    
    class Car {
    public:
        Car() : engine(std::make_unique<Engine>()) {}
        void startCar() { engine->start(); }
    private:
        std::unique_ptr<Engine> engine; // Engine destroyed with Car
    };
   ```

**Key Takeaways**

1. **Association**: Loose relationship (e.g., pointers/references).

2. **Aggregation**: Shared ownership (e.g., pointers with external lifetime).

3. **Composition**: Exclusive ownership (e.g., direct members or unique_ptr).

---

# 1. Creational Patterns

Creational design patterns abstract the instantiation process. They help make a system independent of how its objects are created, composed, and represented.

---

### **Patterns Overview**

- **[Abstract Factory](./Creational/Abstract_Factory.cpp)**
  
  ![image](https://github.com/user-attachments/assets/5058b9c6-8163-44a7-8080-feda18f55406)  
  **Why Needed**: Ensures **compatibility among related objects** (e.g., UI components for a specific OS theme).  

- **[Builder](./Creational/Builder.cpp)**
  
  ![image](https://github.com/user-attachments/assets/8e7a7c24-c860-4fc1-be2b-a3f9679fac65)  
  **Why Needed**: Simplifies **step-by-step creation of complex objects** with optional components.   

- **[Factory Method](./Creational/Factory_Method.cpp)**
  
  ![image](https://github.com/user-attachments/assets/c2ca6208-953c-4ae7-9331-939929de3848)  
  **Why Needed**: **Decouples code** from concrete classes by letting subclasses decide object creation.  

- **[Prototype](./Creational/Prototype.cpp)**
  
  ![image](https://github.com/user-attachments/assets/fe6bcd08-1e83-40cb-8eab-9ff07862a421)  
  **Why Needed**: **Avoids costly initialization** by cloning pre-configured instances.  

- **[Singleton](./Creational/Singleton.cpp)**
  
  ![image](https://github.com/user-attachments/assets/bb2687cf-b62c-4e3e-a5c7-4098f1b0d2dd)  
  **Why Needed**: **Restricts a class to one global instance** to prevent resource conflicts.
  
---

### **Pattern Comparison Table**

| Pattern          | Intent                                                                 | Key Features                                  | When to Use                                      |
|------------------|-----------------------------------------------------------------------|----------------------------------------------|--------------------------------------------------|
| **Abstract Factory** | Create families of related/dependent objects                        | Factory interfaces, product consistency      | Cross-platform UI, themed component kits         |
| **Builder**      | Build complex objects incrementally                                   | Step-by-step construction, fluent interface  | Objects with optional/configurable parts         |
| **Factory Method** | Let subclasses decide which class to instantiate                     | Virtual constructor, inheritance-based       | Decoupling client code from concrete classes     |
| **Prototype**    | Clone existing instances to avoid re-initialization                   | `clone()` method, prototype registry         | Costly object creation (e.g., database-heavy)    |
| **Singleton**    | Ensure a single global instance                                       | Private constructor, static access method    | Shared resources (e.g., config managers)         |

---

## When to Use Which Pattern?
- Use **Singleton** for global access to a single instance.  
- Use **Factory Method** when subclassing determines the object type.  
- Use **Abstract Factory** for creating entire product families.  
- Use **Builder** to handle complex object assembly with optional steps.  
- Use **Prototype** to avoid costly initialization via cloning.  

---

# 2. Structural Patterns

---

### **Patterns Overview**

- **[Adapter Pattern](./Structural/adapter.cpp)**

   1. Implementation using inheritance of target and adaptee class : 
      
      ![image](https://github.com/user-attachments/assets/00312613-19ab-4613-99a7-140df51368ca)

   2. Implementation using composition class :

      ![image](https://github.com/user-attachments/assets/cdfc577e-95ef-4ff6-9c77-f605f22934a5)

  
  **Why Needed**: 

- **[Bridge Pattern](./Structural/bridge.cpp)**
  
   ![image](https://github.com/user-attachments/assets/9a455a4a-cf5b-4bfb-bfef-bc8eca5a0c5b)

- **[Composite Pattern](./Structural/composite.cpp)**
  
   ![image](https://github.com/user-attachments/assets/8a063c09-7df9-465c-aedc-d3b35455dd1f)



---
