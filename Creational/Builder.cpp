#include <iostream>
#include <vector>

/**
 * @brief The cycle class contains the various parts.
 */
class Cycle
{
public:
    std::vector<std::string> _parts;

    void listParts() const
    {
        std::cout << "Product parts: ";
        for (size_t i = 0; i < _parts.size(); i++)
        {
            if (_parts[i] == _parts.back())
            {
                std::cout << _parts[i];
            }
            else
            {
                std::cout << _parts[i] << ", ";
            }
        }
        std::cout << "\n\n";
    }
};

/**
 * @brief The builder is used to implement different parts.
 * 
 */
class Builder
{

public:
    virtual ~Builder() {}
    virtual void produceWheels() const = 0;
    virtual void produceHandle() const = 0;
    virtual void produceBreaks() const = 0;
};

/**
 * @brief The sportsCycle is made by using the builder
 * 
 */
class SportsCycle : public Builder
{

    Cycle *cycle;

public:
    SportsCycle()
    {
        this->reset();
    }

    ~SportsCycle()
    {
        delete cycle;
    }

    void reset()
    {

        this->cycle = new Cycle();
    }

    void produceWheels() const override
    {

        this->cycle->_parts.push_back("Wide Wheels");
    }

    void produceHandle() const override
    {

        this->cycle->_parts.push_back("Slim Handle");
    }

    void produceBreaks() const override
    {

        this->cycle->_parts.push_back("A2 Breaks");
    }

    Cycle *getProduct()
    {
        Cycle *result = this->cycle;
        this->reset();
        return result;
    }
};

/**
 * @brief The director guides the build about what to make 
 * 
 */
class Director
{

    Builder *builder;

public:
    void setBuilder(Builder *builder)
    {

        this->builder = builder;
    }

    void buildFrame()
    {

        this->builder->produceHandle();
        this->builder->produceWheels();
    }

    void buildComplete()
    {

        this->builder->produceBreaks();
        this->builder->produceHandle();
        this->builder->produceWheels();
    }
};


/**
 * @brief The ClientCode asks the director.
 *
 */
void ClientCode(Director &director)
{
    SportsCycle *builder = new SportsCycle();

    director.setBuilder(builder);

    std::cout << "Standard basic product:\n";
    director.buildFrame();

    Cycle *p = builder->getProduct();
    p->listParts();
    delete p;

    std::cout << "Standard full featured product:\n";
    director.buildComplete();

    p = builder->getProduct();
    p->listParts();
    delete p;

    // Remember, the Builder pattern can be used without a Director class.
    std::cout << "Custom product:\n";
    builder->produceHandle();
    builder->produceWheels();
    p = builder->getProduct();
    p->listParts();
    delete p;

    delete builder;
}

// The main driver code
int main()
{
    Director *director = new Director();
    ClientCode(*director);
    delete director;
    return 0;
}