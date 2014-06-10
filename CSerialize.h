//
#include <cstdio>
using namespace std;

#define SPLIT_CHAR	"$##$"
#define MAX_SERIALIZE_BUF	(1024*1024)
#define MAX_LENGH_SIZE	30 //


//head  char[4] as the lengh of msg,[0 , (255 +255*256^1 + 255*256^2 + 255*256^3)]


class CSerialize{
private:
	char m_pStr[MAX_SERIALIZE_BUF];
	char m_szTmpNum[MAX_LENGH_SIZE];
	//char *m_pCur;
	//int m_nPos;

public:
	CSerialize()
	{
		memset(m_pStr,'\0',MAX_SERIALIZE_BUF);
		//m_pStr = ptr;
		//m_nPos = 0;
	}
	~CSerialize()
	{

	}

public:
	void resetBuffer()
	{
		memset(m_pStr,'\0',MAX_SERIALIZE_BUF);
		//m_pCur = m_pStr;
	}
	char *getBuffer()
	{
//		int nLengh = strlen(m_pStr) + 1;
//		char *ptr = (char *)malloc(nLengh);
//		snprintf(ptr,nLengh,"%s",m_pStr);
		return m_pStr;
	}
	void serialize(const int n)
	{
		//char tmp[MAX_LENGH_SIZE];
		//int + SPLIT_CHAR
		memset(m_szTmpNum,'\0',MAX_LENGH_SIZE);

		snprintf(m_szTmpNum,MAX_LENGH_SIZE,"%d%s",n,SPLIT_CHAR);
		strcat(m_pStr,m_szTmpNum);
	}
	void serialize(const long n)
	{
		//char tmp[MAX_LENGH_SIZE];
		//int + SPLIT_CHAR
		memset(m_szTmpNum,'\0',MAX_LENGH_SIZE);

		snprintf(m_szTmpNum,MAX_LENGH_SIZE,"%ld%s",n,SPLIT_CHAR);
		strcat(m_pStr,m_szTmpNum);
	}
	void serialize(const char *ptr)
	{
		//size + SPLIT_CHAR + string + SPLIT_CHAR
		char tmp[MAX_SERIALIZE_BUF];
		snprintf(tmp,MAX_SERIALIZE_BUF,"%d%s%s%s",strlen(ptr),SPLIT_CHAR,ptr,SPLIT_CHAR);
		strcat(m_pStr,tmp);
	}
};

class CUNSerialize{
private:
	char *m_pStr;
	char m_szTmpNum[MAX_LENGH_SIZE];
	//int m_nPos;
public:
	CUNSerialize()
	{
		//m_pStr = ptr;
		//m_nPos = 0;
	}

	CUNSerialize(char *ptr)
	{
		m_pStr = ptr;
		//m_nPos = 0;
	}
	~CUNSerialize()
	{

	}
public:
	void setStr(char *ptr)
	{
		m_pStr = ptr;
	}
	void unserialize(int &n)
	{
		char *pNewStr = strstr(m_pStr,SPLIT_CHAR);
		if(pNewStr == NULL)
		{
			//NOT FIND
		}
		int nPos = pNewStr - m_pStr;
		//char szSize[MAX_LENGH_SIZE];
		memset(m_szTmpNum,'\0',MAX_LENGH_SIZE);
		strncpy(m_szTmpNum,m_pStr,nPos);
		m_szTmpNum[nPos] = '\0';
		n = atoi(m_szTmpNum);

		m_pStr = pNewStr + strlen(SPLIT_CHAR);
	}
	void unserialize(long &n)
	{
		char *pNewStr = strstr(m_pStr,SPLIT_CHAR);
		if(pNewStr == NULL)
		{
			//NOT FIND
		}
		int nPos = pNewStr - m_pStr;
		//char szSize[MAX_LENGH_SIZE];
		memset(m_szTmpNum,'\0',MAX_LENGH_SIZE);
		strncpy(m_szTmpNum,m_pStr,nPos);
		m_szTmpNum[nPos] = '\0';
		n = atol(m_szTmpNum);

		m_pStr = pNewStr + strlen(SPLIT_CHAR);
	}
	void unserialize(char *pStr)
	{

		char *pNewStr = strstr(m_pStr,SPLIT_CHAR);
		if(pNewStr == NULL)
		{
			//NOT FIND
		}
		int nPos = pNewStr - m_pStr;
		memset(m_szTmpNum,'\0',MAX_LENGH_SIZE);
		//char szSize[MAX_LENGH_SIZE];
		strncpy(m_szTmpNum,m_pStr,nPos);
		m_szTmpNum[nPos] = '\0';
		m_pStr = pNewStr + strlen(SPLIT_CHAR);

		int nSize = atoi(m_szTmpNum);
		strncpy(pStr,m_pStr,nSize);
		pStr[nSize] = '\0';

		m_pStr = m_pStr + nSize + strlen(SPLIT_CHAR);
	}
};
