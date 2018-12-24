//  main.cpp
//  Test program for option classes
//
//  AB
//
//  Created by Yaojia Huang on 2018/10/31.

#include <iostream>
#include <vector>
#include <map>
#include "Exception.hpp"
#include "EuropeanOption.hpp"
#include "PerpetualAmericanOption.hpp"
#include "OptionMatrix.hpp"

using namespace std;
using namespace All_Options;
using European::EuropeanOption;
using PerpetualAmerican::PerpetualAmericanOption;
int main()
{
    
    cout << "Testing Constructors, Getters and Setters, and Price Calculation.\n" << endl;
    
    // Create four batches
    OptionData Batch1;
    
    // Set the data of each Batches. Name and optType are optional
    Batch1.T = 1.5; Batch1.K = 120; Batch1.sig = 0.4; Batch1.r = 0.04; Batch1.b = 0.0; Batch1.S = 100; Batch1.optType = 'C';
    //Batch1.T = 0.5; Batch1.K = 100; Batch1.sig = 0.36; Batch1.r = 0.1; Batch1.b = 0; Batch1.S = 105;
    EuropeanOption euro(Batch1);
    
    cout << "C price: " << euro.Price() << endl;
    cout << "C delta: " << euro.Delta() << endl;
    cout << "Gamma: " << euro.Gamma() << endl;
    
    euro.toggle();
    cout << "P price: " << euro.Price() << endl;
    cout << "P delta: " << euro.Delta() << endl;
    cout << "Gamma: " << euro.Gamma() << "\n" << endl;
    
    std::vector<double> price_s = euro.Price("SiG", 0.1, 0.9, 0.2);
    cout << "Put prices of varying sig(from 0.1 to 0.9 with step = 0.2):" << endl;
    for (int i = 0; i < price_s.size(); i++)
    {
        cout << price_s[i] << ", ";
    }
    cout << "\n" << endl;
    
    
    std::vector<double> delta_vector = euro.Delta("b", 0.02, 0.1, 0.01);
    cout << "Put delta of varying b(from 0.02 to 0.1 with step = 0.01):" << endl;
    for (int i = 0; i < delta_vector.size(); i++)
    {
        cout << delta_vector[i] << ", ";
    }
    cout << "\n" << endl;
    

    cout << "Approximate delta: " << euro.Approx_Delta(0.01) <<"\n"<< endl;
    cout << "Approximate gamma: " << euro.Approx_Gamma(0.01) <<"\n"<< endl;
    

    
    cout << "//////////////////Testing Perpetual American/////////////////.\n" << endl;
    
    
    // Create a perpetual American option data struct
    OptionData Amebatch1;
    
    // Set the data
    Amebatch1.K = 100; Amebatch1.sig = 0.1; Amebatch1.r = 0.1; Amebatch1.b = 0.02; Amebatch1.S = 110; Amebatch1.name = "American";
    
    // Create a perpetual American option
    PerpetualAmericanOption Ame1(Amebatch1);
    
    cout << Ame1 << "\n" << endl;
    
    // Print its put price
    cout << "Put Price: " << Ame1.Price() << endl;
    // Change the option type
    Ame1.toggle();
    // Print the call price
    cout << "Call Price: " << Ame1.Price() << "\n" << endl;

    
    
    
    // Get the price vector of Ame1 with varying r (0.1 to 0.5 with step = 0.1)
    vector<double> Ameprice = Ame1.Price("r", 0.1, 0.5, 0.1);
    
    // Print each price
    for (int i = 0; i < Ameprice.size(); i++)
    {
        cout << Ameprice[i] << endl;
    }
    cout << "\n";

}
