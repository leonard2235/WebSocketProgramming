	cmake_minimum_required(VERSION 2.6)
	add_executable(	client examples/client-server/client.cpp	)
	add_executable(	server examples/client-server/server.cpp	)
	add_executable(	client examples/p2p/client.cpp	)
	add_executable(	server examples/p2p/server.cpp	)
	add_executable(	connection test/connection.cpp	)
	add_executable(	input_client test/input_client.cpp	)
	add_executable(	input_server test/input_server.cpp	)
	add_executable(	output_client test/output_client.cpp	)
	add_executable(	output_server test/output_server.cpp	)
	add_executable(	output_server_many_clients test/output_server_many_clients.cpp	)
