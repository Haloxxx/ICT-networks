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

        /*uint8_t digit = 0;

        vector<uint8_t> vectorOfdigits;

        for(int i =0; i<size-1; ++i)
        {
            uint8_t operative;
            operative = memblock[i];

            digit = operative + memblock[i+1];

            cout<<"digit = "<<int(digit)<<'\n';

            vectorOfdigits.push_back(digit);
        }

        if(size%2) vectorOfdigits.push_back(memblock[size-1]);
        else
        {
            vectorOfdigits[size-1]+=memblock[size-1];
        }

        for(int i = 0; i<vectorOfdigits.size(); ++i) cout<<vectorOfdigits[i]<<" ";
        cout<<"\n\n\n";


        vectorOfdigits.push_back(1);
        vectorOfdigits.push_back(2);
        vectorOfdigits.push_back(3);
        vectorOfdigits.push_back(4);
*/

        int result2 = 0;

        //cout<<"test = "<<result2+memblock[0]<<'\n';

        for(int i = 0; i<size; ++i)
        {
            result2+=value*memblock[i];
            //cout<<"memblock[i] = "<<memblock[i]<<" "<<"result2 = "<<result2<<'\n';

            value +=addon;
            addon*=-1;

            //cout<<"value = "<<value<<'\n';
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
