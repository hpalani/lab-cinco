/*
 NAME: Harish Palani
 CRN: 11467
 ASSIGNMENT: Lab 5
 SOURCES: stackoverflow.com
 */

#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;

void evaluator(double polynomial[], int n, double x);

int main() {
    
    cout << endl;
    for (int n = 1; n <= 25; n++) {
        double* polynomial;
        polynomial = new double[n + 1];
        
        for (int i = 0; i < n + 1; i++) {
            // Generate random real integers between 1 and 99 (TO-DO)
            std::random_device deviceA;
            std::mt19937 generatorA(deviceA());
            std::uniform_int_distribution<int> integers(1, 99);
            
            polynomial[i] = (double) integers(generatorA);
        }
        
        // Generate random real double between -20 and 20
        std::random_device deviceB;
        std::mt19937 generatorB(deviceB());
        std::uniform_real_distribution<double> reals(-20, 20);
        
        double x = reals(generatorB);
        
        // Evaluate away!
        evaluator(polynomial, n, x);
    }
}

// Evaluates polynomials using both Horner's algorithm & normal
void evaluator(double polynomial[], int n, double x) {
    // Print degree for this particular iteration of the algorithm
    cout << "DEGREE " << n << endl;
    
    // Print corresponding polynomial
    for (int i = n; i >= 0; i--) {
        cout << ((int) polynomial[i]);
        cout << "x";
        cout << "^" << i;
        if (i > 0) { cout << " + "; }
    }
    
    cout << endl;
    cout << endl;
    
    cout.precision(3);
    cout << "x = " << fixed << x << endl;
    
    using namespace std::chrono;
    steady_clock::time_point t1 = steady_clock::now();
    
    // Run values through Horner's algorithm & calculate time
    long double horner = polynomial[n];
    for (int i = n - 1; i >= 0; i--) {
        horner = (horner * x) + polynomial[i];
    }
    
    steady_clock::time_point t2 = steady_clock::now();
    duration<long double> time_span1 = duration_cast<duration<long double>>(t2 - t1);
    
    cout << "P(" << fixed << x << "), by Horner's algorithm = " << fixed << horner;
    cout << " (calculated in " << scientific << time_span1.count() << " seconds)" << endl;
    
    steady_clock::time_point t3 = steady_clock::now();
    
    // Run values through straight evaluation & calculate time
    long double straight = polynomial[0];
    for (int i = n; i > 0; i--) {
        double x2 = 1;
        for (int j = 0; j < i; j++) {
            x2 = x2 * x;
        }
        straight = straight + (polynomial[i] * x2);
    }
    
    steady_clock::time_point t4 = steady_clock::now();
    duration<long double> time_span2 = duration_cast<duration<long double>>(t4 - t3);
    
    cout << "P(" << fixed << x << "), by straight evaluation = " << fixed << straight;
    cout << " (calculated in " << scientific << time_span2.count() << " seconds)" << endl;
    
    cout << endl;
    cout << endl;
}