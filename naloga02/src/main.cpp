#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>


void izpisStackov(std::vector<std::stack<int>> stackVector, int steviloPloscic) {
    std::cout << std::setw(steviloPloscic + 10) << "[Stolp 1]";
    std::cout << std::setw(steviloPloscic + 10) << "[Stolp 2]";
    std::cout << std::setw(steviloPloscic + 10) << "[Stolp 3]\n\n";


    // Ce je skupno 7 ploscic bo potrebnih 7 vrstic (+ 1 za podlago)
    for (int i = steviloPloscic; i >= 0; i--) {
        for (auto& s : stackVector) {
            std::cout << std::setw(steviloPloscic + 10);

            if (i == 0) {                                           // Ce je i == 0 izrisi podlago
                std::cout << std::string(steviloPloscic + 4, '-');
            }
            else if (!s.empty() && s.size() == (size_t) i) {      // Ce stack vsebuje elt jih izrisi z *
                std::cout << std::string(s.top(), '*');
                s.pop();
            }
            else {                                                  // Sicer izrisi presledke
                std::cout << std::string(steviloPloscic + 3, ' ');
            }
        }
        std::cout << "\n";
    }
}

void premakniFromTo(const int from, const int to, std::vector<std::stack<int>>& stackVector) {

    if (stackVector[from - 1].size() == 0) {
        std::cout << "\n\033[1;31m***** NAPAKA: Na stolpu " << from << " ni nobene ploscice. *****\033[0m\n";
    }
    else if (!(stackVector[to - 1].empty()) && stackVector[from - 1].top() > stackVector[to - 1].top()) {
        std::cout << "\n\033[1;31m***** NAPAKA: Ne mores premakniti vecje ploscice na manjso. *****\033[0m\n";
    }
    else {
        stackVector[to - 1].push(stackVector[from - 1].top());
        stackVector[from - 1].pop();
    }
}

void vnosUporabnika(std::vector<std::stack<int>>& stackVector) {
    int from, to;

    do {
        std::cin.clear();
        std::cout << "\nPremakni ploscico iz stolpa na stolp. Loci stevili s presledkom: ";
        std::cin >> from >> to;
    } while ((from < 1 || from > 3) || (to < 1 || to > 3) || from == to);

    premakniFromTo(from, to, stackVector);
}

int vnosStevilaPloscic() {
    int steviloPloscic;

    do {
        std::cout << "Vnesi stevilo ploscic (min 2): ";
        std::cin >> steviloPloscic;
    } while (steviloPloscic < 2);

    return steviloPloscic;
}

int main() {
    // Nastavim stacke za igro
    int steviloPloscic = vnosStevilaPloscic();
    std::vector<std::stack<int>> stackVector;

    stackVector.emplace_back(std::stack<int>());
    stackVector.emplace_back(std::stack<int>());
    stackVector.emplace_back(std::stack<int>());

    for (int i = steviloPloscic; i > 0; i--) {
        stackVector[0].push(i);
    }

    // Zacetek igre
    izpisStackov(stackVector, steviloPloscic);
    while (stackVector[2].size() != (size_t) steviloPloscic) {
        vnosUporabnika(stackVector);
        izpisStackov(stackVector, steviloPloscic);
    }
    std::cout << "\n\033[1;32m===== Bravo! Uspesno si zakljucil igro. =====\033[0m\n";


    return 0;
}
