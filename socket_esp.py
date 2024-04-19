import socket
import time


class MySocket:
    def __init__(self,ip,port):
        if ip is None or not isinstance(ip,str) or len(str(ip).strip()) == 0:
            raise ValueError('ip must be a non-empty value and must be an string')

        if port is None or not isinstance(port,int) or len(str(port).strip()) == 0:
            raise ValueError('port must be a non-empty value and must be an integer')
        self._ip = ip
        self._port = port
        self.my_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connected = False
    @property
    def ip(self):
        return self._ip
    @property
    def port(self):
        return self._port

    def connect(self):
        try:
            self.my_socket.connect((self.ip,self.port))
            print(f"socket connection successful {self._ip,self._port}")
            self.connected = True
        except Exception as ex :
            print(f"connection failed {self._ip,self._port} error: [{ex}]")

    def send(self,msg,fchar=" ",echar=" "):
        try:
            if self.connected:
                data = f'{fchar}{msg}{echar}\n'
                self.my_socket.sendall(data.encode())
            else:
                print("Socket is not connected..")

        except Exception as ex:
            print(f'Send failed --- eror[{ex}]')

    def receive(self):
        try:
            if self.connected:
                return self.my_socket.recv(1023).decode()
            else:
                print("Socket is not connected..")

        except Exception as ex:
            print(f'Receive failed --- eror[{ex}]')

    def close(self):
        try:
            self.my_socket.close()
            print(f"disconnected successful {self._ip, self._port}")
        except Exception as ex:
            print(f'Error while closing connection --- error [{ex}]')
def main():
    client = MySocket(ip='192.168.1.10', port=5055)
    client.connect()
    while True:
        data_send = 'hello data from python' #chuỗi không lỗi
        # data_send = '⸮bb⸮⸮⸮b⸮⸮⸮b⸮⸮⸮b⸮⸮⸮b⸮⸮⸮b⸮⸮⸮b⸮⸮⸮b⸮⸮⸮b⸮⸮⸮R' #chuỗi lỗi
        client.send(msg=data_send)
        time.sleep(0.5)
        data_received = client.receive()
        print('data: ',str(data_received).strip())
        print('length data: ',len(str(data_received).strip()))
if __name__ == '__main__':
    main()
