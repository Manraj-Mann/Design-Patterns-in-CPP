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
