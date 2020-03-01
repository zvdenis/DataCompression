
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;


struct Node {
    Node *left;
    Node *right;
    int count;
    string code;


    void buildCodes(string code) {
        this->code = code;
        if (this->left != nullptr || this->right != nullptr) {
            left->buildCodes(code + "1");
            right->buildCodes(code + "0");
        }
    }

};


class ShannonFano {
public:
    vector<int> numbers;
    vector<int> pref;
    vector<string> codes;

    int sumLR(int l, int r) {
        return pref[r] - pref[l] + numbers[l];
    }

    void buildFano(int l, int r, string str)// можно изменить что бы принимал на вход количесво элементов
    {
        if (r - l < 1) {
            codes[l] = str;
            return;
        }

        int mid = l;
        for (int i = l; i < r; i++) {
            if (sumLR(l, i) >= sumLR(i + 1, r)) {
                int sum1 = abs(sumLR(l, i) - sumLR(i + 1, r));
                int sum2 = abs(sumLR(l, i - 1) - sumLR(i, r));
                if(sum1 >= sum2){
                    i--;
                }
                mid = i;
                break;
            }
        }
        buildFano(l, mid, str + "0");
        buildFano(mid + 1, r, str + "1");
    }

    void build() {
        codes.resize(numbers.size());
        buildFano(0, numbers.size() - 1, "");
    }

    void addChance(int chance) {
        // добавляет элемент в список (дерево, все зависит от реализации)
        numbers.push_back(chance);
        if (pref.size() == 0) {
            pref.push_back(chance);
        } else {
            pref.push_back(pref.back() + chance);
        }
    }

    string get(int i) {
        return codes[i];
    }

};


int main() {

    int n;
    ShannonFano *shf = new ShannonFano();

    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.is_open()) {
        fin >> n;
        for (int i = 0; i < n; i++) {
            int x;
            fin >> x;
            shf->addChance(x);
        }

        fin.close();

        shf->build();
        fstream fout;
        fout.open("output.txt", ios::out);
        for (int i = 0; i < n; i++) {
            fout << shf->get(i) << (i == n - 1 ? "" : " ");
        }
        fout.close();
        delete shf;

    }
    return 0;
}