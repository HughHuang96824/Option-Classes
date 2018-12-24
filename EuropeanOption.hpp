// EuropeanOption.hpp
//
// Class that represents European options.
// It can be used to calculate the put/call price,
// put/call delta and gamma of a European option.
//
// AB
//
//  Created by Yaojia Huang on 2018/10/31.

#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp

#include "Options.hpp"

namespace All_Options
{
    namespace European
    {
        class EuropeanOption: public Option
        {
        private:
            
            ////////////////////////Private Price and Sensitivity Calculators///////////////////////////////////
            
            // Calculate Call Price
            static double CallPrice
            (const double& T, const double& K, const double& sig, const double& r, const double& b, const double& S);
            
            // Calculate Put Price
            static double PutPrice
            (const double& T, const double& K, const double& sig, const double& r, const double& b, const double& S);
            
            // Calculate Call Delta
            static double CallDelta
            (const double& T, const double& K, const double& sig, const double& r, const double& b, const double& S);
            
            // Calculate Put Delta
            static double PutDelta
            (const double& T, const double& K, const double& sig, const double& r, const double& b, const double& S);
            
            // Calculate Gamma
            static double Gamma
            (const double& T, const double& K, const double& sig, const double& r, const double& b, const double& S);
            
            
            // Serve for public Price(), Delta(), Gamma() function
            // Return the call/put price, delta or gamma of the option depneding on the input function
            double Calculate
            (double (*func)(const double&, const double&, const double&, const double&, const double&, const double&),
             std::string factor, const double& value) const;
            
            
            // Serve for Price(), Delta(), Gamma() functions that return vectors of price/delta/gamma
            // Return the call/put price, delta or gamma vectors of the option depneding on the input function
            std::vector<double> Mat
            (double (*func)(const double&, const double&, const double&, const double&, const double&, const double&),
             std::string factor, const double& start, const double& end, const double& step) const;
            
        public:
            
            ////////////////////////////////////////Constructors///////////////////////////////////////////////
            
            EuropeanOption();                                    // Default EuropeanOption Constructor
            EuropeanOption(const EuropeanOption& option2);	     // Copy Constructor
            EuropeanOption(const char& optionType);              // Constructe an option of certain type
            EuropeanOption(const struct OptionData& optionData); // Constructe an option using given data
            
            /////////////////////////////////////////Destructor///////////////////////////////////////////////
            
            virtual ~EuropeanOption();
            
            /////////////////////////////////////////Operators///////////////////////////////////////////////
            
            // Assignment operator
            EuropeanOption& operator = (const EuropeanOption& option2);
            
            // Get the information of the object using <<
            friend std::ostream& operator << (std::ostream& os, const EuropeanOption& op);
            
            //////////////////////////////////////Price Getters/////////////////////////////////////////////////
            
            // Calculate the price of the option
            virtual double Price() const;
            
            // Given a factor name and its value, calculate the price of the option
            // The class variable is not changed to the given value.
            virtual double Price(std::string factor, const double& value) const;
            
            // Given a factor name and start, end and step of the factor
            // Calculte the price of the option for each variable change. Output a vector of prices
            virtual std::vector<double> Price(std::string factor, const double& start, const double& end, const double& step) const;
            
            //////////////////////////////////////Delta Getters/////////////////////////////////////////////////
            
            // Calculate the delta of the option
            double Delta() const;
            
            // Given a factor name and its value, calculate the delta of the option
            // The class variable is not changed to the given value.
            double Delta(std::string factor, const double& value) const;
            
            // Given a factor name and start, end and step of the factor
            // Calculte the delta of the option for each variable change. Output a vector of deltas
            std::vector<double> Delta(std::string factor, const double& start, const double& end, const double& step) const;
            
            // Approximate delta by finding the slope between S-h and S+h
            double Approx_Delta(const double& h) const;
            
            // Approximate delta by finding the slope between s-h and s+h, where s is given by the user
            double Approx_Delta(const double& s, const double& h) const;
            
            //////////////////////////////////////Gamma Getters/////////////////////////////////////////////////
            
            // Calculate the gamma of the option
            double Gamma() const;
            
            // Given a factor name and its value, calculate the gamma of the option
            // The class variable is not changed to the given value.
            double Gamma(std::string factor, const double& value) const;
            
            // Given a factor name and start, end and step of the factor
            // Calculte the gamma of the option for each variable change. Output a vector of gammas
            std::vector<double> Gamma(std::string factor, const double& start, const double& end, const double& step) const;
            
            // Approximate gamma by finding the slope between S-h and S+h
            double Approx_Gamma(const double& h) const;
            
            // Approximate gamma by finding the slope between s-h and s+h, where s is given by the user
            double Approx_Gamma(const double& s, const double& h) const;
            
            //////////////////////////////////////Put-Call Parity///////////////////////////////////////////////
            
            // Given a option type and a price, calculate the parity price
            double Put_Call_Parity(const double& PC, const char& type) const;
            
            // Given two prices, judge whether they satisfy parity
            double Put_Call_Parity(const double& C, const double& P) const;
            
            ////////////////////////////////////////Description/////////////////////////////////////////////////
            
            // Function that gives the information of an option
            virtual std::string ToString() const;
        };
    }
}

#endif
