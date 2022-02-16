Group Members:
- Mujahid Egan
- Slayter Teal
- Jackson Wildman

Please put all test*.c files into a "test" directory to allow for our compilation instructions to work.
Our file structure is as follows:
./"the application goes here"
./test/"unit tests go here, i.e. test*.c files"

Compilation: 
// We're assuming you are in the main project directory for these instructions.
To build entire app: gcc -Wall ./*.c -o a.out -ldt
To build an individual test: gcc -Wall ./test/"name of test".c ./*.c -o a.out -ldt
