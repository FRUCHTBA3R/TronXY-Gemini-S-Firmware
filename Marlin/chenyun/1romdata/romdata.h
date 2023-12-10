#pragma once

#include "../yCommon.h"

class Output
{
public:
	uint8_t imode;//Number system (decimal,), application is passed in through parameters, used by subclasses
	uint8_t index;//Mark the current Out number, starting from 0
	Output();
	virtual void send(uint8_t byte) const = 0;
	Output& operator<<(const char*tstr)
	{
		while(*tstr)send(*tstr++);
		return *this;
	}
	Output& operator<<(double d);
	Output& operator<<(int i);
	Output& operator<<(uint8_t n){return *this << (int)n;}
	Output& operator<<(short n){return *this << (int)n;}
	Output& operator<<(uint16_t n){return *this << (int)n;}
	Output& operator<<(long n){return *this << (int)n;}
	Output& operator<<(uint32_t n){return *this << (int)n;}
	Output& operator<<(char c){send(c);return *this;}
	Output& operator<<(Output& out(Output&)){return out(*this);}
	void print(const char*str,...);
};
inline Output& dec(Output& o){o.imode = 0;return o;}
inline Output& hex(Output& o){o.imode = 1;return o;}
inline Output& oct(Output& o){o.imode = 2;return o;}
inline Output& bin(Output& o){o.imode = 3;return o;}
inline Output& endl(Output& o){return o << "\r\n";}

typedef enum
{
	NUM2 = 2,//binary
	NUM8 = 8,//Octal
	NUM10 = 10,//decimal
	NUM16 = 16 //hexadecimal
}NUM_MODE;

typedef const char* CPSTR;
typedef char* PSTR;

namespace yString
{
	template<typename T>
	int len(const T*str)//Calculate string length
	{
		if(!str)return 0;
		int n = 0;
		while(str[n])n++;
		return n;
	}

	template<typename T>
	int cmp(const T* sce, const T* tar)//Compare the sizes of two strings, source > target returns 1, source < target returns -1, source == target returns 0
	{
		if (!tar && !sce)return 0;
		if (!tar)return 1;
		if (!sce)return -1;
		while (*sce && *tar){
			if (*sce > *tar)return 1;
			else if (*sce < *tar)return -1;
			sce++;
			tar++;
		}
		if (*sce > *tar)return 1;
		else if (*sce < *tar)return -1;
		return 0;
	}

	template<typename T>
	void cpy(T* tar, const T*sce, int maxlen = 0)//Copy source to target
	{
		if(!tar)return;
		if(!sce) {
			*tar = 0;
			return;
		}
		while (*sce) {
			*tar++ = *sce++;
			if(maxlen) {
				--maxlen;
				if(maxlen == 0)break;
			}
		}
		*tar = 0;
	}

	template<typename T>
	void cat(T* tar,const T*sce)//Append source to target
	{
		if(!tar || !sce)return;
		while(*tar)tar++;
		cpy(tar,sce);
	}
	
	void memzero(void* target,int size);
	/*******************************************************************************
	* Class name	：  Command		*function:	hasElement
	* describe		:   Determine whether there is an independent target string in the source string
					:   Independent: After the target string of the source string, when end!=0xFF, it can only be followed by spaces or '\0' or end characters.
				  	    When end==0xFF it can be any character
	* parameter		:   sce-source string, tar-target string
	* return		:   If it exists, return the position of the target string in the source string, otherwise return -1
	* Writer		：  YSZ		date of writing:2020-03-24
	*******************************************************************************/
	int hasElement(const char* sce,const char* tar,uint8_t end = 0);
	uint8_t startWith(const char*source,const char *target);//Source starts with target and returns 1, otherwise returns 0
	uint8_t endWith(const char *source,const char *target);//Source returns 1 if it ends with target, otherwise returns 0

	template<typename T>
	int alignWidth(T* str, const T*src, int srcLen, int width)
	{
		int i = 0;
		if(width < 0){
			width = -width;
			for(; i < width && i < srcLen; i++)str[i] = src[i];
			for(; i < width; i++)str[i] = ' ';
		}
		else if(width > 0){
			int t = width - srcLen;
			for(; i < t; i++)str[i] = ' ';
			for(; i < width; i++)str[i] = src[i - t];
		}
		else {
			while(i < srcLen)str[i] = src[i];
		}
		str[i] = 0;
		return i;
	}
	/*******************************************************************************
	* Function name		：intToStr
	* describe			: Number to string
	*	parameter		:num source number
						:str The converted string storage address
						:mode number system
	*	return			:Converted string length
	* Writer			：YSZ
	* date of writing	：2019-12-28
	*******************************************************************************/
	template<typename T>
	int intToStr(int num, T* str, NUM_MODE mode)
	{
		int tempv = num, n = 0;
		uint32_t temp,t;
		if (!num){
			str[0] = '0';
			str[1] = 0;
			return 1;
		}
		if (mode == 10 && tempv < 0){
			str[0] = '-';
			n = 1;
			temp = -tempv;
		}
		else temp  = tempv;
		for (t = temp; t; n++)t /= mode;//Find the number of display digits
		str[n] = 0;
		for (t = n - 1; temp > 0; t--){
			str[t] = temp % mode;
					if(str[t] > 9)str[t] = str[t] + 'A' - 10;
					else str[t] += '0';
			temp /= mode;
		}
		return n;
	}

	template<typename T>
	int intToStr(int num, T*str, NUM_MODE mode,int width)
	{
		if(width == 0) return intToStr(num,str,mode);
		T tstr[32];
		int r = intToStr(num,tstr,mode);
		return alignWidth(str,tstr,r,width);
	}
	/*******************************************************************************
	* Function name        ：floatToStr
	* describe          : Convert floating point number to string
	* parameter          :num source number
                   :str The converted string storage address
				   :width The total width after rotation, negative numbers are aligned to the left, positive numbers are aligned to the right
				   :dot_num Number of decimal places after conversion
	* return          :Converted string length
	* Writer        ：YSZ
	* date of writing      ：2019-12-28
	*******************************************************************************/
	template<typename T>
	int floatToStr(float num, T*str,int dot_num = 2, int width = 0) {
		uint8_t i;
		T tstr[32];
		int n, tv;
		float t = 0.5;//precision rounding
		for(i = 0;i < dot_num;i ++)t /= 10;
		if(num < 0) {
			num -= t;
			num = -num;
			n = (int)num;
			if(width == 0) {
				str[0] = '-';
				tv = intToStr(n, str + 1,NUM10) + 1;
			}
			else {
				tstr[0] = '-';
				tv = intToStr(n, tstr + 1,NUM10) + 1;
			}
		}
		else {
			num += t;
			n = (int)num;
			if(width == 0) tv = intToStr(n, str,NUM10);
			else tv = intToStr(n, tstr,NUM10);
		}
		num -= n;
		if(width == 0)str[tv ++] = '.';
		else tstr[tv ++] = '.';
		for (i = 0; i < dot_num; i++,tv ++) {
			num *= 10;
			n = (int)num;
			num -= n;
			if(width == 0)str[tv] = n + '0';
			else tstr[tv] = n + '0';
		}
		if(width == 0) {
			str[tv] = 0;
			return tv;
		}
		return alignWidth(str,tstr,tv,width);
	}

	/*******************************************************************************
	* Function name		：strToInt
	* describe			: Convert string to number
	*	parameter	:str source string
					:mode number system
	*	return	:converted result
	* Writer		：YSZ
	* date of writing	：2020-01-12
	*******************************************************************************/
	template<typename T>
	int strToInt(const T* str,NUM_MODE mode) {
		int n = 0,sign = 1;
		while(*str == ' ')str++;//Skip spaces
		switch(mode)
		{
			case NUM2:
				while(*str == '0' || *str == '1'){
					n = (n << 1) + *str - '0';
					str ++;
				}
				break;
			case NUM8:
				while(*str >= '0' && *str <= '7'){
					n = (n << 3) + *str - '0';
					str ++;
				}
				break;
			case NUM10:
				if(*str == '-'){
					str ++;
					sign = -1;
				}
				while(*str >= '0' && *str <= '9'){
					n = n * 10 + *str - '0';
					str ++;
				}
				n *= sign;
				break;
			case NUM16:
				while(1){
					if(*str >= '0' && *str <= '9')n = (n << 4) + *str - '0';
					else if(*str >= 'A' && *str <= 'F')n = (n << 4) + *str - 'A' + 10;
					else if(*str >= 'a' && *str <= 'f')n = (n << 4) + *str - 'a' + 10;
					else break;
					str ++;
				}
				break;
		}
		return n;
	}

	/*******************************************************************************
	* Function name		：strToDouble
	* describe			: String to floating point number
	*	parameter		:str source string
	*	return			:converted result
	* Writer			：YSZ
	* date of writing	：2020-01-12
	*******************************************************************************/
	template<typename T>
	float strToDouble(const T* str) {
		int sign = 1,dot = 0,pos = 1;
		float d = 0.0;
		while(*str && *str != '-' && (*str < '0' || *str > '9'))str++;//Skip non-numeric fields
		if(!*str)return 0.0;
		if(*str == '-'){
			sign = -1;
			str ++;
		}
		while(1){
			if(*str == '.' && dot == 0){
				dot = 1;
			}else if(*str >= '0' && *str <= '9'){
				if(dot == 1)pos *= 10;
				d = d * 10 + *str - '0';
			}
			else break;
			str ++;
		}
		d /= pos * sign;
		return d;
	}

	inline uint8_t isspace(char x){return x == ' ' || x == '\t' || x == '\f' || x == '\r' || x == '\n';}
	inline uint8_t isseparate(char x,char v){return isspace(x) || x == v;}
	inline void pass(PSTR& x,char v){while(*x && !isseparate(*x,v))x++; while(isseparate(*x,v))x ++;}
};

extern uint32_t romdataAddr;
void romdataUpdate(void);
uint8_t romdataReset(uint32_t taddr,uint32_t period = 200); //Failure return0xFF
uint8_t romdataGetOnebyte(void);//return0xFF may be a failure
uint8_t romdataGetData(uint8_t *dst,int len);//Failure return0xFF
void romdataJump(uint32_t leng);

