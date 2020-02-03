#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <random>


int packetSize = 2;

namespace fs = std::filesystem;

#pragma pack(push, 1)
struct packet
{
    uint8_t number;
    uint8_t sizeofData;
};
#pragma pack(pop)


template<class T>
char* as_bytes(T& i) 
{
    void* addr = &i; 
    return static_cast<char*>(addr);
}


std::vector<uint8_t> readFile(std::string file_path)
{
    fs::path p = fs::current_path()/file_path;
    int size = fs::file_size(p)+1;

    std::vector<uint8_t> memblock(size-1);

    std::ifstream file (file_path, std::ios_base::binary);

    if(file.is_open())
    {
        int for_loop_iterator = 0;
        for(uint8_t x; file.read(as_bytes(x),sizeof(uint8_t));)
            {memblock[for_loop_iterator]=x; ++for_loop_iterator;}

    } else std::cout<<"Nie udało się\n";

    return memblock;
}

int writeFile(std::string file_path, std::vector<int> indexes, std::vector<uint8_t> memblock)
{
    int wsize = memblock.size()+int(memblock.size()/2)*sizeof(packet);

    std::ofstream file (file_path);

    for(int i : indexes)
    {
        packet part;
        part.number = i;
        part.sizeofData = 2;
        if(wsize%2 && i==wsize-1) part.sizeofData = 1;

        //file.write(part, sizeof(part)); //zapisywać bezpośrednio!
        file.write(reinterpret_cast<char*>(&part), sizeof(packet));
        file.write(as_bytes(memblock[i]), sizeof(uint8_t));
    }

    return 0;
}

uint8_t* writeBlock(std::string file_path, std::vector<int> indexes, std::vector<uint8_t> memblock)
{
    /*uint8_t * buffer;
    buffer = new uint8_t[sizeof(packet) + 2];
    packet* SP1 = (packet*)buffer;
    uint8_t * d = (uint8_t*)(SP1 + 1);

    packet pakiecik;
    pakiecik.number = indexes[0];
    pakiecik.sizeofData = 2;

    *SP1 =  pakiecik;
    *d = memblock[pakiecik.number]; 

    buffer[0]=pakiecik.number;
    buffer[1] = pakiecik.sizeofData;
    buffer[2] = memblock[pakiecik.number];
    buffer[3] = memblock[pakiecik.number+1];


    for(int i =0; i< 4; ++i)
    {
        std::cout<<(int) memblock[i]<<": "<<(int)buffer[i]<<" ";
    }*/
    int reminder = 0;

    //std::cout<<"memblock.size() "<<memblock.size()<<'\n';
    //std::cout<<"memblock.size() "<<memblock.size()/packetSize<<'\n';

    uint8_t * buffer;
    //std::cout<<"test1\n";

    if(memblock.size()%packetSize) 
    {
        //++bufferSize;
        reminder = 1;
    }

    int bufferSize = memblock.size() + sizeof(packet)*(int(memblock.size()/packetSize)+reminder);
    //std::cout<<"test\n";
    
    buffer = new uint8_t[bufferSize];
    //std::cout<<"buffersize = "<<bufferSize<<'\n';
    
    int prev_iter = 0;

    for(int i = 0; i<(memblock.size()/packetSize+reminder); ++i)
    {
        packet head;
        head.number = i;
        head.sizeofData = packetSize;
        
        if(memblock.size()%packetSize && i==memblock.size()-1) head.sizeofData = packetSize-(memblock.size()%packetSize);

        buffer[prev_iter]=head.number;
        buffer[prev_iter+1]=head.sizeofData;
        for(int j = 1; j<=head.sizeofData; ++j)
        {
            buffer[prev_iter+1+j] = memblock[packetSize*i+j-1];
            //std::cout<<memblock[i+j-1]<<" iterator = "<<i+j-1<<'\n';
        }
        prev_iter = prev_iter+sizeof(packet)+head.sizeofData;
        //std::cout<<"prev = "<<prev_iter<<'\n';
    }


    return buffer;
}

uint8_t* readBlock(uint8_t * buffer, int fileSize, int bufferSize)
{
    uint8_t * result;
    result = new uint8_t[fileSize];
    /*packet* SP1 = (packet*)buffer;
    uint8_t * d = (uint8_t*)(SP1 + 1);//[(*SP1).sizeofData];

    std::cout<<"\nb1 = "<<(int)buffer[4];
    std::cout<<"\ndane = "<<d<<'\n';*/
    //std::cout<<"sp1 = "<<*SP1<<'\n';

    int prev_iter = 0;
    int sec_iter = 0;
    int i = 0;
    
    while(i < (bufferSize-fileSize)/sizeof(packet))
    {
        packet head;
        head.number = buffer[prev_iter];
        head.sizeofData = buffer[prev_iter+1];

        //std::cout<<'\n';

        if(head.number == i)
        {
            for(int j = 1; j<=head.sizeofData; ++j)
            {
                //std::cout<<"\ntest = "<<(bufferSize-fileSize)/sizeof(packet)<<'\n';
                result[sec_iter+j-1] = buffer[prev_iter+1+j];
                //std::cout<<buffer[prev_iter+1+j]<<" iterator = "<<sec_iter+j-1<<'\n';
            }
        }
        else{
            for(int j = 1; j<=head.sizeofData; ++j)
            {
                result[packetSize*head.number+j-1] = buffer[prev_iter+1+j];
            }
        }
        prev_iter = prev_iter+sizeof(packet)+head.sizeofData;
        sec_iter = sec_iter + head.sizeofData;

        ++i;
    }

    return result;
}

/*auto readcorr(std::string file_path)
{
    fs::path p = fs::current_path()/file_path;
    int size = fs::file_size(p);

    std::ifstream file (file_path, std::ios_base::binary);

    if(file.is_open())
    {
        int i = 0;
        while(file){

        
            if (auto p = std::malloc(size)){
                packet portion;
                file.read(reinterpret_cast<char*>(p), sizeof(packet));
                if(portion.number == i)
                {
                    //*(packet *)p = portion;
                    char* data = new char(portion.sizeofData);
                    file.read(reinterpret_cast<char*>(p)+sizeof(portion)), sizeof(portion.sizeofData));  
                    //*(char *)(p+(packet*)) = data;
                }

            }

            ++i;
        }


    } else std::cout<<"Nie udało się\n";

    return p;
}*/


struct error_result{

    std::vector<uint8_t> memblock;
    std::vector<int> indexes;
};


error_result error(std::vector<uint8_t> memblock)
{
    std::vector<int> indexes (memblock.size());

    for(int i = 0; i<indexes.size(); ++i)
        indexes[i] = i;

    std::random_device rd;

    
    for(int i =0; i<(indexes.size()/10); ++i)
    {
        std::uniform_int_distribution<int> r1 (0, indexes.size());

        int p1 = r1(rd);
        int p2 = r1(rd);

        int copy = -2;

        copy = indexes[p1];
        indexes[p1]=indexes[p2];
        indexes[p2]=copy;

        uint8_t data_copy = memblock[p1];
        memblock[p1]=memblock[p2];
        memblock[p2]=memblock[p1];

    }

    error_result result;
    result.indexes = indexes;
    result.memblock = memblock;

    return result;

}

uint8_t* blockError(uint8_t * buffer, int buffersize)
{
    int allowed = buffersize/packetSize * packetSize;
    //int allowed = packetSize+sizeof(packet)-1+2*(sizeof(packet)+packetSize);

    uint8_t* copy = new uint8_t[packetSize+sizeof(packet)];

    //if((packetSize+sizeof(packet))*3<=allowed)
    if(packetSize+sizeof(packet)-1+2*(sizeof(packet)+packetSize)<=allowed)
    {
        for(int i = 0; i < packetSize+sizeof(packet); ++i)
        {
            copy[i] = buffer[i];
        }

        //std::cout<<"\ncopy:\n";
        //for(int i = 0; i < packetSize+sizeof(packet); ++i)
            //std::cout<<(int)copy[i]<<" ";

        for(int i =0; i < packetSize+sizeof(packet); ++i)
        {
            //buffer[i] = buffer[i+buffersize-(packetSize+sizeof(packet))];
            buffer[i] = buffer[i+2*(sizeof(packet)+packetSize)];
            //std::cout<<"\nczemu: "<<(int)buffer[i+buffersize-(packetSize+sizeof(packet))];
        }

        for(int i =0; i < packetSize+sizeof(packet); ++i)
        {
            //buffer[i+buffersize-(packetSize+sizeof(packet))] = copy[i];
            buffer[i+2*(sizeof(packet)+packetSize)] = copy[i];
        }
    }

    return buffer;
}


int main()
{

    std::vector<uint8_t> memblock = readFile("plik.bin");

    int fileSize = memblock.size();


    int reminder = 0;

    if(memblock.size()%packetSize) 
    {
        //++bufferSize;
        reminder = 1;
    }

    int bufferSize = memblock.size() + sizeof(packet)*(int(memblock.size()/packetSize)+reminder);

    std::vector<int> indexes (memblock.size());

    for(int i = 0; i<indexes.size(); ++i)
        indexes[i] = i;

    for(uint8_t x : memblock)
        std::cout<<(int)x<<" ";

    std::cout<<" \n";

    uint8_t* buffer = writeBlock("wynik.bin",indexes,memblock);

    std::cout<<'\n';
    for(int i =0; i< bufferSize; ++i)
        std::cout<<(int)buffer[i]<<" ";

    uint8_t* error = blockError(buffer, bufferSize);

    std::cout<<"\nbłędy:\n";
    for(int i =0; i< bufferSize; ++i)
        std::cout<<(int)buffer[i]<<" ";

    uint8_t* transmitted = readBlock(buffer, fileSize, bufferSize);

    std::cout<<'\n';
    std::cout<<'\n';
    std::cout<<'\n';
    for(int i =0; i< fileSize; ++i)
        std::cout<<(int)transmitted[i]<<" ";



}