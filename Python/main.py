import nmap
nmScan = nmap.PortScanner()

nmScan.scan('127.0.0.1', '21-443')