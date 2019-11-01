import random
import socket
import sys
import threading


def usage():
	print('Usage:')
	print('./proxy.py localhost localport remotehost remoteport')
	print('./proxy.py 192.0.0.2 6000 127.0.0.1 5000')


def handle(buffer):
	return buffer


def transfer(src, dst, direction):
	src_name = src.getsockname()
	src_address = src_name[0]
	src_port = src_name[1]
	dst_name = dst.getsockname()
	dst_address = dst_name[0]
	dst_port = dst_name[1]
	while True:
		buffer = src.recv(0x400)
		if len(buffer) == 0:
			print("[-] No data received! Breaking...")
			break
		# print "[+] %s:%d => %s:%d [%s]" % (src_address, src_port, dst_address, dst_port, repr(buffer))
		if direction:
			print(f'[+] {src_address}:{src_port} >>> {dst_address}:{dst_port} bytes: [{len(buffer)}]')
		else:
			print(f'[+] {dst_address}:{dst_port} >>> {src_address}:{src_port} bytes: [{len(buffer)}]')
		dst.send(handle(buffer))
	print(f'[-]  Closing connection! {src_address}:{src_port}')
	src.shutdown(socket.SHUT_RDWR)
	src.close()

	print(f'[-] Closing connection! {dst_address}:{dst_port}')
	dst.shutdown(socket.SHUT_RDWR)
	dst.close()


def server(local_host, local_port, remote_host, port_list, max_connections):

	server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	try:
		server_socket.bind((local_host, local_port))
		print(f'Server bound to {local_host}:{local_port}')

	except Exception as e:
		print(f'Failed to bind to {local_host}:{local_port}')
		print('Check for already open port and/or permissions')
		print(f'[X] Error message: {e}')
		usage()
		sys.exit(0)

	server_socket.listen(max_connections)

	print(f'[+]Server listening on {local_host}:{local_port}')

	while True:
		remote_port = port_list[random.randint(0, len(port_list)-1)]
		local_socket, local_address = server_socket.accept()
		print(f'[+] Receiving incoming connection from {local_address[0]}:{local_address[1]}')
		print(f'[+] Trying to connect to remote server on {remote_host}:{remote_port}')

		remote_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

		try:
			remote_socket.connect((remote_host, remote_port))
			print(f'Connect to {local_host}:{local_port} to get content of {remote_host}:{remote_port}')

		except Exception as e:
			print(f'[!] Could not connect to server on {remote_host}:{remote_port}')
			print(f'[X] Error message: {e}')
			break

		print('[+] Tunnel opened! Transferring Data...')

		src = threading.Thread(target=transfer, args=(remote_socket, local_socket, False))

		rmt = threading.Thread(target=transfer, args=(local_socket, remote_socket, True))

		src.start()
		rmt.start()

	print('[-] Releasing resources')
	remote_socket.shutdown(socket.SHUT_RDWR)
	remote_socket.close()
	local_socket.shutdown(socket.SHUT_RDWR)
	local_socket.close()

	print('[-] Closing server...')
	server_socket.shutdown(socket.SHUT_RDWR)
	server_socket.close()
	print('[-] Server shutdown')


def main():
	local_host = '127.0.0.1'
	local_port = 7000

	remote_host = '127.0.0.1'
	remote_port_list = [5020, 5021]

	max_connections = 0x10

	server(local_host, local_port, remote_host, remote_port_list, max_connections)


if __name__ == '__main__':
	main()
