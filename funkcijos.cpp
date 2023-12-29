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
        if (pora.second.size() > 1) {
            outputas << left << setw(maxilgis + 10) << pora.first << left << setw(maxilgis + 10) << pora.second.size();

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
    ofstream outputas(rezultatas);
    string eil;

    regex linkas(R"((https?:\/\/[^\s]+)|(www\.[^\s]+))");

    if (!inputas.is_open()) {
        cerr << "Nepavyko atidaryti failo" << endl;
        return;
    }

    while (getline(inputas, eil)) {
        smatch url;
        while (regex_search(eil, url, linkas)) {
            outputas << url[0] << endl;
            eil = url.suffix().str();
        }
    }

    inputas.close();
    outputas.close();
}

