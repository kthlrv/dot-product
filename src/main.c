/**
* LBYARCH MP2 - Dot Product (Group 9, S18A)
*   NARVAJA, KATE ASHLEY ATACADOR
*   PINEDA, MARK GABRIEL ALIPIO
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern void dotProductASM(int n, const float* A, const float* B, float* result);
float dotProductC(const float* A, const float* B, int n);
void initializeVectors(float* A, float* B, int n);
void runPerformanceTest(int n, const char* sizeName);
void printSummary(const char* sizeName, double avgTimeC, double avgTimeASM, int correctCount);

int main() {
    printf("Note: PASS means Assembly output matches the C output. FAIL means otherwise.\n");
    printf("========================================\n\n");

    srand((unsigned int)time(NULL));

    runPerformanceTest(1048576, "20");
    runPerformanceTest(16777216, "24");
    runPerformanceTest(268435456, "28");

    return 0;
}

void initializeVectors(float* A, float* B, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = (float)rand() / RAND_MAX;
        B[i] = (float)rand() / RAND_MAX;
    }
}

void printSummary(const char* sizeName, double avgTimeC, double avgTimeASM, int correctCount) {
    printf("\n[SUMMARY for 2^%s] \n", sizeName);
    printf("C version average time: %0.6f seconds\n", avgTimeC);
    printf("Assembly version average time: %0.6f seconds\n", avgTimeASM);
    printf("Correctness: %d/20 passed\n\n", correctCount);
    printf("========================================\n\n");
}

void runPerformanceTest(int n, const char* sizeName) {
    printf("Testing vector size: 2^%s (%d elements)\n", sizeName, n);

    // allocate memory
    float* A = (float*)malloc(n * sizeof(float));
    float* B = (float*)malloc(n * sizeof(float));

    if (A == NULL || B == NULL) {
        printf("Memory allocation failed for size 2^%s\n", sizeName);
        return;
    }

    printf("Initializing vectors with random data...\n");
    initializeVectors(A, B, n);

    double totalTimeC = 0.0;
    double totalTimeASM = 0.0;
    int correctCount = 0;

    printf("\nRunning 20 iterations:\n");
    printf("Run # | C Time (s)   | ASM Time (s) | C Result     | ASM Result   | Check\n");
    printf("------|--------------|--------------|--------------|--------------|--------\n");

    for (int run = 0; run < 20; run++) {
        clock_t start, end;
        float resultC, resultASM;
        double timeC, timeASM;

        // time for C
        start = clock();
        resultC = dotProductC(A, B, n);
        end = clock();
        timeC = ((double)(end - start)) / CLOCKS_PER_SEC;
        totalTimeC += timeC;

        // time for assembly
        start = clock();
        dotProductASM(n, A, B, &resultASM);
        end = clock();
        timeASM = ((double)(end - start)) / CLOCKS_PER_SEC;
        totalTimeASM += timeASM;

        int isCorrect = (fabs(resultC - resultASM) < 0.001f);
        if (isCorrect)
            correctCount++;

        printf("%4d  | %12.6f | %12.6f | %12.2f | %12.2f | %s\n", run + 1, timeC, timeASM, resultC, resultASM, isCorrect ? "PASS" : "FAIL");
    }

    double avgTimeC = totalTimeC / 20.0;
    double avgTimeASM = totalTimeASM / 20.0;
    printSummary(sizeName, avgTimeC, avgTimeASM, correctCount);

    free(A);
    free(B);
}