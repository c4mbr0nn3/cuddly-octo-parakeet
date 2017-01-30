#include <iostream>
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))
#include<array>

using namespace std;

int main()
{
    int k = 9;
    string a= "red";
    string b= "BLUE";
    string c;
    int j;

    string gino [2*k];

    for (int i=0; i<2*k; i=i+2) // populate array
    {
        gino[i]=a;
        gino[i+1]=b;
    }

    cout << ARRAY_SIZE(gino) << endl;

    for (int i=0; i < ARRAY_SIZE(gino); ++i)  // print array not sorted
    {
        cout << gino[i] << endl;
    }

    for (int i=1; i<2*k-2;++i)  // sort array
    {
        if (gino[i]!=gino[i+1])
        {
            c= gino[i];
            gino[i]=gino[i+1];
            gino[i+1]=c;
            j=i;
            while (gino[j]!=gino[j-1])
            {
                c=gino[j-1];
                gino[j-1]=gino[j];
                gino[j]=c;
                --j;
            }
            j=0;
        }
    }
    for (int i=0; i < ARRAY_SIZE(gino); ++i) // print sorted array
    {
        cout << gino[i] << endl;
    }
    return 0;
}
