#include <tins/tins.h>
#include <iostream>
#include <stddef.h>

using namespace Tins;

int counter = 1;

bool handler(const PDU& pkt) {
    // Lookup the UDP PDU
    const EthernetII &ethii = pkt.rfind_pdu<EthernetII>();
    std::cout<<"\nEthernet II:\nAdres źrodła: "<<ethii.src_addr()<<" Adres urządzenia docelowego: "<<ethii.dst_addr()<<'\n';
    
    uint8_t protocol = 0;
    try{
        const IP &ip = pkt.rfind_pdu<IP>();
        std::cout<<"    IP:\n    Wersja: "<<int(ip.version())<<" Adres źrodła: "<<ip.src_addr()<<" Adres urządzenia docelowego: "<<ip.dst_addr()<<" Protokoł: "<<int(protocol = ip.protocol())<<'\n';
    }
    catch(exception_base e){
        const ICMP &icmp = pkt.rfind_pdu<ICMP>();
        std::cout<<"    ICMP:\n    Typ: "<<int(icmp.type())<<" Kod: "<<icmp.code()<<'\n';
    }
    


    switch(int(protocol)){

        case 6: {
            const TCP &tcp = pkt.rfind_pdu<TCP>();
            std::cout<<"        TCP:\n        Port źrodła: "<<int(tcp.sport())<<" Port urządzenia docelowego: "<<tcp.dport()<<'\n';
            break;
        }
        case 17: {
            const UDP &udp = pkt.rfind_pdu<UDP>();
            std::cout<<"        UDP:\n        Port źrodła: "<<int(udp.sport())<<" Port urządzenia docelowego: "<<udp.dport()<<'\n';
            break;
        }
    }
    
    try{

        DNS dns = pkt.rfind_pdu<RawPDU>().to<DNS>();
        std::cout<<"                DNS\n";
    } catch(exception_base){
        try{
            const DHCP &dhcp = pkt.rfind_pdu<DHCP>();
            std::cout<<"                DHCP\n";
        }

        catch(exception_base){
            std::cout<<"                HTTP\n";
        }
    }


    
    


    counter++;
    return true;
}

int main() {

    SnifferConfiguration config;
    Sniffer sniffer("en0", config);


    sniffer.sniff_loop(handler);
}