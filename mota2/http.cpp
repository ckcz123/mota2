#include "stdafx.h"

Http::Http() {
	strcpy_s(server, "47.93.40.127");
	port=23456;
}

char* Http::get(char* host, int port, char* path, char* parameters)
{
	if (WSAStartup(0x101, &wsaData)!=0)
		return NULL;

	long fileSize;
	char* memBuffer=readUrl2(host, port, path, parameters, fileSize);
	WSACleanup();
	if (fileSize>0)
		return memBuffer;
	return NULL;
}

SOCKET Http::connectToServer(char *szServerName, WORD portNum)
{
	struct hostent *hp;
	struct sockaddr_in server;
	SOCKET conn;

	conn=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (conn==INVALID_SOCKET)
		return NULL;

	unsigned long ss_addr=inet_addr(szServerName);

	if (ss_addr==INADDR_NONE)
	{
		hp=gethostbyname(szServerName);
		if (hp==NULL)
		{
			closesocket(conn);
			return NULL;
		}
		ss_addr=*((unsigned long*)hp->h_addr);
	}

	//if (inet_addr(szServerName)==INADDR_NONE)
	//{
	//	hp=gethostbyname(szServerName);
	//}
	//else
	//{
	//	addr=inet_addr(szServerName);
	//	hp=gethostbyaddr((char*)&addr, sizeof(addr), AF_INET);
	//}

	// server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
	server.sin_addr.s_addr=ss_addr;
	server.sin_family=AF_INET;
	server.sin_port=htons(portNum);
	if (connect(conn, (struct sockaddr*)&server, sizeof(server)))
	{
		closesocket(conn);
		return NULL;
	}
	return conn;
}

int Http::getHeaderLength(char *content)
{
	const char *srchStr1="\r\n\r\n", *srchStr2="\n\r\n\r";
	char *findPos;
	int ofset=-1;

	findPos=strstr(content, srchStr1);
	if (findPos!=NULL)
	{
		ofset=findPos-content;
		ofset+=strlen(srchStr1);
	}

	else
	{
		findPos=strstr(content, srchStr2);
		if (findPos!=NULL)
		{
			ofset=findPos-content;
			ofset+=strlen(srchStr2);
		}
	}
	return ofset;
}

char* Http::readUrl2(char *hostname, int port, char* path, char* parameters, long &bytesReturnedOut)
{
	const int bufSize=512;
	char readBuffer[bufSize], sendBuffer[bufSize];
	char *tmpResult=NULL, *result;
	SOCKET conn;
	string server, filepath, filename;
	long totalBytesRead, thisReadSize, headerLen;

	///////////// step 1, connect //////////////////////
	conn=connectToServer(hostname, port);

	///////////// step 2, send GET request /////////////
	strcpy_s(sendBuffer, "");
	if (parameters==NULL)
		strcat_s(sendBuffer, "GET ");
	else
		strcat_s(sendBuffer, "POST ");
	strcat_s(sendBuffer, path);
	strcat_s(sendBuffer, " HTTP/1.0\r\n");
	strcat_s(sendBuffer, "Host: ");
	strcat_s(sendBuffer, hostname);
	strcat_s(sendBuffer, "\r\n");
	strcat_s(sendBuffer, "Cache-Control: no-cache\r\n");
	if (parameters!=NULL)
	{
		strcat_s(sendBuffer, "Content-Type: application/x-www-form-urlencoded\r\n");
		char s[100];
		sprintf_s(s, "Content-Length: %d\r\n", strlen(parameters));
		strcat_s(sendBuffer, s);
		strcat_s(sendBuffer, "\r\n");
		strcat_s(sendBuffer, parameters);
	}
	strcat_s(sendBuffer, "\r\n");
	send(conn, sendBuffer, strlen(sendBuffer), 0);

	//    SetWindowText(edit3Hwnd, sendBuffer);
	// printf("Buffer being sent:\n%s", sendBuffer);

	///////////// step 3 - get received bytes ////////////////
	// Receive until the peer closes the connection
	totalBytesRead=0;
	while (1)
	{
		memset(readBuffer, 0, bufSize);
		thisReadSize=recv(conn, readBuffer, bufSize, 0);

		if (thisReadSize<=0)
			break;

		tmpResult=(char*)realloc(tmpResult, thisReadSize+totalBytesRead);

		memcpy_s(tmpResult+totalBytesRead, thisReadSize, readBuffer, thisReadSize);
		totalBytesRead+=thisReadSize;
	}

	if (tmpResult==NULL)
		return NULL;

	headerLen=getHeaderLength(tmpResult);
	long contenLen=totalBytesRead-headerLen;
	result=new char[contenLen+1];
	memcpy_s(result, contenLen+1, tmpResult+headerLen, contenLen);
	result[contenLen]=0x0;
	delete tmpResult;

	bytesReturnedOut=contenLen;
	closesocket(conn);
	return(result);
}