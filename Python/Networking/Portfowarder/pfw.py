import random
import socket
import sys
import threading
import time
from click._compat import raw_input

webserverports = []
temp = None
count = 0

def client_handler(client_socket, ):
    global  temp
    webservice_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        servport = balance()
        webservice_socket.connect(("127.0.0.1", servport))
        print("[*] Webservice bound to port {0}".format(servport))

        try:
            # print("spinning off threads")
            clientthread = threading.Thread(target=forward(client_socket, webservice_socket))
            clientthread.start()
            webservthread = threading.Thread(target=forward(webservice_socket, client_socket))
            webservthread.start()
        except:

            print("[*]Couldn't start forward")

    except ConnectionError as err:
        print(str(err))

    # try:
    #     # print("spinning off threads")
    #     clientthread = threading.Thread(target=forward(client_socket, webservice_socket))
    #     clientthread.start()
    #     webservthread = threading.Thread(target=forward(webservice_socket, client_socket))
    #     webservthread.start()
    # except:
    #
    #     print("[*]Couldn't start forward")


def forward(source, destination):
    message = ""

    while len(message) < 1:
        message = source.recv(4096)
        # print("[>] Receiving {0} bytes from {1}".format(len(message), source))

        if message:
            # print("[<] sending {0} bytes to {1}".format(len(message), destination))
            destination.sendall(message)
            time.sleep(1)

        else:
            # print("[X] Shutting down socket")
            source.shutdown()


def balance():
    global  count
    if (count < len(webserverports)):
        colour = webserverports[count]
        count = count + 1
    else:
        count = 0
        colour = webserverports[count]
        count = count + 1
    return colour

def server_loop(target, port):
    if not port > 0:
        port = int(1337)
    if not len(target):
        target = "0.0.0.0"

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        server.bind((target, port))
        print("[*] Bound server to {0}:{1}".format(target, port))

    except ConnectionError as err:
        print(str(err))
        print("[*] Couldn't bind server")

    server.listen(5)

    while True:
        client_socket, address = server.accept()
        print("[*] incoming connection from {0}:{1}".format(address[0], address[1]))
        client_thread = threading.Thread(target=client_handler(client_socket, ), args=(client_socket,))
        client_thread.start()


def usage():
    print("Usage:\npfw.py -t target_host -p port\n")
    print("Example:\npfw.py -t 192.168.0.1 -p 5555\n")
    sys.exit(0)


def main():
    global webserverports
    serveramount = int(sys.argv[1])

    for i in range(serveramount):
        webserverports.append(int(raw_input("server {0} is on which port: ".format(i))))
        print(webserverports)

    try:
        server_loop("127.0.0.1", 1337)

    except IOError as err:

        print(str(err))
        print("[*] Couldn't run loop")


main()
