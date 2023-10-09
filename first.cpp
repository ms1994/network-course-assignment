#include <bits/stdc++.h>
#define sz(a) ((int)((a).size()))
/*
 *Asignacion numero 1 del curso.
 *
 * */
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
// mt19937 rnd(239);
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
 
typedef long long ll;
typedef long double ld;
 
void get_broadcast_address(char *ip_addr, int mask, char *output_buffer) {
    // fist network id
    struct in_addr ip, netmask, network, broadcast;
    char resp[20];
    // Convert strings to in_addr structs
    inet_aton(ip_addr, &ip);

    // Calculate netmask from CIDR
    if (mask > 0 && mask <= 32) {
        // negative of 32 - masks menos 1 shift to left
        netmask.s_addr = htonl(~((1 << (32 - mask)) - 1));
    } else {
        printf("Invalid CIDR value\n");
        return;
    }
    // calculate network_id and operation between ip and netsubmask
    network.s_addr = ip.s_addr & netmask.s_addr;

    // Calculate broadcast address: ip OR (NOT netmask) o puedes user network address
    //broadcast.s_addr = ip.s_addr | ~netmask.s_addr;
    broadcast.s_addr = network.s_addr | ~netmask.s_addr;
    char *temp = inet_ntoa(broadcast);
    
    //strncpy(output_buffer, temp, 49);
    //output_buffer[sizeof(output_buffer) - 1] = '\0';  // Ensure null termination
    //printf("dentro de la funcion %s\n", output_buffer);
    strncpy(resp, temp, sizeof(resp) - 1);
    resp[sizeof(resp) - 1] = '\0';
    for (int i = 0; i < (int) sizeof(resp); i++) {
        output_buffer[i] = resp[i];
    }
    return;
}

unsigned long get_ip_integer_equivalent(char* ip_add) {
    unsigned long integer_ip;
    integer_ip = ntohl(inet_addr(ip_add));
    return integer_ip;
}

void get_abcd_ip_format(unsigned int ip_int, char* buffer) {
     struct in_addr ip_addr;

    // Convert integer to in_addr struct
    ip_addr.s_addr = htonl(ip_int);

    // Convert in_addr struct to string
    const char *ip_str = inet_ntoa(ip_addr);

    // Copy string to buffer
    strncpy(buffer, ip_str, strlen(ip_str) + 1);
}

unsigned int get_subnet_cardinality(int mask) {
    // Calculate subnet cardinality: 2^(32 - CIDR) - 2
    return pow(2, (32 - mask)) - 2;
}

int check_ip_subnet_membership(char * network_id, int mask, char * ip_add) {
    struct in_addr ip, network, netmask;

    // Convert strings to in_addr structs
    inet_aton(ip_add, &ip);
    inet_aton(network_id, &network);

    // Calculate netmask from CIDR
    if (mask > 0 && mask <= 32) {
        netmask.s_addr = htonl(~((1 << (32 - mask)) - 1));
    } else {
        printf("Invalid CIDR value\n");
        return -1;
    }

    // Check if ip AND netmask equals network AND netmask
    if ((ip.s_addr & netmask.s_addr) == (network.s_addr & netmask.s_addr)) {
        return 0;  // IP is in subnet
    } else {
        return -1;  // IP is not in subnet
    }

}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    char *ip_addr = "192.168.2.10"; 
    int masks = 20;
    char ip_buffer[20];
    memset(ip_buffer, 0, sizeof(ip_buffer));
    get_broadcast_address(ip_addr, masks,ip_buffer);
    printf("broadcast buffer %s\n", ip_buffer);
    unsigned long integer_ip = get_ip_integer_equivalent(ip_addr);
    printf("inter value of %s is %lu\n", ip_addr, integer_ip);
    memset(ip_buffer, 0, sizeof(ip_buffer));
    unsigned int ip_int = 2058138165;
    get_abcd_ip_format(ip_int, ip_buffer);
    printf("abcd format is %s\n", ip_buffer);
    printf("subnet cardinatilty is %u\n", get_subnet_cardinality(masks));

    char* network_id = "192.168.0.0";
    int mask2 = 24;
    char* check_ip = "192.168.0.13";
    int result = check_ip_subnet_membership(network_id, mask2, check_ip);
    if (result == 0) {
        printf("Belongs to the subnet");
    }
    else printf("Do not belong to the subnet");

    return 0;
}
