//  OptionMatrix.cpp
//  Global functions that take matrix of option data and
//  calculate the price of each row
//
//  AB
//
//  Created by Yaojia Huang on 2018/11/5.


#include "OptionMatrix.hpp"
#include "Exception.hpp"
#include "EuropeanOption.hpp"
#include "PerpetualAmericanOption.hpp"
#include <boost/math/distributions/normal.hpp>
#include <cctype>

namespace All_Options
{
    
    // The function takes in one OptionData structure
    // Also take the name of the varying parameter and its range and step size
    // Return a matrix of option data
    std::vector<std::vector<double>> GenerateMatrix
    (const struct OptionData& source, const std::string& factor, const double& start, const double& end, const double& step)
    {
        // Make the factor uppercase
        std::string str = boost::to_upper_copy(factor);
        
        // Check factors' names
        if (str != "R" && str != "T" && str != "K" && str != "B" && str != "S" && str != "SIG")
            throw InvalidFactorException(factor);
        
        // Check range and step
        if (((end - start) < 0 && step >= 0) || ((end - start) > 0 && step <= 0) || step == 0)
            throw InvalidStepException(step, start, end);
        
        // Create a matrix, a vector and a map
        std::vector<std::vector<double>> matrix;
        std::vector<double> each;
        std::map<std::string, double> mp;
        
        // Put the data in the map
        mp["R"] = source.r;
        mp["B"] = source.b;
        mp["SIG"] = source.sig;
        mp["T"] = source.T;
        mp["K"] = source.K;
        mp["S"] = source.S;
        
        // Record whether the varying parameter is increasing or decreasing
        int direction = (end > start)? 1:-1;
        
        // Loop over each option in the vector
        for (double i = start; (i - end) * direction <= 0; i += step)
        {
            // Change the value of the specified factor
            mp[str] = i;
            
            // Fill the vector with the data
            each.push_back(mp["T"]);
            each.push_back(mp["K"]);
            each.push_back(mp["SIG"]);
            each.push_back(mp["R"]);
            each.push_back(mp["B"]);
            each.push_back(mp["S"]);
            
            // Put the vector in the matrix
            matrix.push_back(each);
            
            // Clear the vector and ready for the next iteration
            each.clear();
        }
        return matrix;
    }
    
    
    
    // The function takes in a vector of OptionData structures
    // Return a matrix of option data
    std::vector<std::vector<double>> GenerateMatrix
    (const std::vector<struct OptionData>& batches)
    {
        // Create a matrix and a vector
        std::vector<std::vector<double>> matrix;
        std::vector<double> each;
        
        // Loop over each option in the vector
        for (int i = 0; i < batches.size(); i++)
        {
            // Fill the vector with the data
            each.push_back(batches[i].T);
            each.push_back(batches[i].K);
            each.push_back(batches[i].sig);
            each.push_back(batches[i].r);
            each.push_back(batches[i].b);
            each.push_back(batches[i].S);
            
            // Put the vector in the matrix
            matrix.push_back(each);
            
            // Clear the vector and ready for the next iteration
            each.clear();
        }
        return matrix;
    }
    
    
    
    namespace European
    {
        // Take in a matrix of option data and return a vector of prices
        std::vector<double> MatrixPricer(const std::vector<std::vector<double>>& matrix, const char& type)
        {
            // Create a option data structure
            OptionData batch;
            
            // Create a European option
            EuropeanOption opt;
            
            // Vector that stores the prices
            std::vector<double> price;
            
            // Iterate every row of the matrix
            for (int i = 0; i < matrix.size(); i++)
            {
                // the data structure takes the data from each row of the matrix
                batch.T = matrix[i][0]; batch.K = matrix[i][1]; batch.sig = matrix[i][2];
                batch.r = matrix[i][3]; batch.b = matrix[i][4]; batch.S = matrix[i][5]; batch.optType = type;
                
                // Set the data of the European option
                opt.set_data(batch);
                
                // Get the price of the option and put the price in the vector
                price.push_back(opt.Price());
                
            }
            
            return price;
        }
        
        // Take in a matrix of option data and return a vector of deltas
        std::vector<double> MatrixDelta(const std::vector<std::vector<double>>& matrix, const char& type)
        {
            // Create a option data structure
            OptionData batch;
            
            // Create a European option
            EuropeanOption opt;
            
            // Vector that stores the deltas
            std::vector<double> delta;
            
            // Iterate every row of the matrix
            for (int i = 0; i < matrix.size(); i++)
            {
                // the data structure takes the data from each row of the matrix
                batch.T = matrix[i][0]; batch.K = matrix[i][1]; batch.sig = matrix[i][2];
                batch.r = matrix[i][3]; batch.b = matrix[i][4]; batch.S = matrix[i][5]; batch.optType = type;
                
                // Set the data of the European option
                opt.set_data(batch);
                
                // Get the delta of the option and put the delta in the vector
                delta.push_back(opt.Delta());
                
            }

            return delta;
        }
        
        // Take in a matrix of option data and return a vector of gammas
        std::vector<double> MatrixGamma(const std::vector<std::vector<double>>& matrix)
        {
            // Create a option data structure
            OptionData batch;
            
            // Create a European option
            EuropeanOption opt;
            
            // Vector that stores the gammas
            std::vector<double> gamma;
            
            // Iterate every row of the matrix
            for (int i = 0; i < matrix.size(); i++)
            {
                // the data structure takes the data from each row of the matrix
                batch.T = matrix[i][0]; batch.K = matrix[i][1]; batch.sig = matrix[i][2];
                batch.r = matrix[i][3]; batch.b = matrix[i][4]; batch.S = matrix[i][5];
                
                // Set the data of the European option
                opt.set_data(batch);
                
                // Get the gamma of the option and put the gamma in the vector
                gamma.push_back(opt.Gamma());
            }
            
            return gamma;
        }
    }
    
    
    namespace PerpetualAmerican
    {
        // Take in a matrix of option data and return a vector of prices
        std::vector<double> MatrixPricer(const std::vector<std::vector<double>>& matrix, const char& type)
        {
            // Create a option data structure
            OptionData batch;
            
            // Create a perpetual American option
            PerpetualAmericanOption opt;
            
            // Vector that stores the prices
            std::vector<double> price;
            
            // Iterate every row of the matrix
            for (int i = 0; i < matrix.size(); i++)
            {
                // the data structure takes the data from each row of the matrix
                batch.K = matrix[i][1]; batch.sig = matrix[i][2]; batch.r = matrix[i][3];
                batch.b = matrix[i][4]; batch.S = matrix[i][5]; batch.optType = type;
                
                // Set the data of the European option
                opt.set_data(batch);
                
                // Get the price of the option and put the price in the vector
                price.push_back(opt.Price());
            }
            
            return price;
        }
    }
}
