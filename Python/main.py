import nmap
nmScan = nmap.PortScanner()

print(nmScan.scan('127.0.0.1', '21-443'))