from Client import Client
from Server import Server
import threading
import getopt
import sys


def usage():
	print("""
	Server:
		usage: ./main.py -s -i 127.0.0.1 -p 5000 
	
	Client:
		usage: ./main.py -c -i 127.0.0.1 -p 5000
		
	Options:
		[-h] show usage
		[-s] make server socket
		[-c] make client socket
		[-i] set ip
		[-p] set port
	""")


def main(argv):
	mode = ""
	ip = ""
	port = 0

	if not len(sys.argv[1:]):
		usage()
		print("Start in (s)erver or in (c)lient mode?")
		new_mode = str(input()).strip()
		if new_mode.lower() == "s":
			mode = "s"
		elif new_mode.lower() == "c":
			mode = "c"
		else:
			print("invalid input, please see usage")

	try:
		opts, args = getopt.getopt(argv, "hsc:i:p:", ["help", "server", "client", "ip", "port"])

		for o, a in opts:
			if o in ("-h", "--help"):
				usage()

			elif o in ("-s", "--server"):
				mode = "s"

			elif o in ("-c", "--client"):
				mode = "c"

			elif o in ("-i", "--ip"):
				ip = str(a)

			elif o in ("-p", "--port"):
				port = int(a)

	except getopt.GetoptError as go_error:
		print(str(go_error))

	if mode == 's':
		if not ip:
			ip = str(input("Insert host ip: "))
		if port == 0:
			port = int(input("insert host port: "))
		server = Server(ip, port)
		server_thread = threading.Thread(target=server.start_listen)
		server_thread.start()

	if mode == 'c':
		if not ip:
			ip = str(input("Insert target ip: "))
		if port == 0:
			port = int(input("insert target port: "))
		client = Client(ip, port)
		client_thread = threading.Thread(target=client.spin_off_client)
		client_thread.start()


if __name__ == '__main__':
	main(sys.argv[1:])