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
    ~HeapA() {a = nullptr;}    
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

// ====================================================

struct FloatType
{
    const float epsilon = 0.00001f;
    
    float add( float lhs, float rhs );
    float subtract( float lhs, float rhs );
    float multiply( float lhs, float rhs );
    float divide( float lhs, float rhs );
};

float FloatType::add( float lhs, float rhs )
{
    return lhs + rhs;
}

float FloatType::subtract( float lhs, float rhs )
{
    return lhs - rhs;
}

float FloatType::multiply( float lhs, float rhs )
{
    return lhs * rhs;
}

// Reference:
// https://www.tutorialspoint.com/what-is-the-most-effective-way-for-float-and-double-comparison-in-c-cplusplus
float FloatType::divide( float lhs, float rhs )
{
    if( std::abs(rhs - 0.0f) < epsilon )
        std::cout << "Warning: Use of " << rhs << " in this operation would result in a divide-by-zero situation : ";
    return lhs / rhs;
}

// ====================================================

struct DoubleType
{
    const double epsilon = 0.00001;

    double add( double lhs, double rhs );
    double subtract( double lhs, double rhs );
    double multiply( double lhs, double rhs );
    double divide( double lhs, double rhs );
};

double DoubleType::add( double lhs, double rhs )
{
    return lhs + rhs;
}

double DoubleType::subtract( double lhs, double rhs )
{
    return lhs - rhs;
}

double DoubleType::multiply( double lhs, double rhs )
{
    return lhs * rhs;
}

// Reference:
// https://www.tutorialspoint.com/what-is-the-most-effective-way-for-float-and-double-comparison-in-c-cplusplus
double DoubleType::divide( double lhs, double rhs )
{
    if( fabs(rhs - 0.0) < epsilon )
        std::cout << "Warning: Use of " << rhs << " in this operation would result in a divide-by-zero situation : ";
    return lhs / rhs;
}

// ====================================================

struct IntType
{
    const double epsilon = 0;

    int add( int lhs, int rhs );
    int subtract( int lhs, int rhs );
    int multiply( int lhs, int rhs );
    int divide( int lhs, int rhs );
};

int IntType::add( int lhs, int rhs )
{
    return lhs + rhs;
}

int IntType::subtract( int lhs, int rhs )
{
    return lhs - rhs;
}

int IntType::multiply( int lhs, int rhs )
{
    return lhs * rhs;
}

// Reference:
// https://www.tutorialspoint.com/what-is-the-most-effective-way-for-float-and-double-comparison-in-c-cplusplus
int IntType::divide( int lhs, int rhs )
{
    if( std::abs(rhs - 0) <= epsilon )
    {
        std::cout << "Warning: Use of " << rhs << " in this operation would result in a divide-by-zero situation : ";
        return 0;
    }
    return lhs / rhs;
}

// ====================================================

int main()
{
    std::cout << std::endl;

    // ====================================================

    FloatType ft1;
    std::cout << "FloatType ft1\t : (3.2, 23.0)" << std::endl;
    std::cout << "ft1.add()\t\t = " << ft1.add( 3.2f, 23.0f ) << std::endl;
    std::cout << "ft1.subtract()\t = " << ft1.subtract( 3.2f, 23.0f ) << std::endl;
    std::cout << "ft1.multiply()\t = " << ft1.multiply( 3.2f, 23.0f ) << std::endl;
    std::cout << "ft1.divide()\t = " << ft1.divide( 3.2f, 23.0f ) << std::endl;
    std::cout << std::endl;


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

    std::cout << "good to go!" << std::endl;
}
