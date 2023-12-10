
#pragma once

inline unsigned int buffToInt(void const *src, int bytes)
{
	unsigned char *p = (unsigned char*)src;
	switch (bytes)
	{
		case 4:
			return(*p | *(p + 1) << 8 | *(p + 2) << 16 | *(p + 3) << 24);
		case 3: 
			return(*p | *(p + 1) << 8 | *(p + 2) << 16);
		case 2:
			return(*p | *(p + 1) << 8);
		case 1: 
			return(*p);
	}
	return 0;
}
inline void intToBuff(unsigned int f, void *dst, unsigned int bytes)
{
	unsigned char *p = (unsigned char*)dst;
	switch (bytes){
		case 4: 
			*p = (unsigned char)f;
			*(p + 1) = (unsigned char)(f >> 8);
			*(p + 2) = (unsigned char)(f >> 16);
			*(p + 3) = (unsigned char)(f >> 24);
			return;
		case 3:
			*p = (unsigned char)f;
			*(p + 1) = (unsigned char)(f >> 8);
			*(p + 2) = (unsigned char)(f >> 16);
			return;
		case 2:
			*p = (unsigned char)f;
			*(p + 1) = (unsigned char)(f >> 8);
			return;
		case 1:
			*p = (unsigned char)f;
			return;
	}
}
unsigned int yDecompressSize(const void *source);//Read from the compressed file stream to the large amount of data generated after decompressing the file.
unsigned int yCompressSize(const void *source);//Read the compressed data size from the compressed file stream (not the size of the file itself)
int yCompress(const void *source, void *destination, unsigned int totalSize,const unsigned short sector);
unsigned int yDecompress(const void *source, void *destination);
unsigned int _decompress(const void *source, int sorceLen, void *destination,int decompressSize);


