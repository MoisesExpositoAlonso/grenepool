
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <limits>
using namespace std;
#include </ebio/abt6/mexposito/softwares/boost/boost/algorithm/string.hpp>
#include <bits/stdc++.h>

////
// int usage(char **argv)
// {
//   printf("\nPrint a pseudo-vcf of base frequencies of one/multiple pooled populations.\n");
//   printf("\nUsage: %s [options] file.freq\n\n", argv[0]);
//   printf("Options:\n");
//
//   printf("\t-h\tonly print heterozygous positions\n");
//   printf("\t-f\tmin fraction of read support\n");
//   printf("\t-q\tmin map quality\n");
//   printf("\t-c\tmin coverage of position to be reported\n");
//   printf("\t-m\tmax coverage of position to be reported\n\n");
//   printf("\t-r\tonly print raw counts without bases, coverage or position\n\n");
//
//   printf("Default output:\nSeq\tPos\tCov\tBase1\tCount1\t...\tBaseN\tCountN\n\n");
//   return 1;
// }
////

// int main(){
//   std::ifstream file("toy2.freq");
//   if (file.is_open()) {
//       std::string line;
//       std::getline(file, line); // skip the first line
//       while (getline(file, line)) {
//           // using printf() in all tests for consistency
//           printf("%s\n", line.c_str());
//       }
//       file.close();
//   }
//   return(1);
// }

// int main(){
//   std::ifstream file("toy2.freq");
//   if (file.is_open()) {
//       std::string line;
//       std::getline(file, line); // skip the first line
//       while (getline(file, line)) {
//           // using printf() in all tests for consistency
//           printf("%s\n", line.c_str());
//           std::vector<std::string> line;
//           boost::split(results, text, [](char c){return c == ' ';});
//           // std::istringstream iss(line);
//           // std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
//           //                                  std::istream_iterator<std::string>());
//          printf("%c\n", results.at(1));
//       }
//       file.close();
//   }
//   return(1);
// }

////////////////////////////////////////////////////////////////////////////////
//https://stackoverflow.com/questions/39518689/executing-line-counting-bash-command-wc-l-inside-a-c-program
int countfilerows(string FILE_NAME){
    // fstream in("toynoheader.freq");
    // string FILE_NAME(argv[1]);
    fstream in(FILE_NAME);
    int lines = 0;
    char endline_char = '\n';
    while (in.ignore(numeric_limits<streamsize>::max(), in.widen(endline_char)))
    {
      ++lines;
    }
    // cout << "-> reading " << lines << " lines in file..." << endl;
    return lines;
}

////////////////////////////////////////////////////////////////////////////////
// Hash

class Hash{
  public:
    map<string,string> mm;
    string outfile;
    string samplefile;
    // member function declarations
    void setfile(string filename);
    void addontop(string key,string val);
    void newadd(string key,string val);
    void printhash();
};
// member functions definitions
void Hash::setfile(string filename){
  string outfile=filename,
  stirng samplefile=filename;

  samplefile.append(".sample");
  outfile.append('.fvcf')
}

void Hash::addontop(string key,string val){
    if ( mm.find(key) != mm.end()){
      // found
      string str;
      string spacer="-";
      str.append(mm[key]);
      str.append(spacer);
      str.append(val);
      mm[key]=str;
    }
  }
void Hash::newadd(string key,string val){
      mm[key]=val;
  }
// IO functions
void Hash::printhash(void){
      map<string, string>::iterator it = mm.begin();

      while(it != mm.end()){
        string genotype = it->second;
        string index = it->first;
        char chr = index.at(0);
        string pos = index.erase(0,0);

        if(genotype.find('-') != std::string::npos) // only if there are more than 1 genotype
          std::cout<<chr<<"\t"<<pos<<"\t"<<genotype<<std::endl;
        it++;
      }
  }

  // int main () {
  //   ofstream myfile;
  //   myfile.open ("example.txt");
  //   myfile << "Writing this to a file.\n";
  //   myfile.close();
  //   return 0;
  // }


class Samples:
  private ss vector<string>
     Samples();
     add samples
     write to file
}



////////////////////////////////////////////////////////////////////////////////
// from https://stackoverflow.com/questions/15588800/reading-matrix-from-a-text-file-to-2d-integer-array-c
// Open file and read int matrix
// remember order Seq	Pos	Cov	#A	#C	#G	#T	#N	#D

int main(int argc, char *argv[]){

  //// Handle lack of arguments
  if (argc <=2){
		// if (argv[0])
		// 	std::cout << "Usage: " << argv[0] << " <filename>.freq" << '\n';
		// else
			std::cout << "Usage: pool <outname> <filename>.freq" << '\n';
		exit(1);
	}
  // define printing file
  string outfile=argv[1];
  // initialize Hash
  Hash m;
  m.setfile(outfile);

  //// iterate over files
  int countfiles=0;
  for (int i = 2; i < argc; ++i)  {
      // printf("argv[%d]: %s\n", i, argv[i]);

      //// read file function
      std::ifstream inputFile(argv[i]);
      const int Rows=countfilerows(argv[i]) -1; // cause array starts 0
      const int Cols=9;

      for(int i = 0; i < Rows; ++i){
          int a[9];
          for(int j=0; j< Cols; j++){
            inputFile >> a[j];
          }
          char newkey[50];
          char newval[50];
          int n1, n2;
            n1=sprintf (newkey, "%d%d", a[0], a[1]);
            n2=sprintf (newval, "%d:%d:%d:%d", a[3],a[4],a[5],a[6]);
          if (countfiles==0){
            m.newadd(newkey,newval);
          }else{
            m.addontop(newkey,newval);
          }
      }

      countfiles++;
  } // end files

  //// Output intersect hash
  m.printhash();

  //// Output samples
  vector<string> Samples;
  for (int i = 2; i < argc; ++i) samples.push_back(argv[i]);
  string samplesfile=outfile.append('');
    int main () {
      ofstream myfile;
      myfile.open ("example.txt");
      myfile << "Writing this to a file.\n";
      myfile.close();
      return 0;
    }

  // delete [] a;
  return(1);
}


// int** a = new int*[Rows];
//   for(int i = 0; i < Rows; ++i){
//       a[i] = new int[Cols];
//       for(int j=0; j< Cols; j++){
//         inputFile >> a[i][j];
//         // cout << a[i][j] << '\t';
//       }
//       // cout << '\n';
//   }
