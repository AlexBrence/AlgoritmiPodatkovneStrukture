#include <iostream>


struct Stack {
    int *S_arr;
    int vrh = -1;
};

struct RoundedQueue {
    int *Q_arr;
    int glava = -1;
    int rep = 0;
};
bool running = true;
unsigned int MAX;


void push(Stack& stack, const int x) {
    if (stack.vrh == MAX - 1) {
        std::cout << "\n***** NAPAKA: Sklad je poln. *****";
    } else {
        stack.S_arr[++stack.vrh] = x;
    }
}

void pop(Stack& stack) {
    if (stack.vrh == -1) {
        std::cout << "\n***** NAPAKA: Sklad je prazen. *****";
    } else {
        std::cout << stack.S_arr[stack.vrh--];
    }
}

void print(const Stack& stack) {
    if (stack.vrh == -1) {
        std::cout << "\n***** NAPAKA: Sklad je prazen. *****";
    } else {
        for (int i = 0; i <= stack.vrh; i++) {
            std::cout << stack.S_arr[i] << ", ";
        }
    }
}

void vpisi(RoundedQueue& queue, const int x) {
    if (queue.glava % MAX == (queue.rep + 1) % MAX) {
        std::cout << "\n***** NAPAKA: Vrsta je polna. *****";
    }
    else {
        queue.Q_arr[queue.rep++] = x;
        queue.rep %= MAX;
    }
    if (queue.glava == -1) queue.glava++;
}

void beriVrsta(RoundedQueue& queue) {
    int num;

    if (queue.glava == queue.rep) {
        std::cout << "\n***** NAPAKA: Vrsta je prazna. *****";
    } else {
        std::cout << queue.Q_arr[queue.glava];
        queue.glava++;
        queue.glava %= MAX;
    }
}

void izpisVrste(const RoundedQueue& queue) {
    if (queue.glava == queue.rep) {
        std::cout << "\n***** NAPAKA: Vrsta je prazna. *****";
    } else {
        int i = queue.glava;
        do {
            std::cout << queue.Q_arr[i++] << ", ";
            i %= MAX;
        }
        while (i % MAX != queue.rep);
    }
}



void menu(Stack& stack, RoundedQueue& queue) {
    int choice, number;
    
    std::cout << "Sklad - izbira:\n";
    std::cout << "1. Vnos podatka\n";
    std::cout << "2. Branje podatka in izpis\n";
    std::cout << "3. Izbis vsebine sklada\n\n";
    std::cout << "Krožna vrsta - izbira:\n";
    std::cout << "4. Vnos podatka\n";
    std::cout << "5. Branje podatka in izpis\n";
    std::cout << "6. Izpis vrste od glave do repa\n\n";
    std::cout << "7. Konec\n\n";
    std::cout << "Izbira: ";

    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "Vnesi število: ";
            std::cin >> number;
            push(stack, number);
            break;
        case 2:
            pop(stack);
            break;
        case 3:
            print(stack);
            break;
        case 4:
            std::cout << "Vnesi število: ";
            std::cin >> number;
            vpisi(queue, number);
            break;
        case 5:
            beriVrsta(queue);
            break;
        case 6:
            izpisVrste(queue);
            break;
        case 7:
            running = false;
            break;
        default:
            std::cout << "\n***** NAPAČEN VNOS *****";
    }

    std::cout << "\n\n";
}


int main() {
    Stack stack;
    RoundedQueue queue;

    std::cout << "Vnesi max velikost: ";
    std::cin >> MAX;

    stack.S_arr = new int[MAX];
    queue.Q_arr = new int[MAX];

    while (running) {
        menu(stack, queue);
    }


    delete[] stack.S_arr;
    delete[] queue.Q_arr;
    return 0;
}
