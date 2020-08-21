import socket

total_packet = packet_len+teeth_bytes+image_len+jpeg_bytes;
packet_len => 4 bytes
teeth_bytes => 6 bytes
image_len => 4 bytes
alertListener = AlertListener()
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(('0.0.0.0', 5001))
    s.listen(5)
    
screen_msg =conn.recv(1)
                full_msg = screen_msg.decode("utf-8")
                if full_msg == "d":
                    print('D recibido')
                    try:
                        #si se recibio "d", se envia todo el paquete
                        conn.send(total_packet)