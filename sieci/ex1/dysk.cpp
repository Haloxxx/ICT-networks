#include <iostream>
#include <fstream>
#include <vector>

using namespace std;





int main()
{
    streampos size;
    char* memblock;

    int result = 0;


    ifstream file ("plik.bin", ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char [size];
        file.seekg (0, ios::beg);
        file.read(memblock, size);
        file.close();


        int example = 1;

        for(int i = 0; i<size; ++i)
        {
            if(memblock[i] && example) result=(result+1)%2;

            example = example<<1;
        }


        ///Control
        /*for(int i = 0; i<size; ++i)
        {
            cout<<memblock[i]<<'\n';
        }

        cout<<"\n\n\n";
*/

        //result=result xor 1;


        ////////////////////
        ////Suma modulo/////////
        ///////////////////////

        int value = 2;
        int addon = -1;


        int result2 = 0;


        for(int i = 0; i<size; ++i)
        {
            result2+=value*memblock[i];
            

            value +=addon;
            addon*=-1;

            
        }
        result2%=10;

        cout<<"Suma modulo = "<<result2<<'\n';
        //////////////
        ///////////////
        //////////////



        //////////////////
        //////CRC//////
        /////////////////

        int divider = 11;




        /////////////////
        //////////////////
        ////////////////


        delete[] memblock;
    }
    else cout<<"Unable to open the file\n";

    cout<<"\nBit = "<<result<<'\n';
}
