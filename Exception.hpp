//  exception.hpp
//  Exception that can store the information of errors and show what the error is
//
//  AB
//
//  Created by Yaojia Huang on 2018/10/31.

#ifndef Exception_hpp
#define Exception_hpp

#include <iostream>

// Base class of all exceptions
class OptionException
{
public:
    // Default destructor
    virtual ~OptionException();
    
    // Pure virtual member function
    virtual std::string GetMessage() const = 0;
            
};



// Exception that checks the name of factors
class InvalidFactorException: public OptionException
{
private:
    // erroneous factor name
    std::string err;
    
public:
    
    // Constructor that stores the erroneous factor name
    InvalidFactorException(const std::string& factor);
            
    // Default destructor
    virtual ~InvalidFactorException();
            
    // Print error message
    std::string GetMessage() const;
};



// Exception that checks the option type
class InvalidOptionTypeException: public OptionException
{
private:
    // erroneous option type
    char err;
    
public:
    // Constructor that stores the erroneous option type
    InvalidOptionTypeException(const char& type);
    
    // Default destructor
    virtual ~InvalidOptionTypeException();
    
    // Print error message
    std::string GetMessage() const;
};



// Exception that checks the step value
class InvalidStepException: public OptionException
{
private:
    // start and end of a varying factor and its step
    double step, start, end;
    
public:
    // Constructor that stores the start, end and erroneous step
    InvalidStepException(const double& Step, const double& Start, const double& End);
    
    // Default destructor
    virtual ~InvalidStepException();
    
    // Print error message
    std::string GetMessage() const;
};



// Exception that checks the value of the factors
class InvalidValueException: public OptionException
{
public:
    // Default destructor
    virtual ~InvalidValueException();
    
    // Print error message
    std::string GetMessage() const;
};


#endif
