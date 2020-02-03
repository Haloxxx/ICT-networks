#include <iostream>
#include <fstream>
#include <random>

using namespace std;


int parity_bit(char* memblock, int size)
{
    int result = 0;
    int example = 1;

        for(int i = 0; i<size; ++i)
        {
            if(memblock[i] && example) result=(result+1)%2;

            example = example<<1;

            //cout<<"iteracja\n";
        }

    return result xor 1;
}

int modulo(char* memblock, int size)
{
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

    return result2;
}


int crc(char* memblock, int divider, int size)
{
    int result = 0;

    for(int i = 0; i<size; ++i)
    {
        memblock[i] = memblock[i] xor divider;
    }


    return 0 xor divider;
}

char error1 (char memblock, int size, double percent)
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 7);
    

    int result = 1;

    for(int i = 0; i<size*percent+1; ++i)
    {
        result=1;
        result = result<<dist(rd);
    }

    return memblock xor result;
}

char error2 (char memblock, int size, double percent)
{

}



int main()
{
    streampos size;
    char* memblock;

    int result = 0;


    ifstream file ("test.MOV", ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char [int(size)+1];
        file.seekg (0, ios::beg);
        file.read(memblock, size);
        file.close();


        cout<<"Rozmiar = "<<size<<'\n';


        int variant = 0;

        std::cout<<"Podaj sumę kontrolną: ";
        std::cin>>variant;

        int result = 0;

        switch(variant)
        {
            case 1:
            {
                result = parity_bit(memblock, int(size));
                break;
            }

            case 2:
            {
                result = modulo(memblock, int(size));
                break;
            }

            case 3:
            {
                //crc(memblock, int(size));
                break;
            }


        }

        cout<<result<<'\n';

        //char* output = new char[int(size)+1];
        
        //for(int i = 0; i<size; ++i) output[i]=memblock[i];
        //output[size]=result;


        memblock[size]=result;

        ofstream file2 ("wynik.bin", ios::binary);
        file2.write(reinterpret_cast<char*>(&memblock), sizeof memblock);
        //file2<<memblock<<result;
        file2.close();


        ifstream file3 ("wynik.bin", ios::in|ios::binary|ios::ate);
        if (file3.is_open())
        {
            streampos size2;
            char* memblock2;

            size2 = file3.tellg();
            memblock2 = new char [size2];
            file3.seekg (0, ios::beg);
            file3.read(reinterpret_cast<char*>(&memblock2), size2);
            file3.close();

            cout<<memblock2<<" size2 = "<<size2<<'\n';

            
        }



    }
    else cout<<"Unable to open the file\n";
}