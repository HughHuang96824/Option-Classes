This is class that can calculates the prices and sensitivities of European options or perpetual American options.


The European option class resides in All_Options::European namespace.
The perpetual American class resides in All_Options::PerpetualAmerican namespace.


The data of an option is stored in All_Options::OptionData, which is a data structure that has attributes T(exercise (maturity) date), K(strike price), sig(constant volatility), r(risk-free interest rate), b(cost of carry), S(asset price), optType(option type: 'c' for call and 'p' for put), name.


To use the member functions of these two classes, see the comments in EuropeanOption.hpp/EuropeanOption.cpp and PerpetualAmericanOption.hpp/PerpetualAmericanOption.cpp for details.


There are some global functions in the namespace All_Options for European and perpetual American options. These functions are used to calculate a vector of prices/sensitivities of an option with one varying parameter such as sig. See OptionMatrix.hpp/OptionMatrix.cpp for details.