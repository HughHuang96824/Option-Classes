//  OptionData.hpp
//  Structure that holds the data and information of an option
//
//  AB
//
//  Created by Yaojia Huang on 2018/11/5.

#ifndef OptionData_hpp
#define OptionData_hpp

namespace All_Options
{
    struct OptionData
    {
        double T = 0;   // Expiry time
        double K = 1;   // Strike price
        double sig = 0; // volatility
        double r = 0;   // Risk free interest rate
        double b = 0;   // Cost of carry
        double S = 0;   // Asset price
        char   optType = 0; // Option Type
        std::string name = "Default"; // Asset name
    };
}

#endif
