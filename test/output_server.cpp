/// Simple sockets buffer output client test
/// This test cover if simple socket client can send message to a boost based
/// server application.

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <memory>
#include <list>
#include <assert.h>
#include <sstream>
#include "../src/ServerSocketStream.hpp"

using boost::asio::ip::tcp;

size_t bytesReaded;
std::string message;
std::string expectedMessage = "I'm here!";
boost::system::error_code error;

const int PORT = 12346;

/// Server side, boost pure implementation
/**
 * Open port listening for a connection,
 * when someone connects send a message.
 */
void server(void) {
	simple::ServerSocketStream client(PORT);

	client << expectedMessage << std::flush;

	simple::ServerSocketStream nonClient(PORT); // you can connect another client
}

#include <istream>

/// Client side using simple sockets
/**
 * Connect to server and receive a message.
 */
void client(void) {
	boost::asio::io_service io_service;

	tcp::resolver resolver(io_service);
	tcp::resolver::query query("localhost", std::to_string(PORT));
	tcp::resolver::iterator endpoint = resolver.resolve(query);

	tcp::socket socket(io_service);
	boost::asio::connect(socket, endpoint);

	boost::array<char, 128> buffer;
	boost::system::error_code error;

	size_t length = socket.read_some(boost::asio::buffer(buffer.data(), buffer.size()), error);

	message = std::string(buffer.cbegin(), buffer.cbegin() + length);
	bytesReaded = message.size();

	boost::asio::connect(socket, endpoint); // close nonClient await
}

#include <thread>

/// Main test
/**
 * Start server take a while and start client.
 * Then test if communication is ok.
 */
int main(void) {
	std::thread serverThread(server);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	client();
	
	assert(error == 0);
	assert(bytesReaded == expectedMessage.size());
	assert(message == expectedMessage);

	serverThread.join();
	return 0;
}
