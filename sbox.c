#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int poly_mult(int a, int b, int mod_pol)
{
    int ab = 0;
    
    // Perform multiplication
    for (int i_bit = 0; i_bit < 8; i_bit++) {
        if (a & (1 << i_bit)) {
            int b_shift = b << i_bit;
            ab ^= b_shift;
        }
    }
    
    // Perform modulo operation
    for (int i_bit = 15; i_bit >= 8; i_bit--) {
        if (ab & (1 << i_bit)) {
            int mod_pol_shift = mod_pol << (i_bit - 8);
            ab ^= mod_pol_shift;
        }
    }
    
    return ab;
}

int find_inverse(int b_in, int mod_pol)
{
    int b_inv;
    int prod;
    
    // Iterate through all possible inverse values
    for (int i = 1; i <= 255; i++) {
        prod = poly_mult(b_in, i, mod_pol);
        if (prod == 1) {
            b_inv = i;
            break;
        }
    }
    
    return b_inv;
}

int aff_trans(int b_in)
{
    int mod_pol = 0x101; // Binary representation: 100000001 -> 257
    int mult_pol = 0x1F;  // Binary representation: 00011111 -> 31
    int add_pol = 0x63;   // Binary representation: 01100011 -> 99
    
    // Compute the product of b_in and mult_pol modulo mod_pol
    int temp = poly_mult(b_in, mult_pol, mod_pol);
    
    // Compute the affine transformation of temp
    int b_out = temp ^ add_pol;
    
    return b_out;
}

void s_box_gen(int *s_box, int *inv_s_box, int mod_pol)
{
    int inverse[256] = {0};
    
    // Compute the inverse of each element in GF(256)
    inverse[1] = 0;
    for (int i = 1; i < 256; i++) {
        inverse[i] = find_inverse(i, mod_pol);
    }
    
    // Compute the S-box using the affine transformation of the inverses
    for (int i = 0; i < 256; i++) {
        s_box[i] = aff_trans(inverse[i]);
    }
    
    // Compute the inverse S-box using the inverse of the affine transformation
    for (int i = 0; i < 256; i++) {
        inv_s_box[s_box[i]] = i;
    }
}

int main() {
    //int m;
    char filename[100];
    int s_box[256] = {0};
    int inv_s_box[256] = {0};
    FILE *input_file;
    FILE *output_file;
    char binary[32];
    
    // Open the file in read mode
    printf("\nEnter binary file name: ");
    scanf("%s", &filename);
    input_file = fopen(filename, "r");
    
    if (input_file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    output_file = fopen("sbox_output.txt", "w");

    while (fscanf(input_file, "%s", binary) != EOF) {
        int decimal = 0;
        int length = strlen(binary);
        
        // Convert binary to decimal
        for (int i = length - 1; i >= 0; i--) {
            if (binary[i] == '1') {
                decimal += pow(2, length - i - 1);
            }
        }

        s_box_gen(s_box, inv_s_box, decimal);

        printf("\n---------------------------------------------------------\n");
        fprintf(output_file, "\n---------------------------------------------------------\n");
        
        printf("\nS-box for the irreducible polynomial %d\n", decimal);
        fprintf(output_file, "\nS-box for the irreducible polynomial %d\n", decimal);

        printf("\nS-box:\n");
        fprintf(output_file, "\nS-box:\n");
        printf("\n");
        fprintf(output_file, "\n");
        for (int i = 0; i < 256; i++) {
            printf("0x%x ", s_box[i]);
            fprintf(output_file, "0x%x ", s_box[i]);
            if ((i+1) % 16 == 0) {
                printf("\n");
                fprintf(output_file, "\n");
            }
        }
        
        printf("\nInverse S-box:\n");
        fprintf(output_file, "\nInverse S-box:\n");
        printf("\n");
        fprintf(output_file, "\n");
        for (int i = 0; i < 256; i++) {
            printf("0x%x ", inv_s_box[i]);
            fprintf(output_file, "0x%x ", inv_s_box[i]);
            if ((i+1) % 16 == 0) {
                printf("\n");
                fprintf(output_file, "\n");
            }
        }

        printf("\n---------------------------------------------------------\n");
        fprintf(output_file, "\n---------------------------------------------------------\n");
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}
