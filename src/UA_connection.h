/*
 * opcua_connectionHelper.h
 *
 *  Created on: Jan 13, 2014
 *      Author: opcua
 */

#ifndef OPCUA_CONNECTIONHELPER_H_
#define OPCUA_CONNECTIONHELPER_H_
#include "opcua.h"

enum UA_MessageType
{
	UA_MESSAGETYPE_HEL = 0x48454C, // H E L
	UA_MESSAGETYPE_ACK = 0x41434B, // A C k
	UA_MESSAGETYPE_ERR = 0x455151, // E R R
	UA_MESSAGETYPE_OPN = 0x4F504E, // O P N
	UA_MESSAGETYPE_MSG = 0x4D5347, // M S G
	UA_MESSAGETYPE_CLO = 0x434C4F  // C L O
};
enum connectionState
{
	connectionState_CLOSED,
	connectionState_OPENING,
	connectionState_ESTABLISHED,

};

typedef struct
{
	UA_UInt32 secureChannelId;
	UA_UInt32 tokenId;
	UA_DateTime createdAt;
	UA_Int32 revisedLifetime;
}SL_ChannelSecurityToken;

typedef struct
{
	UA_UInt32 protocolVersion;
	UA_UInt32 sendBufferSize;
	UA_UInt32 recvBufferSize;
	UA_UInt32 maxMessageSize;
	UA_UInt32 maxChunkCount;
}TL_buffer;

struct TL_connection
{
	UA_Int32 socket;
	UA_UInt32 connectionState;
	TL_buffer remoteConf;
	TL_buffer localConf;
	UA_String endpointURL;
};
typedef struct
{
	UA_ByteString SecurityPolicyUri;
	UA_ByteString SenderCertificate;
	UA_ByteString ReceiverCertificateThumbprint;

}AsymmetricAlgSecuritySettings;



struct SL_connection
{
	AsymmetricAlgSecuritySettings remoteAsymAlgSettings;
	AsymmetricAlgSecuritySettings localAsymAlgSettings;
/*
	UA_ByteString SecurityPolicyUri;
	UA_ByteString SenderCertificate;
	UA_ByteString ReceiverCertificateThumbprint;
*/
	UA_UInt32 sequenceNumber;
	UA_UInt32 requestType;
	UA_String secureChannelId;
	//UInt32 UInt32_secureChannelId;
	UA_UInt32 securityMode;
	UA_ByteString remoteNonce;
	UA_ByteString localNonce;
	UA_UInt32 connectionState;
	SL_ChannelSecurityToken securityToken;
	UA_UInt32 requestId; // request Id of the current request
};

struct SS_connection
{
	UA_Int32 dummy;
};

typedef struct T_UA_connection
{
	struct TL_connection transportLayer;
	struct SL_connection secureLayer;
	struct SS_connection serviceLayer;

	UA_Boolean newDataToRead;
	UA_ByteString readData;
	UA_Boolean newDataToWrite;
	UA_ByteString writeData;
}UA_connection;



#endif /* OPCUA_CONNECTIONHELPER_H_ */
