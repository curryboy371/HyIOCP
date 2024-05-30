class ProtoParser():
	def __init__(self, is_server, start_id, client, server, server_br):
		self.is_server = is_server	# Server or Client
		self.send_pkt = []			# send packet list
		self.recv_pkt = []			# recv packet list
		self.total_pkt = []			# 모든 패킷 목록
		self.start_id = start_id
		self.id = start_id
		self.client = client
		self.server = server
		self.server_br = server_br

	def parse_proto(self, path):
		f = open(path, 'r', encoding='utf-8')
		lines = f.readlines()

		for line in lines:
			if line.startswith('message') == False:
				continue

			if self.is_server == True:
				pkt_name = line.split()[1].upper()
				if pkt_name.startswith(self.client):
					self.recv_pkt.append(Packet(pkt_name, self.id))
				elif pkt_name.startswith(self.server):
					self.send_pkt.append(Packet(pkt_name, self.id))
				elif pkt_name.startswith(self.server_br):
					self.send_pkt.append(Packet(pkt_name, self.id))
				else:
					continue
			else:
				pkt_name = line.split()[1].upper()
				if pkt_name.startswith(self.client):
					self.send_pkt.append(Packet(pkt_name, self.id))
				elif pkt_name.startswith(self.server):
					self.recv_pkt.append(Packet(pkt_name, self.id))
				elif pkt_name.startswith(self.server_br):
					self.recv_pkt.append(Packet(pkt_name, self.id))
				else:
					continue

			self.total_pkt.append(Packet(pkt_name, self.id))
			self.id += 1

		f.close()

class Packet:
	def __init__(self, name, id):
		self.name = name
		self.id = id