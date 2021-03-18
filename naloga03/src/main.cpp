#include <iostream>


struct Node {
    int key;
    Node* prev, *next;
};

bool running = true;
Node* head = nullptr;
Node* tail = nullptr;

int najdi(const int key) {
    Node* tmp = head;

    while (tmp != nullptr && tmp->key != key) {
        tmp = tmp->next;
    }
    return (tmp == nullptr ? INT32_MIN : tmp->key);
}

void vnosGlava(const int newKey) {
    Node* node = new Node();
    node->key = newKey;
    node->prev = nullptr;

    if (head != nullptr) {
        head->prev = node;
        node->next = head;
    } else {
        node->next = nullptr;
        tail = node;
    }

    head = node;
}
    
void vnosZa(const int key, const int newKey) {
    if (head == nullptr) {
        std::cout << "***** NAPAKA: Seznam je prazen.\n";
        return;
    }

    Node* tmp = head;
    while (tmp != nullptr && tmp->key != key) {
        tmp = tmp->next; 
    }
    // Ce ni elementa, za katerim zelimo vstaviti
    if (tmp == nullptr) {
        std::cout << "***** NAPAKA: Element, za katerega zelis vstaviti nov kljuc ne obstaja.\n";
        return;
    }

    Node* node = new Node();
    node->prev = tmp;
    node->key = newKey;

    if (tmp->next == nullptr) {
        node->next = nullptr;
        tail = node;
    } else {
        node->next = tmp->next;
        node->next->prev = node;
    }
    tmp->next = node;
}

void vnosRep(const int newKey) {
    Node* node = new Node();
    node->key = newKey;
    node->next = nullptr;

    if (tail != nullptr) {
        tail->next = node;
        node->prev = tail;
    } else {
        node->prev = nullptr; 
        head = node;
    }

    tail = node;
}

void brisanje(const int key) {
    Node *tmp = head;

    if (tmp == nullptr) {
        std::cout << "***** NAPAKA: Seznam je prazen.\n";
        return;
    }
    while (tmp != nullptr && tmp->key != key) {
        tmp = tmp->next;
    }

    if (tmp == nullptr) {
        std::cout << "***** NAPAKA: Tega ključa ni v seznamu.\n";
        return;
    }

    // Ce je to edini element v seznamu
    if (tmp->prev == nullptr && tmp->next == nullptr) {
        head = tail = nullptr;

    } else if (tmp->prev == nullptr || tmp->next == nullptr) {

        // Ce je zadnji element v seznamu
        if (tmp->next == nullptr) {
            tmp->prev->next = nullptr;
            tail = tmp->prev;
        }

        // Ce je prvi element v seznamu
        if (tmp->prev == nullptr) {
            tmp->next->prev = nullptr;
            head = tmp->next;
        }

    } else {
        tmp->next->prev = tmp->prev;
        tmp->prev->next = tmp->next;
    }
    delete tmp;

    std::cout << "Izbrisano.\n";
}



void izpisGlavaRep() {
    Node* tmp = head;

    if (tmp == nullptr) {
        std::cout << "***** NAPAKA: Seznam je prazen.\n";
    } else {
        while (tmp != nullptr) {
            std::cout << tmp->key << (tmp->next == nullptr ? ".\n" : ", ");
            tmp = tmp->next;
        }
        std::cout << head->key << " " << tail->key << std::endl;
    }
}

void izpisRepGlava() {
    Node* tmp = tail;

    if (tmp == nullptr) {
        std::cout << "***** NAPAKA: Seznam je prazen.\n";
    } else {
        while (tmp != nullptr) {
            std::cout << tmp->key << (tmp->prev == nullptr ? ".\n" : ", ");
            tmp = tmp->prev;
        }
        std::cout << head->key << " " << tail->key << std::endl;
    }
}

// TODO: test hitrosti

void menu() {
    int choice, number, node;

    std::cout << "Dvojno Povezan Seznam - izbira:\n\n";
    std::cout << "1) Iskanje podatka\n";
    std::cout << "2) Vnos podatka v glavo\n";
    std::cout << "3) Vnos podatka za elementom\n";
    std::cout << "4) Vnos podatka za repom\n";
    std::cout << "5) Brisanje podatka\n";
    std::cout << "6) Izpis seznama od glave proti repu\n";
    std::cout << "7) Izpis seznama od repa proti glavi\n";
    std::cout << "8) Testiraj hitrost\n";
    std::cout << "9) Konec\n\n";
    std::cout << "Izbira: ";

    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "Vnesi iskani kljuc: ";
            std::cin >> number;
            node = najdi(number);
            std::cout << "Je kljuc " << number << " v seznamu: " << (node == INT32_MIN ? "NE" : "DA");
            break;
        case 2:
            std::cout << "Vnesi nov kljuc: ";
            std::cin >> number;
            vnosGlava(number);
            break;
        case 3:
            std::cout << "Vnesi <za_katerim_elt> <kljuc>: ";
            std::cin >> node >> number;
            vnosZa(node, number);
            break;
        case 4:
            std::cout << "Vnesi nov kljuc: ";
            std::cin >> number;
            vnosRep(number);
            break;
        case 5:
            std::cout << "Vnesi kljuc, ki ga zelis izbrisati: ";
            std::cin >> number;
            brisanje(number);
            break;
        case 6:
            izpisGlavaRep();
            break;
        case 7:
            izpisRepGlava();
            break;
        case 8:
            break;
        case 9:
            running = false;
            break;
        default:
            std::cout << "\n***** NAPAČEN VNOS *****";
            break;
    }

    std::cout << "\n\n";
}


int main() {
    while (running) {
        menu();
    }
}
