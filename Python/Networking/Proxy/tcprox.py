import sys
import socket
import threading

from numpy import unicode
from pip._vendor.urllib3.connectionpool import xrange


def server_loop(local_host,local_port,remote_host,remote_port,receive_first):
    server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

    try:
        server.bind((local_host,local_port))

    except:
        print("[!!] failed to listen on &s:%d"% local_host,local_port)
        sys.exit(0)

    print("listening on &s:%d"% local_host,local_port)
    server.listen(5)

    while True:
        client_socket, addr = server.accept()
        print("[==>] received incoming connection from %s:&d"% addr[0],addr[1])
        proxy_thread = threading.Thread(target=proxy_handler, args=(client_socket,remote_host,remote_port,receive_first))

        proxy_thread.start()

def proxy_handler(client_socket,remote_host,remote_port,receive_first):

    # connect to remote host
    remote_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    remote_socket.connect((remote_host,remote_port))


    # receive data from remote if needed
    remote_buffer = receive_from(remote_socket)
    hexdump(remote_buffer)

    #if we have data, send to our local client
    if len(remote_buffer):
        print("[<==] Sending %s bytes to localhost") % len(remote_buffer)
        client_socket.send(remote_buffer)

    while True:

        local_buffer = receive_from(client_socket)

        if len(local_buffer):
            print("[==> received %d from localhost]" %len(local_buffer))
            hexdump(local_buffer)

            local_buffer = request_handler(local_buffer)

            remote_socket.send(local_buffer)
            print("[==> Send to remote]")

        remote_buffer = receive_from(remote_socket)

        if len(remote_buffer):

            hexdump(remote_buffer)

            remote_buffer = response_handler(remote_buffer)

            client_socket.send(remote_buffer)

            print("[<==] Send to localhost")

        if not len(local_buffer) or not (remote_buffer):
            client_socket.close()
            remote_socket.close()
            print("[*] No more data")

            break

def hexdump(src, lenght=16):

    result = []
    digits = 4 if isinstance(src,unicode) else 2

    for i in xrange(0, len(src),lenght):
        s = src[i:i+lenght]
        hexa = b''.join(["50*X" % (digits,ord(x)) for x in s])
        text = b''.join([x if 0x20 <= ord(x) < 0x7F else b'.' for  x in s])
        result.append(b"%04X %-*s %s" % (i,lenght*(digits + 1), hexa, text))

    print(b'\n'.join(result))

def receive_from(connection):

    buffer = ""

    connection.settimeout(2)

    try:
        while True:
            data = connection.recv(4096)

            if not data:
                break

            buffer += data

    except:
        pass

    return buffer

def request_handler(buffer):
    return buffer

def response_handler(buffer):
    return buffer

def Main():

    if len(sys.argv[1:]) != 5:
        print("Usage: ./tcprox.py [localhost] [localport] [remotehost] [remoteport] [receive_first]")
        print("Example: ./tcprox 127.0.0.1 9000 8.8.8.8 9000 True")

        #setup local listening params
        local_host = sys.argv[1]
        local_port = int(sys.argv[2])

        # setup remote params
        remote_host = sys.argv[3]
        remote_port = int(sys.argv[4])

        receive_first = sys.argv[5]

        if "True" in receive_first:
            receive_first = True
        else:
            receive_first = False

            server_loop(local_host,local_port,remote_host,remote_port,receive_first)
Main()
