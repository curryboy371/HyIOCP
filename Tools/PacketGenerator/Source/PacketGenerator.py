import argparse
import jinja2
import ProtoParser
import os

def main():

	arg_parser = argparse.ArgumentParser(description = 'PacketGenerator')
	arg_parser.add_argument('--is_server', action='store_true', help='set this flag if it is a server')
	arg_parser.add_argument('--path', type=str, default='Proto/Protocol.proto', help='proto path')
	arg_parser.add_argument('--output', type=str, default='TestPacketHandler', help='output file')
	arg_parser.add_argument('--client', type=str, default='CS_', help='c2s convention')
	arg_parser.add_argument('--server', type=str, default='SC_', help='s2c convention')
	arg_parser.add_argument('--server_br', type=str, default='BC_', help='s2b convention')
	arg_parser.add_argument('--start_pk_id', type=int, default=1000, help='start packet ID')

	args = arg_parser.parse_args()


	print(args.is_server)

	parser = ProtoParser.ProtoParser(args.is_server, args.start_pk_id, args.client, args.server, args.server_br)
	parser.parse_proto(args.path)
	file_loader = jinja2.FileSystemLoader('Templates')
	env = jinja2.Environment(loader=file_loader)

	template = env.get_template('PacketHandler.h')
	output = template.render(parser=parser, output=args.output)


	# 출력 경로에 Output을 추가
	output_directory="Output"
	if not os.path.exists(output_directory):
	    os.makedirs(output_directory)
	args.output = output_directory +'/' + args.output

	f = open(args.output+'.h', 'w+', encoding='utf-8')
	f.write(output)
	f.close()

	return

if __name__ == '__main__':
	main()