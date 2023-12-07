#include <iostream>
#include <vector>

using namespace std;
const float EPSILON = 1e-6;

void gaussianElimination(vector<vector<float>>& A, vector<float>& b) {
    int n = A.size();

    for (int i = 0; i < n; i++) {
        // Najdu ten pit radek
        int pivotrow = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[pivotrow][i])) {
                pivotrow = j;
            }
        }
        if (abs(A[pivotrow][i]) < EPSILON) {                    //kontroliju nulovz pivot
            cout << "Nekonecne mnoho reseni" << endl;
            return;
        }
        // swap aktual radek a pit
        for (int k = i; k < n; k++) {                           //prochazim poyice v radku
            swap(A[i][k], A[pivotrow][k]);                      //a swapuju
        }
        swap(b[i], b[pivotrow]);                                // swap u B matice

        // Eliminace
        for (int j = i + 1; j < n; j++) {                       //prochazim radkz
            float factor = A[j][i] / A[i][i];                   //pocitam faktor
            for (int k = i; k < n; k++) {                       //projdu prvky radku
                A[j][k] -= factor * A[i][k];                    //Vypocet a aktualizace prvku
            }
            b[j] -= factor * b[i];                              //Stejne pro b
        }
    }

    // Zpetne vzsubstituuju
    vector<float> x(n);
    for (int i = n - 1; i >= 0; i--) {                          //od posledniho k prvnimu
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {                       //od yacatku
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    // Vypis
    cout << "Reseni:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }
}

int main() {
    vector<vector<float>> A_1 = {
        {1, 2, -3, 4, 5},
        {2, 1, 0, 3, 0},
        {0, 2, 1, 2, -1},
        {3, -1, 0, 5, 2},
        {2, 1, 2, 3, -4}
    };
    vector<float> B_1 = { 4, 9, 5, 3, 2 };
    // result == {10.529, 7.794, 8.794, -6.618, 6.147}

    vector<vector<float>> A_2 = {
    {2,4,-2,-2},
    {1,2,4,-3},
    {-3,-3,8,-2},
    {-1,1,6,-3}
    };
    vector<float> B_2 = { -4,5,7,7 };
    // result == {1.0, 2.0, 3.0, 4.0}

    vector<vector<float>> A_3 = {
        {1,2,3,4,5},
        {6,7,8,9,10},
        {11,12,13,14,15},
        {16,17,18,19,20},
        {21,22,23,24,25}
    };
    vector<float> B_3 = { 1,2,3,4,5 };
    // result == "Nekonecne mnoho rerseni"

    vector<vector<float>> A_4 = {
        {2,5,0,8},
        {1,4,2,6},
        {7,8,9,3},
        {1,5,7,8}
    };
    vector<float> B_4 = { 6,5,4,3 };
    // result == {-2.162, 3.575, -0.737, -0.944}

    gaussianElimination(A_1, B_1);
    gaussianElimination(A_2, B_2);
    gaussianElimination(A_3, B_3);
    gaussianElimination(A_4, B_4);

    return 0;
}



