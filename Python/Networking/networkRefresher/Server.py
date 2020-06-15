import socket
import threading


class Server:
	def __init__(self, ip, port):
		self.clients = []
		self.ip = ip
		self.port = port

		self.message_handler = None
		self.client_handler = None

		self.serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.serversocket.bind((self.ip, self.port))

	def start_listen(self):

		self.serversocket.listen(5)
		print(f"[+] Server started listening on {self.ip}:{self.port}")

		self.message_handler = threading.Thread(target=self.message_thread)
		self.message_handler.start()

		while True:
			client, addr = self.serversocket.accept()
			self.clients.append(client)
			print(f"[server] Accepted connection from {addr[0]}:{addr[1]}")
			client.send("Connected to Node".encode('utf-8'))
			self.client_handler = threading.Thread(target=self.handle_client, args=(client, addr))
			self.client_handler.start()

	def handle_client(self, clientsocket, addr):

		while True:
			try:
				request = clientsocket.recv(1024)
				print(f"[{addr[0]}:{addr[1]}] : {request.decode('utf-8')}")
				
			except:
				clientsocket.close()
				print(f"[-]{addr[0]}:{addr[1]} left")
				break

	def message_thread(self):
		while True:
			msg = input()
			if msg:
				for client in self.clients:
					try:
						client.sendall(msg.encode('utf-8'))
					except:
						client.close()
						self.clients.remove(client)
