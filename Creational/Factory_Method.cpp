#include <iostream>


// -----------------------------------------------------------------------------------------------------//
/**
 * @brief Teaching method acts as interface
 *
 * The teaching class acts as the interface for the
 * other classes which will help to implement the
 * English , Maths ... etc
 *
 */

class Teaching
{

public:
    // virtual destructor
    virtual ~Teaching() {}

    // abstract method
    virtual std::string teach() const = 0;
};

/**
 * @brief Implementing the English Teaching method
 *
 */
class English : public Teaching
{
public:
    // override the teach method of the Teaching
    std::string teach() const override
    {
        return "English Teacher";
    }
};

class Maths : public Teaching
{
public:
    // override the teach method of the Teaching
    std::string teach() const override
    {
        return "Maths Teacher";
    }
};

// -----------------------------------------------------------------------------------------------------//

// Now lets use the code which we have above to create a teacher , since teacher can be of any subject this will also act as interface

class Teacher
{

public:
    virtual ~Teacher()
    {
    }

    // abstract method to be implemented
    virtual Teaching *getTeacher() const = 0;

    std::string SomeOperation() const
    {
        // Call the factory method to create a Product object.
        Teaching *teacher = this->getTeacher();
        // Now, use the product.
        std::string result = "Creator: The same creator's code has just worked with " + teacher->teach();
        delete teacher;

        return result;
    }
};

// English teacher is implemented using Teacher
class EnglishTeacher : public Teacher
{

public:
    // overriding the getTeacher method
    Teaching *getTeacher() const override
    {
        return new English();
    }
};

// Maths teacher is implemented using Teacher
class MathsTeacher : public Teacher
{

public:
    // overriding the getTeacher method
    Teaching *getTeacher() const override
    {
        return new Maths();
    }
};

// Method to made the use the client
void ClientCode(const Teacher &teacher)
{
    std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
              << teacher.SomeOperation() << std::endl;
}

int main()
{
    std::cout << "App: Launched with the EnglishTeacher.\n";

    Teacher *teacher1 = new EnglishTeacher(); // call the EnglishTeacher() ===> getTeacher() is over-ridden by the English()

    ClientCode(*teacher1);

    std::cout << std::endl;

    std::cout << "App: Launched with the MathsTeacher.\n";

    Teacher *teacher2 = new MathsTeacher();

    ClientCode(*teacher2);

    delete teacher1;
    delete teacher2;

    return 0;
}
