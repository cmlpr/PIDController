#include "PID.h"
#include <math.h>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double pK_init[3]) {
    pK[0] = pK_init[0];
    pK[1] = pK_init[1];
    pK[2] = pK_init[2];

    pid_err[0] = 0.0;
    pid_err[1] = 0.0;
    pid_err[2] = 0.0;

    twd_err = 0.0;
    twd_besterr = 0.0;
    dpK[0] = pK[0] * 0.05;
    dpK[1] = pK[1] * 0.05;
    dpK[2] = pK[2] * 0.05;

    max_iter = 2000;
    iter = 0;
    p_iter = 0;
    twd_initialized = false;
}

void PID::UpdateError(double cte) {
    pid_err[2] = cte - pid_err[0];
    pid_err[0] = cte;
    pid_err[1] += cte;

    twd_err += pow(cte, 2.0);

}

double PID::TotalError() {
    return - pK[0] * pid_err[0] - pK[1] * pid_err[1] - pK[2] * pid_err[2];
}

void PID::Twiddle() {

    if (!twd_initialized) {
        if ((((iter+1) % max_iter) == 0)) {
            twd_besterr = twd_err;
            twd_err = 0.0;
            iter = 0;
            twd_initialized = true;
            return;
        } 
    }

    if (twd_initialized && iter == 0) {
        pK[p_iter%3] += dpK[p_iter%3];
    }

    if (twd_initialized && iter == max_iter) {
        if (twd_err < twd_besterr) {
            twd_besterr = twd_err;
            dpK[p_iter%3] *= 1.1;
            twd_err = 0.0;
            iter = 0;
            p_iter += 1;
            return;
        } 
        else {
            pK[p_iter%3] -= 2.0 * dpK[p_iter%3];
            twd_err = 0.0;
        }
    }

    if (twd_initialized && iter == max_iter * 2) {
        if (twd_err < twd_besterr) {
            twd_besterr = twd_err;
            dpK[p_iter%3] *= 1.1;
        } 
        else {
            pK[p_iter%3] += dpK[p_iter%3];
            dpK[p_iter%3] *= 0.9;
        }
        twd_err = 0.0;
        iter = 0;
        p_iter += 1;
        return;
    }

    iter += 1;
}