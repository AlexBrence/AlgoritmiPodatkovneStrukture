#include <cstdint>
#include <iostream>
#include <memory>


struct Node {
    int key;
    std::shared_ptr<Node> father = nullptr;
    std::shared_ptr<Node> leftSon = nullptr;
    std::shared_ptr<Node> rightSon = nullptr;
};
bool running = true;
//std::shared_ptr<Node> root = nullptr;



void napaka(const std::string& what = "") {
    std::cout << "***** NAPAKA: " << what;
}

void iskanjePodatka(const std::shared_ptr<Node>& node, const int key) {
    if (node->key == key) {
        std::cout << "Kljuc " << key << " se nahaja v drevesu.";
        return;

    } else {
        if (key < node->key) {
            iskanjePodatka(node->leftSon, key);
        } else {
            iskanjePodatka(node->rightSon, key);
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
        } else if (key > node->key) {
            node = node->rightSon;
        } else {
            napaka();
            return;
        }
    }

    // Creating a new node
    std::shared_ptr<Node> newNode = std::make_shared<Node>();
    newNode->key = key; 
    newNode->father = nodeFather;

    if (nodeFather == nullptr) {
        root = newNode;
    } else {
        if (newNode->key < nodeFather->key) {
            nodeFather->leftSon = newNode;
        } else {
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


void menu(std::shared_ptr<Node>& root) {
    int choice, value;

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
            else iskanjePodatka(root, value);
            break;
        case 5:
            if (root == nullptr) napaka("Drevo je prazno.");
            else {
                std::cout << "Min: " << minimum(root)
                        << "\nMax: " << maksimum(root);
            }
            break;
        case 6:
            break;
        case 7:
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
