# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Background
The goal of the project is to control a car in a simulator using classical control methodology. The method we will use is PID (Proportional-Integral-Derivative) control which is a control loop feedback mechanism. This method calculates an error from a desired setpoint and applies a correction based on the proportional, integral and derivative terms. 

## Implementation
The simulator (link provided below) provides us a track and a car with basic controls. The C++ program gets the cross-track-error (cte) from the simulator and allows us to send steering angle and throttle back to the simulator. "Main.cpp" provides the codes necessary to do this communication. 

CTE measures the deviation from the centerline of the track. 

Proportianl term allows us to adjust the steering angle so that car turns to the middle of the road. We achieve this by multiplying the CTE with the proportional gain. When CTE is large the steering angle will also be large and when CTE is small the angle will also be small. When only P term is applied in the control the car osciallates around a horizontal line with an amplitude decay over time. The P control suffers from overshoot.

Derivative term tries to bring the rate of change of the error to zero. This helps us to flatten out the osciallation amplitude reducing the overshoot. We multiply the rate of change of CTE ((current CTE - previous CTE) / Delta T) by the D factor. 

Integral term applies a correction that increases over time. If the car does not converge to center line, the error will accumulate and I term will start being effective to bring the car to the centerline. The integral term corrects any systematic bias that might exist in the system. Some examples could be the drift in the tires and bias in steering wheel. 

PID controller is applied using the "PID.cpp" and "PID.h" files. The PID objects are created for both steering angle and the throttle. Initial values are found using trial and error. A hill climbing algorithm (Twiddle) has also been implemented to find better gain values. Since we cannot run the simulator multiple times to find the best parameters, I tried this method in real time. It record the cumulative error for 2000 iterations and compares it to the best available error to fine tune the gain values. Due to the time intensive nature of the method, I decided to use the parameters ajusted manually to record this [video] (https://www.youtube.com/watch?v=q_Cu8AFisB4). 

The PID controller for the steering angle is similar to the Python program we developed in the course. The throttle version is however is insensitive to the sign of the CTE. This is because the throttle behaviour should be the same when if the car is positioned on the left or the right side of the lane. Since we are using absolute value of the CTE, integral gain is assigned to zero. 

In "main.cpp"

  Final Controller Gains:
    double pK_init_steer[3] = {0.2, 0.0004, 4.0};
    double pK_init_throttle[3] = {0.3, 0.0000, 0.025};

  Twiddle can be activated by activating:
    pid_steer.Twiddle();
    pid_throttle.Twiddle();

--

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

