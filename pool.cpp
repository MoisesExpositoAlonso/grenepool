#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>

#include "utils.h"


int usage(char **argv)
{
  printf("\Print a pseudo-vcf of base frequencies of one/multiple pooled populations.\n");
  printf("\nUsage: %s [options] file.freq\n\n", argv[0]);
  printf("Options:\n");

  printf("\t-h\tonly print heterozygous positions\n");
  printf("\t-f\tmin fraction of read support\n");
  printf("\t-q\tmin map quality\n");
  printf("\t-c\tmin coverage of position to be reported\n");
  printf("\t-m\tmax coverage of position to be reported\n\n");
  printf("\t-r\tonly print raw counts without bases, coverage or position\n\n");

  printf("Default output:\nSeq\tPos\tCov\tBase1\tCount1\t...\tBaseN\tCountN\n\n");
  return 1;
}



void processfiles(std::string filename)
{
    std::ifstream file(filename);
    std::string str;
    while (std::getline(file, str))
    {
        // Process str
        std::cout << str << std::endl;
    }
}


std::vector<std::string> strs;
boost::split(strs, "string to split", boost::is_any_of("\t"));

freqclass freq;
for(int i=1; i <= argc; i++){
             std::string fn = argv[i]; //filename
             std::cout << fn <<std::endl;

                 while (std::getline(file, str))
                 {
                     // Process str
                     std::cout << str << std::endl;
                 }
             // fstream f;
             // f.open(fn);
             //your logic here
             // processfile(fn);
             // end logic
             // f.close();
     }


int main(int argc, char **argv)
{
  if (argc < 2){
    usage(argv);
  }
  else{
    processfiles(argc,argv);
    return 0;
  }

}



// std::vector<std::string> readFileToVector(const std::string& filename)
// {
//     std::ifstream source;
//     source.open(filename);
//     std::vector<std::string> lines;
//     std::string line;
//     while (std::getline(source, line))
//     {
//         lines.push_back(line);
//     }
//     return lines;
// }
//
// void displayVector(const std::vector<std::string&> v)
// {
//     for (int i(0); i != v.size(); ++i)
//         std::cout << "\n" << v[i];
// }
//
// int main(int argc,  char **argv)
// {
//     std::string charactersFilename(argv[1]);
//     std::string matchesFilename(argv[2]);
//     std::vector<std::string> characters = readFileToVector(charactersFilename);
//     std::vector<std::string> matches = readFileToVector(matchesFilename);
//
//     displayVector(characters);
//     displayVector(matches);
// }
