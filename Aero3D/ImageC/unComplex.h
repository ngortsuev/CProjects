//------------------------------------------------------------------------------
#ifndef unComplexH
#define unComplexH

#include <system.hpp>
#include <sysutils.hpp>
//------------------------------------------------------------------------------
class Complex
{
 private:
        double EPS;
        double re,im;
 public:
        Complex(double re,double im);
        Complex(double re);
        Complex();
        Complex(const Complex &z);
        double getRe();
        double getIm();
        double getZ();
        void setRe(double re);
        void setIm(double im);
        void setZ(Complex z);
        double mod();
        double arg();
        boolean isReal();
        AnsiString toString();
        Complex operator=(Complex z);
        void operator+=(Complex z);
        void operator-=(Complex z);
        void operator*=(Complex z);
        void operator/=(Complex z);

        Complex operator+(Complex z);
        Complex operator-(Complex z);
        Complex operator*(Complex z);
        Complex operator/(Complex z);

        Complex operator+(double z);
        Complex operator-(double z);
        Complex operator*(double z);
        Complex operator/(double z);

        bool operator!=(Complex z);

};
//------------------------------------------------------------------------------
#endif
