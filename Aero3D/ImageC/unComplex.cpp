//------------------------------------------------------------------------------
#include <math.h>
#pragma hdrstop
#include "unComplex.h"
//------------------------------------------------------------------------------
Complex::Complex(double re,double im)
{
 EPS=1e-6;
 this->re=re;
 this->im=im;
}
//------------------------------------------------------------------------------
Complex::Complex(double re)
{
 EPS=1e-6;
 this->re=re;
 this->im=0.0;
}
//------------------------------------------------------------------------------
Complex::Complex()
{
 EPS=1e-6;
 this->re=0.0;
 this->im=0.0;
}
//------------------------------------------------------------------------------
Complex::Complex(const Complex &z)
{
 EPS=1e-6;
 this->re=z.re;
 this->im=z.im;
}
//------------------------------------------------------------------------------
double Complex::getRe()
{
 return re;
}
//------------------------------------------------------------------------------
double Complex::getIm()
{
 return im;
}
//------------------------------------------------------------------------------
void Complex::setRe(double re)
{
 this->re=re;
}
//------------------------------------------------------------------------------
void Complex::setIm(double im)
{
 this->im=im;
}
//------------------------------------------------------------------------------
double Complex::mod()
{
 return sqrt(re*re+im*im);
}
//------------------------------------------------------------------------------
double Complex::arg()
{
 return atan2(re,im);
}
//------------------------------------------------------------------------------
boolean Complex::isReal()
{
 return abs(im)<EPS;
}
//------------------------------------------------------------------------------
AnsiString Complex::toString()
{
 return FloatToStr(re)+" "+FloatToStr(im);
}
//------------------------------------------------------------------------------
Complex Complex::operator=(Complex z)
{
 this->re=z.re;
 this->im=z.im;
 return *this;
}
//------------------------------------------------------------------------------
void Complex::operator+=(Complex z)
{
 this->re+=z.re;
 this->im+=z.im;
}
//------------------------------------------------------------------------------
void Complex::operator-=(Complex z)
{
 this->re-=z.re;
 this->im-=z.im;
}
//------------------------------------------------------------------------------
void Complex::operator*=(Complex z)
{
 this->re*=z.re;
 this->im*=z.im;
}
//------------------------------------------------------------------------------
void Complex::operator/=(Complex z)
{
 this->re/=z.re;
 this->im/=z.im;
}
//------------------------------------------------------------------------------
Complex Complex::operator+(Complex z)
{
 Complex temp;
 temp.re=this->re+z.re;
 temp.im=this->im+z.im;
 return temp;
}
//------------------------------------------------------------------------------
Complex Complex::operator-(Complex z)
{
 Complex temp;
 temp.re=this->re-z.re;
 temp.im=this->im-z.im;
 return temp;
}
//------------------------------------------------------------------------------
Complex Complex::operator*(Complex z)
{
 Complex temp;
 temp.re=this->re*z.re;
 temp.im=this->im*z.im;
 return temp;
}
//------------------------------------------------------------------------------
Complex Complex::operator/(Complex z)
{
 Complex temp;
 if(z.re!=0 && z.im!=0)
 {
  temp.re=re/z.re;
  temp.im=im/z.im;
 }
 return temp;
}
//------------------------------------------------------------------------------
Complex Complex::operator+(double z)
{
 Complex temp;
 temp.re=this->re+z;
 temp.im=this->im+z;
 return temp;
}
//------------------------------------------------------------------------------
Complex Complex::operator-(double z)
{
 Complex temp;
 temp.re=this->re-z;
 temp.im=this->im-z;
 return temp;
}
//------------------------------------------------------------------------------
Complex Complex::operator*(double z)
{
 Complex temp;
 temp.re=this->re*z;
 temp.im=this->im*z;
 return temp;
}
//------------------------------------------------------------------------------
Complex Complex::operator/(double z)
{
 Complex temp;
 temp.re=this->re/z;
 temp.im=this->im/z;
 return temp;
}
//------------------------------------------------------------------------------
bool Complex::operator!=(Complex z)
{
 if(this->re!=z.re)return false;
 if(this->im!=z.im)return false;
 return true;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#pragma package(smart_init)
