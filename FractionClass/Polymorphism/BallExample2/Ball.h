// Polymorphism Example with no comments

#ifndef BALL_H
#define BALL_H

class Ball
{
  public:
    virtual void print() const; // add a '= 0' to const to change class Ball to an abstract class. 
};

class Baseball : public Ball
{
  public:
    virtual void print() const;
};

class Football : public Ball
{
  public:
    virtual void print() const;
};

class Basketball : public Ball
{
  public:
    virtual void print() const;
};

#endif

// If you take off the 'virtual' before the function in the .h file you turn off polymorphism.
// The compiler will be forced to choose what function to call at run time instead of the correct functions.
// The compiler will choose the correct functions while it is running when using polymorphism and will choose the correct derived class to print.
