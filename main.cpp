/*
 Project 4 - Part 3 / 9
 Video: Chapter 4 Part 3 
 Casting

 Create a branch named Part3
 
 ******** do not remove anything from main(). **************
 you'll be revising your main() to work with these new code changes.
 
    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.

 1) remove your functions that accepted a User-Defined Type
 
 2) remove any getValue() functions if you added them
 
 3) move all of your add/subtract/multiply/divide implementations out of the class.
  
 4) add user-defined conversion functions that convert to the numeric type your object holds.
        i.e. if your type holds an int, you'll need an operator int() function.
 
 5) make your member variable private.
         this conversion function should be the ONLY WAY to access the held value.
         use the proper casting technique to invoke this conversion function
 
 6) clean up any forward declaration that you might have.
 
 7) make sure it compiles & runs without errors.
 
 8) use your knowledge of casting to remove any conversion warnings. 
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

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
