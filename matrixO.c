//
// Matrix Multiplication using AVX Instruction + OpenMP Libraby
//

#include <x86intrin.h> 
#include <stdio.h>
#include <stdlib.h>

float *matrix_a;
float *matrix_b;
float result[1536][1536];

void chunked_mm(int chunk, int n_chunks) 
{
    __m256 va, vb, vtemp;
    __m128 vlow, vhigh, vresult;
    for (int i = chunk*(1536/n_chunks); i < (chunk+1)*(1536/n_chunks); i++) 
    {
        for (int j = 0; j < 1536; j++) 
        {
            for (int k = 0; k < 1536; k += 8) 
            {
                
                // load 8 float data in XMM registers
                va = _mm256_loadu_ps(matrix_a+(i*1536)+k); // matrix_a[i][k]
                vb = _mm256_loadu_ps(matrix_b+(j*1536)+k); // matrix_b[j][k]

                // multiply two registers (8 float operations)
                vtemp = _mm256_mul_ps(va, vb);

                // extract higher four floats
                vhigh = _mm256_extractf128_ps(vtemp, 1); // high 128
                
                // add higher four floats to lower floats
                vresult = _mm_add_ps(_mm256_castps256_ps128(vtemp), vhigh);
                
                // add all results in one value
                vresult = _mm_hadd_ps(vresult, vresult);
                vresult = _mm_hadd_ps(vresult, vresult);

                // store value in result[i][j] matrix
                result[i][j] += _mm_cvtss_f32(vresult);
                
            }
        }
    }
}

int main(int argc, char **argv) 
{

    // initialize matrix_a and matrix_b
    matrix_a = malloc(1536*1536*sizeof(float));
    matrix_b = malloc(1536*1536*sizeof(float));

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

    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < 4; i++) 
    {
        chunked_mm(i, 4);
    }
    
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
