#include "PID.h"
#include <iostream>
using namespace std;
/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
	/**
	 * TODO: Initialize PID coefficients (and errors, if needed)
	 */
	PID pid;
	this->Kp = Kp_;
	this->Ki = Ki_;
	this->Kd = Kd_;

	p_error = 0;
	i_error = 0;
	d_error = 0;

}

void PID::UpdateError(double cte) {
	/**
	 * TODO: Update PID errors based on cte.
	 */

	d_error = cte - p_error;
	p_error = cte;
	i_error += cte;

}

double PID::TotalError() {
	/**
	 * TODO: Calculate and return the total error
	 */
	return Kp * p_error + Ki * i_error + Kd * d_error;
	//return 0.0;  // TODO: Add your total error calc here!
}

double PID::twiddle(double cte)
{
	//double sum_pid = this->Kp + this->Ki + this->Kd;
	double dp_p = 1;
	double dp_i = 1;
	double dp_d = 1;
	double sum_dp = dp_p + dp_i + dp_d;
	//double total_err;
	double best_err;
	double steer_value;
	int it = 1;
	while (sum_dp > 0.01)
	{
		this->Kp += dp_p;
		this->Ki += dp_i;
		this->Kd += dp_d;
		UpdateError(cte);
		steer_value = TotalError();
		if (cte < p_error)
		{
			best_err = cte;
			dp_p *= 1.1;
			dp_i *= 1.1;
			dp_d *= 1.1;
		}
		else
		{
			dp_p -= 2 * dp_p;
			dp_i -= 2 * dp_i;
			dp_d -= 2 * dp_d;

			UpdateError(cte);
			steer_value = TotalError();
			if (cte < best_err)
			{
				best_err = cte;
				dp_p *= 1.1;
				dp_i *= 1.1;
				dp_d *= 1.1;
			}
			else
			{
				this->Kp += dp_p;
				this->Ki += dp_i;
				this->Kd += dp_d;
				dp_p *= 0.9;
				dp_i *= 0.9;
				dp_d *= 0.9;
			}
		}
	}
	it++;
	std::cout << it << endl;
	return steer_value;
}