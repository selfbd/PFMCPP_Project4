/*
 Project 4 - Part 2 / 9
 Video: Chapter 3 Part 6

 Create a branch named Part2

New/This/Pointers/References conclusion

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 0) in the blank space below, declare/define an empty struct named 'A' on a single Line. 
     on the lines below it, write a struct named 'HeapA' that correctly shows how to own an instance of 'A' 
         on the heap without leaking, without using smart pointers. 
 */

struct A {};
struct HeapA
{
    A* a;
    HeapA() : a(new A) {}
    ~HeapA() {delete a; a = nullptr;}    
};

 /*
 1) Edit your 3 structs so that they own a heap-allocated primitive type without using smart pointers  
         IntType should own a heap-allocated int, for example.
 
 2) give it a constructor that takes the appropriate primitive
    this argument will initialize the owned primitive's value.
         i.e. if you're owning an int on the heap, your ctor argument will initialize that heap-allocated int's value.
 
 3) modify those add/subtract/divide/multiply member functions from chapter 2 on it
         a) make them modify the owned numeric type
         b) set them up so they can be chained together.
             i.e.
             DoubleType dt(3.5);
             dt.add(3.0).multiply(-2.5).divide(7.2); //an example of chaining
 
 4) write add/subtract/divide/multiply member functions for each type that take your 3 UDTs
        These are in addition to your member functions that take primitives
        for example, IntType::divide(const DoubleType& dt);
        These functions should return the result of calling the function that takes the primitive.
     
 
 5) print out the results with some creative couts 
    i.e.
         FloatType ft(0.1f);
         IntType it(3);
         std::cout << "adding 3 and subtracting 'it' from 'ft' results in the following value: " << *ft.add(2.f).subtract( it ).value << std::endl;  //note the dereference of the `value` member of `ft`
 
 6) Don't let your heap-allocated owned type leak!
 
 7) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

#include <iostream>
#include <iomanip>
#include <cmath>

// Forward declarations
struct FloatType;
struct DoubleType;
struct IntType;

// FloatType - BEGIN ==================================

struct FloatType
{
    const float epsilon = 0.00001f;
    float* ownedFloat;

    FloatType(float floatValue) : ownedFloat(new float(floatValue)) {}
    ~FloatType() {delete ownedFloat; ownedFloat = nullptr;}

    FloatType& add(float rhs);
    FloatType& subtract(float rhs);
    FloatType& multiply(float rhs);
    FloatType& divide(float rhs);

    FloatType& add(const FloatType& rhs);
    FloatType& subtract(const FloatType& rhs);
    FloatType& multiply(const FloatType& rhs);
    FloatType& divide(const FloatType& rhs);

    FloatType& add(const DoubleType& rhs);
    FloatType& subtract(const DoubleType& rhs);
    FloatType& multiply(const DoubleType& rhs);
    FloatType& divide(const DoubleType& rhs);

    FloatType& add(const IntType& rhs);
    FloatType& subtract(const IntType& rhs);
    FloatType& multiply(const IntType& rhs);
    FloatType& divide(const IntType& rhs);
};

// FloatType member functions with primitive parameters - BEGIN =============

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

// FloatType member functions with primitive parameters - END ===============

// FloatType - END ====================================

// DoubleType - BEGIN =================================

struct DoubleType
{
    const double epsilon = 0.00001;
    double* ownedDouble;

    DoubleType(double doubleValue) : ownedDouble(new double(doubleValue)) {}
    ~DoubleType() {delete ownedDouble; ownedDouble = nullptr;}

    DoubleType& add(double rhs);
    DoubleType& subtract(double rhs);
    DoubleType& multiply(double rhs);
    DoubleType& divide(double rhs);

    DoubleType& add(const FloatType& rhs);
    DoubleType& subtract(const FloatType& rhs);
    DoubleType& multiply(const FloatType& rhs);
    DoubleType& divide(const FloatType& rhs);

    DoubleType& add(const DoubleType& rhs);
    DoubleType& subtract(const DoubleType& rhs);
    DoubleType& multiply(const DoubleType& rhs);
    DoubleType& divide(const DoubleType& rhs);

    DoubleType& add(const IntType& rhs);
    DoubleType& subtract(const IntType& rhs);
    DoubleType& multiply(const IntType& rhs);
    DoubleType& divide(const IntType& rhs);
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
    int* ownedInt;

    IntType(int intValue) : ownedInt(new int(intValue)) {}
    ~IntType() {delete ownedInt; ownedInt = nullptr;}

    IntType& add(int rhs);
    IntType& subtract(int rhs);
    IntType& multiply(int rhs);
    IntType& divide(int rhs);

    IntType& add(const FloatType& rhs);
    IntType& subtract(const FloatType& rhs);
    IntType& multiply(const FloatType& rhs);
    IntType& divide(const FloatType& rhs);

    IntType& add(const DoubleType& rhs);
    IntType& subtract(const DoubleType& rhs);
    IntType& multiply(const DoubleType& rhs);
    IntType& divide(const DoubleType& rhs);

    IntType& add(const IntType& rhs);
    IntType& subtract(const IntType& rhs);
    IntType& multiply(const IntType& rhs);
    IntType& divide(const IntType& rhs);
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

// Reference:
// https://www.tutorialspoint.com/what-is-the-most-effective-way-for-float-and-double-comparison-in-c-cplusplus
IntType& IntType::divide(int rhs)
{
    if( std::abs(rhs - 0) <= epsilon)
    {
        std::cout << "Warning: Use of " << rhs << " in this operation would result in a divide-by-zero situation : ";
        return *this;
    }
    *ownedInt /= rhs;
    return *this;
}

// IntType - END  =====================================

// FloatType add member function with other UDTs as parameters - BEGIN =======

FloatType& FloatType::add(const FloatType& ft)
{
    return add(*ft.ownedFloat);
}

FloatType& FloatType::add(const DoubleType& dt)
{
    return add(*dt.ownedDouble);
}

FloatType& FloatType::add(const IntType& it)
{
    return add(*it.ownedInt);
}

// FloatType add member function with other UDTs as parameters - END =========

// FloatType subtract member function with other UDTs as parameters - BEGIN ==

FloatType& FloatType::subtract(const FloatType& ft)
{
    return subtract(*ft.ownedFloat);
}

FloatType& FloatType::subtract(const DoubleType& dt)
{
    return subtract(*dt.ownedDouble);
}

FloatType& FloatType::subtract(const IntType& it)
{
    return subtract(*it.ownedInt);
}

// FloatType subtract member function with other UDTs as parameters - END ====

// FloatType multiply member function with other UDTs as parameters - BEGIN ==

FloatType& FloatType::multiply(const FloatType& ft)
{
    return multiply(*ft.ownedFloat);
}

FloatType& FloatType::multiply(const DoubleType& dt)
{
    return multiply(*dt.ownedDouble);
}

FloatType& FloatType::multiply(const IntType& it)
{
    return multiply(*it.ownedInt);
}

// FloatType multiply member function with other UDTs as parameters - END ====

// FloatType divide member function with other UDTs as parameters - BEGIN ====

FloatType& FloatType::divide(const FloatType& ft)
{
    return divide(*ft.ownedFloat);
}

FloatType& FloatType::divide(const DoubleType& dt)
{
    return divide(*dt.ownedDouble);
}

FloatType& FloatType::divide(const IntType& it)
{
    return divide(*it.ownedInt);
}

// FloatType divide member function with other UDTs as parameters - END ======

// DoubleType add member function with other UDTs as parameters - BEGIN ======

DoubleType& DoubleType::add(const FloatType& ft)
{
    return add(*ft.ownedFloat);
}

DoubleType& DoubleType::add(const DoubleType& dt)
{
    return add(*dt.ownedDouble);
}

DoubleType& DoubleType::add(const IntType& it)
{
    return add(*it.ownedInt);
}

// DoubleType add member function with other UDTs as parameters - END ========

// DoubleType subtract member function with other UDTs as parameters - BEGIN =

DoubleType& DoubleType::subtract(const FloatType& ft)
{
    return subtract(*ft.ownedFloat);
}

DoubleType& DoubleType::subtract(const DoubleType& dt)
{
    return subtract(*dt.ownedDouble);
}

DoubleType& DoubleType::subtract(const IntType& it)
{
    return subtract(*it.ownedInt);
}

// DoubleType subtract member function with other UDTs as parameters - END ===

// DoubleType multiply member function with other UDTs as parameters - BEGIN =

DoubleType& DoubleType::multiply(const FloatType& ft)
{
    return multiply(*ft.ownedFloat);
}

DoubleType& DoubleType::multiply(const DoubleType& dt)
{
    return multiply(*dt.ownedDouble);
}

DoubleType& DoubleType::multiply(const IntType& it)
{
    return multiply(*it.ownedInt);
}

// DoubleType multiply member function with other UDTs as parameters - END ===

// DoubleType divide member function with other UDTs as parameters - BEGIN ===

DoubleType& DoubleType::divide(const FloatType& ft)
{
    return divide(*ft.ownedFloat);
}

DoubleType& DoubleType::divide(const DoubleType& dt)
{
    return divide(*dt.ownedDouble);
}

DoubleType& DoubleType::divide(const IntType& it)
{
    return divide(*it.ownedInt);
}

// DoubleType divide member function with other UDTs as parameters - END =====

// IntType add member function with other UDTs as parameters - BEGIN =========

IntType& IntType::add(const FloatType& ft)
{
    return add(*ft.ownedFloat);
}

IntType& IntType::add(const DoubleType& dt)
{
    return add(*dt.ownedDouble);
}

IntType& IntType::add(const IntType& it)
{
    return add(*it.ownedInt);
}

// IntType add member function with other UDTs as parameters - END ===========

// IntType subtract member function with other UDTs as parameters - BEGIN ====

IntType& IntType::subtract(const FloatType& ft)
{
    return subtract(*ft.ownedFloat);
}

IntType& IntType::subtract(const DoubleType& dt)
{
    return subtract(*dt.ownedDouble);
}

IntType& IntType::subtract(const IntType& it)
{
    return subtract(*it.ownedInt);
}

// IntType subtract member function with other UDTs as parameters - END ======

// IntType multiply member function with other UDTs as parameters - BEGIN ====

IntType& IntType::multiply(const FloatType& ft)
{
    return multiply(*ft.ownedFloat);
}

IntType& IntType::multiply(const DoubleType& dt)
{
    return multiply(*dt.ownedDouble);
}

IntType& IntType::multiply(const IntType& it)
{
    return multiply(*it.ownedInt);
}

// IntType multiply member function with other UDTs as parameters - END ======

// IntType divide member function with other UDTs as parameters - BEGIN ======

IntType& IntType::divide(const FloatType& ft)
{
    return divide(*ft.ownedFloat);
}

IntType& IntType::divide(const DoubleType& dt)
{
    return divide(*dt.ownedDouble);
}

IntType& IntType::divide(const IntType& it)
{
    return divide(*it.ownedInt);
}

// IntType divide member function with other UDTs as parameters - END ========

int main()
{
    std::cout << std::endl;

    // ====================================================

    FloatType ft(1.6f);
    std::cout << "FloatType ft\t : " << *ft.ownedFloat << std::endl;
    //std::cout << "ft1.add()\t\t = " << ft1.add(23.0f) << std::endl;
    //std::cout << "ft1.subtract()\t = " << *ft1.subtract(23.0f) << std::endl;
    //std::cout << "ft1.multiply()\t = " << *ft1.multiply(23.0f) << std::endl;
    //std::cout << "ft1.divide()\t = " << *ft1.divide(23.0f) << std::endl;
    //std::cout << std::endl;

/*
    FloatType ft2;
    std::cout << "FloatType ft2\t : ( 98.6, -0.2 )" << std::endl;
    std::cout << "ft2.add()\t\t = " << ft2.add( 98.6f, -0.2f ) << std::endl;
    std::cout << "ft2.subtract()\t = " << ft2.subtract( 98.6f, -0.2f ) << std::endl;
    std::cout << "ft2.multiply()\t = " << ft2.multiply( 98.6f, -0.2f ) << std::endl;
    std::cout << "ft2.divide()\t = " << ft2.divide( 98.6f, -0.2f ) << std::endl;
    std::cout << std::endl;

    FloatType ft3;
    std::cout << "FloatType ft3\t : ( -123456.78, -987.654 )" << std::endl;
    std::cout << "ft3.add()\t\t = " << ft3.add( -123456.78f, -987.654f ) << std::endl;
    std::cout << "ft3.subtract()\t = " << ft3.subtract( -123456.78f, -987.654f ) << std::endl;
    std::cout << "ft3.multiply()\t = " << ft3.multiply( -123456.78f, -987.654f ) << std::endl;
    std::cout << "ft3.divide()\t = " << ft3.divide( -123456.78f, -987.654f ) << std::endl;
    std::cout << std::endl;

    FloatType ft4;
    std::cout << "FloatType ft4\t : ( 0.0, 3.14 )" << std::endl;
    std::cout << "ft4.add()\t\t = " << ft4.add( 0.0f, 3.14f ) << std::endl;
    std::cout << "ft4.subtract()\t = " << ft4.subtract( 0.0f, 3.14f ) << std::endl;
    std::cout << "ft4.multiply()\t = " << ft4.multiply( 0.0f, 3.14f ) << std::endl;
    std::cout << "ft4.divide()\t = " << ft4.divide( 0.0f, 3.14f ) << std::endl;
    std::cout << std::endl;

    FloatType ft5;
    std::cout << "FloatType ft5\t : ( 3.14159, 0.0 )" << std::endl;
    std::cout << "ft5.add()\t\t = " << ft5.add( 3.14159f, 0.0f ) << std::endl;
    std::cout << "ft5.subtract()\t = " << ft5.subtract( 3.14159f, 0.0f ) << std::endl;
    std::cout << "ft5.multiply()\t = " << ft5.multiply( 3.14159f, 0.0f ) << std::endl;
    std::cout << "ft5.divide()\t = " << ft5.divide( 3.14159f, 0.0f ) << std::endl;
    std::cout << std::endl;

    // ====================================================

    DoubleType dt1;
    std::cout << "DoubleType dt1\t : (3.2, 23.0)" << std::endl;
    std::cout << "dt1.add()\t\t = " << dt1.add( 3.2, 23.0 ) << std::endl;
    std::cout << "dt1.subtract()\t = " << dt1.subtract( 3.2, 23.0 ) << std::endl;
    std::cout << "dt1.multiply()\t = " << dt1.multiply( 3.2, 23.0 ) << std::endl;
    std::cout << "dt1.divide()\t = " << dt1.divide( 3.2, 23.0 ) << std::endl;
    std::cout << std::endl;

    DoubleType dt2;
    std::cout << "DoubleType dt2\t : (98.6, -0.2)" << std::endl;
    std::cout << "dt2.add()\t\t = " << dt2.add( 98.6, -0.2 ) << std::endl;
    std::cout << "dt2.subtract()\t = " << dt2.subtract( 98.6, -0.2 ) << std::endl;
    std::cout << "dt2.multiply()\t = " << dt2.multiply( 98.6, -0.2 ) << std::endl;
    std::cout << "dt2.divide()\t = " << dt2.divide( 98.6, -0.2 ) << std::endl;
    std::cout << std::endl;

    DoubleType dt3;
    std::cout << "DoubleType dt3\t : (-123456.78, -987.654)" << std::endl;
    std::cout << "dt3.add()\t\t = " << dt3.add( -123456.78, -987.654 ) << std::endl;
    std::cout << "dt3.subtract()\t = " << dt3.subtract( -123456.78, -987.654 ) << std::endl;
    std::cout << "dt3.multiply()\t = " << dt3.multiply( -123456.78, -987.654 ) << std::endl;
    std::cout << "dt3.divide()\t = " << dt3.divide( -123456.78, -987.654 ) << std::endl;
    std::cout << std::endl;

    DoubleType dt4;
    std::cout << "DoubleType dt4\t : (0.0, 3.14159265359)" << std::endl;
    std::cout << "dt4.add()\t\t = " << std::setprecision(12) << dt4.add( 0.0, 3.14159265359 ) << std::endl;
    std::cout << "dt4.subtract()\t = " << dt4.subtract( 0.0, 3.14159265359 ) << std::endl;
    std::cout << "dt4.multiply()\t = " << dt4.multiply( 0.0, 3.14159265359 ) << std::endl;
    std::cout << "dt4.divide()\t = " << dt4.divide( 0.0, 3.14159265359 ) << std::endl;
    std::cout << std::endl;

    DoubleType dt5;
    std::cout << "DoubleType dt5\t : (3.14159265359, 0.0)" << std::endl;
    std::cout << "dt5.add()\t\t = " << std::setprecision(15) << dt5.add( 3.14159265359, 0.0 ) << std::endl;
    std::cout << "dt5.subtract()\t = " << dt5.subtract( 3.14159265359, 0.0 ) << std::endl;
    std::cout << "dt5.multiply()\t = " << dt5.multiply( 3.14159265359, 0.0) << std::endl;
    std::cout << "dt5.divide()\t = " << dt5.divide( 3.14159265359, 0.0 ) << std::endl;
    std::cout << std::endl;

    // ====================================================

    IntType it1;
    std::cout << "IntType it1\t\t : (3, 23)" << std::endl;
    std::cout << "it1.add()\t\t = " << it1.add( 3, 23 ) << std::endl;
    std::cout << "it1.subtract()\t = " << it1.subtract( 3, 23 ) << std::endl;
    std::cout << "it1.multiply()\t = " << it1.multiply( 3, 23 ) << std::endl;
    std::cout << "it1.divide()\t = " << it1.divide( 3, 23 ) << std::endl;
    std::cout << std::endl;

    IntType it2;
    std::cout << "IntType it2\t\t : (-12345678, -98)" << std::endl;
    std::cout << "it2.add()\t\t = " << it2.add( -12345678, -98 ) << std::endl;
    std::cout << "it2.subtract()\t = " << it2.subtract( -12345678, -98 ) << std::endl;
    std::cout << "it2.multiply()\t = " << it2.multiply( -12345678, -98 ) << std::endl;
    std::cout << "it2.divide()\t = " << it2.divide( -12345678, -98 ) << std::endl;
    std::cout << std::endl;

    IntType it3;
    std::cout << "IntType it3\t\t : (20, -98)" << std::endl;
    std::cout << "it3.add()\t\t = " << it3.add( 20, -98 ) << std::endl;
    std::cout << "it3.subtract()\t = " << it3.subtract( 20, -98 ) << std::endl;
    std::cout << "it3.multiply()\t = " << it3.multiply( 20, -98 ) << std::endl;
    std::cout << "it3.divide()\t = " << it3.divide( 20, -98 ) << std::endl;
    std::cout << std::endl;

    IntType it4;
    std::cout << "IntType it4\t\t : (-20, 98)" << std::endl;
    std::cout << "it4.add()\t\t = " << it4.add( -20, 98 ) << std::endl;
    std::cout << "it4.subtract()\t = " << it4.subtract( -20, 98 ) << std::endl;
    std::cout << "it4.multiply()\t = " << it4.multiply( -20, 98 ) << std::endl;
    std::cout << "it4.divide()\t = " << it4.divide( -20, 98 ) << std::endl;
    std::cout << std::endl;

    IntType it5;
    std::cout << "IntType it5\t\t : (20, 0)" << std::endl;
    std::cout << "it5.add()\t\t = " << it5.add( 20, 0 ) << std::endl;
    std::cout << "it5.subtract()\t = " << it5.subtract( 20, 0 ) << std::endl;
    std::cout << "it5.multiply()\t = " << it5.multiply( 20, 0 ) << std::endl;
    std::cout << "it5.divide()\t = " << it5.divide( 20, 0 ) << std::endl;

    // ====================================================
*/
    std::cout << std::endl;
    std::cout << "good to go!" << std::endl;
}
