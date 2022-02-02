#!/usr/bin/python3
import socket
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("-p",help="port to bind to")
args = parser.parse_args()
if not args.p:
  print("Port required")
  exit(0)

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM);
sock.bind(("0.0.0.0",int(args.p)))
sock.listen(10)
while True:
  try:
    conn, addr = sock.accept()
    print(f"New connection from {addr[0]}:{addr[1]}")
    while conn:
      data = conn.recv(1024)
      print(f"Recved from {addr[0]}: {data}")  
      conn.close()
  except:
    sock.close()