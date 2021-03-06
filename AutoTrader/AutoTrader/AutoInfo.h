#pragma once
#include <vector>
//#include "MinuteData.h"

using namespace std;

#define HOST "192.168.74.147"
//#define HOST "localhost"
//#define USER "lio"
#define DatabaseUSER "lio"
//#define USER "root"
#define PORT "3306"
#define PASSWD "niumuguang"
//#define PASSWD "1987724202"
#define DBNAME "VDatabase"
#define CHARSET "utf8"
#define STANDARDIP "116.236.239.129"

struct ListData
{
	char ID[10];
	char TotalPacket[10];
	bool Falg;
	char Protocol[20];
	char sIP[16],sMac[19],sPort[10];
	char dIP[16],dMac[19],dPort[10];
	char Len[10];
	char Text[50];
};

typedef struct HSTimer
{
public:
	HSTimer(){
		 m_Year = 0;
		 m_Month = 0;
		 m_Day = 0;
		 m_Hour = 0;
		 m_Minute = 0;
		 m_Second = 0;
		 m_MilliSecond = 0;

		 m_StringTimer = _T("");
		 m_StringDate = _T("");
	};

	HSTimer(CString TimeStr){
		m_StringTimer = TimeStr;
		SplitTimeStr();
	};

	HSTimer(CString TimeStr,CString DateStr){
		m_StringTimer = TimeStr;
		m_StringDate = DateStr;
		SplitTimeStr();
		SplitDateStr();
	};

	~HSTimer(void){
	};

// 	friend int operator-(HSTimer com1,HSTimer com2)//友元运算符重载函数
// 	{
// 		return 0;
// 	};

// 	HSTimer& operator = (HSTimer TimeStr)//友元运算符重载函数
// 	{
// 		this = &TimeStr;
// 		//SplitTimeStr();
// 		return;
// 	};

	bool isSameMinute(const HSTimer &t1){
		if (t1.m_Year == m_Year && t1.m_Month == m_Month && t1.m_Day == m_Day && t1.m_Hour == m_Hour && t1.m_Minute == m_Minute)
		{
			return true;
		}
		return false;
	};


	bool isFifteenMinute(const HSTimer &t1)
	{
		if (t1.m_Year == m_Year && t1.m_Month == m_Month && t1.m_Day == m_Day)
		{
			if (m_Hour == t1.m_Hour)// 小时相同
			{
				if( int(m_Minute/15) == int(t1.m_Minute/15) )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		return false;
	}

	bool isFiveMinute(const HSTimer &t1){
		if (t1.m_Year == m_Year && t1.m_Month == m_Month && t1.m_Day == m_Day)
		{
			if (m_Hour == t1.m_Hour)// 小时相同
			{
				if( int(m_Minute/5) == int(t1.m_Minute/5) )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		return false;
	}


	bool operator==(const HSTimer &t1)const{
		if (t1.m_Year == m_Year && t1.m_Month == m_Month && t1.m_Day == m_Day && t1.m_Hour == m_Hour && t1.m_Minute == m_Minute && t1.m_Second == m_Second && t1.m_MilliSecond == m_MilliSecond)
		{
			return true;
		}
		return false;
	};

	bool isInTradeTime(){
		if (m_Hour == 0 && m_Minute == 0 && m_Second == 0 && m_MilliSecond == 0)
		{
			return false;
		}
		if (m_Hour == 8)
		{
			if(m_Minute == 59)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		// 9:00 to 11:30
		else if(9 <= m_Hour && m_Hour < 12)
		{
			if (m_Hour== 11)
			{
				if (m_Minute > 30)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			else if (m_Hour == 10)
			{
				if (0 <= m_Minute && m_Minute < 16)
				{
					return true;
				}
				else if( 15<m_Minute && m_Minute<29)
				{
					return false;
				}
				else// 大于等于30分的
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
		// 13:30 to 15:00
		else if ( 13 <= m_Hour && m_Hour <= 15)
		{
			if (m_Hour == 13)
			{
				// 25分以后为true
				if (0<=m_Minute && m_Minute<29)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			else if (m_Hour == 15)
			{
				if (m_Minute > 0)
				{
					return false;
				}
				else if(m_Minute == 0)
				{
					if (m_Second == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			//////////////////////////////////////////////////////////////////////////
			// 14:00 返回 在时间范围
			else
			{
				return true;
			}
		}

		else if(m_Hour == 20)
		{
			if (m_Minute == 59)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		// 21:00 to 23:59
		else if(21 <= m_Hour && m_Hour < 24)
		{
			return true;
		}
		// 00:00 to 02:30
		else if (0 <= m_Hour && m_Hour < 3)
		{
			if (m_Hour == 2)
			{
				if ( m_Minute > 30 )
				{
					return false;
				}
				else
				{
					if (m_Minute == 30)
					{
						if (m_Second == 0)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					return true;
				}
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	};

 	bool isInOneMinute(HSTimer inputData)
 	{
 		if (m_Year == inputData.m_Year && m_Month == inputData.m_Month && m_Day == inputData.m_Day && m_Hour == inputData.m_Hour)
 		{
 			if (m_Minute == inputData.m_Minute)
 			{
 				return true;
 			}
 			else if( abs(m_Minute - inputData.m_Minute) == 59)
 			{
 				return false;
  			}
 // 
 		}
 		else
 		{
 			return false;
 		}
 
 	};

	void SetData(CString TimeStr,CString DateStr){
		m_StringTimer = TimeStr;
		m_StringDate = DateStr;
		SplitTimeStr();
		SplitDateStr();
	};


public:
	int m_Year;
	int m_Month;
	int m_Day;
	int m_Hour;
	int m_Minute;
	int m_Second;
	int m_MilliSecond;

	CString m_StringTimer;
	CString m_StringDate;

private:
	void SplitTimeStr(){
		int StringLen = m_StringTimer.GetLength();
		if (StringLen < 9)
		{
			for (int i=0; i<9-StringLen;i++)
			{
				m_StringTimer.Insert(0,_T("0"));
			}
		}

		//
		CString temp_Hour = m_StringTimer.Mid(0,2);
		m_Hour= _ttoi(temp_Hour);
		CString temp_Minute = m_StringTimer.Mid(2,2);
		m_Minute = _ttoi(temp_Minute);
		CString temp_Second = m_StringTimer.Mid(4,2);
		m_Second = _ttoi(temp_Second);
		CString temp_MSecond = m_StringTimer.Mid(6,3);
		m_MilliSecond = _ttoi(temp_MSecond);
	};

	void SplitDateStr(){
		vector<CString> res;

		CString strArr = m_StringDate;
		LPCTSTR strSplit = _T("-");
		CStringArray* arr = new CStringArray;

		int iStart = 0 , iFind = 0;
		do
		{
			iFind = strArr.Find(strSplit , iStart);
			if(iFind == -1)
				arr->Add(strArr.Mid(iStart));
			else
				arr->Add(strArr.Mid(iStart , iFind - iStart));
			iStart = iFind + 1;
		}while(iFind != -1);

		//arr->GetCount()
		for (int i=0; i<arr->GetCount();i++)
		{
			res.push_back(arr->GetAt(i));
		}
		// 用- 分割


		//CString temp_Year = m_StringDate.Mid(0,4);
		m_Year= _ttoi(res.at(0));
		//CString temp_Month = m_StringDate.Mid(5,2);
		m_Month = _ttoi(res.at(1));
		//CString temp_Day = m_StringDate.Mid(8,2);
		m_Day = _ttoi(res.at(2));
		
	};

	bool InFiveMinute(HSTimer otherTimer){
		if (otherTimer.m_Hour == m_Hour)
		{
			// 同一小时之内
			if ( m_Minute = otherTimer.m_Minute)
			{
			}
			else if (m_Minute != otherTimer.m_Minute)
			{

			}
		}
		else if ( abs(otherTimer.m_Hour - m_Hour) == 1 )
		{
			// 跨小时
		}

	};
};





//*************************************
// 函数名:  	SplitStr
// 目的:	如果不足9位则自动补齐
// 时间：   2014/04/01
//*************************************
//void HSTimer::SplitStr()
//{
// 	if (m_String.GetLength() < 9)
// 	{
// 
// 	}
//}



// CString Int2CString(int InputData)
// {
// 	char a[200];
// 	_itoa_s(InputData, a, 10);
// 	CString ss(a);
// 	return ss;
// }



typedef struct  StrategyData
{
public:
	StrategyData(){
 		ID = -1;CODE = _T("");
		HSTIME  = _T("");HSDATE = _T("");
		OpenPrice = 0; ClosePrice =0;
		HightPrice = 0; LowPrice =0;
		BuyVolume = 0; SellVolume =0;
		TradeVolume =0;HoldPosition=0;

	};

	

	StrategyData(vector<CString> inputData){
		//ID = inputData.at(0);
		ID = _ttoi(inputData.at(0));
		CODE = inputData.at(1);
		HSTIME = inputData.at(30);
		HSDATE = inputData.at(50);

		timer.SetData(HSTIME,HSDATE);

		// cstring 转 float
		OpenPrice = _tstof(inputData.at(3));
		ClosePrice = _tstof(inputData.at(7));

		SellPrice = _tstof(inputData.at(4));
		BuyPrice = _tstof(inputData.at(5));

		SellVolume = _ttoi(inputData.at(8));
		BuyVolume = _ttoi(inputData.at(9));

		HightPrice = _tstof(inputData.at(11));
		LowPrice = _tstof(inputData.at(12));

		AveragePrice = _tstof(inputData.at(13));
		TradeVolume = _ttoi(inputData.at(15));
		HoldPosition = _ttoi(inputData.at(16));

		UpLimitPrice = _tstof(inputData.at(18));
		DownLimitPrice = _tstof(inputData.at(19));
	};

	int ID;// ID
	CString CODE;// 编码
	CString HSTIME;// 恒生时间
	CString HSDATE;// 恒生日期

	HSTimer timer;

	float OpenPrice;//开盘价
	float ClosePrice;// 收盘价
	float HightPrice;// 最高价
	float LowPrice;// 最低价
	float AveragePrice;// 均价

	float SellPrice;
	float BuyPrice;

	float UpLimitPrice;
	float DownLimitPrice;

	int BuyVolume;// 买量
	int SellVolume; // 卖量

	int TradeVolume;// 交易量 
	int HoldPosition;// 持仓量


};


enum OPENCLOSE
{
	OPEN = 0,
	CLOSE,
	UNKNOWORDER
};

enum BUYSELL
{
	BUY = 0,
	SELL,
	UNKNOW

};