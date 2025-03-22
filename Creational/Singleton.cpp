#include <iostream>

/*
    Intent : Ensure a class only has one instance, and provide a global point of access to it.

    Consequences : 

        1. Controlled access to sole instance
        
        2. Reduced name space -  It avoids polluting the name space with global variables that store sole instances.
        
        3. Permits refinement of operations and representation - The Singleton class may be subclassed, and it's easy to configure an application with an instance of this extended class. You can configure the application with an instance of the class you need at run-time.
        
        4. Permits a variable number of instances
        
        5. More flexible than class operations.Another way to package a singleton's functionality is to use class operations (that is,static member functions in C++).

    Implementation : 

        1. Ensuring a unique instance : 

            A common way to do this is to hide the operation that creates the instance behind a class operation (that is, either a static member function or a class method) that guarantees only one instance is created. This approach ensures that a singleton is created and initialized before its first use. Notice that the constructor is protected. A client that tries to instantiate Singleton directly will get an error at compile-time. This ensures that only one instance can ever get created.
            
            class Singleton 
            {
                public:
                    static Singleton* Instance();
                protected:
                    Singleton();
                private:
                    static Singleton* _instance;
            };

            - There's another thing to note about the C++ implementation. It isn't enough to define the singleton as a global or static object and then rely on "automatic initialization"-

                1. We can't guarantee that only one instance of a static object will ever be declared.
                2. We might not have enough information to instantiate every singleton at static initialization time.
                3. C++ doesn't define the order in which constructors for global objects are called across translation units. This means that no dependencies can exist between singletons.

        2. Subclassing the Singleton class : 

            In essence, the variable that refers to the singleton instance must get initialized with an instance of the subclass. The simplest technique is to determine which singleton you want to use in the Singleton's Instance operation - 

            MazeFactory* MazeFactory::Instance () 
            {
                if (_instance = = 0 ) 
                {
                    const char* mazeStyle - getenv("MAZESTYLE");
                    if (strcmp(mazeStyle, "bombed") == 0) 
                    {
                        _instance = new BombedMazeFactory;
                    } 
                    else if (strcmp(mazeStyle, "enchanted") == 0) 
                    {
                        _instance = new EnchantedMazeFactory;
                        // ... other possible subclasses
                    } 
                    else 
                    { // default
                        _instance = new MazeFactory;
                    }
                }
                return _instance;
            }

            - **A more flexible approach uses a registry of singletons : Instead of having Instance define the set of possible Singleton classes, the Singleton classes can register their singleton instance by name in a well-known registry. All it requires is a common interface for all Singleton classes that includes operations for the registry:

                class Singleton 
                {
                    public:
                        static void Register(const char* name, Singleton*);
                        static Singleton* Instance();
                    protected:
                        static Singleton* Lookup(const char* name);
                        Singleton();
                    private:
                        static Singleton* _instance;
                        static List<NameSingletonPair>* _registry;
                };

                Singleton* Singleton::Instance () 
                {
                    if (_instance == 0 ) 
                    {
                        const char* singletonName = getenv("SINGLETON");
                        // user or environment supplies this at startup
                        _instance = Lookup(singletonName);
                        // Lookup returns 0 if there's no such singleton
                    }
                    return _instance;
                }
                
                Where to place register : 

                    MySingleton::MySingleton() 
                    {
                        // . . .
                        Singleton::Register("MySingleton", this);
                    }

                Of course, the constructor won't get called unless someone instantiates the class, which echoes the problem the Singleton pattern is trying to solve!
                
                - We can get around this problem in C++ by defining a static instance of MySingleton. For example, we can define
                
                    static MySingleton theSingleton;
                
                    in the file that contains MyS ingleton'simplementation

            - The static object approach still has a potential drawback — namely that instances of all possible Singleton subclasses must be created, or else they won't get registered.

            - The static keyword at file scope gives theSingleton internal linkage, meaning:

                * It is only visible within the translation unit (the .cpp file) where it’s defined.
                * Other files cannot directly access theSingleton, enforcing encapsulation.
*/


/*class Singleton 
{
    public:
        static Singleton* Instance();
    protected:
        Singleton();
    private:
        static Singleton* _instance;
};

Singleton* Singleton::_instance = 0;

Singleton::Singleton(){}

Singleton* Singleton::Instance () 
{
    if (_instance == 0) 
    {
        _instance = new Singleton;
    }
    return _instance;
}*/

class MazeFactory 
{
    public:
        static MazeFactory* Instance();
        // existing interface goes here
    protected:
        MazeFactory();
    private:
        static MazeFactory* _instance;
};

MazeFactory* MazeFactory::_instance = 0;
MazeFactory::MazeFactory(){}
MazeFactory* MazeFactory::Instance () 
{
    if (_instance == 0 ) 
    {
        _instance = new MazeFactory;
    }
    return _instance;
}

int main()
{
    return 0;
}