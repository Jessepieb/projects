#!/opt/local/bin/python2.7

import sys
import socket
import getopt
import threading
import subprocess
import random


# define some global variables

listen = False
target = ""
port = 0
srvamount = 3
serverports = [8001,8002]
colors = ["Green", "Blue", "Red"]


def proxy_handler(client_socket,):
    # connect to remote host
    remote_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    remote_socket.connect(("127.0.0.1", 8002))
    print(remote_socket)
    print(client_socket)
    # receive data from remote if needed
    remote_buffer = receive_from(client_socket)
    #print("remote buffer: "+ remote_buffer)
    #hexdump(remote_buffer,len(remote_buffer))

    #if we have data, send to our local client
    if len(remote_buffer):
        remote_socket.send(remote_buffer)

    while True:

        local_buffer = receive_from(remote_socket)
        print(local_buffer)
        if len(local_buffer):
            print("[==> received {0} from localhost]".format(local_buffer))
            #hexdump(local_buffer)

            local_buffer = request_handler(local_buffer)

            remote_socket.send(local_buffer)
            print("[==> Send to remote]")

        remote_buffer = receive_from(client_socket)

        if len(remote_buffer):
            #hexdump(remote_buffer)
            print("remote buff")
            remote_buffer = response_handler(remote_buffer)
            print(len(remote_buffer))
            client_socket.send(remote_buffer)

            print("[<==] Send to localhost")

        if not len(local_buffer) or not (remote_buffer):
            client_socket.close()
            remote_socket.close()
            print("[*] No more data")

            break
#
#
# def hexdump(src, lenght=16):
#     result = []
#     from numpy import unicode
#     digits = 4 if isinstance(src, unicode) else 2
#
#     from numpy.core.tests.test_mem_overlap import xrange
#     for i in xrange(0, len(src), lenght):
#         s = src[i:i + lenght]
#         hexa = b''.join(["50*X" % (digits, ord(x)) for x in s])
#         text = b''.join([x if 0x20 <= ord(x) < 0x7F else b'.' for x in s])
#         result.append(b"%04X %-*s %s" % (i, lenght * (digits + 1), hexa, text))
#
#     print(b'\n'.join(result))
#     return result


def receive_from(connection):
    print("test")
    connection.settimeout(5 )
    buffer = None
    try:
        while True:
            print("receiving..")
            data = connection.recv(4096)
            #print("data: {0}".format(data))
            buffer += data

            if not data:
                pass
    except:
        pass
    return data


def request_handler(buffer):
    print("reuquest handler")
    return buffer


def response_handler(buffer):
    print("response handler")
    return buffer


# this is for incoming connections
def server_loop():

    global target
    global port

    # if no target is defined we listen on all interfaces
    if not len(target):
        target = "0.0.0.0"

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        server.bind((target, port))
        print("server bound to {0}:{1}".format(target,port))
    except:
        print("couldn't bind the server")

    # for i in range(srvamount):
    #
    #     serverthread = threading.Thread(target=server_handler(i))
    #     serverthread.

    server.listen(5)
    while True:
        client_socket, addr = server.accept()
        print("incoming connection...")
        # spin off a thread to handle our new client
        client_thread = threading.Thread(target=proxy_handler(client_socket,), args=(client_socket,))
        client_thread.start()

# def serverbuilder(amount):


def usage():
    print("Usage: Portforwarder.py -t target_host -p port")
    print("-l --listen   - listen on [host]:[port] for incoming connections")
    print
    print("Examples: ")
    print("Portforwarder.py -t 192.168.0.1 -p 5555 -l")
    sys.exit(0)


def main():
    global listen
    global port
    global target

    # if not len(sys.argv[1:]):
    #     usage()

    # read the commandline options
    # try:
    #     opts, args = getopt.getopt(sys.argv[1:], "h:t:p:l", ["help", "listen", "target", "port"])
    # except getopt.GetoptError as err:
    #     print(str(err))
    #     usage()
    listen = True
    port = 5000
    target = "127.0.0.1"

    # for o, a in opts:
    #     if o in ("-h", "--help"):
    #         usage()
    #     elif o in ("-l", "--listen"):
    #         listen = True
    #     elif o in ("-t", "--target"):
    #         target = a
    #     elif o in ("-p", "--port"):
    #         port = int(a)
    #     # elif o in ("-s", "--server"):
    #     #     srvamount = int(a)
    #     else:
    #         assert False, "Unhandled Option"

    # are we going to listen or just send data from stdin

    if listen:
        server_loop()


main()