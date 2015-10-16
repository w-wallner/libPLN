
Simple demo program to demonstrate the usage of libPLN
==============================================================

Description
-------------------------------

This is a simple demo program that uses one the example oscillator that are provided with libPLN
and queries the time deviation value at different points in time either for the current time
or for a time in the future.

Usage
-------------------------------

    $> ./SimpleDemo [seed_value]
    
If no seed value is provided or the seed value if 0 a seed will be chosen based on the current system time. 

Example
-------------------------------

Running the program without supplying any parameter could result in an output like the following:



    ===========================================================
    Simple demo program to demonstrate the usage of libPLN
    ===========================================================
    
    No seed has been supplied on the command line.
    You could have supplied one as the first command line argument.
     --> Using time() to supply a random seed for this run.
    If a seed value of 0 is supplied, a time based seed is chosen without this warning.
    Your seed for the current run is 1445004648.
    
    Starting to query the simulated oscillator for the time deviation at different points in time.
    
    Step 1: Requesting the current time deviation at time 0.1
    Description of current request: Asking the current time, this returns a stable result that won't change
      Current time:   0.1
      Requested time: 0.1
      Result: 8.07704e-10
    
    Step 2: Requesting the current time deviation at time 0.1
    Description of current request: Asking the current time again --> result stays the same
      Current time:   0.1
      Requested time: 0.1
      Result: 8.07704e-10
    
    Step 3: Requesting and estimate for time deviation at time 0.5
    Description of current request: Asking for an estimate at a future time
      Current time:   0.1
      Requested time: 0.5
      Result: 3.30077e-09
    
    Step 4: Requesting and estimate for time deviation at time 0.4
    Description of current request: Asking for an estimate at *another* future time --> old estimate becomes invalid
      Current time:   0.1
      Requested time: 0.4
      Result: 2.2758e-09
    
    Step 5: Requesting and estimate for time deviation at time 0.5
    Description of current request: Asking for an estimate of future time again --> this leads now to a different result
      Current time:   0.1
      Requested time: 0.5
      Result: 3.13896e-09
    
    Step 6: Requesting and estimate for time deviation at time 0.5
    Description of current request: Asking again for an estimate at the same future time several times returns the same result
      Current time:   0.1
      Requested time: 0.5
      Result: 3.13896e-09
    
    Step 7: Requesting and estimate for time deviation at time 0.5
    Description of current request: ... even if the is done at another time
      Current time:   0.2
      Requested time: 0.5
      Result: 3.13896e-09
    
    Step 8: Requesting and estimate for time deviation at time 0.5
    Description of current request: ... and again.
      Current time:   0.3
      Requested time: 0.5
      Result: 3.13896e-09
    
    Step 9: Requesting the current time deviation at time 0.5
    Description of current request: The previous estimate now actually became the truth and won't change anymore
      Current time:   0.5
      Requested time: 0.5
      Result: 3.13896e-09
    
    Finished