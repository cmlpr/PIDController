#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double pid_err[3];

  /*
  * Coefficients
  */ 
  double pK[3];

  /* 
  * Twiddle Parameters
  */
  double twd_err;
  double twd_besterr;
  double dpK[3];
  int max_iter;
  int iter;
  int p_iter;
  bool twd_initialized;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double pK_init[3]);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
  * Twiddle related calcs
  */
  void Twiddle();

};

#endif /* PID_H */
