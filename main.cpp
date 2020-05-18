
#include <iostream>
/*
Project 4: Part 5 / 9
 video: Chapter 5 Part 2
 Operator Overloading.

Do not delete your previous main. 

 Create a branch named Part5

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) replace the add/subtract/multiply/etc functions with overloaded math operators 
        e.g. add() would become operator+=() because it modifies the internal heap-allocated object.
 
 2) Your overloaded operators should only take primitives, passed by value.
 
 3) don't delete your conversion functions.
         if you removed them in Chapter 4 Part 7, put them back in.
         uncomment them if you commented them in Chapter 4 Part 7
 
 4) your main() function should be the same as Chapter 4 Part 7.  
     
 5) if your Chapter4 Part7 task didn't use any [+ - * or /], 
         add some in and fix the build errors that might result via the techniques you have learned in the previous weeks (hint: casting)
         i.e.
 */
#if false
namespace Example
{
    int main()
    {
        FloatType floatNum(4.3f);
        IntType intNum(2);
        IntType intNum2(6);

        /* 
        if you previously had a line like this demonstrating chaining:
            
            intNum.add(3).add(4.5f).divide(floatNum); 

        it should become:
        */
        intNum += 3;
        intNum += 4.5f;
        intNum /= floatNum;
        std::cout << "intNum: " << intNum << std::endl;
        
        return 0;
    }
}
#endif
 /*
 6) compile/link/run to make sure you don't have any errors

 */

#include <iostream>
#include <iomanip>
#include <cmath>

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
        std::cout << "Warning: Use of " << rhs << " in this operation would result in a divide-by-zero situation : ";
    *ownedFloat /= rhs;
    return *this;
}

// FloatType Implementations - END ====================

// DoubleType Implementations - BEGIN =================

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
        std::cout << "Warning: Use of " << rhs << " in this operation would result in a divide-by-zero situation : ";
    *ownedDouble /= rhs;
    return *this;
}

// DoubleType Implementations - END ===================

// IntType Implementations - BEGIN ====================

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
        std::cout << "Warning: Use of " << rhs << " in this operation would result in a divide-by-zero situation. Divide operation aborted. : ";
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

int main()
{
    /*
    FloatType ft1(1.6f), ft2(-1.6f), ft3(1.6f), ft4(3.14f);
    std::cout << std::endl;
    std::cout << "FloatType ft1\t : " << ft1 << std::endl;
    std::cout << "FloatType ft2\t : " << ft2 << std::endl;
    std::cout << "FloatType ft3\t : " << ft3 << std::endl;
    std::cout << "FloatType ft4\t : " << ft4 << std::endl;
    std::cout << std::endl;
*/
    {
    FloatType ft1(1.6f), ft2(-1.6f), ft3(1.6f), ft4(3.14f);
    DoubleType dt1(0.81234), dt2(0.81234), dt3(3.14);
    IntType it1(3), it2(2);

    std::cout << std::endl;
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

    Point p1(0.f, 0.f), p1f(0.f, 0.f), p1ft(0.f, 0.f), p1dt(0.f, 0.f), p1it(0.f, 0.f);
    Point p2(9.5f, 2.6f), p2f(9.5f, 2.6f), p2ft(9.5f, 2.6f), p2dt(9.5f, 2.6f), p2it(9.5f, 2.6f);
    Point p3(100.f, 10.f), p3f(100.f, 10.f), p3ft(100.f, 10.f), p3dt(100.f, 10.f), p3it(100.f, 10.f);

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
    
    //Tests from project4 parts - END 
    }
}
