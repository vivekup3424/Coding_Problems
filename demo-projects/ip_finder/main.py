import os
import sys
import socket
import psutil
import ipaddress
from scapy.all import ARP, Ether, srp  # type: ignore

def get_interfaces() -> list[dict[str, str]]:
    """Lists available network interfaces with their IP addresses."""
    interfaces: list[dict[str, str]] = []
    for iface, addrs in psutil.net_if_addrs().items():
        for addr in addrs:
            if addr.family == socket.AF_INET and addr.netmask: # IPv4 only
                interfaces.append({
                    "name": iface,
                    "ip": addr.address,
                    "mask": addr.netmask
                })
    return interfaces

def scan_network(interface_ip: str, netmask: str) -> dict[str, dict[str, str]]:
    """Performs an ARP scan on the subnet and resolves hostnames."""
    print(f"Scanning subnet associated with {interface_ip}...")
    
    # Calculate CIDR range (e.g., 192.168.1.0/24)
    network = ipaddress.IPv4Interface(f"{interface_ip}/{netmask}").network
    
    # Create ARP packet
    arp = ARP(pdst=str(network))  # type: ignore
    ether = Ether(dst="ff:ff:ff:ff:ff:ff")  # type: ignore
    packet = ether/arp  # type: ignore

    # Send packet and capture responses
    result = srp(packet, timeout=3, verbose=0)[0]  # type: ignore

    devices: dict[str, dict[str, str]] = {}
    for _, received in result:
        ip = received.psrc
        mac = received.hwsrc
        try:
            # Attempt to resolve hostname
            hostname = socket.gethostbyaddr(ip)[0]
        except (socket.herror, socket.gaierror):
            hostname = "Unknown"
        
        devices[ip] = {"mac": mac, "hostname": hostname}
    
    return devices

def main():
    if os.getuid() != 0 if hasattr(os, 'getuid') else False:
        print("Error: This script must be run with sudo/administrator privileges.")
        sys.exit(1)

    # 1. Choose Interface
    ifaces = get_interfaces()
    print("\nAvailable Network Interfaces:")
    for i, iface in enumerate(ifaces):
        print(f"[{i}] {iface['name']} - IP: {iface['ip']}")

    choice = int(input("\nSelect the interface index connected to the LAN: "))
    selected = ifaces[choice]

    # 2. First Scan (With Pi connected)
    print("\n--- STEP 1 ---")
    input(f"Ensure the Raspberry Pi is CONNECTED to the LAN, then press Enter to scan...")
    scan1 = scan_network(selected['ip'], selected['mask'])
    print(f"Found {len(scan1)} devices.")

    # 3. Second Scan (With Pi disconnected)
    print("\n--- STEP 2 ---")
    input("Now, DISCONNECT the Raspberry Pi from the LAN, then press Enter to scan again...")
    scan2 = scan_network(selected['ip'], selected['mask'])
    print(f"Found {len(scan2)} devices.")

    # 4. Find the difference
    print("\n--- RESULTS ---")
    # The Pi is the IP that was in scan1 but is NOT in scan2
    missing_ips = set(scan1.keys()) - set(scan2.keys())

    if not missing_ips:
        print("No difference found. Try increasing the scan timeout or ensure the Pi was active.")
    else:
        for ip in missing_ips:
            device = scan1[ip]
            print(f"FOUND DEVICE (Now Missing):")
            print(f"  IP Address: {ip}")
            print(f"  Hostname:   {device['hostname']}")
            print(f"  MAC Vendor: {device['mac']}")
            
            # Raspberry Pi 5 MAC addresses often start with these prefixes
            if device['mac'].lower().startswith(("d8:3a:dd", "dc:a6:32")):
                print("  Note: MAC prefix matches Raspberry Pi Foundation!")

if __name__ == "__main__":
    main()