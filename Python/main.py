import nmap

# initialize the port scanner
nmScan = nmap.PortScanner()
ip = '192.168.192.'
ip += str(input())
# scan localhost for ports in range 21-443
nmScan.scan(ip, '21-443')

# run a loop to print all the found result about the ports
for host in nmScan.all_hosts():
    print('Host : %s (%s)' % (host, nmScan[host].hostname()))
    print('State : %s' % nmScan[host].state())
    for proto in nmScan[host].all_protocols():
        print('----------')
        print('Protocol : %s' % proto)

        lport = nmScan[host][proto].keys()
        lport.sort()
        for port in lport:
            print ('port : %s\tstate : %s' % (port, nmScan[host][proto][port]['state']))