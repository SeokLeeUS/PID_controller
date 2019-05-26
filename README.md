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
  main body code to call out UpdateError/TotalError functions
          pid.UpdateError(cte); //calling UpdateError function
          steer_value = pid.TotalError();  //calling TotalError function
          // DEBUG
          std::cout << "CTE: " << cte << " Steering Value: " << steer_value 
```
```
// set up initializer
int main(int argc, char *argv[]) {
  uWS::Hub h;

  PID pid;
  /**
   * TODO: Initialize the pid variable.
   */
  double init_Kp = atof(argv[1]);
  double init_Ki = atof(argv[2]);
  double init_Kd = atof(argv[3]);
  pid.Init(init_Kp,init_Ki,init_Kd);

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
- P gain first
1.start with [Kp= -0.5, Ki = 0, Kd = 0]: vehicle oscillates too much. but at least I was able to make the vehicle move. 

- Consider I gain to attenuate the oscillation. Remember, Ki should consider the simulation time step to determine the magnitude. The update rate of simulation is 20ms. Therefore, Kd = 50*gain_value. 
2. [Kp= -0.1, Ki = 0, Kd = 20] :vehicle is able to complete a full lap without falling under the bank.However, it still oscillates but a lot shorter interval as d gain tries to attenuates the larger frequency of oscillation. 

3. What's the next? lower Kp gain to reduce down larger frequency oscillation. 

4. [Kp= -0.05, Ki = 0, Kd = 20] : frequency of small oscillation gets reduced. try to even cut more Kp?

5. [Kp= -0.02, Ki = 0, Kd = 20] : I don't see much improvement, probably increase derivative gain to improve the performance when abrupt steering change is attempted?

6. [Kp= -0.02, Ki = 0, Kd = -50] : I see there's overshoot when Kd kicks in to attenuate the oscillation. now it's time to add Ki. 

7. [Kp= -0.02, Ki = -5, Kd = -50] : hmm. vehicle at start rotates immediately. wrong value... 

8. [Kp= -0.02, Ki = -0.5, Kd = -50] : still doesn't look right as vehicle circles around at the start, but at least no oscillation. 

9. [Kp= -0.02, Ki = -0.05, Kd = -50] : vehicle follows the tract, less oscillation on the front steering wheels comparing to step 6. It seems overshoot driven by Kd seems too high so Ki may not be able to help. 

10. [Kp= -0.01, Ki = -0.05, Kd = -25]: Kd in half, and Kp in half while holding Ki. a bit better, it looks kp is still high. will cut down more kp, and leave Kd as is. 

11. [Kp= -0.005, Ki = -0.05, Kd = -25]:a bit better, stick Kp, but cut down Kd as there looks like overshoot. 

12. [Kp= -0.005, Ki = -0.05, Kd = -20]:a bit better, still bit of overshoot on the steering, but now I need to correct the vehicle trajectory (zigzag behaviour, it's related to Ki, I believe). 

13. [Kp= -0.005, Ki = -0.025, Kd = -15]:getting worse

14. [Kp= -0.005, Ki = -0.1, Kd = -20]: a lot more zigzagging. 

15. [Kp= -0.005, Ki = -0.01, Kd = -20]: a lot less zigzagging, but oscillation on the front wheel. kp/kd needs adjustment. 

16. [Kp= -0.002, Ki = -0.01, Kd = -10]: a lot better, but cornering response needs improvement, but I am okay with this set up. 

















