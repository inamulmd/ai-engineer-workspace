
#if defined(__GNUC__) && defined(__i386__)
#pragma GCC target("sse2,fpmath=sse")
#endif

#include <cstdio>
#include <chrono>

static inline double calculate(int iterations, int param1, int param2) {
    double result = 1.0;
    double p1 = static_cast<double>(param1);
    double p2 = static_cast<double>(param2);

    int i = 1;
    for (; i <= iterations - 3; i += 4) {
        double d0 = static_cast<double>(i) * p1;
        double d1 = static_cast<double>(i + 1) * p1;
        double d2 = static_cast<double>(i + 2) * p1;
        double d3 = static_cast<double>(i + 3) * p1;

        double inv0_a = 1.0 / (d0 - p2);
        double inv0_b = 1.0 / (d0 + p2);
        double inv1_a = 1.0 / (d1 - p2);
        double inv1_b = 1.0 / (d1 + p2);
        double inv2_a = 1.0 / (d2 - p2);
        double inv2_b = 1.0 / (d2 + p2);
        double inv3_a = 1.0 / (d3 - p2);
        double inv3_b = 1.0 / (d3 + p2);

        result -= inv0_a;
        result += inv0_b;
        result -= inv1_a;
        result += inv1_b;
        result -= inv2_a;
        result += inv2_b;
        result -= inv3_a;
        result += inv3_b;
    }

    for (; i <= iterations; ++i) {
        double d = static_cast<double>(i) * p1;
        result -= 1.0 / (d - p2);
        result += 1.0 / (d + p2);
    }

    return result;
}

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();
    double result = calculate(200000000, 4, 1) * 4.0;
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end_time - start_time;

    std::printf("Result: %.12f\n", result);
    std::printf("Execution Time: %.6f seconds\n", elapsed.count());

    return 0;
}
