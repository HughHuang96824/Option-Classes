//  Options.hpp
//  Option class(base class of European and perpetual American classes)
//  The class stores that information of the option. And it can set the
//  data, change option type or check input.
//
//  AB
//
//  Created by Yaojia Huang on 2018/11/1.

#ifndef Options_hpp
#define Options_hpp
#include <string>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>
#include "Exception.hpp"
#include "OptionData.hpp"

namespace All_Options
{
    class Option
    {
    protected:
        ///////////////////////////////////////////Protected data//////////////////////////////////////////////////
        
        OptionData data;

        ////////////////////////////////////////Checking Functions/////////////////////////////////////////////////
        
        // Check the input option type
        void CheckOptionType(const char& type) const;
        
        // Check the input factor value
        void CheckFactorValue(const double& T, const double& K, const double& sig, const double& r, const double& b, const double& S) const;
        
        // Check the input factor name
        void CheckFactorName(const std::string& factor) const;
        
        // Check whether the step works for the varying range of a factor
        void CheckStep(const double& start, const double& end, const double& step) const;

    public:
        ////////////////////////////////////////Constructors///////////////////////////////////////////////
        
        Option();                               // Default Constructor
        Option(const Option& op);               // Copy Constructor
        Option(const char& optType);            // Constructe an option of certain type
        Option(const struct OptionData& data);  // Constructe an option of certain typ
        
        /////////////////////////////////////////Destructor/////////////////////////////////////////////////
        
        virtual ~Option();
        
        //////////////////////////////////////////Operators/////////////////////////////////////////////////
        
        // Assignment operator
        Option& operator = (const Option& op);
        
        /////////////////////////////////Pure Virtual Price Getters/////////////////////////////////////////
        
        virtual double Price() const = 0;
        
        ///////////////////////////////////////////Getter///////////////////////////////////////////////////
        
        // Get the description of the object
        virtual std::string ToString() const;
        
        // Give the data of the object in the map form
        std::map<std::string, double> Factors() const;
        
        // Get the OptionData structure
        const struct OptionData& get_data() const;
        
        ////////////////////////////////////////Modifiers///////////////////////////////////////////////////
        
        // Set the data of the object
        void set_data(const struct OptionData& data);
        
        // Change option type (C/P, P/C)
        void toggle();
    };
}

#endif
