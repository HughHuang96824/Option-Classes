//  PerpetualAmericanOption.cpp
//  Class that represents perpetual American options.
//  It can be used to calculate the put/call price,
//  put/call delta and gamma of a perpetual American option.
//
//  AB
//
//  Created by Yaojia Huang on 2018/11/3.

#include "PerpetualAmericanOption.hpp"
#include <boost/math/distributions/normal.hpp>
#include <cmath>

namespace All_Options
{
    namespace PerpetualAmerican
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////Private Price Calculator/////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        // Calculate Call Price
        double PerpetualAmericanOption::CallPrice
        (const double& K, const double& sig, const double& r, const double& b, const double& S) const
        {
            double tmp = sqrt((b/sig/sig-0.5)*(b/sig/sig-0.5) + 2*r/sig/sig);
            double y = 0.5 - b/sig/sig + tmp;
            return (K / (y - 1)) * pow( ( (y-1) * S / K / y ), y);
        }
        
        // Calculate Put Price
        double PerpetualAmericanOption::PutPrice
        (const double& K, const double& sig, const double& r, const double& b, const double& S) const
        {
            double tmp = sqrt((b/sig/sig-0.5)*(b/sig/sig-0.5) + 2*r/sig/sig);
            double y = 0.5 - b/sig/sig - tmp;
            return (K / (1 - y)) * pow( ( (y-1) * S / K / y ), y);
        }
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////Constructors/////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        // Default PerpetualAmericanOption constructor
        PerpetualAmericanOption::PerpetualAmericanOption(): Option() {}

        // Copy option
        PerpetualAmericanOption::PerpetualAmericanOption(const PerpetualAmericanOption& o2): Option(o2) {}

        // Create an option of certain type
        PerpetualAmericanOption::PerpetualAmericanOption(const char& optionType): Option(optionType) {}

        // Create an option using given data
        PerpetualAmericanOption::PerpetualAmericanOption(const struct OptionData& data): Option(data) {}

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////Destructor/////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        PerpetualAmericanOption::~PerpetualAmericanOption() {}
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////Operators/////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        // Assignment operator
        PerpetualAmericanOption& PerpetualAmericanOption::operator = (const PerpetualAmericanOption& option2)
        {
            // Return original objects if addresses are the same
            if (this == &option2) return *this;
            
            // Get the description from ToString() function
            Option::operator = (option2);
            return *this;
        }
        
        // Get the information of the object using <<
        std::ostream& operator << (std::ostream& os, const PerpetualAmericanOption& op)
        {
            // Get the description from ToString() function
            os << op.ToString();
            return os;
        }
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////Price Getters/////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        // Calculate the price of the option
        double PerpetualAmericanOption::Price() const
        {
            // Call the corresponding price calculator depending on the option type
            if (data.optType == 'C')
                return CallPrice(data.K, data.sig, data.r, data.b, data.S);
            return PutPrice(data.K, data.sig, data.r, data.b, data.S);
        }
        
        // Given a factor name and its value, calculate the price of the option
        // The class variable is not changed to the given value.
        double PerpetualAmericanOption::Price(std::string factor, const double& value) const
        {
            // Check if the input string matches any of the factors' name
            CheckFactorName(factor);
            
            // Get all factors in a map
            std::map<std::string, double> mp = Factors();
            
            // Change the factor to upper case
            boost::to_upper<std::string>(factor);
            
            // Change the value corresponding to the input factor name
            mp[factor] = value;
            
            // Check if the values of parameter are valid
            CheckFactorValue(mp["T"], mp["K"], mp["SIG"], mp["R"], mp["B"], mp["S"]);
            
            // Get the price
            if (data.optType == 'C')
                return CallPrice(mp["K"], mp["SIG"], mp["R"], mp["B"], mp["S"]);
            return PutPrice(mp["K"], mp["SIG"], mp["R"], mp["B"], mp["S"]);
        }
        
        
        // Given a factor name and start, end and step of the factor
        // Calculte the price of the option for each variable change. Output a vector of prices
        std::vector<double> PerpetualAmericanOption::Price
        (std::string factor, const double& start, const double& end, const double& step) const
        {
            // Check if the input string matches any of the factors' name
            CheckFactorName(factor);
            // Check whether the step is valid
            CheckStep(start, end, step);
            
            // Change the factor to upper case
            boost::to_upper<std::string>(factor);
            
            // Check the value of the input factor
            if ((end < 0 || start < 0) || ((end == 0 || start ==0) && factor == "K"))
                throw InvalidValueException();
            
            // Get all factors in a map
            std::map<std::string, double> mp = Factors();
            
            // Create a vector that will store prices of different option parameters
            std::vector<double> price_vec;
            
            // Use to determine whether the varying parameter is increasing or decreasing
            int direction = (end > start)? 1:-1;
            
            if (data.optType == 'C')
            {
                // Loop over varying options
                for (double i = start; (i - end) * direction <= 0; i += step)
                {
                    // Change the value corresponding to the input factor name
                    mp[factor] = i;
                    // Get the price and put it in the vector
                    price_vec.push_back(CallPrice(mp["K"], mp["SIG"], mp["R"], mp["B"], mp["S"]));
                }
            }
            else
            {
                // Loop over varying options
                for (double i = start; (i - end) * direction <= 0; i += step)
                {
                    // Change the value corresponding to the input factor name
                    mp[factor] = i;
                    // Get the price and put it in the vector
                    price_vec.push_back(PutPrice(mp["K"], mp["SIG"], mp["R"], mp["B"], mp["S"]));
                }
            }
            
            return price_vec;
        }
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////Description/////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        std::string PerpetualAmericanOption::ToString() const
        {
            // Create a stringstream
            std::stringstream str;
            
            // Put the content from Options to the stringstream
            str << "Perpetual American Option\n" << Option::ToString();
            return str.str();
        }
    }
}


