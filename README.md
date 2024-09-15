# Large Integer Math Operations Program

This C program is designed to perform mathematical operations on two large integers, where the size exceeds the typical four-byte limit. The program supports addition, subtraction, multiplication, and division operations.

## Features
Handles large integers beyond the four-byte size limit.
Supports basic math operations:
Addition
Subtraction
Multiplication
Division

## Requirements
To run this program, you'll need:

A C compiler (e.g., GCC)
Terminal/Command Line access

## User Instructions

1. Download the Repository
Clone or download the repository to your local machine.

2. Prepare Input File
Fill out the inputfile.txt with the desired large integers. The format should be:

```php
<integer_1>
<integer_2>
```
These will be the two integers used for the operations.

3. Compile the Program
If you haven't already compiled the program, you can do so by running the following command in the terminal:

```bash
gcc -o a.exe main.c
```
4. Execute the Program
Run the compiled program by executing the following command in the terminal:

```bash
./a.exe
```
5. View Results
The program will output the results of the math operations (add, subtract, multiply, and divide) between the two integers.

## Note
This program is still under development and may contain bugs or unexpected behavior. Further improvements are planned to enhance its performance and accuracy.

## How the Project Works
1. Input Parsing: 
The program starts by reading two large integers from the inputfile.txt. Each integer is stored as a string since their size exceeds the typical data types such as int or long in C, which are limited to 4 bytes (32 bits).

2. Large Integer Representation: 
To handle these large integers, the program stores them in a doubly linked list of digits where the head of the list point at the leas significant bit of the large integer. This allows us to perform math operations digit by digit, similar to how arithmetic is done manually.

3. Addition of Large Integers
The addition algorithm works similarly to the way humans perform addition on paper. It starts from the least significant digit (rightmost) and adds corresponding digits from both numbers, keeping track of the carry.


4. Subtraction of Large Integers
Subtraction follows a similar approach to addition, but here we need to keep track of borrowing when the digit in the first integer is smaller than the corresponding digit in the second integer.


5. Multiplication of Large Integers
For multiplication, the program uses a method similar to long multiplication done by hand. It multiplies each digit of one number by every digit of the other and then sums the intermediate results, shifting them according to their position.


6. Division of Large Integers
Division is handled by repeatedly subtracting the divisor from the dividend and counting how many times this operation can be performed. This method mimics long division but on arrays representing large numbers.

Step-by-step process:
Subtract the divisor from the dividend.
Keep track of how many times you perform this operation.
The quotient is the result of this counting, and any remaining value is the remainder.

7. Output
Once all operations are completed, the program outputs the results (sum, difference, product, and quotient) to the terminal or console.

## Author

This program was fully written by Taleen Abuzulof


## License

[MIT](https://choosealicense.com/licenses/mit/)
