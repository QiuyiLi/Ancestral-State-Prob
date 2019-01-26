#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<string> seqs;            // data seqences
    string line;                    // read line
    ifstream myfile("data/fakeExampleByQiuyi.states.log");    // file

    // read file
    if (myfile.is_open())
    {
        // skip lines
        while (getline(myfile, line))
        {
            char *cstr = new char[line.length() + 1];
            strcpy(cstr, line.c_str());
            char *token = strtok(cstr, "\t");
            if (!strcmp(token, "state"))
            {
                break;
            }
            else
                continue;
        }

        // read sequences
        while (getline(myfile, line))
        {
            char *cstr = new char[line.length() + 1];
            strcpy(cstr, line.c_str());
            char *token = strtok(cstr, "\t");
            token = strtok(NULL, "\t");
            string seq(token);
            seqs.push_back(seq.substr(1, seq.length() - 3));
        }
        myfile.close();
    }
    else
        cout << "Unable to open file";
    
    // remove first 10%
    // cout << seqs.size() << endl;
    // seqs.erase(seqs.begin(), seqs.begin() + seqs.size()/10);
    // cout << seqs.size() << endl;

    string alphabet("ACTG");             // data type
    unordered_map<char, int> umap;  // dictionary

    // initialise dictionary
    for (int i = 0; i < alphabet.length(); i++)
    {
        umap.insert(make_pair(alphabet[i], i));
    }

    vector<vector<int>> prob_matrix(alphabet.length(), vector<int>(seqs[0].length(), 0));   // probability matrix

    // count frequency
    for (auto seq : seqs)
    {
        for (int i = 0; i < seq.length(); i++)
        {
            prob_matrix[umap[seq[i]]][i] += 1;
        }
    }

    cout << fixed;
    cout << setprecision(4);
    
    // print probability matrix
    for (int i = 0; i < prob_matrix.size(); i++)
    {
        cout << alphabet[i] << ": ";
        for (int j = 0; j < prob_matrix[i].size(); j++)
        {
            cout << 1.0 * prob_matrix[i][j] / seqs.size() << "  ";
        }
        cout << endl;
    }

    double prob = 1.0;
    for (int j = 0; j < prob_matrix[0].size(); j++)
    {
        double max = 0.0 - 1.0;
        for (int i = 0; i < prob_matrix.size(); i++)
        {
            double tmp = 1.0 * prob_matrix[i][j] / seqs.size();
            if (tmp >= max) {
                max = tmp;
            }
        }
        prob *= max;
    }

    cout << prob << endl;

    return 0;
}
