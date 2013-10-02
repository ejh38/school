Adding a new system call to the kernel was an interesting experience. I followed the instructions as written but there were a few minor changes I had to make to get it to work. For example, the gcc -m32 line is wrong as written; it says:
gcc -m32 -o testsystemcall -I /u/OSLab/<YOUR_USERNAME>/linux-
2.6.23.1/include/testsystemcall.c

but should be:
gcc -m32 -o testsystemcall -I /u/OSLab/<YOUR_USERNAME>/linux-
2.6.23.1/include/ testsystemcall.c

In addition, I used the math library so I had to add -lm to the command for a total of:

gcc -m32 -lm -o testsystemcall -I /u/OSLab/<YOUR_USERNAME>/linux-
2.6.23.1/include/testsystemcall.c

But that aside, I found the process pretty simple and fun.




The experiment I used to test the execution time of the system call was pretty simple. In my testsystemcall.c function I take in a command-line argument for how many iterations of the system call we would like to do. Then I perform the system call that many times, taking the time before and after the system call using gettimeofday. Then I take the difference of the two time_t.tv_sec values, multiply by 1,000,000 to go from seconds to microseconds, then add the difference of the two time_t.tv_usec values, to get the total difference in microseconds between gettimeofday before and after the system calls.
Each iteration I store this value to an array (which is malloc'ed to be sized appropriately to the command-line argument), so that by the end I have each value. From there I can calculate the average and standard deviation and I print them out to the user.

Here are the results of my expirementation:
Iterations | Average | Std deviation
100			 292.93		2392.08
100			 107.14		195.47
100			 342.08		2032.53
100			 189.50		1253.81
100			 229.96		922.18

1000		 133.08		1355.94
1000		 110.91		1040.40
1000		 157.57		1211.06
1000		 119.11 	938.84
1000		 128.10 	1028.81

10000		 131.04		1226.93
10000		 133.95		1186.83
10000		 128.52 	1178.82
10000		 123.75 	1149.67
10000		 119.00 	1165.88

100000		 117.88 	1091.69
100000 		 121.86 	1162.72
100000 		 131.98 	1191.19
100000 		 118.85 	1154.78
100000 		 121.83 	1184.11

So it looks like the average time for system call execution is around 121-131 microseconds, and the standard deviation is about 1200 microseconds.






































