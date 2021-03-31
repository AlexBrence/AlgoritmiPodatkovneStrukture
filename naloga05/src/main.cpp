#include <iostream>
#include <map>
#include <list>
#include <fstream>
#include <algorithm>
#include <chrono>


std::map<int, std::list<std::string>> T;
bool running = true;



void vnosFilma(const int datum, const std::string& ime) {
    std::list<std::string> seznam;

    if (T.find(datum) == T.end()) {
        seznam.push_back(ime);
        T.insert(std::make_pair(datum, seznam));
    }
    else {
        T[datum].push_back(ime);
    }
}



void urejenIzpis() {
    for (const auto& line : T) {
        std::cout << line.first << " ";
        for (const auto& ime : line.second) {
            std::cout << ime << ", ";
        }
        std::cout << std::endl;
    }
}


void iskanjePoDatumu(const int datum) {
    auto searchStart = std::chrono::steady_clock::now();
    T.find(datum);
    auto searchStop = std::chrono::steady_clock::now();

    if (T.find(datum) != T.end()) {
        for (const auto& ime : T[datum]) {
            std::cout << ime << ", ";
        }
        std::cout << "\nĆas iskanja: " <<
            std::chrono::duration_cast<std::chrono::microseconds>(searchStop-searchStart).count()
        << " mikrosekund.";
    }
    else {
        std::cout << "=== TA DATUM NE OBSTAJA! ===";
    }
}


int minimum() {
    min_element(T.begin(), T.end(), [](const auto &l, const auto &r) {return l.first < r.first;});
}

int maximum() {
    max_element(T.begin(), T.end(), [](const auto &l, const auto &r) {return l.first < r.first;});
}


// TODO Naslednik, predhodnik


void brisiDatum(const int datum) {
    if (T.find(datum) == T.end()) {
        std::cout << "TA DATUM NE OBSTAJA!";
    }
    else {
        T.erase(T.find(datum));
    }
}


void nalaganjeFilmov(const std::string& pot) {
    std::ifstream in(pot);

    int N;
    std::string ime;
    int datum;


    auto Start = std::chrono::steady_clock::now();
    in >> N;
    for (int i = 0; i < N; i++) {
        in >> datum;
        getline(in, ime, '\r');
        vnosFilma(datum, ime);
        if (i % 1000 == 0) {
            std::cout << '*' << std::flush;
            std::cout << std::endl;
        }
    }
    auto Stop = std::chrono::steady_clock::now();

    std::cout << "Čas pri nalaganju filmov je " <<
        std::chrono::duration_cast<std::chrono::microseconds>(Stop - Start).count()
    << " mikrosekund." << std::endl;

    in.close();
}


void izpisSeznama() {
    int izbira, date;
    std::string name, pot;


    std::cout << "Filmi - izbira:\n\n";

    std::cout << "1) Vnos filma\n";
    std::cout << "2) Urejen izpis filmov\n";
    std::cout << "3) Iskanje po datumu izdaje\n"; 
    std::cout << "4) Poisci minumum in maksimum\n"; 
    std::cout << "5) Poisci predhodnika in naslednika\n"; 
    std::cout << "6) Brisi datum\n"; 
    std::cout << "7) Nalaganje filmov iz datoteke\n"; 
    std::cout << "8) Konec\n\n"; 
    std::cout << "Izbira: "; 
    std::cin >> izbira;
    std::cout << "\n";

    switch(izbira) {
        case 1:
            std::cout << "Vnesi datum(YYYYMMDD): "; 
            std::cin >> date;
            std::cout << "\nVnesi ime filma: "; 
            std::cin.ignore();
            getline(std::cin, name);
            vnosFilma(date, name);
            break;
        case 2:
            urejenIzpis();
            break;
        case 3:
            std::cout << "Vnesi datum, ki ga zelis poiskati"; 
            std::cin >> date;
            iskanjePoDatumu(date);
            break;
        case 4:
            std::cout << "Minumum je: " << minimum();
            std::cout << "\nMaximum je: " << maximum();
            break;
        case 5:
            // TODO predhodnik, naslednik
            break;
        case 6:
            std::cout << "Vnesi datum, ki ga zelis izbrisati: "; 
            std::cin >> date;
            brisiDatum(date);
            break;
        case 7:
            std::cout << "Vnesi celotno pot do mape s filmi: "; 
            std::cin >> pot;
            pot = "IMDB_date_name_mini.list";
            nalaganjeFilmov(pot);
            break;
        case 8:
            running = false;
            break;
        default:
            izpisSeznama();
            break;
    }
    std::cout << "\n\n";
}


int main() {

    T.clear();

    while (running) {
        izpisSeznama();
    }


    return 0;
}

