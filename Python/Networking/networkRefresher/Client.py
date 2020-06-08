import socket
import threading


class Client:
	def __init__(self, target_host, target_port):
		self.target_host = target_host
		self.target_port = target_port

		self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	def spin_off_client(self):
		self.client.connect((self.target_host, self.target_port))
		server_handler = threading.Thread(target=self.listen_thread)
		server_handler.start()

		while True:
			msg = str(input())
			if msg.lower() == "exit()":
				self.client.sendall(msg.encode('utf-8'))
				break
			elif msg:
				try:
					self.client.sendall(msg.encode('utf-8'))
				except Exception as e:
					print(f'can\'t connect to {self.target_host}:{self.target_port}')
					print(e)
					break
		self.client.close()

	def listen_thread(self):
		while True:
			msg = self.client.recv(4096)
			if not msg:
				break
			print(f"[Server] {msg.decode('utf-8')}")