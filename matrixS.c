//
// Matrix Multiplication using SSE3 Instruction 
//

#include <x86intrin.h>
#include <stdio.h>
#include <stdlib.h>

float result[1536][1536];
    
int main(int argc, char **argv) 
{
    
    float *matrix_a = malloc(1536*1536*sizeof(float));
    float *matrix_b = malloc(1536*1536*sizeof(float));

    __m128 va, vb, vresult;

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
            for (int k = 0; k < 1536; k += 4) 
            {
                
                // load 4 float data in XMM registers
                va = _mm_loadu_ps(matrix_a+(i*1536)+k); // matrix_a[i][k]
                vb = _mm_loadu_ps(matrix_b+(j*1536)+k); // matrix_b[j][k]

                // multiply two registers (4 float operations)
                vresult = _mm_mul_ps(va, vb);

                // add all results in one value
                vresult = _mm_hadd_ps(vresult, vresult);
                vresult = _mm_hadd_ps(vresult, vresult);

                // store value in result[i][j] matrix
                result[i][j] += _mm_cvtss_f32(vresult);
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
