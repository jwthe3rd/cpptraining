#include <math.h>
#include <iostream>
#include <tuple>


using namespace std;

void mat_mul(float *result, float *mat1, float*mat2, tuple<int, int> dims1, 
                tuple<int, int> dims2)
{

    int rows1 = get<0>(dims1);
    int cols1 = get<1>(dims1);
    int cols2 = get<1>(dims2);

    for (int i=0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            float count = 0;
            for (int k=0; k < cols1; k++)
            {
                count += mat1[i * cols1 + k]*mat2[k*cols2 + j];
            } 
        result[i*cols2 + j] = count;
        }
    }

}


int main()
{

    int a = 3;
    int b = 3;
    int c = 2;

    float m1[a][b];
    float m2[b][c];
    float res[a][c];

    tuple<int, int> d1;tuple<int,int> d2;

    d1 = make_tuple(a,b);
    d2 = make_tuple(b,c);

    for (int i=0; i<a; i++)
    {
        for (int j=0; j<b; j++)
        {
            m1[i][j] = i*j+2;
        }
    }

    for (int i=0; i<b; i++)
    {
        for (int j=0; j<c; j++)
        {
            m2[i][j] = i*j+2;
        }
    }

    mat_mul((float*)res, (float*)m1, (float*)m2, d1, d2);

    // After initialization, add:
cout << "Matrix res:" << endl;
for (int i = 0; i < a; i++) {
    for (int j = 0; j < c; j++) {
        cout << res[i][j] << " ";
    }
    cout << endl;
}


    return 0;
}