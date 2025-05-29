#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>
using namespace std;

#define MAX 100 


bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    FILE *inputFile = fopen("array2.txt", "rt");
    if (!inputFile) {
        cout << "Khong the mo file array2.txt!" << endl;
        return 1;
    }

    
    FILE *outputFile = fopen("array2.out", "wt");
    if (!outputFile) {
        cout << "Khong the mo file array2.out!" << endl;
        fclose(inputFile);
        return 1;
    }

    int m, n;
    fscanf(inputFile, "%d %d", &m, &n); 

    if (m > MAX || n > MAX) {
        cout << "Kich thuoc ma tran qua loon!" << endl;
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    int matrix[MAX][MAX]; 
    int primeCount = 0;
    int rowSums[MAX] = {0}; 
    int colSums[MAX] = {0};

    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(inputFile, "%d", &matrix[i][j]);

            
            if (isPrime(matrix[i][j])) {
                primeCount++;
            }

            
            rowSums[i] += matrix[i][j];
            colSums[j] += matrix[i][j];
        }
    }

    
    fprintf(outputFile, "So luong so nguyen to: %d\n", primeCount);

    fprintf(outputFile, "Tong tren tung dong: ");
    for (int i = 0; i < m; i++) {
        fprintf(outputFile, "%d ", rowSums[i]);
    }
    fprintf(outputFile, "\n");

    fprintf(outputFile, "Tong tren tung cot: ");
    for (int j = 0; j < n; j++) {
        fprintf(outputFile, "%d ", colSums[j]);
    }
    fprintf(outputFile, "\n");

    
    fclose(inputFile);
    fclose(outputFile);

    cout << "Xu ly xong, vui long kiem tra file array2.out!" << endl;
    return 0;
}
