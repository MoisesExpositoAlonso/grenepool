
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

    // member function declarations
    void addontop(string key,string val);
    void newadd(string key,string val);
    void printhash();
    void writehash(string outfile);
};
// member functions definitions
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
        string pos = index.erase(0,1);

        if(genotype.find('-') != std::string::npos){ // only if there are more than 1 genotype
          std::replace( genotype.begin(), genotype.end(), '-', '\t'); //
          std::cout<<chr<<"\t"<<pos<<"\t"<<genotype<<std::endl;
        } // only if there are more than 1 genotype
        it++;
      }
  }
  void Hash::writehash(string outfile){
      printf("writing hash to file\n");
        ofstream myfile;
        myfile.open (outfile);

        map<string, string>::iterator it = mm.begin();
        while(it != mm.end()){
          string genotype = it->second;
          string index = it->first;
          char chr = index.at(0);
          string pos = index.erase(0,1);

          if(genotype.find('-') != std::string::npos){
            std::replace( genotype.begin(), genotype.end(), '-', '\t'); //
            myfile<<chr<<"\t"<<pos<<"\t"<<genotype<<"\n";
          } // only if there are more than 1 genotype
          it++;
        }

        myfile.close();
    }


////////////////////////////////////////////////////////////////////////////////
// formating functions
char base(int p){
  char b;
  switch (p){
    case 0: b='A';
      break;
    case 1: b='C';
      break;
    case 2: b='G';
      break;
    case 3: b='T';
      break;
  }
  return(b);
}

string formatkey( int a[]){
  char newkey[50];
  int n;
  n=sprintf (newkey, "%d%d", a[0], a[1]);
  return(newkey);
}
string formatval_vcf(int a[]){
  char newval[50];
  int n;
  n=sprintf (newval, "%d:%d:%d:%d", a[3],a[4],a[5],a[6]);
  return(newval);
}

string formatval_maf(int a[]){
  char newval[50];
  int mymax = a[3];
  int loc=3;
  for (int i = 3; i < 7; i++){
    if (a[i] > mymax){
      mymax = a[i];
      loc=i;
  }}
  char b = base(loc-3);
  // frequency
  int cov=a[2];
  int n;
  float f = (float)mymax / (float)cov;
  n=sprintf (newval, "%c%f",b,f);
  return(newval);
}


////////////////////////////////////////////////////////////////////////////////
// from https://stackoverflow.com/questions/15588800/reading-matrix-from-a-text-file-to-2d-integer-array-c
// Open file and read int matrix
// remember order Seq	Pos	Cov	#A	#C	#G	#T	#N	#D


int main(int argc, char *argv[]){

  //// Handle lack of arguments
  if (argc <=2 || argc<4 ){
		// if (argv[0])
		// 	std::cout << "Usage: " << argv[0] << " <filename>.freq" << '\n';
		// else
			std::cout << "Usage: pool <outname> <filename1>.freq <filename2>.freq ..." << '\n';
		exit(1);
	}

  // initialize Hash
  Hash m;
  int counter=0;
  //// iterate over files
  for (int e = 2; e < argc; ++e)  {
      // printf("reading file argument %d: %s\n", e, argv[e]);

      //// read file function
      std::ifstream inputFile(argv[e]);
      const int Rows=countfilerows(argv[e]) -1; // cause array starts 0
      const int Cols=9;
      // printf("file contains %d rows \n", Rows);


      for(int i = 0; i < Rows; ++i){
        // printf("reading row %d\n", i);
          int a[9];
          for(int j=0; j< Cols; j++){
            inputFile >> a[j];
          }
          string newkey = formatkey(a);
          string newval= formatval_maf(a);
          // string newval= formatval_vcf(a);
          if (counter==0){
            m.newadd(newkey,newval);
          }else{
            m.addontop(newkey,newval);
          }
      } // end rows
      counter++;

  } // end files

  //// Output intersect hash
  string outfile=argv[1];
  string extension1=".fvcf";
  outfile.append(extension1);
  m.writehash(outfile);

  //// laternatively print
  // m.printhash();

  //// Output samples
  string samplefile=argv[1];
  string extension2=".samples";
  samplefile.append(extension2);
  ofstream myfile;
  myfile.open(samplefile);
  for (int i = 2; i < argc; ++i) myfile <<argv[i] << "\n";
  myfile.close();

  return(1);
}
