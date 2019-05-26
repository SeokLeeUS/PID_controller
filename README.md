# PID_controller
Udacity self-driving car #8 project

## Reference:
Udacity's PID walkthrough session: https://www.youtube.com/watch?v=YamBuzDjrs8&feature=youtu.be
Udacity's PID course material (all snapshots appeared in this section are from the course material)

## Project rubrics:

|CRITERIA                                                        |MEETS SPECIFICATIONS|
|:---                                                            |:-                  |
|~Your code should compile.~ | ~Code must compile without errors with cmake and make.Given that we've made CMakeLists.txt as general as possible, it's recommend that you do not change it unless you can guarantee that your changes will still compile on any platform.~|
|~The PID procedure follows what was taught in the lessons.~|~It's encouraged to be creative, particularly around hyperparameter tuning/optimization. However, the base algorithm should follow what's presented in the lessons.~|
|~Describe the effect each of the P, I, D components had in your implementation.~|~Student describes the effect of the P, I, D component of the PID algorithm in their implementation. Is it what you expected?Visual aids are encouraged, i.e. record of a small video of the car in the simulator and describe what each component is set to.~|
|~Describe how the final hyperparameters were chosen.~|~Student discusses how they chose the final hyperparameters (P, I, D coefficients). This could be have been done through manual tuning, twiddle, SGD, or something else, or a combination~|  
|~The vehicle must successfully drive a lap around the track.~|~No tire may leave the drivable portion of the track surface. The car may not pop up onto ledges or roll over any surfaces that would otherwise be considered unsafe (if humans were in the vehicle).~|

# working code before manual tuning:

@ main.cpp
```
  //TODO
          pid.UpdateError(cte); //calling UpdateError function
          steer_value = pid.TotalError();  //calling TotalError function
          // DEBUG
          std::cout << "CTE: " << cte << " Steering Value: " << steer_value 
```

@PID.cpp
```
//initializer
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
```
```
//UpdateError
void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  
  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;

}

```
```
//TotalError
double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  return Kp*p_error + Ki*i_error + Kd*d_error;
  //return 0.0;  // TODO: Add your total error calc here!
}
```
## tuning process:
P gain: start with -0.5 0 -0.5 
