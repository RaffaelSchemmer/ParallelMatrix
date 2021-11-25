//
// Classic Matrix Multiplication without using SIMD or MIMD techniques
//

#include <stdio.h>
#include <stdlib.h>

float result[1536][1536];
    
int main(int argc, char **argv) 
{
    
    float *matrix_a = malloc(1536*1536*sizeof(float));
    float *matrix_b = malloc(1536*1536*sizeof(float));

    // __m128 va, vb, vresult;

    // initialize matrix_a and matrix_b
    for (int i = 0; i < 2359296; i++) 
    {
        
        *(matrix_a+i) = 0.1f;
        *(matrix_b+i) = 0.2f;
        
    }
    
    // initialize result matrix
    for (int i = 0; i < 1536; i++) 
    {
        for (int j = 0; j < 1536; j++) 
        {
            result[i][j] = 0;
        }
    }

    for (int i = 0; i < 1536; i++) 
    {
        for (int j = 0; j < 1536; j++) 
        {
            for (int k = 0; k < 1536; k++) 
            {
                result[i][j] = result[i][j] +  (matrix_a[i][k] *  matrix_b[k][j]);
            }
        }
    }
    
    // print result matrix
    for (int i = 0; i < 1536; i++) 
    {
        for (int j = 0; j < 1536; j++) 
        {
            //printf("%f ", result[i][j]);
        }
        //printf("\n");
    }
    
    return 0;
}
