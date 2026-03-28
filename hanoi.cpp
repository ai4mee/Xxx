#include <iostream>
#include <vector>
#include <string>
#include <string_view>

struct Pegs {
    std::vector<int> A, B, C;
};

std::vector<int>& getPeg(Pegs& pegs, char name) {
    if (name == 'A') return pegs.A;
    if (name == 'B') return pegs.B;
    return pegs.C;
}

void draw(const Pegs& pegs, int n, int step, std::string_view move) {
    int diskWidth = 2 * n - 1;
    int pegSpacing = 4;
    int totalWidth = (diskWidth + pegSpacing) * 3;

    std::cout << "\nSchritt " << step << ": " << move << "\n\n";

    const std::vector<int>* stacks[3] = {&pegs.A, &pegs.B, &pegs.C};
    char names[3] = {'A', 'B', 'C'};

    for (int row = n; row >= 1; --row) {
        for (int i = 0; i < 3; ++i) {
            int stackSize = static_cast<int>(stacks[i]->size());

            if (stackSize >= row) {
                int diskSize = (*stacks[i])[row - 1];
                int currentDiskWidth = 2 * diskSize - 1;
                int padding = (diskWidth - currentDiskWidth) / 2;

                std::cout << std::string(padding, ' ')
                          << std::string(currentDiskWidth, '=')
                          << std::string(padding, ' ');
            } else {
                int padding = diskWidth / 2;
                std::cout << std::string(padding, ' ') << "|" << std::string(padding, ' ');
            }
            std::cout << std::string(pegSpacing, ' ');
        }
        std::cout << "\n";
    }

    for (int i = 0; i < 3; ++i) {
        int padding = diskWidth / 2;
        std::cout << std::string(padding, ' ') << names[i] << std::string(padding, ' ')
                  << std::string(pegSpacing, ' ');
    }
    std::cout << "\n" << std::string(totalWidth, '-') << "\n";
}

void moveDisk(char from, char to, Pegs& pegs, int total, int& step) {
    step++;
    int disk = getPeg(pegs, from).back();
    getPeg(pegs, from).pop_back();
    getPeg(pegs, to).push_back(disk);

    std::string moveMsg = "Scheibe " + std::to_string(disk) + ": " + from + " -> " + to;
    draw(pegs, total, step, moveMsg);
}

void hanoi(int n, char source, char target, char auxiliary, Pegs& pegs, int total, int& step) {
    if (n == 0) return;

    hanoi(n - 1, source, auxiliary, target, pegs, total, step);
    moveDisk(source, target, pegs, total, step);
    hanoi(n - 1, auxiliary, target, source, pegs, total, step);
}

void solve(int n) {
    Pegs pegs;
    for (int i = n; i >= 1; --i) pegs.A.push_back(i);

    int step = 0;
    std::cout << "Tuerme von Hanoi mit " << n << " Scheibe(n)\n";
    draw(pegs, n, 0, "Ausgangszustand");

    hanoi(n, 'A', 'C', 'B', pegs, n, step);

    long long optimal = (1LL << n) - 1;
    std::cout << "\nFertig! Benoetigt: " << step
              << " Zuege (Minimum: " << optimal << ")\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Verwendung: " << argv[0] << " <Anzahl_Scheiben>\n";
        return 1;
    }

    try {
        int n = std::stoi(argv[1]);
        if (n < 1) throw std::invalid_argument("Zu klein");
        if (n > 10) {
            std::cout << "Warnung: Bei n > 10 wird die Ausgabe sehr lang.\n";
        }
        solve(n);
    } catch (...) {
        std::cerr << "Fehler: Bitte eine positive ganze Zahl angeben.\n";
        return 1;
    }

    return 0;
}
