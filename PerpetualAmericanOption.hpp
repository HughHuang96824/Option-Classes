//  PerpetualAmericanOption.hpp
//  Class that represents perpetual American options.
//  It can be used to calculate the put/call price,
//  put/call delta and gamma of a perpetual American option.
//
//  AB
//
//  Created by Yaojia Huang on 2018/11/3.

#ifndef PerpetualAmericanOption_hpp
#define PerpetualAmericanOption_hpp

#include "Options.hpp"

namespace All_Options
{
    namespace PerpetualAmerican
    {
        class PerpetualAmericanOption: public Option
        {
        private:
            
            ///////////////////////////////////Private Price Calculator////////////////////////////////////////
            
            // Calculate Call Price
            double CallPrice
            (const double& K, const double& sig, const double& r, const double& b, const double& S) const;
            
            // Calculate Put Price
            double PutPrice
            (const double& K, const double& sig, const double& r, const double& b, const double& S) const;
            
        public:
            
            ////////////////////////////////////////Constructors///////////////////////////////////////////////
            
            // Default PerpetualAmericanOption constructor
            PerpetualAmericanOption();
            
            // Copy Constructor
            PerpetualAmericanOption(const PerpetualAmericanOption& option2);
            
            // Constructe an option of certain type
            PerpetualAmericanOption(const char& optionType);
            
            // Constructe an option using given data
            PerpetualAmericanOption(const struct OptionData& optionData);
            
            /////////////////////////////////////////Destructor/////////////////////////////////////////////////
            
            virtual ~PerpetualAmericanOption();
            
            //////////////////////////////////////////Operators/////////////////////////////////////////////////
            
            // Assignment operator
            PerpetualAmericanOption& operator = (const PerpetualAmericanOption& option2);
            
            // Get the information of the object using <<
            friend std::ostream& operator << (std::ostream& os, const PerpetualAmericanOption& op);
            
            //////////////////////////////////////Price Getters/////////////////////////////////////////////////
            
            // Calculate the price of the option
            virtual double Price() const;
            
            // Given a factor name and its value, calculate the price of the option
            // The class variable is not changed to the given value.
            virtual double Price(std::string factor, const double& value) const;
            
            // Given a factor name and start, end and step of the factor
            // Calculte the price of the option for each variable change. Output a vector of prices
            virtual std::vector<double> Price(std::string factor, const double& start, const double& end, const double& step) const;
            
            ////////////////////////////////////////Description/////////////////////////////////////////////////
            
            virtual std::string ToString() const;
        };
    }
}

#endif
