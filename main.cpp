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

#include <iostream>
#include <iomanip>
#include <cmath>

struct FloatType;
struct DoubleType;
struct IntType;

/*
 3) modify the Point class below to have Constructors that accept your UDTs.
     a) make the Constructor's UDT arguments initialize the Point class's two member variables.
     b) overload the multiply() function so it can accept each of your UDTs.  I've added an implementation you can mimick for this function.
     c) add a toString() function to the Point class that prints out the x and y members via std::cout.
*/

struct Point
{
    Point(float x_, float y_);
    Point(FloatType x_, FloatType y_);
    Point(DoubleType x_, DoubleType y_);
    Point(IntType x_, IntType y_);

    Point& multiply(float m);
    Point& multiply(FloatType m);
    Point& multiply(DoubleType m);
    Point& multiply(IntType m);
    void toString();

private:
    float x{0}, y{0};
};

// FloatType - BEGIN ==================================

struct FloatType
{
    const float epsilon = 0.00001f;

    FloatType(float floatValue) : ownedFloat(new float(floatValue)) {}
    ~FloatType() { delete ownedFloat; ownedFloat = nullptr; }
    FloatType& operator=(const FloatType&);

    operator float() { return *ownedFloat;}
    operator float() const { return *ownedFloat; }

    FloatType& add(float rhs);
    FloatType& subtract(float rhs);
    FloatType& multiply(float rhs);
    FloatType& divide(float rhs);

    FloatType& pow(float rhs);
    FloatType& pow(const FloatType& rhs);
    FloatType& pow(const DoubleType& rhs);
    FloatType& pow(const IntType& rhs);

private:
    float* ownedFloat;
    FloatType& powInternal(const float value);
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

FloatType& FloatType::powInternal(const float value)
{
    *this = std::pow(*this, value);
    return *this;
}

FloatType& FloatType::pow(float rhs)
{
    return powInternal(rhs);
}

FloatType& FloatType::pow(const FloatType& rhs)
{
    return powInternal(static_cast<float>(rhs));
}

FloatType& FloatType::pow(const DoubleType& rhs)
{
    return powInternal(static_cast<float>(rhs));
}

FloatType& FloatType::pow(const IntType& rhs)
{
    return static_cast<float>(powInternal(static_cast<float>(rhs)));
}

// FloatType - END ====================================

// DoubleType - BEGIN =================================

struct DoubleType
{
    const double epsilon = 0.00001;

    DoubleType(double doubleValue) : ownedDouble(new double(doubleValue)) {}
    ~DoubleType() { delete ownedDouble; ownedDouble = nullptr; }
    DoubleType& operator=(const DoubleType&);

    operator double() { return *ownedDouble; }
    operator double() const { return *ownedDouble; }

    DoubleType& add(double rhs);
    DoubleType& subtract(double rhs);
    DoubleType& multiply(double rhs);
    DoubleType& divide(double rhs);

    DoubleType& pow(double rhs);
    DoubleType& pow(const FloatType& rhs);
    DoubleType& pow(const DoubleType& rhs);
    DoubleType& pow(const IntType& rhs);

private:
    double* ownedDouble;
    DoubleType& powInternal(const double value);
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

DoubleType& DoubleType::powInternal(const double value)
{
    *this = std::pow(*this, value);
    return *this;
}

DoubleType& DoubleType::pow(double rhs)
{
    return powInternal(rhs);
}

DoubleType& DoubleType::pow(const FloatType& rhs)
{
    return powInternal(static_cast<double>(rhs));
}

DoubleType& DoubleType::pow(const DoubleType& rhs)
{
    return powInternal(static_cast<double>(rhs));
}

DoubleType& DoubleType::pow(const IntType& rhs)
{
    return powInternal(static_cast<double>(rhs));
}

// DoubleType - END ===================================

// IntType - BEGIN  ===================================

struct IntType
{
    const double epsilon = 0;

    IntType(int intValue) : ownedInt(new int(intValue)) {}
    ~IntType() { delete ownedInt; ownedInt = nullptr; }
    IntType& operator=(const IntType&);

    operator int() { return *ownedInt; }
    operator int() const { return *ownedInt; }

    IntType& add(int rhs);
    IntType& subtract(int rhs);
    IntType& multiply(int rhs);
    IntType& divide(int rhs);

    IntType& pow(int rhs);
    IntType& pow(const FloatType& rhs);
    IntType& pow(const DoubleType& rhs);
    IntType& pow(const IntType& rhs);

private:
    int* ownedInt;
    IntType& powInternal(const int value);
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

IntType& IntType::powInternal(const int value)
{
    *this = static_cast<int>(std::pow(static_cast<int>(*this), static_cast<int>(value)));
    return *this;
}

IntType& IntType::pow(int rhs)
{
    return powInternal(rhs);
}

IntType& IntType::pow(const FloatType& rhs)
{
    return powInternal(static_cast<int>(rhs));
}

IntType& IntType::pow(const DoubleType& rhs)
{
    return powInternal(static_cast<int>(rhs));
}

IntType& IntType::pow(const IntType& rhs)
{
    return powInternal(static_cast<int>(rhs));
}

// IntType - END  =====================================

// Point Implementations - BEGIN ======================

Point::Point(float x_, float y_) : x(x_), y(y_) {}
Point::Point(FloatType x_, FloatType y_) : x(static_cast<float>(x_)), y(static_cast<float>(y_)) {}
Point::Point(DoubleType x_, DoubleType y_) : x(static_cast<float>(x_)), y(static_cast<float>(y_)) {}
Point::Point(IntType x_, IntType y_) : x(static_cast<int>(x_)), y(static_cast<int>(y_)) {}

Point& Point::multiply(float m)
{
    x *= m;
    y *= m;
    return *this;
}

Point& Point::multiply(FloatType m)
{
    x *= static_cast<float>(m);
    y *= static_cast<float>(m);
    return *this;
}

Point& Point::multiply(DoubleType m)
{
    x *= static_cast<float>(m);
    y *= static_cast<float>(m);
    return *this;
}

Point& Point::multiply(IntType m)
{
    x *= static_cast<float>(m);
    y *= static_cast<float>(m);
    return *this;
}

void Point::toString() { std::cout << "Point (x,y) = " << x << "," << y << ")" << std::endl; }

// Point Implementations - END ========================

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
