#include <iostream>
#include <cmath>
#include <omp.h>

struct Vector {
    double x, y, z;
};

double calculateVectorLength(const Vector& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

int main() {
    Vector vector = { 12.0, 73.0, 129.0 };
    double vectorLength = 0.0;

#pragma omp parallel num_threads(4)
    {
        double localLength = 0.0;

#pragma omp sections
        {
#pragma omp section
            {
                localLength = calculateVectorLength(vector);
            }

#pragma omp section
            {
                localLength = calculateVectorLength(vector);
            }

#pragma omp section
            {
                localLength = calculateVectorLength(vector);
            }

#pragma omp section
            {
                localLength = calculateVectorLength(vector);
            }
        }

#pragma omp critical
        {
            vectorLength += localLength;
        }
    }

    std::cout << "Dlugosc wektora: " << vectorLength << std::endl;

    return 0;
}
