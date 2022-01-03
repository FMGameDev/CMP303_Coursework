#pragma once

#include <queue>
#include "../../NetworkFramework/ConnectionMessage.h"

//This is a network simulation and doesn't actually do any networking!
class NetworkSimulator
{
public:
	
	//Create a Network simulator with the designated Send Rate and Latency
	NetworkSimulator(float sendRate, float latency);
	~NetworkSimulator();


	/** Receive the next message from the network. Non-blocking.
	Returns true if a message was received, false if there are no more messages to process. */
	bool ReceiveMessage(PlayerInfo &result);

	float Time() { return m_Time; }
	void Update(float dt);

	void SetLatency(float);
	void SetSendRate(float);
	void SetNextPrint(float);

	float getSendRate() { return m_SendRate; };
	float getNextPrint() { return m_NextPrint; };
	float getStartTime() { return m_StartTime; };

	void Reset();

	int m_MyID = -1;

private:
	float m_Time, m_SentTime;
	std::queue<PlayerInfo> m_MessageQueue;
	float m_SentX, m_SentY; //The last sent position
	float m_SentVX;
	float m_SentVY;
	std::string m_Colour;
	float m_Latency = 0.1f;	
	float m_SendRate = 0.5f;
	float m_StartTime;
	float m_NextPrint;
};

