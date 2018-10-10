# Parallel_For
FOR loops are inherently serial. This code tests whether my method for parallelizing a FOR loop can speed up the calculations.

The plan is to split the loop in half with each thread performing work on each half of the loop. If one thread finishes before the other thread, then a redefinition of the bounds is signaled. During the redefinition, the finished thread will take half of the remaining work from the unfinished thread. This process will continue until the calcualtions are complete.

In order to prevent overhead from locking and unlocking the shared variables, the threads will not continue redefining loop bounds once they reach a specific number of remaining elements. The new bounds will also only be calculated if a redefinition is signaled so that the bounds of the loop do not need to be continually locked and unlocked.
