//
// Created by srikanth on 7/8/17.
//
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <map>
using namespace std;

map<char, int> a_map = {{'A', 0},
                             {'C', 1},
                             {'G', 2},
                             {'T', 3},
                             {'N', 4}};

void load_sequences(string sequences_file, vector<string>& sequences){
    ifstream input_file(sequences_file, ifstream::in);

    for(string sequence; getline(input_file, sequence);){
        uint64_t pos;
        if((pos=sequence.find('\n')) != string::npos){
            sequence.erase(pos);
        }
        if((pos=sequence.find('\r')) != string::npos){
            sequence.erase(pos);
        }
        sequences.push_back(sequence);
    }
}

void makeQueriesFile(string sequences_file, uint64_t number_of_queries){

    vector<string> sequences;
    ofstream queries_file(sequences_file + "_"+to_string(number_of_queries)+"_queries_");
    load_sequences(sequences_file, sequences);
    uint64_t data_size = sequences.size();
    uint64_t steps = 50, step_size = number_of_queries / steps;
    uint64_t remainder = number_of_queries % steps;
    if(remainder > 0){
        steps += 1;
    }

    for(uint64_t i = 0; i < steps; i++){
        uint64_t step_end = (steps == i + 1) ? (i - 1) * step_size + remainder :  i * step_size;

        for(uint64_t j = i; j < step_end; i++){
            string query = sequences[rand()%data_size];
            uint64_t query_size = query.size();
            for(uint64_t k = 0; k < i + 1; k++){
                uint64_t pos = rand()%query_size;
                uint64_t replace_character = rand()%4;
                query[pos] = a_map[replace_character];
            }
        }

    }

}

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

int extractKMERSFromKCFileCommand(int argc, char** argv){
    if(argc < 3){
        cout << "Usage: ./" << argv[0] << " InputKCFile outputKmersFile minimum_kmer_count" << endl;
        return 1;
    }

    extractKMERSFromKCFile(argv[1], argv[2], stoi(argv[3]));
    return 0;
}

int makeQueriesFileCommand(int argc, char** argv){
    if(argc < 3){
        cout << "Usage: ./" << argv[0] << " sequences_file number_of_queries" << endl;
        return 1;
    }

    makeQueriesFile(argv[1], stoi(argv[2]));
    return 0;
}

int main(int argc, char** argv) {
    makeQueriesFileCommand(argc, argv);
}

