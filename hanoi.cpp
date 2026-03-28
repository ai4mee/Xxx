#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

struct Pegs {
    std::vector<int> A, B, C;
};

std::vector<int>& getPeg(Pegs& pegs, const std::string& name) {
    if (name == "A") return pegs.A;
    if (name == "B") return pegs.B;
    return pegs.C;
}

void draw(const Pegs& pegs, int n, int step, const std::string& move) {
    int width = 2 * n + 1;

    std::cout << "\nSchritt " << step << ": " << move << "\n\n";

    const std::vector<int>* stacks[3] = {&pegs.A, &pegs.B, &pegs.C};
    const std::string names[3] = {"A", "B", "C"};

    for (int row = n; row >= 1; --row) {
        for (int i = 0; i < 3; ++i) {
            std::string cell;
            int stackSize = (int)stacks[i]->size();
            if (stackSize >= row) {
                int disk = (*stacks[i])[row - 1];
                std::string diskStr(disk, '=');
                // center diskStr in width
                int padding = width - (int)diskStr.size();
                int left = padding / 2;
                int right = padding - left;
                cell = std::string(left, ' ') + diskStr + std::string(right, ' ');
            } else {
                int left = width / 2;
                int right = width - left - 1;
                cell = std::string(left, ' ') + "|" + std::string(right, ' ');
            }
            std::cout << cell;
            if (i < 2) std::cout << "  ";
        }
        std::cout << "\n";
    }

    // peg labels
    for (int i = 0; i < 3; ++i) {
        int left = width / 2;
        int right = width - left - 1;
        std::string label = std::string(left, ' ') + names[i] + std::string(right, ' ');
        std::cout << label;
        if (i < 2) std::cout << "  ";
    }
    std::cout << "\n";
    std::cout << std::string(3 * width + 4, '-') << "\n";
}

void hanoi(int n, const std::string& source, const std::string& target,
           const std::string& auxiliary, Pegs& pegs, int total, int& step) {
    if (n == 1) {
        ++step;
        int disk = getPeg(pegs, source).back();
        getPeg(pegs, source).pop_back();
        getPeg(pegs, target).push_back(disk);
        draw(pegs, total, step,
             "Scheibe " + std::to_string(disk) + ": " + source + " -> " + target);
        return;
    }
    hanoi(n - 1, source, auxiliary, target, pegs, total, step);
    ++step;
    int disk = getPeg(pegs, source).back();
    getPeg(pegs, source).pop_back();
    getPeg(pegs, target).push_back(disk);
    draw(pegs, total, step,
         "Scheibe " + std::to_string(disk) + ": " + source + " -> " + target);
    hanoi(n - 1, auxiliary, target, source, pegs, total, step);
}

void solve(int n) {
    Pegs pegs;
    for (int i = n; i >= 1; --i) pegs.A.push_back(i);

    int step = 0;
    std::cout << "Tuerme von Hanoi mit " << n << " Scheibe(n)\n";
    draw(pegs, n, 0, "Ausgangszustand");
    hanoi(n, "A", "C", "B", pegs, n, step);

    int optimal = (1 << n) - 1;
    std::cout << "\nFertig! Benoetigt: " << step
              << " Zuege (Minimum: " << optimal << ")\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Verwendung: " << argv[0] << " <Anzahl_Scheiben>\n";
        return 1;
    }

    int n;
    try {
        n = std::stoi(argv[1]);
    } catch (...) {
        std::cerr << "Fehler: Anzahl der Scheiben muss eine ganze Zahl sein.\n";
        return 1;
    }

    if (n < 1) {
        std::cerr << "Fehler: Mindestens 1 Scheibe erforderlich.\n";
        return 1;
    }

    solve(n);
    return 0;
}
