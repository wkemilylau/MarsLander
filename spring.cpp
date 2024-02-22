#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {

    // declare variables
    double t, t_max, dt, a, new_x, x, v;
    int it, m, k;

    // mass, spring constant, initial position and velocity
    m = 1;
    k = 1;
    x = 0;
    v = 1;


    // simulation time, timestep, and number of iterations
    t_max = 100;
    dt = 0.1;
    it = t_max / dt;

    // initialise position, velocity and time vectors
    vector<double> x_list(it, 0), v_list(it, 0), t_list(it, 0);
    for (int i = 0; i < it; i++) {
        t_list[i] = dt * i;
    }

    // initial velocity
    v_list[0] = 1.0;

    // Verlet integration
    for (int i = 1; i < it - 1; i++) {

        x_list[i] = x;
        v_list[i] = v;
        a = -k * x / m;


        if (i == 1) {
            x = x + dt * v;
            v = v + dt * a;
        }
        else {
            new_x = 2 * x - x_list[i - 1] + dt * dt * a;
            v = (new_x - x_list[i - 1]) / (2 * dt);
            x = new_x;
        }

    }


    // Write the trajectories to file
    ofstream fout;
    fout.open("trajectories.txt");
    if (fout) { // file opened successfully
        for (int i = 0; i < t_list.size(); i = i + 1) {
            fout << t_list[i] << ' ' << x_list[i] << ' ' << v_list[i] << ' ' << a << endl;
        }
    }
    else { // file did not open successfully
        cout << "Could not open trajectory file for writing" << endl;
    }

}
