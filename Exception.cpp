//  exception.cpp
//  Exception that can store the information of errors and show what the error is
//
//  AB
//
//  Created by Yaojia Huang on 2018/10/31.

#include "Exception.hpp"
#include <iostream>
#include <sstream>

//////////////////Destructors for different exceptions of Option classes////////////////////////
OptionException::~OptionException() {};

InvalidFactorException::~InvalidFactorException() {};

InvalidOptionTypeException::~InvalidOptionTypeException() {};

InvalidStepException::~InvalidStepException() {};

InvalidValueException::~InvalidValueException() {};

//////////////////Constructors for different exceptions of Option classes////////////////////////

// Exception that checks the name of factors
InvalidFactorException::InvalidFactorException(const std::string& factor): err(factor) {};

// Exception that checks the option type
InvalidOptionTypeException::InvalidOptionTypeException(const char& type): err(type) {};

// Exception that checks the step value
InvalidStepException::InvalidStepException(const double& Step, const double& Start, const double& End):
step(Step), start(Start), end(End) {};

///////////////////////////////////////Error Message////////////////////////////////////////////

std::string InvalidFactorException::GetMessage() const
{
    std::stringstream str;
    // Tell the factor name is not valid and show the user the acceptable names
    str << err << " is not a valid factor!\n" <<
    "Valid factors are \"S\", \"T\", \"K\", \"sig\", \"r\" and \"b\".";
    return str.str();
}

std::string InvalidOptionTypeException::GetMessage() const
{
    std::stringstream str;
    // Tell the option type is not valid and show the user the acceptable types
    str << err << " is not a valid option type!\nValid types are 'C' and 'P'." ;
    return str.str();
}

std::string InvalidStepException::GetMessage() const
{
    std::stringstream str;
    // Tell the step does not work for the given range
    str << "Cannot apply " << step << " as step size to range (" << start << ", " << end << ")!";
    return str.str();
}

std::string InvalidValueException::GetMessage() const
{
    std::stringstream str;
    // Tell the value of parameter is not acceptable
    str << "Parameters cannot be negative and K must be positive!";
    return str.str();
}
