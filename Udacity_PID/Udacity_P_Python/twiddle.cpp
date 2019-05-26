double PID::twiddle(double cte,  double prev_err)
{
	double sum_pid = this->Kp + this->Ki + this->Kd;
	double dp_p = 1;
	double dp_i = 1;
	double dp_d = 1;
	double total_err;
	double best_err = prev_err;
	while (sum_pid > 0.01)
	{
		this->Kp += dp_p;
		this->Ki += dp_i;
		this->Kd += dp_d;

		UpdateError(cte);
		total_err =  TotalError();
		if (total_err < prev_err)
		{
			best_err = total_err;
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
			total_err = TotalError();

			if (total_err < best_err)
			{
				best_err = total_err;
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
}