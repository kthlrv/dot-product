#include <stdio.h>

float dotProductC(const float* A, const float* B, int n) {
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += A[i] * B[i];
    }
    return sum;
}