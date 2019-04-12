#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>

// #include "utils.hpp"



/// Fitness class
// class FREQ{
//   private:
//     std::map fmap<std::std::vector<int> ,std::vector<double> >;
//
//   public:
//     FREQ(){};
//
//     // fitness functions
//     double freqSE(const double &s , const int &x, const double e=2){
//       switch(mode){
//         case 1:  // multiplicative
//           return 1 + (s * x) ;
//           break;
//         case 2:  // additive
//           return  (s * x) ;
//           break;
//         case 3:  // inverse multiplicative
//           // return 1 / (1 + s * x);
//           return pow((1 + s),x);
//           break;
//         default:  // multiplicative
//           return 1 - (s * x) ;
//           break;
//       }
//     }

int main(){
  std::vector<std::string> strs;
  boost::split(strs, "string to split", boost::is_any_of("\t"));
  std::cout<<  strs << std::endl;
  return 1;
}

// int testfreq (std::string filename="out/toyseeds.freq")
// {
//       std::ifstream file(filename);
//       std::string str;
//       while (std::getline(file, str))
//       {
//           // Process str
//           // std::cout << str << std::endl;
//           boost::split(str, "string to split", boost::is_any_of("\t"));
//
//       }
//     return (0);
// }
