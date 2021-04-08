#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <chrono>

bool running = true;

void napaka(const std::string& what = "") {
    std::cout << "***** NAPAKA: " << what;
}

void generirajNakljucnoZaporedje(std::vector<int>& zaporedje, const int input) {
    if (input < 1) return napaka("Dolzina mora biti vecja od 0");
    
    std::random_device rd;
    std::uniform_int_distribution<int> stevila(0, input);
    for (int i = 0; i < input; i++) {
        zaporedje.push_back(stevila(rd));
    }
}

void generirajNarascajoceZaporedje(std::vector<int>& zaporedje, const int input) {
    if (input < 1) return napaka("Dolzina mora biti vecja od 0");
    
    for (int i = 0; i < input; i++) {
        zaporedje.push_back(i);
    }
}

void generirajPadajoceZaporedje(std::vector<int>& zaporedje, const int input) {
    if (input < 1) return napaka("Dolzina mora biti vecja od 0");
    
    for (int i = 0; i < input; i++) {
        zaporedje.push_back(input - i - 1);
    }
}

void izpisZaporedja(const std::vector<int>& zaporedje) {
    if (zaporedje.empty()) return napaka("Zaporedje je prazno");

    for (const auto& z : zaporedje) {
        std::cout << z << ", ";
    }
}


int deli(std::vector<int>& zaporedje, const int dno, const int vrh, const bool zMediano) {
    // Ce je urejeno, zamenjamo sredino polja in pivota
    if (zMediano) {
        int m = dno + (vrh - dno) / 2;
        std::swap(zaporedje[dno], zaporedje[m]);
    }

    int pivot = zaporedje[dno];     // Primerjalno stevilo
    int l = dno;
    int d = vrh;


    // Dokler se nista levi in desni index prekrizala
    while (l < d) {
        
        // Dokler ne najdemo stevilo, vecje od pivota ali pridemo do vrha
        while (zaporedje[l] <= pivot && l < vrh) {
            l++;
        }
        // Dokler ne najdemo stevilo, manjse od pivota ali pridemo do dna
        while (zaporedje[d] >= pivot && d > dno) {
            d--;
        }
        if (l < d) {
            std::swap(zaporedje[l], zaporedje[d]);
        }
    }
    // Zamenjamo, da bo pivot na pravem mestu
    std::swap(zaporedje[dno], zaporedje[d]);
    return d;
}

void hitroUredi(std::vector<int>& zaporedje, const int dno, const int vrh, const bool zMediano) {
    if (dno < vrh) {
        int j = deli(zaporedje, dno, vrh, zMediano);
        hitroUredi(zaporedje, dno, j - 1, zMediano);
        hitroUredi(zaporedje, j + 1, vrh, zMediano);
    }
}


void meriCasHitroUrejanje(std::vector<int>& zaporedje, const int dno, const int vrh, const bool zMediano) {
    auto start = std::chrono::steady_clock::now();
    hitroUredi(zaporedje, dno, vrh, zMediano);
    auto stop = std::chrono::steady_clock::now();

    std::cout << "Čas pri urejanju s QS algoritmom je " <<
        std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()
        << " mikrosekund.";
}


void bubbleSort(std::vector<int>& zaporedje) {
    for (size_t i = 0; i < zaporedje.size(); i++) {
        for (size_t j = 0; j < zaporedje.size() - i - 1; j++) {
            if (zaporedje[j] > zaporedje[j + 1]) {
                std::swap(zaporedje[j], zaporedje[j + 1]);
            }
        }
    }
}

void meriCasBubbleSort(std::vector<int>& zaporedje) {
    auto start = std::chrono::steady_clock::now();
    bubbleSort(zaporedje);
    auto stop = std::chrono::steady_clock::now();

    std::cout << "Čas pri urejanju z Bubble Sort algoritmom je " <<
        std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()
        << " mikrosekund.";
}



void meni(std::vector<int>& zaporedje) {
    int izbira, input;


    std::cout << "Hitro uredi - izbira\n\n";

    std::cout << "1) Generiraj naključno zaporedje\n";
    std::cout << "2) Generiraj naraščajoče zaporedje\n";
    std::cout << "3) Generiraj padajoče zaporedje\n";
    std::cout << "4) Izpis zaporedja\n";
    std::cout << "5) Preveri ali je zaporedje urejeno\n";
    std::cout << "6) Uredi s hitrim urejanjem brez mediane\n";
    std::cout << "7) Uredi s hitrim urejanjem z mediano\n";
    std::cout << "8) Uredi z drugim algoritmom za urejanjem\n";
    std::cout << "9) Konec\n\n";
    std::cout << "Izbira: "; 
    std::cin >> izbira;
    std::cout << "\n";

    switch(izbira) {
        case 1:
            std::cout << "Doloci dolzino zaporedja: ";
            std::cin >> input;
            if (!zaporedje.empty()) {
                zaporedje.clear();
            }
            zaporedje.reserve(input);

            generirajNakljucnoZaporedje(zaporedje, input);
            break;
        case 2:
            std::cout << "Doloci dolzino zaporedja: ";
            std::cin >> input;
            if (!zaporedje.empty()) {
                zaporedje.clear();
            }
            zaporedje.reserve(input);

            generirajNarascajoceZaporedje(zaporedje, input);
            break;
        case 3:
            std::cout << "Doloci dolzino zaporedja: ";
            std::cin >> input;
            if (!zaporedje.empty()) {
                zaporedje.clear();
            }
            zaporedje.reserve(input);

            generirajPadajoceZaporedje(zaporedje, input);
            break;
        case 4:
            izpisZaporedja(zaporedje);
            break;
        case 5:
            if (zaporedje.empty()) {
                napaka("Zaporedje je prazno");
                break;
            }
            std::cout << "Zaporedje " 
                << ((std::is_sorted(zaporedje.begin(), zaporedje.end()) ? "JE" : "NI"))
                << " urejeno";
            break;
        case 6:
            if (zaporedje.empty()) {
                napaka("Zaporedje je prazno");
                break;
            }
            meriCasHitroUrejanje(zaporedje, 0, zaporedje.size() - 1, false);
            break;
        case 7:
            if (zaporedje.empty()) {
                napaka("Zaporedje je prazno");
                break;
            }
            meriCasHitroUrejanje(zaporedje, 0, zaporedje.size() - 1, true);
            break;
        case 8:
            if (zaporedje.empty()) {
                napaka("Zaporedje je prazno");
                break;
            }
            meriCasBubbleSort(zaporedje);
            break;
        case 9:
            running = false;
            break;
        default:
            std::cout << "***** NAPAKA: Napačna izbira";
            break;
    }
    std::cout << "\n\n";
}


int main() {
    std::vector<int> zaporedje;

    while (running) {
        meni(zaporedje);
    }


    return 0;
}
