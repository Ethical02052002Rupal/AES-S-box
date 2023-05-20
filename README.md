# S-box
C implementation of custom S-Box generation for any degree 8 irreducible polynomial.

## What is S-box?

In cryptography, an S-box (substitution-box) is a basic component of symmetric key algorithms which performs substitution. In block ciphers, they are typically used to obscure the relationship between the key and the ciphertext, thus ensuring Shannon's property of confusion.

In general, an S-box takes some number of input bits, m, and transforms them into some number of output bits, n, where n is not necessarily equal to m. An m×n S-box can be implemented as a lookup table with 2m words of n bits each. Fixed tables are normally used, as in the Data Encryption Standard (DES), but in some ciphers the tables are generated dynamically from the key.

## What does this program do?

Basically, fixed tables are used in encryption and decryption algorithms which are pre-calculated values according to some irreducible polynomial. So, what my program does is, it generates s-box and its corresponding inverse s-box according to the degree 8 irreducible polynomial that you give in input.

## Usage

The usage of this tool is very simple and straight forward.

1. Compile the C file

    Use GCC to compile the file:
    ```console
    gcc sbox.c -o <output file name>
    ```

2. Use the generated executable file to generate s-box
    
    You will be prompted to enter a file name. Enter the name of the file in which the binary form of the irreducible polynomial is written. (An example file is provided here which contains all the degree 8 irreducible polynomials)

    **NOTE**: All the polynomials should be in seperate lines. (If you are adding some by any chance, see the example file for reference)

3. Output
    
    Output will be generated on the console as well as in a seperate text named **sbox_output.txt**.

