#include iostream
#include cstdlib
#include ctime
#include cmath
#include thread
#include vector

void monte_carlo(int num_points, int& num_inside_circle) {
    stdsrand(stdtime(nullptr));
    for (int i = 0; i  num_points; i++) {
        double x = ((double)stdrand()  RAND_MAX)  2 - 1;
        double y = ((double)stdrand()  RAND_MAX)  2 - 1;
        if (stdpow(x, 2) + stdpow(y, 2) = 1) {
            num_inside_circle++;
        }
    }
}

int main() {
    const int num_points = 10000000;
    const int num_threads = 8;
    stdvectorint num_inside_circle(num_threads);

    stdvectorstdthread threads;
    int points_per_thread = num_points  num_threads;
    for (int i = 0; i  num_threads; i++) {
        threads.emplace_back(monte_carlo, points_per_thread, stdref(num_inside_circle[i]));
    }

    for (auto& t  threads) {
        t.join();
    }

    int total_inside_circle = 0;
    for (int i = 0; i  num_threads; i++) {
        total_inside_circle += num_inside_circle[i];
    }

    double pi = 4.0  total_inside_circle  num_points;

    stdcout  Approximate value of Pi   pi  stdendl;

    return 0;
}
