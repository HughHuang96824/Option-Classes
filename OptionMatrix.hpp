//  OptionMatrix.hpp
//  Global functions that take matrix of option data and
//  calculate the price of each row
//
//  AB
//
//  Created by Yaojia Huang on 2018/11/5.

#ifndef OptionMatrix_hpp
#define OptionMatrix_hpp

#include <cmath>
#include <vector>
#include "Exception.hpp"

namespace All_Options
{

    // The function takes in one OptionData structure
    // Also take the name of the varying parameter and its range and step size
    // Return a matrix of option data
    std::vector<std::vector<double>> GenerateMatrix
    (const struct OptionData& data, const std::string& factor, const double& start, const double& end, const double& step);
    
    
    // The function takes in a vector of OptionData structures
    // Return a matrix of option data
    std::vector<std::vector<double>> GenerateMatrix(const std::vector<struct OptionData>& batches);
    
    
    namespace European // In the European Namespace
    {
        // Take in a matrix of option data and return a vector of prices
        std::vector<double> MatrixPricer(const std::vector<std::vector<double>>& matrix, const char& type = 'C');
        
        // Take in a matrix of option data and return a vector of deltas
        std::vector<double> MatrixDelta(const std::vector<std::vector<double>>& matrix, const char& type = 'C');
        
        // Take in a matrix of option data and return a vector of gammas
        std::vector<double> MatrixGamma(const std::vector<std::vector<double>>& matrix);
    }
    
    namespace PerpetualAmerican // In the PerpetualAmerican Namespace
    {
        // Take in a matrix of option data and return a vector of prices
        std::vector<double> MatrixPricer(const std::vector<std::vector<double>>& matrix, const char& type = 'C');
    }
}

#endif
