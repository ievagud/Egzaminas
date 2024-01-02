#include "funkcijos.h"

bool Skyrybos_zenk(char x) {
    const string zenkl = "  “”„\"  ";
    return ispunct(x) || zenkl.find(x) != string::npos;
}


void Zodziu_sk(string tekstas, string rezultatas) {
    ifstream failas(tekstas);
    if (!failas.is_open()) {
        cerr << "Nepavyko atidaryti failo" << endl;
        return;
    }

    map<string, int> zodziu_sk;
    map<string, set<int>> zdz_eil;
    string eil, zdz;
    int eil_nr = 0;
    size_t maxilgis = 0;

    while (getline(failas, eil)) {
        eil_nr++;
        istringstream eilstr(eil);
        while (eilstr >> zdz) {
            zdz.erase(remove_if(zdz.begin(), zdz.end(), Skyrybos_zenk), zdz.end());
            if (!zdz.empty()) {
                zodziu_sk[zdz]++;
                zdz_eil[zdz].insert(eil_nr);
                maxilgis = max(maxilgis, zdz.size());
            }
        }
    }

    failas.close();

    ofstream outputas(rezultatas);
    outputas << left << setw(maxilgis + 10) << "Zodis"
               << left << setw(maxilgis + 10) << "Pasikartojimai"
               << left << setw(maxilgis + 10) << "Eilutes" << endl;
    outputas << string(maxilgis + 50, '-') << endl;

    for (const auto& pora : zdz_eil) {
        if (zodziu_sk[pora.first] > 1) {
            outputas << left << setw(maxilgis + 10) << pora.first
                     << left << setw(maxilgis + 10) << zodziu_sk[pora.first];

            auto it = pora.second.begin();
            outputas << *it;
            ++it;
            for (; it != pora.second.end(); ++it) {
                outputas << "," << *it;
            }
            outputas << endl;
        }
    }

    outputas.close();
}

void linkai(const string& tekstas, const string& rezultatas) {
    ifstream inputas(tekstas);
    if (!inputas.is_open()) {
        cerr << "Nepavyko atidaryti failo" << endl;
        return;
    }

    ofstream outputas(rezultatas);
    string eil;

    while (getline(inputas, eil)) {
        size_t ind = 0;
        while (ind < eil.length()) {
            size_t httpInd = eil.find("http://", ind);
            size_t httpsInd = eil.find("https://", ind);
            size_t wwwInd = eil.find("www.", ind);

            size_t ind1 = min({httpInd, httpsInd, wwwInd});

            if (ind1 != string::npos) {
                size_t pask_ind = eil.find(' ', ind1);
                if (pask_ind == string::npos) {
                    pask_ind = eil.length();
                }
                string url = eil.substr(ind1, pask_ind - ind1);
                outputas << url << endl;
                ind = pask_ind;
            } else {
                break;
            }
        }
    }

    inputas.close();
    outputas.close();
}
