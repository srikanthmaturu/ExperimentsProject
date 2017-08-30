//
// Created by srikanth on 7/8/17.
//
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void extractKMERSFromKCFile(string inputKmersWithCountsFile, string outputKmersFile, uint64_t minCount){
    ifstream ifs(inputKmersWithCountsFile, ifstream::in);
    ofstream ofs(outputKmersFile, ofstream::out);
    for(string line; getline(ifs, line);){
        uint64_t pos = line.find(' ', 0), count = stoi(line.substr(pos + 1, string::npos));
        if(count >= minCount){
            ofs << line.substr(0, pos) << "\n";
        }
    }
    ifs.close();
    ofs.close();
}

int main(int argc, char** argv){
    if(argc < 3){
        cout << "Usage: ./" << argv[0] << " InputKCFile outputKmersFile minimum_kmer_count" << endl;
        return 1;
    }

    extractKMERSFromKCFile(argv[1], argv[2], stoi(argv[3]));
    return 0;
}


