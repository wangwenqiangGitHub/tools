//=====================================================================
//
// h264.cpp - 
//
// Created by wwq on 2022/08/10
// Last Modified: 2022/08/10 20:31:42
// H.264码流解析程序，可以分离并解析NALU
//=====================================================================

/***
原理：
H.264原始码流(又称为"裸流")是由一个一个的NALU组成的，结构如下:
|-----------------------------------------|
|...| NALU | NALU | NALU | NALU | ...     |
|-----------------------------------------|
NALU(Network Abstract Layer Unit)其中每个NALU之间通过startcode(起始码)进行分割，起始码分成两种:0x000001(3Byte)或者0x00000001(4Byte)。如果NALU对应的Slice为一帧的开始就用0x00000001,否则就用0x000001。
H.264码流解析的步骤就是首先从码流中搜索0x000001和0x00000001，分离出NALU;然后在分析NALU的各个字段.
 ***/
/**int fseek( FILE *stream, long offset, int origin );
 * 第一个参数stream为文件指针
 * 第二个参数offset为偏移量，整数表示正向偏移，负数表示负向偏移
 * 第三个参数origin设定从文件的哪里开始偏移,可能取值为：SEEK_CUR、 SEEK_END 或 SEEK_SET)
 * SEEK_SET： 文件开头
 * SEEK_CUR： 当前位置
 * SEEK_END： 文件结尾
fseek(fp,100L,0);把fp指针移动到离文件开头100字节处；
fseek(fp,100L,1);把fp指针移动到离文件当前位置100字节处；
fseek(fp,100L,2);把fp指针退回到离文件结尾100字节处。
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
	NALU_TYPE_SLICE    = 1,
	NALU_TYPE_DPA      = 2,
	NALU_TYPE_DPB      = 3,
	NALU_TYPE_DPC      = 4,
	NALU_TYPE_IDR      = 5,
	NALU_TYPE_SEI      = 6,
	NALU_TYPE_SPS      = 7,
	NALU_TYPE_PPS      = 8,
	NALU_TYPE_AUD      = 9,
	NALU_TYPE_EOSEQ    = 10,
	NALU_TYPE_EOSTREAM = 11,
	NALU_TYPE_FILL     = 12,
} NaluType;

typedef enum {
	NALU_PRIORITY_DISPOSABLE   = 0,
	NALU_PRIORITY_LOW          = 1,
	NALU_PRIORITY_HIGH       = 2,
	NALU_PRIORITY_HIGHEST    = 3
} NaluPriority;


typedef struct
{
	int startcodeprefix_len;
	unsigned len;
	unsigned max_size;
	int forbidden_bit;
	int nal_reference_idc;
	int nal_unit_type;
	char* buf;
} NALU_t;

FILE *h264bitstream = NULL;

int info2 = 0, info3 = 0;

static int FindStartCode2(unsigned char* Buf)
{
	if(Buf[0]!=0 || Buf[1] != 0 || Buf[2] != 1) return 0;//0x000001?
	else return 1;
}


static int FindStartCode3 (unsigned char *Buf){
	if(Buf[0]!=0 || Buf[1]!=0 || Buf[2] !=0 || Buf[3] !=1) return 0;//0x00000001?
	else return 1;
}

int GetAnnexbNALU(NALU_t *nalu)
{
	int pos = 0;
	int StartCodeFound, rewind;
	unsigned char* Buf;

	if((Buf = (unsigned char*)calloc(nalu->max_size,sizeof(char))) == NULL)
	{
		printf("GetAnnexbNALU: Could not allocate Buf memory\n");
	}
	nalu->startcodeprefix_len = 3;
	
	if(3 != fread(Buf, 1, 3, h264bitstream)){
		free(Buf);
		return 0;
	}
	info2 = FindStartCode2(Buf);
	if(info2!=1)
	{
		if(1!= fread(Buf+3, 1, 1, h264bitstream))
		{
			free(Buf);
			return 0;
		}
		info3 = FindStartCode3(Buf);
		if(info3!=1)
		{
			free(Buf);
			return -1;
		}else{
			pos = 4;
			nalu->startcodeprefix_len = 4;
		}
	}
	else
	{
		nalu->startcodeprefix_len = 3;
		pos = 3;
	}

	StartCodeFound = 0;
	info2 = 0;
	info3 = 0;

	while(!StartCodeFound)
	{
		//检测流上的文件结束符，如果结束返回非0，否则返回0.
		if(feof(h264bitstream)){
			nalu->len = (pos -1)-nalu->startcodeprefix_len;
			memcpy(nalu->buf, &Buf[nalu->startcodeprefix_len], nalu->len);
			nalu->forbidden_bit = nalu->buf[0] & 0x80; //1 bit
			nalu->nal_reference_idc = nalu->buf[0] & 0x60; // 2 bit
			nalu->nal_unit_type = (nalu->buf[0]) & 0x1f;// 5 bit
			free(Buf);
			return pos-1;
		}
		Buf[pos++] = fgetc(h264bitstream);
		info3 = FindStartCode3(&Buf[pos - 4]);
		if(info3 != 1)
			info2 = FindStartCode2(&Buf[pos-3]);
		StartCodeFound = (info2 == 1 || info3 == 1);
	}

	// Here, we have found another start code(and read length of startcode bytes more than we should have, Hence, go back in the file)
	
	rewind = (info3 == 1)? -4 : -3;

	if(0!=fseek(h264bitstream, rewind, SEEK_CUR)){
		free(Buf);
		printf("GetAnnexbNALU:cannot fseek in the bit stream file\n");
	}

	nalu->len = (pos+rewind)-nalu->startcodeprefix_len;
	memcpy(nalu->buf, &Buf[nalu->startcodeprefix_len], nalu->len);
	nalu->forbidden_bit = nalu->buf[0] & 0x80; //1 bit
	nalu->nal_reference_idc = nalu->buf[0] & 0x60; // 2 bit
	nalu->nal_unit_type = (nalu->buf[0]) & 0x1f;// 5 bit
	free(Buf);
	return 0;
}

int simplest_h264_parser(char* url)
{
	NALU_t *n;
	int buffersize = 100000;

	// FILE *myout=fopen("output_log.txt", "wb+");
	FILE* myout=stdout;
	h264bitstream = fopen(url, "rb+");
	if(h264bitstream == NULL){

	}
	n = (NALU_t*)calloc(1, sizeof(NALU_t));
	if(n == NULL){
		printf("Alloc NALU Erro\n");
		return 0;
	}
	n->max_size = buffersize;
	n->buf = (char*) calloc(buffersize, sizeof(char));
	if(n->buf == NULL){
		free(n);
		printf("AllocNALU; n->buf\n");
		return 0;
	}


	int data_offset=0;
	int nal_num=0;
	printf("-----+-------- NALU Table ------+---------+\n");
	printf(" NUM |    POS  |    IDC |  TYPE |   LEN   |\n");
	printf("-----+---------+--------+-------+---------+\n");


	while(!feof(h264bitstream))
	{
		int data_lenth;
		data_lenth = GetAnnexbNALU(n);

		char type_str[20]={0};
		switch(n->nal_unit_type){
			case NALU_TYPE_SLICE:sprintf(type_str, "SLICE");break;
			case NALU_TYPE_DPA:sprintf(type_str,"DPA");break;
			case NALU_TYPE_DPB:sprintf(type_str,"DPB");break;
			case NALU_TYPE_DPC:sprintf(type_str,"DPC");break;
			case NALU_TYPE_IDR:sprintf(type_str,"IDR");break;
			case NALU_TYPE_SEI:sprintf(type_str,"SEI");break;
			case NALU_TYPE_SPS:sprintf(type_str,"SPS");break;
			case NALU_TYPE_PPS:sprintf(type_str,"PPS");break;
			case NALU_TYPE_AUD:sprintf(type_str,"AUD");break;
			case NALU_TYPE_EOSEQ:sprintf(type_str,"EOSEQ");break;
			case NALU_TYPE_EOSTREAM:sprintf(type_str,"EOSTREAM");break;
			case NALU_TYPE_FILL:sprintf(type_str,"FILL");break;
		}
		char idc_str[20]={0};
		switch(n->nal_reference_idc >> 5){
			case NALU_PRIORITY_DISPOSABLE:sprintf(idc_str, "DISPOS");break;
			case NALU_PRIORITY_LOW: sprintf(idc_str,"LOW");break;
			case NALU_PRIORITY_HIGH:sprintf(idc_str,"HIGH");break;
			case NALU_PRIORITY_HIGHEST:sprintf(idc_str,"HIGHEST");break;
		}

		fprintf(myout,"%5d| %8d| %7s| %6s| %8d|\n",nal_num,data_offset,idc_str,type_str,n->len);
		data_offset = data_offset + data_lenth;
		nal_num++;
	}
	if(n)
	{
		if(n->buf){
			free(n->buf);
			n->buf= NULL;
		}
	}

	return 0;
}

__int32_t read_bytes(char* p)
{
	__int32_t value;
	char* pp = (char*)&value;
	pp[3] = *p++;
	pp[2] = *p++;
	printf("%d\n",pp[2]);
	pp[1] = *p++;
	pp[0] = *p++;
	return value;

}
int main(int argc, char** argv)
{
	simplest_h264_parser("sintel.h264");
	return 0;
}
