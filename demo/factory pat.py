from abc import ABC, abstractmethod  
import serial  
import socket  
  
# 通信接口抽象基类  
class CommunicationInterface(ABC):  
    @abstractmethod  
    def open(self):  
        pass  
  
    @abstractmethod  
    def close(self):  
        pass  
  
    @abstractmethod  
    def send(self, data):  
        pass  
  
    @abstractmethod  
    def receive(self):  
        pass  
  
# 串口通信类  
class SerialCommunication(CommunicationInterface):  
    def __init__(self, port, baudrate=9600):  
        self.serial = serial.Serial(port, baudrate)  
  
    def open(self):  
        if not self.serial.isOpen():  
            self.serial.open()  
  
    def close(self):  
        if self.serial.isOpen():  
            self.serial.close()  
  
    def send(self, data):  
        self.serial.write(data.encode())  
  
    def receive(self):  
        return self.serial.read_all().decode()  
  
# 网络通信类  
class SocketCommunication(CommunicationInterface):  
    def __init__(self, host, port):  
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
        self.host = host  
        self.port = port  
  
    def open(self):  
        self.sock.connect((self.host, self.port))  
  
    def close(self):  
        self.sock.close()  
  
    def send(self, data):  
        self.sock.send(data.encode())  
  
    def receive(self):  
        return self.sock.recv(1024).decode()  
  
# CAN通信类（示例框架）  
class CANCommunication(CommunicationInterface):  
    def __init__(self, channel='can0', bitrate=500000):  
        self.channel = channel  
        self.bitrate = bitrate  
  
    def open(self):  
        pass  # 打开CAN接口的代码  
  
    def close(self):  
        pass  # 关闭CAN接口的代码  
  
    def send(self, data):  
        pass  # 发送CAN数据的代码  
  
    def receive(self):  
        return "CAN data received"  # 接收CAN数据的代码  
  
# 通信接口工厂类  
class CommunicationFactory:  
    @staticmethod  
    def create_communication(type_, *args, **kwargs):  
        if type_ == 'serial':  
            return SerialCommunication(*args, **kwargs)  
        elif type_ == 'socket':  
            return SocketCommunication(*args, **kwargs)  
        elif type_ == 'can':  
            return CANCommunication(*args, **kwargs)  
        else:  
            raise ValueError("Unsupported communication type")  
  
# 使用示例  
if __name__ == "__main__":  
    # 创建串口通信实例  
    serial_comm = CommunicationFactory.create_communication('serial', 'COM3', 115200)  
    serial_comm.open()  
    serial_comm.send("Hello Serial")  
    print(serial_comm.receive())  
    serial_comm.close()  
  
    # 创建网络通信实例  
    socket_comm = CommunicationFactory.create_communication('socket', 'localhost', 12345)  
    socket_comm.open()  
    socket_comm.send("Hello Socket")  
    print(socket_comm.receive())  
    socket_comm.close()  
  
    # 创建CAN通信实例  
    can_comm = CommunicationFactory.create_communication('can', 'can0', 500000)  
    can_comm.open()  
    print(can_comm.receive())  
    can_comm.close()