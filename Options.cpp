//  Options.cpp
//  Option class(base class of European and perpetual American classes)
//  The class stores that information of the option. And it can set the
//  data, change option type or check input.
//
//  AB
//
//  Created by Yaojia Huang on 2018/11/1.

#include "Options.hpp"
#include <cctype>
#include <sstream>

namespace All_Options
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////Checking Functions//////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Check the input option type
    void Option::CheckOptionType(const char& type) const
    {
        // Check if the type is one of C, P, c, p. If not throw exception
        if (type != 'C' && type != 'P' && type != 'c' && type != 'p')
            throw InvalidOptionTypeException(type);
    }
    
    // Check the input factor value
    void Option::CheckFactorValue(const double& T, const double& K, const double& sig, const double& r, const double& b, const double& S) const
    {
        // Check if the value is no less than 0. If not throw exception
        // K has to be larger than 0 to avoid division by 0
        if (T < 0 || sig < 0 || K <= 0 || r < 0 || b < 0 || S < 0)
            throw InvalidValueException();
    }
    
    // Check the input factor name
    void Option::CheckFactorName(const std::string& factor) const
    {
        // Check if the name of the factor is valid. If not throw exception
        std::string str = boost::to_upper_copy<std::string>(factor);
        if (str != "R" && str != "T" && str != "K" && str != "B" && str != "S" && str != "SIG")
            throw InvalidFactorException(factor);
    }
    
    // Check whether the step works for the varying range of a factor
    void Option::CheckStep(const double& start, const double& end, const double& step) const
    {
        if (((end - start) < 0 && step >= 0) || ((end - start) > 0 && step <= 0) || step == 0)
            throw InvalidStepException(step, start, end);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////Constructors////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Default Constructor
    Option::Option(): data(OptionData())
    {
        // Initialize the option type
        data.optType = 'C';
    }

    // Copy Constructor
    Option::Option(const Option& op): data(op.data) {}

    // Constructe an option of certain type
    Option::Option(const char& optType2): data(OptionData())
    {
        // Check input option type
        CheckOptionType(optType2);
        
        // Make option type upper case
        data.optType = toupper(optType2);
    }

    // Constructe an option using given data
    Option::Option(const struct OptionData& source): data(source)
    {
        // Check the values of the input data
        CheckFactorValue(data.T, data.K, data.sig, data.r, data.b, data.S);
        
        // Check whether the default optType in the OptionData Struct is changed
        if (data.optType != 0)
        {
            // If changed, check if it's valid
            CheckOptionType(data.optType);
            
            // Make the type uppercase
            data.optType = toupper(data.optType);
        }
        else // Set to 'C', if the default setting in OptionData Struct is changed
            data.optType = 'C';
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////Destructor//////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    Option::~Option() {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////Operator//////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Assignment operator
    Option& Option::operator = (const Option& op)
    {
        // Check whether the address of the two objects are the same. If same, return itself
        if (this == &op) return *this;
        
        // Assign the data
        data = op.data;

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////Getter///////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Get the description of the object
    std::string Option::ToString() const
    {
        std::stringstream str;
        str << "Asset Name: " << data.name << "\n";
        str << "Option Type: " << data.optType << "\n";
        str << "K:   " << data.K << "\n";
        str << "sig: " << data.sig << "\n";
        str << "r:   " << data.r << "\n";
        str << "b:   " << data.b << "\n";
        str << "S:   " << data.S;
        return str.str();
    }

    // Get the data of the option object in the map form
    std::map<std::string, double> Option::Factors() const
    {
        // Create a map
        std::map<std::string, double> mp;
        
        // Initialize the map with class variables
        mp["R"] = data.r;
        mp["B"] = data.b;
        mp["SIG"] = data.sig;
        mp["T"] = data.T;
        mp["K"] = data.K;
        mp["S"] = data.S;
        return mp;
    }
    
    // Get the data of the option object in the struct OptionData form
    const struct OptionData& Option::get_data() const
    {
        return data;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////Modifiers///////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    // Set the data of the object
    void Option::set_data(const struct OptionData& source)
    {
        // Check the values of the input data
        CheckFactorValue(source.T, source.K, source.sig, source.r, source.b, source.S);
        
        // Keep the optiontype for backup
        char tmp = data.optType;
        
        // Assign the data
        data = source;
        
        // Check whether the default optType in the OptionData Struct is changed
        if (source.optType != 0)
        {
            // If changed, check if it's valid
            CheckOptionType(source.optType);
            
            // Make the type uppercase
            data.optType = toupper(data.optType);
        }
        else // Return to the previous value
            data.optType = tmp;
    }
    
    
    // Change option type (C/P, P/C)
    void Option::toggle()
    {
        data.optType = (data.optType == 'C')? 'P':'C';
    }
}


