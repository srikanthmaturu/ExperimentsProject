//
// Created by srikanth on 8/30/17.
//

#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

map<char, int> a_map = {{'A', 0},
                        {'C', 1},
                        {'G', 2},
                        {'T', 3},
                        {'N', 4}};

map<char, int> ar_map = {{0, 'A'},
                        {1, 'C'},
                        {2, 'G'},
                        {3, 'T'},
                        {4, 'N'}};

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
    ofstream queries_file(sequences_file + "_"+to_string(number_of_queries)+"_queries");
    load_sequences(sequences_file, sequences);
    uint64_t data_size = sequences.size();
    uint64_t steps = sequences[0].size(), step_size = number_of_queries / steps;
    uint64_t remainder = number_of_queries % steps;
    if(remainder > 0){
        steps += 1;
    }

    for(uint64_t i = 0; i < steps; i++){
        uint64_t step_end = (steps == i + 1) ? (i - 1) * step_size + remainder :  (i + 1) * step_size;

        for(uint64_t j = i * step_size; j < step_end; j++){
            string query = sequences[rand()%data_size];
            //cout << "O: " << query << " -> ";
            uint64_t query_size = query.size();
            for(uint64_t k = 0; k < i + 1; k++){
                uint64_t pos = rand()%query_size;
                uint64_t replace_character = rand()%4;
                query[pos] = ar_map[replace_character];
            }
            //cout << "M: " << query << " " << i+1 << endl;
            queries_file << query << endl;
        }
    }
}

int main(int argc, char** argv){
    if(argc < 3){
        cout << "Usage: ./" << argv[0] << " sequences_file number_of_queries" << endl;
        return 1;
    }

    makeQueriesFile(argv[1], stoi(argv[2]));
    return 0;
}