#include "ConnectionBase.h"

ConnectionBase::ConnectionBase()
{
}

ConnectionBase::~ConnectionBase()
{
	// We won't actually get here, but if we did then we'd want to clean up...
	printf("Quitting\n");
}

bool ConnectionBase::udpSendMessage(sf::Packet packet, SockAddr toSockAddr)
{
	printf("UDP Sending Message: ");

	sf::Socket::Status socketStatus = udpSocket.send(packet, toSockAddr.ipAddr, toSockAddr.port);

	while (socketStatus == sf::Socket::Status::Partial)
	{
		socketStatus = udpSocket.send(packet, toSockAddr.ipAddr, toSockAddr.port);
		printf("Partial message sent.\n");
	}

	switch (socketStatus)
	{
	case sf::Socket::Status::Done:
		printf("Message sent to address:%s and port:%d.\n", toSockAddr.ipAddr.toString().c_str(), toSockAddr.port);
		return true;
		break;
	case sf::Socket::Status::Error:
		printf("Error sending message.\n");
		return false;
		break;
	case sf::Socket::Status::Disconnected:
		printf("Socket not available.\n");
		return false;
		break;
	case sf::Socket::Status::NotReady:
		printf("The socket is not ready to send data.\n");
		return false;
		break;
	}
}

bool ConnectionBase::udpReceiveMessage(sf::Packet* packet, SockAddr* fromSockAddr, sf::Time timeout)
{
	// add the socket to the selector
	selector.add(udpSocket);

	if (selector.wait(timeout))
	{
		// Test if we have to read 
		if (selector.isReady(udpSocket))
		{
			printf("UDP Reading Message: ");

			sf::Socket::Status socketStatus = udpSocket.receive(*packet, fromSockAddr->ipAddr, fromSockAddr->port);

			while (socketStatus == sf::Socket::Status::Partial)
			{
				socketStatus = udpSocket.receive(*packet, fromSockAddr->ipAddr, fromSockAddr->port);
				printf("Partial message received.\n");
			}

			switch (socketStatus)
			{
			case sf::Socket::Status::Done:
				printf("Message received from address:%s and port:%d.\n", fromSockAddr->ipAddr.toString().c_str(), fromSockAddr->port);
				return true;
				break;
			case sf::Socket::Status::Error:
				printf("Error receiving message.\n");
				return false;
				break;
			case sf::Socket::Status::Disconnected:
				printf("'From socket' not available.\n");
				return false;
				break;
			case sf::Socket::Status::NotReady:
				printf("Socket is not ready to receive data.\n");
				return false;
				break;
			}
		}
	}

	// timeout finished and none message was received
	return false;
}


bool ConnectionBase::tcpSendMessage(sf::Packet packet, sf::TcpSocket* tcpSocket)
{
	printf("TCP Sending Message: ");

	sf::Socket::Status socketStatus = tcpSocket->send(packet);

	while (socketStatus == sf::Socket::Status::Partial)
	{
		socketStatus = tcpSocket->send(packet);
		printf("Partial message sent.\n");
	}

	switch (socketStatus)
	{
	case sf::Socket::Status::Done:
		printf("Message sent to address:%s and port:%d.\n", tcpSocket->getRemoteAddress().toString(), int(tcpSocket->getLocalPort()));
		return true;
		break;
	case sf::Socket::Status::Error:
		printf("Error sending message.\n");
		return false;
		break;
	case sf::Socket::Status::Disconnected:
		printf("Socket not available.\n");
		return false;
		break;
	case sf::Socket::Status::NotReady:
		printf("The socket is not ready to send data.\n");
		return false;
		break;
	}
}

bool ConnectionBase::tcpReceiveMessage(sf::Packet* packet, sf::TcpSocket& tcpSocket, sf::Time timeout)
{
	// add the socket to the selector
	selector.add(tcpSocket);

	if (selector.wait(timeout))
	{
		// Test if we have to read 
		if (selector.isReady(tcpSocket))
		{
			printf("TCP Reading Message: ");

			sf::Socket::Status socketStatus = tcpSocket.receive(*packet);

			while (socketStatus == sf::Socket::Status::Partial)
			{
				socketStatus = tcpSocket.receive(*packet);
				printf("Partial message received.\n");
			}

			switch (socketStatus)
			{
			case sf::Socket::Status::Done:
				printf("Message received from address:%s and port:%d.\n", tcpSocket.getRemoteAddress().toString(), tcpSocket.getLocalPort());
				return true;
				break;
			case sf::Socket::Status::Error:
				printf("Error receiving message.\n");
				return false;
				break;
			case sf::Socket::Status::Disconnected:
				printf("'From socket' not available.\n");
				return false;
				break;
			case sf::Socket::Status::NotReady:
				printf("Socket is not ready to receive data.\n");
				return false;
				break;
			}
		}
	}

	// timeout finished and none message was received
	return false;
}
