import nmap
nmScan = nmap.PortScanner()

print(nmScan['127.0.0.1']['hostnames'].keys())