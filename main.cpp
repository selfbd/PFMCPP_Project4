/*
Project 4 - Part 6 / 9
Video: Chapter 5 Part 3
 
Create a branch named Part6
 
 Lambdas
 
    Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add two member functions named "apply()" to each of your Heap-Allocated Numeric Type wrappers.
         both apply() functions should work with chaining
 
 2) One of the apply() functions should takes a std::function<> object as the function argument.
    the std::function<> object should return *this;
 
 3) the other apply() function should take a function pointer. 
    the function pointer should return void.
 
 4) Make both of the member functions's Callable Function Parameter use your owned object as it's single parameter.
         e.g. if you manage your owned object via std::unique_ptr<T>, you'd use this for your std::function argument:
             std::function< OwnedT&(std::unique_ptr<T>&)>
             
         if you managed your owned object via a raw pointer, you'd use this for your std::function argument:
             std::function<OwnedT&(T&)>    
 
 5) call that Callable Function Parameter in the apply() member function.
         be sure to practice safe std::function usage (make sure it's not a nullptr function being called)
 
 6) Using one instance of each of your Heap-Allocated Numeric Type wrappers: Call your apply() member function twice in main()
         a) once with a lambda as the argument
         b) once with a free function as the argument.
         c) there will be a total of 6 calls to apply() in main(), 2x per HeapType, IntType, DoubleType instance.
         If this confuses you, rewatch the video where I pass a free function in to a function that wants a function pointer
 
 8) Make your lambda & free function update the value of your held object
 
 9) use std::cout statements to print out the results of calling apply()
 
build/run to make sure you don't have any errors
 
 If you need to see an example, look at https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part6Example.cpp
 */



#include <iostream>
#include <cmath>
#include <functional>

struct FloatType;
struct DoubleType;
struct IntType;

// Type Declarations - BEGIN ==========================

struct Point
{
    Point(float x_, float y_);
    Point(const FloatType& x_, const FloatType& y_);
    Point(const DoubleType& x_, const DoubleType& y_);
    Point(const IntType& x_, const IntType& y_);

    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
    
    Point& multiply(const FloatType& ft);
    Point& multiply(const DoubleType& dt);
    Point& multiply(const IntType& it);
    void toString();

private:
    float x{0}, y{0};
};

struct FloatType
{
    FloatType(float floatValue) : ownedFloat(new float(floatValue)) {}
    ~FloatType() { delete ownedFloat; ownedFloat = nullptr; }
    FloatType& operator=(const FloatType&);

    operator float() const { return *ownedFloat; }

    FloatType& apply(std::function<FloatType&(float&)>);

    using FloatFuncPtr = void(*)(float&);
    FloatType& apply(FloatFuncPtr);

    FloatType& pow(float rhs);
    FloatType& pow(const FloatType& rhs);
    FloatType& pow(const DoubleType& rhs);
    FloatType& pow(const IntType& rhs);

    FloatType& operator+=(float rhs);
    FloatType& operator-=(float rhs);
    FloatType& operator*=(float rhs);
    FloatType& operator/=(float rhs);

private:
    float* ownedFloat;
    FloatType& powInternal(const float value);
};

struct DoubleType
{    
    DoubleType(double doubleValue) : ownedDouble(new double(doubleValue)) {}
    ~DoubleType() { delete ownedDouble; ownedDouble = nullptr; }
    DoubleType& operator=(const DoubleType&);

    operator double() const { return *ownedDouble; }

    DoubleType& apply(std::function<DoubleType&(double&)>);

    using DoubleFuncPtr = void(*)(double&);
    DoubleType& apply(DoubleFuncPtr);

    DoubleType& pow(double rhs);
    DoubleType& pow(const FloatType& rhs);
    DoubleType& pow(const DoubleType& rhs);
    DoubleType& pow(const IntType& rhs);

    DoubleType& operator+=(double rhs);
    DoubleType& operator-=(double rhs);
    DoubleType& operator*=(double rhs);
    DoubleType& operator/=(double rhs);

private:
    double* ownedDouble;
    DoubleType& powInternal(const double value);
};

struct IntType
{
    IntType(int intValue) : ownedInt(new int(intValue)) {}
    ~IntType() { delete ownedInt; ownedInt = nullptr; }
    IntType& operator=(const IntType&);

    operator int() const { return *ownedInt; }

    IntType& apply(std::function<IntType&(int&)>);

    using IntFuncPtr = void(*)(int&);
    IntType& apply(IntFuncPtr);

    IntType& pow(int rhs);
    IntType& pow(const FloatType& rhs);
    IntType& pow(const DoubleType& rhs);
    IntType& pow(const IntType& rhs);

    IntType& operator+=(int rhs);
    IntType& operator-=(int rhs);
    IntType& operator*=(int rhs);
    IntType& operator/=(int rhs);

private:
    int* ownedInt;
    IntType& powInternal(const int value);
};

// Type Declarations - END ============================

// FloatType Implementations - BEGIN ==================

FloatType& FloatType::apply(std::function<FloatType&(float&)> floatFunc)
{
    if(floatFunc)
    {
        return floatFunc(*ownedFloat);
    }
    return *this;
}

FloatType& FloatType::apply(FloatFuncPtr floatFuncPtr)
{
    if(floatFuncPtr)
    {
        floatFuncPtr(*ownedFloat);
    }
    return *this; 
}

FloatType& FloatType::powInternal(const float value)
{
    *ownedFloat = std::pow(*ownedFloat, value);
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
    return powInternal(static_cast<float>(rhs));
}

FloatType& FloatType::operator+=(float rhs)
{
    *ownedFloat += rhs;
    return *this;
}

FloatType& FloatType::operator-=(float rhs)
{
    *ownedFloat -= rhs;
    return *this;
}

FloatType& FloatType::operator*=(float rhs)
{
    *ownedFloat -= rhs;
    return *this;
}

FloatType& FloatType::operator/=(float rhs)
{
    if( std::abs(rhs - 0.0f) < 0.00001f)
        std::cout << "Warning: Divide-by-zero attempt\n";
    *ownedFloat /= rhs;
    return *this;
}

// FloatType Implementations - END ====================

// DoubleType Implementations - BEGIN =================

DoubleType& DoubleType::apply(std::function<DoubleType&(double&)> doubleFunc)
{
    if(doubleFunc)
    {
        return doubleFunc(*ownedDouble);
    }
    return *this;
}

DoubleType& DoubleType::apply(DoubleFuncPtr doubleFuncPtr)
{
    if(doubleFuncPtr)
    {
        doubleFuncPtr(*ownedDouble);
    }
    return *this; 
}

DoubleType& DoubleType::powInternal(const double value)
{
    *ownedDouble = std::pow(*ownedDouble, value);
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

DoubleType& DoubleType::operator+=(double rhs)
{
    *ownedDouble += rhs;
    return *this;
}

DoubleType& DoubleType::operator-=(double rhs)
{
    *ownedDouble -= rhs;
    return *this;
}

DoubleType& DoubleType::operator*=(double rhs)
{
    *ownedDouble *= rhs;
    return *this;
}

DoubleType& DoubleType::operator/=(double rhs)
{
    if( fabs(rhs - 0.0) < 0.00001)
        std::cout << "Warning: Divide-by-zero attempt\n";
    *ownedDouble /= rhs;
    return *this;
}

// DoubleType Implementations - END ===================

// IntType Implementations - BEGIN ====================

IntType& IntType::apply(std::function<IntType&(int&)> intFunc)
{
    if(intFunc)
    {
        return intFunc(*ownedInt);
    }
    return *this;
}

IntType& IntType::apply(IntFuncPtr intFuncPtr)
{
    if(intFuncPtr)
    {
        intFuncPtr(*ownedInt);
    }
    return *this; 
}

IntType& IntType::powInternal(const int value)
{
    *ownedInt = static_cast<int>(std::pow(*ownedInt, value));
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

IntType& IntType::operator+=(int rhs)
{
    *ownedInt += rhs;
    return *this;
}

IntType& IntType::operator-=(int rhs)
{
    *ownedInt -= rhs;
    return *this;
}

IntType& IntType::operator*=(int rhs)
{
    *ownedInt *= rhs;
    return *this;
}

IntType& IntType::operator/=(int rhs)
{
    if(rhs == 0)
    {
        std::cout << "Warning: Divide-by-zero attempt. Divide operation aborted.\n";
        return *this;
    }
    *ownedInt /= rhs;
    return *this;
}

// IntType Implementations - END ======================

// Point Implementations - BEGIN ======================

Point::Point(float x_, float y_) : x(x_), y(y_) {}
Point::Point(const FloatType& x_, const FloatType& y_) : Point(static_cast<float>(x_), static_cast<float>(y_)) {}
Point::Point(const DoubleType& x_, const DoubleType& y_) : Point(static_cast<float>(x_), static_cast<float>(y_)) {}
Point::Point(const IntType& x_, const IntType& y_) : Point(static_cast<float>(x_), static_cast<float>(y_)) {}

Point& Point::multiply(const FloatType& ft)
{
    return multiply(static_cast<float>(ft));
}

Point& Point::multiply(const DoubleType& dt)
{
    return multiply(static_cast<float>(dt));
}

Point& Point::multiply(const IntType& it)
{
    return multiply(static_cast<float>(it));
}

void Point::toString() { std::cout << " : (" << x << "," << y << ")" << std::endl; }

// Point Implementations - END ========================

/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

void freeFuncSquareFloat (float& floatValue)
{
    floatValue = floatValue * floatValue;
}

void freeFuncSquareDouble (double& doubleValue)
{
    doubleValue = doubleValue * doubleValue;
}

void freeFuncSquareInt (int& intValue)
{
    intValue = intValue * intValue;
}

int main()
{
// project4-part6 - BEGIN
    
    std::cout << std::endl;
    std::cout << "**** Part 6 ****" << std::endl;
    std::cout << std::endl;

    // FloatType

    FloatType fta(1.6f);

    std::cout << "\t\tFloatType\tfta\t\t\t\t\t: " << fta << std::endl;

    fta.apply([&fta](float& floatValue) -> FloatType&
    {
        floatValue = floatValue * floatValue * floatValue;
        return fta;
    });
    std::cout << "Cubed\tFloatType\tfta (lambda)\t\t: " << fta << std::endl;

    fta.apply(freeFuncSquareFloat);
    std::cout << "Squared\tFloatType\tfta (free function)\t: " << fta << std::endl;

    // DoubleType

    DoubleType dta(0.81234);

    std::cout << std::endl;
    std::cout << "\t\tDoubleType\tdta\t\t\t\t\t: " << dta << std::endl;

    dta.apply([&dta](double& doubleValue) -> DoubleType&
    {
        doubleValue = doubleValue * doubleValue * doubleValue;
        return dta;
    });
    std::cout << "Cubed\tDoubleType\tdta (lambda)\t\t: " << dta << std::endl;

    dta.apply(freeFuncSquareDouble);
    std::cout << "Squared\tDoubleType\tdta (free function)\t: " << dta << std::endl;

    // IntType

    IntType ita(3);

    std::cout << std::endl;
    std::cout << "\t\tIntType\t\tita\t\t\t\t\t: " << ita << std::endl;

    ita.apply([&ita](int& intValue) -> IntType&
    {
        intValue = intValue * intValue * intValue;
        return ita;
    });
    std::cout << "Cubed\tIntType\t\tita (lambda)\t\t: " << ita << std::endl;

    ita.apply(freeFuncSquareInt);
    std::cout << "Squared\tIntType\t\tita (free function)\t: " << ita << std::endl;

// project4-part6 - END

// ==============================

    std::cout << std::endl;
    std::cout << "**** Parts 1 - 5  ****" << std::endl;
    std::cout << std::endl;

    {
    FloatType ft1(1.6f), ft2(-1.6f), ft3(1.6f), ft4(3.14f);
    DoubleType dt1(0.81234), dt2(0.81234), dt3(3.14);
    IntType it1(3), it2(2);

    std::cout << "Tests - pow" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << std::endl;
    std::cout << "FloatType ft1\t : " << ft1 << std::endl;
    std::cout << "FloatType ft2\t : " << ft2 << std::endl;
    std::cout << "FloatType ft3\t : " << ft3 << std::endl;
    std::cout << "FloatType ft4\t : " << ft4 << std::endl;
    std::cout << "DoubleType dt1\t : " << dt1 << std::endl;
    std::cout << "DoubleType dt2\t : " << dt2 << std::endl;
    std::cout << "DoubleType dt3\t : " << dt3 << std::endl;
    std::cout << "IntType it1\t\t : " << it1 << std::endl;
    std::cout << "IntType it2\t\t : " << it2 << std::endl;

    std::cout << std::endl;
    std::cout << "(ft1)^2\t\t\t : " << ft1.pow(2) << std::endl;
    std::cout << "(ft2)^0.5\t\t : " << ft2.pow(0.5) << std::endl;
    std::cout << "(ft3)^2.0\t\t : " << ft3.pow(2.f) << std::endl;
    std::cout << "(ft4)^0\t\t\t : " << ft4.pow(0) << std::endl;
    std::cout << "(dt1)^0.5\t\t : " << dt1.pow(0.5) << std::endl;
    std::cout << "((dt2)^0.5)^2\t : " << dt2.pow(0.5).pow(2) << std::endl;
    std::cout << "(dt3)^0\t\t\t : " << dt3.pow(0) << std::endl;
    std::cout << "((dt3)^0)^0.5\t : " << dt3.pow(0).pow(0.5) << std::endl;
    std::cout << "(it1)^3\t\t\t : " << it1.pow(3) << std::endl;
    std::cout << "((it2)^12)^2\t : " << it2.pow(12).pow(2) << std::endl;

    std::cout << std::endl;
    std::cout << "Tests - Point" << std::endl;
    std::cout << "-------------" << std::endl;

    // Examples calling Point ctor with floats
    Point p1(0.f, 0.f), p1f(0.f, 0.f), p1ft(0.f, 0.f), p1dt(0.f, 0.f), p1it(0.f, 0.f);
    Point p2(9.5f, 2.6f), p2f(9.5f, 2.6f), p2ft(9.5f, 2.6f), p2dt(9.5f, 2.6f), p2it(9.5f, 2.6f);
    Point p3(100.f, 10.f), p3f(100.f, 10.f), p3ft(100.f, 10.f), p3dt(100.f, 10.f), p3it(100.f, 10.f);

    // Examples calling Point ctor with FloatType, DoubleType, and IntType
    FloatType floatType(4.4f);
    DoubleType doubleType(1.234);
    IntType intType(3);

    Point p4(floatType, floatType), p4f(floatType, floatType), p4ft(floatType, floatType), p4dt(floatType, floatType), p4it(floatType, floatType);
    Point p5(doubleType, doubleType), p5f(doubleType, doubleType), p5ft(doubleType, doubleType), p5dt(doubleType, doubleType), p5it(doubleType, doubleType);
    Point p6(intType, intType), p6f(intType, intType), p6ft(intType, intType), p6dt(intType, intType), p6it(intType, intType);

    // Multipliers
    FloatType ft(1.6f);
    DoubleType dt(0.81234);
    IntType it(7);

    std::cout << std::endl;

    std::cout << "f multipier\t\t : " << "5" << std::endl;
    std::cout << "ft multiplier\t : " << ft << std::endl;
    std::cout << "dt multiplier\t : " << dt << std::endl;
    std::cout << "it multiplier\t : " << it << std::endl;

    // Point:: multiply with p1
    std::cout << std::endl;
    std::cout << "p1\t\t\t\t";
    p1.toString();
    std::cout << "p1 * f\t\t\t";
    p1f.multiply(5.f);
    p1f.toString();
    std::cout << "p1 * ft\t\t\t";
    p1ft.multiply(ft);
    p1ft.toString();
    std::cout << "p1 * dt\t\t\t";
    p1dt.multiply(dt);
    p1dt.toString();
    std::cout << "p1 * it\t\t\t";
    p1it.multiply(it);
    p1it.toString();

    // Point:: multiply with p2
    std::cout << std::endl;
    std::cout << "p2\t\t\t\t";
    p2.toString();
    std::cout << "p2 * f\t\t\t";
    p2f.multiply(5.f);
    p2f.toString();
    std::cout << "p2 * ft\t\t\t";
    p2ft.multiply(ft);
    p2ft.toString();
    std::cout << "p2 * dt\t\t\t";
    p2dt.multiply(dt);
    p2dt.toString();
    std::cout << "p2 * it\t\t\t";
    p2it.multiply(it);
    p2it.toString();

    // Point:: multiply with p3
    std::cout << std::endl;
    std::cout << "p3\t\t\t\t";
    p3.toString();
    std::cout << "p3 * f\t\t\t";
    p3f.multiply(5.f);
    p3f.toString();
    std::cout << "p3 * ft\t\t\t";
    p3ft.multiply(ft);
    p3ft.toString();
    std::cout << "p3 * dt\t\t\t";
    p3dt.multiply(dt);
    p3dt.toString();
    std::cout << "p3 * it\t\t\t";
    p3it.multiply(it);
    p3it.toString();

    // Point:: multiply with p4
    std::cout << std::endl;
    std::cout << "p4\t\t\t\t";
    p4.toString();
    std::cout << "p4 * f\t\t\t";
    p4f.multiply(5.f);
    p4f.toString();
    std::cout << "p4 * ft\t\t\t";
    p4ft.multiply(ft);
    p4ft.toString();
    std::cout << "p4 * dt\t\t\t";
    p4dt.multiply(dt);
    p4dt.toString();
    std::cout << "p4 * it\t\t\t";
    p4it.multiply(it);
    p4it.toString();

    // Point:: multiply with p5
    std::cout << std::endl;
    std::cout << "p5\t\t\t\t";
    p5.toString();
    std::cout << "p5 * f\t\t\t";
    p5f.multiply(5.f);
    p5f.toString();
    std::cout << "p5 * ft\t\t\t";
    p5ft.multiply(ft);
    p5ft.toString();
    std::cout << "p5 * dt\t\t\t";
    p5dt.multiply(dt);
    p5dt.toString();
    std::cout << "p5 * it\t\t\t";
    p5it.multiply(it);
    p5it.toString();

    // Point:: multiply with p6
    std::cout << std::endl;
    std::cout << "p6\t\t\t\t";
    p6.toString();
    std::cout << "p6 * f\t\t\t";
    p6f.multiply(5.f);
    p6f.toString();
    std::cout << "p6 * ft\t\t\t";
    p6ft.multiply(ft);
    p6ft.toString();
    std::cout << "p6 * dt\t\t\t";
    p6dt.multiply(dt);
    p6dt.toString();
    std::cout << "p6 * it\t\t\t";
    p6it.multiply(it);
    p6it.toString();

    std::cout << std::endl;
    std::cout << "good to go!" << std::endl;
    }
        
    //Tests from project4 parts - BEGIN 

    {
    FloatType ft1(1.6f);
    DoubleType dt1(0.81234);
    IntType it1(23);

    std::cout << std::endl;
    std::cout << "FloatType ft1\t : " << ft1 << std::endl;
    std::cout << "DoubleType dt1\t : " << dt1 << std::endl;
    std::cout << "IntType it1\t\t : " << it1 << std::endl;

    std::cout << std::endl;

    ft1 /= static_cast<float>(dt1);
    std::cout << "ft1/dt1\t\t\t : " << ft1 << std::endl;

    ft1 += static_cast<float>(dt1);
    ft1 *= 10;
    std::cout << "(ft1+dt1)*10\t : " << ft1 << std::endl;

    dt1 -= it1;
    dt1 *= it1;
    std::cout << "(dt1-it1)*it1\t : " << dt1 << std::endl;

    FloatType ft2 = 0.f;
    DoubleType dt2 = 0.000987;
    IntType it2 = 0;
    std::cout << std::endl;
    std::cout << "FloatType ft2\t : " << ft2 << std::endl;
    std::cout << "DoubleType dt2\t : " << dt2 << std::endl;
    std::cout << "IntType it2\t\t : " << it2 << std::endl;

    std::cout << std::endl;

    ft2 /= static_cast<float>(dt2);
    std::cout << "ft2/dt2\t\t\t : " << ft2 << std::endl;

    dt2 /= static_cast<double>(ft2);
    std::cout << "dt2/ft2\t\t\t : " << dt2 << std::endl;

    dt2 *= it2;
    dt2 -= 12;
    std::cout << "*dt2*it2-12\t\t : " << dt2 << std::endl;

    FloatType ft3 = 3.1f;
    DoubleType dt3 = 3.14159;
    IntType it3 = 2;
    std::cout << std::endl;
    std::cout << "FloatType ft3\t : " << ft3 << std::endl;
    std::cout << "DoubleType dt3\t : " << dt3 << std::endl;
    std::cout << "IntType it3\t\t : " << it3 << std::endl;

    std::cout << std::endl;

    ft3 *= it3;
    ft3 -= it3;
    std::cout << "ft3*it3-dt3\t\t : " << ft3 << std::endl;

    std::cout << std::endl;

    dt3 *= -1;
    it3 += static_cast<int>(dt3);
    ft3 *= it3;
    std::cout << "ft3*(it3-dt3)\t : " << ft3 << std::endl;

    std::cout << std::endl;

    ft3 /= 0; 
    dt3 /= 0;
    it3 /= 0;
    std::cout << "ft3/0\t\t\t : " << ft3 << std::endl;
    std::cout << "dt3/0\t\t\t : " << dt3 << std::endl;
    std::cout << "it3/0\t\t\t : " << it3 << std::endl;

    //Tests from project4 parts - END 
    }
}
