Group Members ==============================================
- Mujahid Egan
- Slayter Teal
- Jackson Wildman

We tried virtually everything to get POSIX message passing to work. Our initial
test proved sucessfull but scaling it to our app wouldn't work. Testing was difficult as
the tunnel would get bugged when we had to cancel the program. 


Testing ====================================================
Please put all test*.c files into a "test" directory to allow for our compilation instructions to work.
Our file structure is as follows:
./"the application goes here"
./test/"unit tests go here, i.e. test*.c files"
To build an individual test: gcc -Wall ./test/"name of test".c ./*.c -o a.out 

To run POSIX message testing, run:
- gcc POSIXtest.c -o POSIXtest -ldt
- gcc POSIXtest0.c -o POSIXtest0 -ldt
Note: The program has to be closed via <CTRL+c>, we used signal handling to close cleanly.

Compilation: ===============================================
// We're assuming you are in the main project directory for these instructions.
// Server.c and client.c should be in Their own folder!
Build Client (from main project directory): gcc ../client/client.c -o client.out
Build Server (from main project directory): gcc -Wall ./server/server.c ./*.c -o a.out -ldt



References Used ============================================
https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/