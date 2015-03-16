/**************************************************************************

Filename    :   DataParser.h
Content     :   
Created     :   Feb 2015
Authors     :   Ankur Mohan

Copyright   :   Copyright 2015 Ankur Mohan, All Rights reserved.

Use of this software is subject to the terms of the license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "signaldata.h"
#include "qmath.h"
class SamplingThread;

class DataParserImpl
{
public:
	DataParserImpl(SamplingThread* samplingThread, const char* _prefix, int dataLength = 0);
	virtual void Plot(double elapsed)
	{
	}
	virtual float GetData()
	{
		return 0.0;
	}
	virtual bool Parse(char* incomingData, int packetLength, char* commandId = NULL);
	
	char	Prefix[100];
	int		PrefixLength;
	float	Data[4];
	float	RadToDegree;
	int		DataLength;
	bool	bPrefixFound;
	SamplingThread* pSamplingThread;
};

class DataParser
{
public:
	DataParser(){}

	QList<DataParserImpl*> DataParsers;
	QList<DataParserImpl*> AckParsers;

	void RegisterDataParser(DataParserImpl* dataParser)
	{
		DataParsers.push_back(dataParser);
	}

	void RegisterAckParser(DataParserImpl* ackParser)
	{
		AckParsers.push_back(ackParser);
	}

	void RemoveDataParser(DataParserImpl* dataParser)
	{
		DataParsers.removeOne(dataParser);
	}

	void RemoveAckParser(DataParserImpl* ackParser)
	{
		AckParsers.removeOne(ackParser);
	}

	bool ParseData(char* incomingData, int packetLength);
	bool ParseAck(char* incomingData, int packetLength, char* commandId);
	void Plot(double elapsed);
};



class DataParserImplYpr: public DataParserImpl
{
public:
	DataParserImplYpr(SamplingThread* psamplingThread, char* _prefix, int dataLength): DataParserImpl(psamplingThread, _prefix, dataLength){};

	void Plot(double elapsed);
};

class DataParserImplPID: public DataParserImpl
{
public:
	DataParserImplPID(SamplingThread* psamplingThread, char* _prefix, int dataLength): DataParserImpl(psamplingThread, _prefix, dataLength){};

	void Plot(double elapsed);
};

class DataParserImplFusion: public DataParserImpl
{
public:
	DataParserImplFusion(SamplingThread* psamplingThread, char* _prefix, int dataLength): DataParserImpl(psamplingThread, _prefix, dataLength){};
	void Plot(double elapsed);
};

class DataParserImplCommands: public DataParserImpl
{
public:
	DataParserImplCommands(SamplingThread* psamplingThread): DataParserImpl(psamplingThread, "QS"){};
	virtual bool Parse(char* incomingData, int packetLength, char* commandId = NULL);
};

class DataParserImplBeacon: public DataParserImpl
{
public:
	DataParserImplBeacon(SamplingThread* psamplingThread): DataParserImpl(psamplingThread, "Beacon"){};
	virtual bool Parse(char* incomingData, int packetLength, char* commandId = NULL);
};

class DataParserImplAck: public DataParserImpl
{
public:
	DataParserImplAck(SamplingThread* psamplingThread): DataParserImpl(psamplingThread, "Ack", 1){};

	virtual bool Parse(char* incomingData, int packetLength, char* commandId = NULL);

	float GetData()
	{
		return Data[0];
	}
};

class DataParserImplException: public DataParserImpl
{
public:
	DataParserImplException(SamplingThread* psamplingThread): DataParserImpl(psamplingThread, "Exception:"){};

	virtual bool Parse(char* incomingData, int packetLength, char* commandId = NULL);
};