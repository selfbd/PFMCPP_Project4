/*
Project 4: Part 4 / 9
 Chapter 4 Part 7
 Function/Constructor Overloading

 Create a branch named Part4
 
 Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add pow() functions, and a powInternal() function to each of your UDTs
     a) your pow() functions should call powInternal()
     b) add a pow() whose argument type is the primitive your UDT owns.  the argument should be passed by copy.
     c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
         the argument should be passed as const ref
         i.e. if you had UDTs named IntType, FloatType, DoubleType
             in your IntType class, you'd have:
                 pow(const IntType&),
                 pow(const FloatType&),
                 pow(const DoubleType&),
                 and pow(int)
     d) be sure to remember the rules about what member functions can be called on const objects.
             (const objects can only call their const member functions)
     e) the pow() functions should be chainable.
 
 2) your powInternal() function should do something like this in its body:    *val = std::pow( *val, arg );
         where 'arg' is the passed-in type, converted to whatever type your object is holding.
             if your UDT owns an int, then arg would be an int.
             if your UDT owns a float, then arg would be a float.
         std::pow's documentation is found here: https://en.cppreference.com/w/cpp/numeric/math/pow so be sure to include
             the proper header file listed there.
         powInternal() should be chainable.
 
 3) modify the Point class below to have Constructors that accept your UDTs.
     a) make the Constructor's UDT arguments initialize the Point class's two member variables.
     b) overload the multiply() function so it can accept each of your UDTs.  I've added an implementation you can mimick for this function.
     c) add a toString() function to the Point class that prints out the x and y members via std::cout.
 
 4) Add to main()
     a) use your new pow() function in main for all of your types and print out the results.
     b) use the Point class in main and multiply some Point instances with your UDTs
     c) use the Point::toString() function to print out the results.
 
 
 5) make sure it compiles without errors.
 
 You will need to use Forward Declaration and out-of-class definitions to complete this.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

struct Point
{
    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
private:
    float x{0}, y{0};
};



#include <iostream>
#include <iomanip>
#include <cmath>

// FloatType - BEGIN ==================================

struct FloatType
{
    const float epsilon = 0.00001f;

    FloatType(float floatValue) : ownedFloat(new float(floatValue)) {}
    ~FloatType() {delete ownedFloat; ownedFloat = nullptr;}

    operator float() { return *ownedFloat;}

    FloatType& add(float rhs);
    FloatType& subtract(float rhs);
    FloatType& multiply(float rhs);
    FloatType& divide(float rhs);

private:
    float* ownedFloat;
};

FloatType& FloatType::add(float rhs)
{
    *ownedFloat += rhs;
    return *this;
}

FloatType& FloatType::subtract(float rhs)
{
    *ownedFloat -= rhs;
    return *this;
}

FloatType& FloatType::multiply(float rhs)
{
    *ownedFloat *= rhs;
    return *this;
}

// Reference:
// https://www.tutorialspoint.com/what-is-the-most-effective-way-for-float-and-double-comparison-in-c-cplusplus
FloatType& FloatType::divide(float rhs)
{
    if( std::abs(rhs - 0.0f) < epsilon)
        std::cout << "Warning: Use of " << rhs << " in this operation would result in a divide-by-zero situation : ";
    *ownedFloat /= rhs;
    return *this;
}

// FloatType - END ====================================

// DoubleType - BEGIN =================================

struct DoubleType
{
    const double epsilon = 0.00001;

    DoubleType(double doubleValue) : ownedDouble(new double(doubleValue)) {}
    ~DoubleType() {delete ownedDouble; ownedDouble = nullptr;}

    operator double() { return *ownedDouble;}

    DoubleType& add(double rhs);
    DoubleType& subtract(double rhs);
    DoubleType& multiply(double rhs);
    DoubleType& divide(double rhs);

private:
    double* ownedDouble;
};

DoubleType& DoubleType::add(double rhs)
{
    *ownedDouble += rhs;
    return *this;
}

DoubleType& DoubleType::subtract(double rhs)
{
    *ownedDouble -= rhs;
    return *this;
}

DoubleType& DoubleType::multiply(double rhs)
{
    *ownedDouble *= rhs;
    return *this;
}

// Reference:
// https://www.tutorialspoint.com/what-is-the-most-effective-way-for-float-and-double-comparison-in-c-cplusplus
DoubleType& DoubleType::divide(double rhs)
{
    if( fabs(rhs - 0.0) < epsilon)
        std::cout << "Warning: Use of " << rhs << " in this operation would result in a divide-by-zero situation : ";
    *ownedDouble /= rhs;
    return *this;
}

// DoubleType - END ===================================

// IntType - BEGIN  ===================================

struct IntType
{
    const double epsilon = 0;

    IntType(int intValue) : ownedInt(new int(intValue)) {}
    ~IntType() {delete ownedInt; ownedInt = nullptr;}

    operator int() { return *ownedInt;}

    IntType& add(int rhs);
    IntType& subtract(int rhs);
    IntType& multiply(int rhs);
    IntType& divide(int rhs);

private:
    int* ownedInt;
};

IntType& IntType::add(int rhs)
{
    *ownedInt += rhs;
    return *this;
}

IntType& IntType::subtract(int rhs)
{
    *ownedInt -= rhs;
    return *this;
}

IntType& IntType::multiply(int rhs)
{
    *ownedInt *= rhs;
    return *this;
}

IntType& IntType::divide(int rhs)
{
    if(rhs == 0)
    {
        std::cout << "Warning: Use of " << rhs << " in this operation would result in a divide-by-zero situation. Divide operation aborted. : ";
        return *this;
    }
    *ownedInt /= rhs;
    return *this;
}

// IntType - END  =====================================

int main()
{
    FloatType ft1(1.6f);
    DoubleType dt1(0.81234);
    IntType it1(23);

    std::cout << std::endl;
    std::cout << "FloatType ft1\t : " << ft1 << std::endl;
    std::cout << "DoubleType dt1\t : " << dt1 << std::endl;
    std::cout << "IntType it1\t\t : " << it1 << std::endl;

    std::cout << std::endl;
    std::cout << "ft1/dt1\t\t\t : " << static_cast<double>(ft1) / dt1  << std::endl;
    std::cout << "(ft1+dt1)*10\t : " << static_cast<float>( ft1.add( static_cast<float>(dt1) ).multiply( static_cast<float>(10) ) ) << std::endl;
    std::cout << "(dt1-it1)*it1\t : " << static_cast<double>( dt1.subtract(it1).divide( static_cast<double>(it1) ) ) << std::endl;

    FloatType ft2 = 0.f;
    DoubleType dt2 = 0.000987;
    IntType it2 = 0;
    std::cout << std::endl;
    std::cout << "FloatType ft2\t : " << ft2 << std::endl;
    std::cout << "DoubleType dt2\t : " << dt2 << std::endl;
    std::cout << "IntType it2\t\t : " << it2 << std::endl;

    std::cout << std::endl;
    std::cout << "ft2/dt2\t\t\t : " << static_cast<double>(ft2) / dt2 << std::endl;
    std::cout << "dt2/ft2\t\t\t : " << dt2 / static_cast<double>(ft2) << std::endl;
    //std::cout << "it2*dt2-12\t\t : " << it2.multiply(dt2).subtract(12)<< std::endl;
    std::cout << "it2*dt2-12\t\t : " << dt2.multiply( static_cast<double>(it2) ).subtract(12)<< std::endl;

    FloatType ft3 = 3.1f;
    DoubleType dt3 = 3.14159;
    IntType it3 = 2;
    std::cout << std::endl;
    std::cout << "FloatType ft3\t : " << ft3 << std::endl;
    std::cout << "DoubleType dt3\t : " << dt3 << std::endl;
    std::cout << "IntType it3\t\t : " << it3 << std::endl;

    std::cout << std::endl;
    std::cout << "ft3*it3-dt3\t\t : " << ft3.multiply( static_cast<float>(it3) ).subtract( static_cast<float>(dt3) )<< std::endl;
    
    std::cout << std::endl;
    std::cout << "FloatType ft3\t : " << ft3 << std::endl;
    std::cout << "DoubleType dt3\t : " << dt3 << std::endl;
    std::cout << "IntType it3\t\t : " << it3 << std::endl;

    std::cout << std::endl;
    std::cout << "ft3*(it3-dt3)\t : " << ft3 * it3.subtract( static_cast<int>(dt3) ) << std::endl;

    std::cout << std::endl;
    std::cout << "ft3/0\t\t\t : " << ft3.divide(0) << std::endl;
    std::cout << "dt3/0\t\t\t : " << dt3.divide(0) << std::endl;
    std::cout << "it3/0\t\t\t : " << it3.divide(0) << std::endl;

    std::cout << std::endl;
    std::cout << "good to go!" << std::endl;
}
