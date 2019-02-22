import socket
import os

# host to listen on
host = "192.168.192.25"
# create raw socket and bind to public interface
if os.name == "nt":
    socket_protocol = socket.IPPROTO_IP
else:
    socket_protocol = socket.IPPROTO_ICMP

sniffer = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket_protocol)

sniffer.bind((host, 0))

# include packet header
sniffer.setsockopt(socket.IPPROTO_IP, socket.IP_HDRINCL, 1)

# when using windows, send ioctl to setup promiscuous mode
if os.name == "nt":
    sniffer.ioctl(socket.SIO_RCVALL, socket.RCVALL_ON)

# receive single packet
print(sniffer.recvfrom(65565))

# when using windows, turn off promiscuous mode
if os.name == "nt":
    sniffer.ioctl(socket.SIO_RCVALL, socket.RCVALL_OFF)
