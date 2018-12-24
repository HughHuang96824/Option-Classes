// EurpeanOption.cpp
//
// Class that represents European options.
// It can be used to calculate the put/call price,
// put/call delta and gamma of a European option.
//
// AB
//
//  Created by Yaojia Huang on 2018/10/31.

#include "EuropeanOption.hpp"
#include <cctype>
#include <sstream>
#include <iostream>
#include <boost/math/distributions/normal.hpp>
#include <boost/algorithm/string.hpp>

namespace All_Options
{
    namespace European
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////Private Price and Sensitivity Calculators///////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        // Calculate Call Price
        double EuropeanOption::CallPrice
        (const double& T, const double& K, const double& sig, const double& r, const double& b, const double& S)
        {
            double tmp = sig * sqrt(T);
            double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
            double d2 = d1 - tmp;
            boost::math::normal_distribution<> Normal;
            
            return (S * exp((b-r)*T) * cdf(Normal, d1)) - (K * exp(-r * T)* cdf(Normal, d2));
        }
        
        // Calculate Put Price
        double EuropeanOption::PutPrice
        (const double& T, const double& K, const double& sig, const double& r, const double& b, const double& S)
        {
            double tmp = sig * sqrt(T);
            double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
            double d2 = d1 - tmp;
            boost::math::normal_distribution<> Normal;
            
            return (K * exp(-r * T)* cdf(Normal, -d2)) - (S * exp((b-r)*T) * cdf(Normal, -d1));
        }
        
        
        // Calculate Call Delta
        double EuropeanOption::CallDelta
        (const double& T, const double& K, const double& sig, const double& r, const double& b, const double& S)
        {
            double tmp = sig * sqrt(T);
            double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
            boost::math::normal_distribution<> Normal;
            
            return exp((b-r)*T) * cdf(Normal, d1);
        }
        
        // Calculate Put Delta
        double EuropeanOption::PutDelta
        (const double& T, const double& K, const double& sig, const double& r, const double& b, const double& S)
        {
            double tmp = sig * sqrt(T);
            double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
            boost::math::normal_distribution<> Normal;
            
            return exp((b-r)*T) * (cdf(Normal, d1) - 1.0);
        }
        
        // Calculate Gamma
        double EuropeanOption::Gamma
        (const double& T, const double& K, const double& sig, const double& r, const double& b, const double& S)
        {
            double tmp = sig * sqrt(T);
            double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
            boost::math::normal_distribution<> Normal;
            
            return (exp((b-r)*T) * pdf(Normal, d1))/S/tmp ;
        }
        
        
        // Serve for public Price(), Delta(), Gamma() function
        // Return the call/put price, delta or gamma of the option depneding on the input function
        double EuropeanOption::Calculate
        (double (*func)(const double&, const double&, const double&, const double&, const double&, const double&),
         std::string factor, const double& value) const
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
            
            // Call the corresponding input functions depending on the option type
            return func(mp["T"], mp["K"], mp["SIG"], mp["R"], mp["B"], mp["S"]);
        }
        
        
        // Serve for Price(), Delta(), Gamma() function that returns vectors
        // Return the call/put price, delta or gamma vectors of the option depneding on the input function
        std::vector<double> EuropeanOption::Mat
        (double (*func)(const double&, const double&, const double&, const double&, const double&, const double&),
         std::string factor, const double& start, const double& end, const double& step) const
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
            
            // Create a vector that will store data of different option parameters
            std::vector<double> vec;
            
            // Used to determine whether the varying parameter is increasing or decreasing
            int direction = (end > start)? 1:-1;
            
            // Loop over varying options
            for (double i = start; (i - end) * direction <= 0; i += step)
            {
                // Change the value corresponding to the input factor name
                mp[factor] = i;
                // Call the corresponding input function and put the resultant data in the vector
                vec.push_back(func(mp["T"], mp["K"], mp["SIG"], mp["R"], mp["B"], mp["S"]));
            }
          
            return vec;
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////Constructors/////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        // Default EuropeanOption Constructor
        EuropeanOption::EuropeanOption(): Option() {}
        
        
        // Copy Constructor
        EuropeanOption::EuropeanOption(const EuropeanOption& o2): Option(o2) {}
        
        
        // Constructe an option of certain type
        EuropeanOption::EuropeanOption(const char& optionType): Option(optionType) {}
        
        
        // Constructe an option using given data
        EuropeanOption::EuropeanOption(const struct OptionData& data): Option(data) {}
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////Destructor/////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        EuropeanOption::~EuropeanOption() {}

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////Operators/////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        // Assignment operator
        EuropeanOption& EuropeanOption::operator = (const EuropeanOption& option2)
        {
            // Return original objects if addresses are the same
            if (this == &option2) return *this;
            
            // If addresses are not the same, assisgn.
            Option::operator = (option2);
            return *this;
        }
        
        
        // Get the information of the object using <<
        std::ostream& operator << (std::ostream& os, const EuropeanOption& op)
        {
            // Get the description from ToString() function
            os << op.ToString();
            return os;
        }
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////Price Getters/////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        // Calculate the price of the option
        double EuropeanOption::Price() const
        {
            // Call the corresponding price calculator depending on the option type
            if (data.optType == 'C')
                return CallPrice(data.T, data.K, data.sig, data.r, data.b, data.S);
            return PutPrice(data.T, data.K, data.sig, data.r, data.b, data.S);
        }
        
        
        // Given a factor name and its value, calculate the price of the option
        // The class variable is not changed to the given value.
        double EuropeanOption::Price(std::string factor, const double& value) const
        {
            if (data.optType == 'C')
                return Calculate(CallPrice, factor, value);
            return Calculate(PutPrice, factor, value);
        }
        
        
        // Given a factor name and start, end and step of the factor
        // Calculte the price of the option for each variable change. Output a vector of prices
        std::vector<double> EuropeanOption::Price
        (std::string factor, const double& start, const double& end, const double& step) const
        {
            if (data.optType == 'C')
                return Mat(CallPrice, factor, start, end, step);
            return Mat(PutPrice, factor, start, end, step);
        }
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////Delta Getters/////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        // Calculate the delta of the option
        double EuropeanOption::Delta() const
        {
            // Call the corresponding delta calculator depending on the option type
            if (data.optType == 'C')
                return CallDelta(data.T, data.K, data.sig, data.r, data.b, data.S);
            return PutDelta(data.T, data.K, data.sig, data.r, data.b, data.S);
        }
        
        
        // Given a factor name and its value, calculate the delta of the option
        // The class variable is not changed to the given value.
        double EuropeanOption::Delta(std::string factor, const double& value) const
        {
            if (data.optType == 'C')
                return Calculate(CallDelta, factor, value);
            return Calculate(PutDelta, factor, value);
        }
        
        
        // Given a factor name and start, end and step of the factor
        // Calculte the delta of the option for each variable change. Output a vector of deltas
        std::vector<double> EuropeanOption::Delta(std::string factor, const double& start, const double& end, const double& step) const
        {
            if (data.optType == 'C')
                return Mat(CallDelta, factor, start, end, step);
            return Mat(PutDelta, factor, start, end, step);
        }
        
        
        
        // Approximate delta by finding the slope between S-h and S+h
        double EuropeanOption::Approx_Delta(const double& h) const
        {
            return Approx_Delta(data.S, h);
        }
        
        
        // Approximate delta by finding the slope between s-h and s+h, where s is given by the user
        double EuropeanOption::Approx_Delta(const double& s, const double& h) const
        {
            return (Price("S", s+h) - Price("S", s-h))/2/h;
        }
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////Gamma Getters/////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        // Calculate the gamma of the option
        double EuropeanOption::Gamma() const
        {
            // Call the gamma calculator
            return Gamma(data.T, data.K, data.sig, data.r, data.b, data.S);
        }
        
        
        // Given a factor name and its value, calculate the gamma of the option
        // The class variable is not changed to the given value.
        double EuropeanOption::Gamma(std::string factor, const double& value) const
        {
            return Calculate(Gamma, factor, value);
        }
        
        
        // Given a factor name and start, end and step of the factor
        // Calculte the gamma of the option for each variable change. Output a vector of gammas
        std::vector<double> EuropeanOption::Gamma(std::string factor, const double& start, const double& end, const double& step) const
        {
            return Mat(Gamma, factor, start, end, step);
        }
        
        
        // Approximate gamma by finding the slope between S-h and S+h
        double EuropeanOption::Approx_Gamma(const double& h) const
        {
            return Approx_Gamma(data.S, h);
        }
        
        
        // Approximate gamma by finding the slope between s-h and s+h, where s is given by the user
        double EuropeanOption::Approx_Gamma(const double& s, const double& h) const
        {
            return (Price("S", s+h) + Price("S", s-h) - 2 * Price("S", s))/h/h;
        }
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////Put-Call Parity///////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        // Given a option type and a price, calculate the parity price
        double EuropeanOption::Put_Call_Parity(const double& PC, const char& type) const
        {
            // Check whether the input option type is valid
            CheckOptionType(type);
            
            // Check the value of the input price
            if (PC < 0)
                throw InvalidValueException();
            
            // Use different equation according to the option type
            if (toupper(type) == 'C')
                return PC - data.S + data.K * exp(-data.r * data.T);
            
            return PC + data.S - data.K * exp(-data.r * data.T);
        }
        
        
        // Given two prices, judge whether they satisfy parity
        double EuropeanOption::Put_Call_Parity(const double& C, const double& P) const
        {
            // Calculate the parity of C and compare it with P
            // If the difference is smaller than 0.00001, they satisfy parity relation
            return abs(Put_Call_Parity(C, 'C') - P) < 1.0/100000;
        }
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////Description/////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        std::string EuropeanOption::ToString() const
        {
            // Create a stringstream
            std::stringstream str;
            
            // Put the content from Options to the stringstream
            str << "European Option\n" << Option::ToString();
            
            // Add description of T
            str << "\nT:   " << data.T;
            
            return str.str();
        }
    }
}
