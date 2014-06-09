//
#include <cstdio>
using namespace std;

#define SPLIT_CHAR	"$##$"
#define MAX_SERIALIZE_BUF	(32*1024*1024)

class CSerialize{
private:
	char m_pStr[MAX_SERIALIZE_BUF];
	//int m_nPos;

public:
	CSerialize()
	{
		//m_pStr = ptr;
		//m_nPos = 0;
	}
	~CSerialize()
	{

	}
public:
	char *getBuffer()
	{
//		int nLengh = strlen(m_pStr) + 1;
//		char *ptr = (char *)malloc(nLengh);
//		snprintf(ptr,nLengh,"%s",m_pStr);
		return m_pStr;
	}
	void serialize(const int n)
	{
		char tmp[MAX_SERIALIZE_BUF];
		snprintf(tmp,MAX_SERIALIZE_BUF,"%d%s",n,SPLIT_CHAR);
		strcat(m_pStr,tmp);
	}
	void serialize(const char *ptr)
	{
		char tmp[MAX_SERIALIZE_BUF];
		snprintf(tmp,MAX_SERIALIZE_BUF,"%s%s",ptr,SPLIT_CHAR);
		strcat(m_pStr,tmp);
	}
};

class CUNSerialize{
private:
	char *m_pStr;
	//int m_nPos;
public:
	CUNSerialize(char *ptr)
	{
		m_pStr = ptr;
		//m_nPos = 0;
	}
	~CUNSerialize()
	{

	}
public:
	void unserialize(int &n)
	{
		char *pNewStr = strstr(m_pStr,SPLIT_CHAR);
		if(pNewStr == NULL)
		{
			//NOT FIND
		}
		int nPos = pNewStr - m_pStr;
		char *pTmp = (char *)malloc(nPos + 1);
		strncpy(pTmp,m_pStr,nPos);
		pTmp[nPos] = '\0';
		n = atoi(pTmp);
		free(pTmp);
		m_pStr = pNewStr + 3;
	}
	void unserialize(char *pStr)
	{
		char *pNewStr = strstr(m_pStr,SPLIT_CHAR);
		if(pNewStr == NULL)
		{
			//NOT FIND
		}
		int nPos = pNewStr - m_pStr;
		strncpy(pStr,m_pStr,nPos);
		pStr[nPos] = '\0';

		m_pStr = pNewStr + 3;
	}
};
