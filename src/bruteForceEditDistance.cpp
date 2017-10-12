//
// Created by srikanthmaturu on 10/10/2017.
//
#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

size_t uiLevenshteinDistance(const std::string &s1, const std::string &s2)
{
    const size_t m(s1.size());
    const size_t n(s2.size());

    if( m==0 ) return n;
    if( n==0 ) return m;

    size_t *costs = new size_t[n + 1];

    for( size_t k=0; k<=n; k++ ) costs[k] = k;

    size_t i = 0;
    for ( std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i )
    {
        costs[0] = i+1;
        size_t corner = i;

        size_t j = 0;
        for ( std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j )
        {
            size_t upper = costs[j+1];
            if( *it1 == *it2 )
            {
                costs[j+1] = corner;
            }
            else
            {
                size_t t(upper<corner?upper:corner);
                costs[j+1] = (costs[j]<t?costs[j]:t)+1;
            }

            corner = upper;
        }
    }

    size_t result = costs[n];
    delete [] costs;

    return result;
}

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

uint64_t doBruteForce(string databaseFile, string queryFile, uint64_t maxED){
    vector<string> database_kmers;
    vector<string> query_kmers;
    load_sequences(databaseFile, database_kmers);
    load_sequences(queryFile, query_kmers);
    uint64_t count = 0;
    //#pragma omp parallel
    for(uint64_t i = 0; i < query_kmers.size(); i++){
        cout << ">" << query_kmers[i]  << endl;
        for(uint64_t j = 0; j < database_kmers.size(); j++){
            uint64_t editDistance = uiLevenshteinDistance(database_kmers[i], query_kmers[j]);
            if(editDistance <= maxED){
                count++;
                cout << database_kmers[j] << " " << editDistance <<  endl;
            }
        }
        cout << "Query " << i << " Current count: " << count << endl;
    }
    cout << "Total Number of similar kmers for all queries: " << count << endl;
}

int main(int argc, char** argv){
    if(argc < 4){
        cout << "Usage: ./" << argv[0] << " database_file query_file max_edit_distance" << endl;
        return 1;
    }

    doBruteForce(argv[1], argv[2], stoi(argv[3]));
    return 0;
}