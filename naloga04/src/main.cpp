#include <algorithm>
#include <iostream>
#include <memory>


struct Node {
    int key;
    std::shared_ptr<Node> father = nullptr;
    std::shared_ptr<Node> leftSon = nullptr;
    std::shared_ptr<Node> rightSon = nullptr;
};
bool running = true;


void napaka(const std::string& what = "") {
    std::cout << "***** NAPAKA: " << what;
}

std::shared_ptr<Node> iskanjePodatka(const std::shared_ptr<Node>& node, const int key) {
    if (node == nullptr || node->key == key) {
        return node;
    }
    else {
        if (key < node->key) {
            return iskanjePodatka(node->leftSon, key);
        }
        else {
            return iskanjePodatka(node->rightSon, key);
        }
    }
}



void vnosPodatka(std::shared_ptr<Node>& root, const int key) {
    std::shared_ptr<Node> nodeFather = nullptr;
    std::shared_ptr<Node> node = root;

    // Finding place to put in a new node
    while (node != nullptr) {
        nodeFather = node;

        if (key < node->key) {
            node = node->leftSon;
        }
        else if (key > node->key) {
            node = node->rightSon;
        }
        else {
            return napaka();
        }
    }

    // Creating a new node
    std::shared_ptr<Node> newNode = std::make_shared<Node>();
    newNode->key = key; 
    newNode->father = nodeFather;

    if (nodeFather == nullptr) {
        root = newNode;
    } 
    else {
        if (newNode->key < nodeFather->key) {
            nodeFather->leftSon = newNode;
        }
        else {
            nodeFather->rightSon = newNode;
        }
    }
}



void urejenIzpis(const std::shared_ptr<Node>& root) {
    if (root != nullptr) {
        urejenIzpis(root->leftSon);
        std::cout << root->key << " ";
        urejenIzpis(root->rightSon);
    } 
}


void izpisVsehPovezav(const std::shared_ptr<Node>& root) {
    if (root->leftSon != nullptr) {
        std::cout << root->key << " --> " << root->leftSon->key << "\n";
        izpisVsehPovezav(root->leftSon);
    }

    if (root->rightSon != nullptr) {
        std::cout << root->key << " --> " << root->rightSon->key << "\n";
        izpisVsehPovezav(root->rightSon);
    }
}


int minimum(const std::shared_ptr<Node>& root) {
    std::shared_ptr<Node> node = root;

    while (node->leftSon != nullptr) {
        node = node->leftSon;
    }
    return node->key;
}

int maksimum(const std::shared_ptr<Node>& root) {
    std::shared_ptr<Node> node = root;

    while (node->rightSon != nullptr) {
        node = node->rightSon;
    }
    return node->key;
}


int predhodnik(const std::shared_ptr<Node>& root, const int key) {
    std::shared_ptr<Node> node = iskanjePodatka(root, key);

    if (node != nullptr && node->leftSon != nullptr) {
        return maksimum(node->leftSon);
    }
    else if (node == nullptr){
        // napaka("Vnesenega stevila ni v drevesu.");
        return INT32_MIN;
    }

    // Tu gremo gor po drevesu
    std::shared_ptr<Node> tmp = node->father;
    while (tmp != nullptr && node == tmp->leftSon) {
        node = tmp;
        tmp = tmp->father;
    }

    // Preveri, ce predhodnik obstaja
    if (tmp == nullptr) {
        return INT32_MIN;
    }
    else {
        return tmp->key;
    }

}



int naslednik(const std::shared_ptr<Node>& root, const int key) {
    std::shared_ptr<Node> node = iskanjePodatka(root, key);

    if (node != nullptr && node->rightSon != nullptr) {
        return minimum(node->rightSon);
    }
    else if (node == nullptr){
        return INT32_MIN;
    }

    // Tu gremo gor po drevesu
    std::shared_ptr<Node> tmp = node->father;
    while (tmp != nullptr && node == tmp->rightSon) {
        node = tmp;
        tmp = tmp->father;
    }

    // Preveri, ce naslednik obstaja
    if (tmp == nullptr) {
        return INT32_MIN;
    }
    else {
        return tmp->key;
    }
}



void brisanjePodatka(std::shared_ptr<Node>& root, const int key) {
    std::shared_ptr<Node> node = iskanjePodatka(root, key);
    std::shared_ptr<Node> y = nullptr;
    std::shared_ptr<Node> x = nullptr;

    if (node == nullptr) {
        return napaka("Ta kljuc ne obstaja");
    }

    if (node->leftSon == nullptr || node->rightSon == nullptr) {
        y = node;
    }
    else {
        int n = naslednik(root, key);
        y = iskanjePodatka(root, n);
    }

    if (y->leftSon != nullptr) {
        x = y->leftSon;
    }
    else {
        x = y->rightSon;
    }

    if (x != nullptr) {
        x->father = y->father;
    }

    if (y->father == nullptr) {
        root = x;
    }
    else {
        if (y == y->father->leftSon) {
            y->father->leftSon = x;
        }
        else {
            y->father->rightSon = x;
        }
    }

    if (y != node) {
        y->key = node->key;
    }
}


void brisi(std::shared_ptr<Node>& root, const int key) {
    std::shared_ptr<Node> node = iskanjePodatka(root, key);
    std::shared_ptr<Node> y = nullptr;

    if (node == nullptr) return napaka("Podatek ne obstaja.");

    if (node->leftSon == nullptr || node->rightSon == nullptr) {
        brisanjePodatka(root, node->key);
    }
    else {
        int n = naslednik(root, key);
        y = iskanjePodatka(root, n);
        n = y->key;
        brisanjePodatka(root, y->key);
        node->key = n;
    }
    std::cout << "Izbrisano.";
}


void menu(std::shared_ptr<Node>& root) {
    int choice, value, key;

    std::cout << "Binarno Iskalno Drevo - izbira:\n\n";
    std::cout << "1) Vnos podatka\n";
    std::cout << "2) Urejen izpis vrednosti \n";
    std::cout << "3) Izpis povezav\n";
    std::cout << "4) Iskanje\n";
    std::cout << "5) Poisci minimum in maksimum\n";
    std::cout << "6) Poisci predhodnika in naslednika\n";
    std::cout << "7) Brisi vrednost\n";
    std::cout << "8) Konec\n\n";
    std::cout << "Izbira: ";

    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "Vnesi vrednost: ";
            std::cin >> value;
            vnosPodatka(root, value);
            break;
        case 2:
            if (root == nullptr) napaka("Drevo je prazno.");
            else urejenIzpis(root);
            break;
        case 3:
            if (root == nullptr) napaka("Drevo je prazno.");
            else izpisVsehPovezav(root);
            break;
        case 4:
            std::cout << "Vnesi vrednost, ki jo zelis poiskati: ";
            std::cin >> value;
            if (root == nullptr) napaka("Drevo je prazno.");
            else {
                std::cout << "Kljuc " << value << " se " 
                          << ((iskanjePodatka(root, value) == nullptr) ? "ne " : "")
                          << "nahaja v drevesu.";
            }
            break;
        case 5:
            if (root == nullptr) napaka("Drevo je prazno.");
            else {
                std::cout << "Min: " << minimum(root)
                        << "\nMax: " << maksimum(root);
            }
            break;
        case 6:
            std::cout << "Vnesi vrednost: ";
            std::cin >> value;
            if (root == nullptr) napaka("Drevo je prazno.");
            else {
                key = predhodnik(root, value);
                std::cout << "Predhodnik: ";
                if (key != INT32_MIN) std::cout << key;
                else std::cout << "Ga ni";

                key = naslednik(root, value);
                std::cout << "\nNaslednik: ";
                if (key != INT32_MIN) std::cout << key;
                else std::cout << "Ga ni";
            }
            break;
        case 7:
            std::cout << "Vnesi vrednost: ";
            std::cin >> value;
            if (root == nullptr) napaka("Drevo je prazno.");
            else brisi(root, value);
            break;
        case 8:
            running = false;
            break;
        default:
            std::cout << "\n***** NAPAČEN VNOS *****";
            break;
    }

    std::cout << "\n\n";
}


int main() {
    std::shared_ptr<Node> root = nullptr;

    while (running) {
        menu(root);
    }
}
