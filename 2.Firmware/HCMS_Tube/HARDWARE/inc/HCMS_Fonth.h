#ifndef __HCMS_Fonth_H
#define __HCMS_Fonth_H 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//�����ߣ�����LCLR
//������̳:www.54lcl.com
//�޸�����:2020/03/20
//�汾��V2.0
//All rights reserved									  

const long long unsigned int Fonth[95]={
0X0000000000,/*" ",0 */
0X00005F0000,/*" ",1 */    
0X0006000600,/*""",2 */
0X147F147F14,/*"#",3 */
0x242A072A12,/*"$",4 */    
0x2313086462,/*"%",5 */    
0x3749552250,/*"&",6 */
0x0005030000,/*"'",7 */
0x001C224100,/*"(",8 */
0x0041221C00,/*")",9 */
0x082A1C2A08,/*"*",10*/
0x08083E0808,/*"+",11*/
0x0050300000,/*",",12*/
0x0808080808,/*"-",13*/
0x0060600000,/*".",14*/
0x2010080402,/*"/",15*/
0x3E5149453E,/*"0",16*/
0x00427F4000,/*"1",17*/
0x4261514946,/*"2",18*/
0x2141454B31,/*"3",19*/
0x1814127F10,/*"4",20*/
0x2745454539,/*"5",21*/
0x3C4A494930,/*"6",22*/
0x0171090503,/*"7",23*/
0x3649494936,/*"8",24*/
0x064949291E,/*"9",25*/
0x0036360000,/*":",26*/
0x0056360000,/*";",27*/
0x0008142241,/*"<",28*/
0x1414141414,/*"=",29*/
0x4122140800,/*">",30*/
0x0201510906,/*"?",31*/
0x324979413E,/*"@",32*/
0x7E1111117E,/*"A",33*/
0x7F49494936,/*"B",34*/
0x3E41414122,/*"C",35*/
0x7F4141221C,/*"D",36*/
0x7F49494941,/*"E",37*/
0x7F09090101,/*"F",38*/
0x3E41415132,/*"G",39*/
0x7F0808087F,/*"H",40*/
0x00417F4100,/*"I",41*/
0x2040413F01,/*"J",42*/
0x7F08142241,/*"K",43*/
0x7F40404040,/*"L",44*/
0x7F0204027F,/*"M",45*/
0x7F0408107F,/*"N",46*/
0x3E4141413E,/*"O",47*/
0x7F09090906,/*"P",48*/
0x3E4151215E,/*"Q",49*/
0x7F09192946,/*"R",50*/
0x4649494931,/*"S",51*/
0x01017F0101,/*"T",52*/
0x3F4040403F,/*"U",53*/
0x1F2040201F,/*"V",54*/
0x7F2018207F,/*"W",55*/
0x6314081463,/*"X",56*/
0x0304780403,/*"Y",57*/
0x6151494543,/*"Z",58*/
0x00007F4141,/*"[",59*/
0x0204081020,/*"\",60*/
0x41417F0000,/*"]",61*/
0x0402010204,/*"^",62*/
0x4040404040,/*"_",63*/
0x0001020400,/*"`",64*/
0x2054545478,/*"a",65*/
0x7F48444438,/*"b",66*/
0x3844444420,/*"c",67*/
0x384444487F,/*"d",68*/
0x3854545418,/*"e",69*/
0x087E090102,/*"f",70*/
0x081454543C,/*"g",71*/
0x7F08040478,/*"h",72*/
0x00447D4000,/*"i",73*/
0x2040443D00,/*"j",74*/
0x007F102844,/*"k",75*/
0x00417F4000,/*"l",76*/
0x7C04180478,/*"m",77*/
0x7C08040478,/*"n",78*/
0x3844444438,/*"o",79*/
0x7C14141408,/*"p",80*/
0x081414187C,/*"q",81*/
0x7C08040408,/*"r",82*/
0x4854545420,/*"s",83*/
0x043F444020,/*"t",84*/
0x3C4040207C,/*"u",85*/
0x1C2040201C,/*"v",86*/
0x3C4030403C,/*"w",87*/
0x4428102844,/*"x",88*/
0x0C5050503C,/*"y",89*/
0x4464544C44,/*"z",90*/
0x0008364100,/*"{",91*/
0x00007F0000,/*"|",92*/
0x0041360800,/*"}",93*/
0x0201020402,/*"~",94*/

};


const unsigned char Four_Fonth[95][5]={
{0X00,0x00,0x00,0x00,0x00},/*" ",0*/
{0X00,0x00,0x5F,0x00,0x00},/*" ",0*/    
{0X00,0x06,0x00,0x06,0x00},/*""",2*/
{0X14,0x7F,0x14,0x7F,0x14},/*"#",3*/
{0x24,0x2A,0x07,0x2A,0x12},/*"$",4*/    
{0x23,0x13,0x08,0x64,0x62},/*"%",5*/    
{0x37,0x49,0x55,0x22,0x50},/*"&",6*/
{0x00,0x05,0x03,0x00,0x00},/*"'",89*/
{0x00,0x1C,0x22,0x41,0x00},/*"(",89*/
{0x00,0x41,0x22,0x1C,0x00},/*")",89*/
{0x08,0x2A,0x1C,0x2A,0x08},/*"*",89*/
{0x08,0x08,0x3E,0x08,0x08},/*"+",89*/
{0x00,0x50,0x30,0x00,0x00},/*",",89*/
{0x08,0x08,0x08,0x08,0x08},/*"-",89*/
{0x00,0x60,0x60,0x00,0x00},/*".",89*/
{0x20,0x10,0x08,0x04,0x02},/*"/",89*/
{0x3E,0x51,0x49,0x45,0x3E},/*"0",89*/
{0x00,0x42,0x7F,0x40,0x00},/*"1",89*/
{0x42,0x61,0x51,0x49,0x46},/*"2",89*/
{0x21,0x41,0x45,0x4B,0x31},/*"3",89*/
{0x18,0x14,0x12,0x7F,0x10},/*"4",89*/
{0x27,0x45,0x45,0x45,0x39},/*"5",89*/
{0x3C,0x4A,0x49,0x49,0x30},/*"6",89*/
{0x01,0x71,0x09,0x05,0x03},/*"7",89*/
{0x36,0x49,0x49,0x49,0x36},/*"8",89*/
{0x06,0x49,0x49,0x29,0x1E},/*"9",89*/
{0x00,0x36,0x36,0x00,0x00},/*":",89*/
{0x00,0x56,0x36,0x00,0x00},/*";",89*/
{0x00,0x08,0x14,0x22,0x41},/*"<",89*/
{0x14,0x14,0x14,0x14,0x14},/*"=",89*/
{0x41,0x22,0x14,0x08,0x00},/*">",89*/
{0x02,0x01,0x51,0x09,0x06},/*"?",89*/
{0x32,0x49,0x79,0x41,0x3E},/*"@",89*/
{0x7E,0x11,0x11,0x11,0x7E},/*"A",89*/
{0x7F,0x49,0x49,0x49,0x36},/*"B",89*/
{0x3E,0x41,0x41,0x41,0x22},/*"C",89*/
{0x7F,0x41,0x41,0x22,0x1C},/*"D",89*/
{0x7F,0x49,0x49,0x49,0x41},/*"`E",89*/
{0x7F,0x09,0x09,0x01,0x01},/*"F",89*/
{0x3E,0x41,0x41,0x51,0x32},/*"G",89*/
{0x7F,0x08,0x08,0x08,0x7F},/*"H",89*/
{0x00,0x41,0x7F,0x41,0x00},/*"I",89*/
{0x20,0x40,0x41,0x3F,0x01},/*"J",89*/
{0x7F,0x08,0x14,0x22,0x41},/*"K",89*/
{0x7F,0x40,0x40,0x40,0x40},/*"L",89*/
{0x7F,0x02,0x04,0x02,0x7F},/*"M",89*/
{0x7F,0x04,0x08,0x10,0x7F},/*"N",89*/
{0x3E,0x41,0x41,0x41,0x3E},/*"O",89*/
{0x7F,0x09,0x09,0x09,0x06},/*"P",89*/
{0x3E,0x41,0x51,0x21,0x5E},/*"Q",89*/
{0x7F,0x09,0x19,0x29,0x46},/*"R",89*/
{0x46,0x49,0x49,0x49,0x31},/*"S",89*/
{0x01,0x01,0x7F,0x01,0x01},/*"T",89*/
{0x3F,0x40,0x40,0x40,0x3F},/*"U",89*/
{0x1F,0x20,0x40,0x20,0x1F},/*"V",89*/
{0x7F,0x20,0x18,0x20,0x7F},/*"W",89*/
{0x63,0x14,0x08,0x14,0x63},/*"X",89*/
{0x03,0x04,0x78,0x04,0x03},/*"Y",89*/
{0x61,0x51,0x49,0x45,0x43},/*"Z",89*/
{0x00,0x00,0x7F,0x41,0x41},/*"[",89*/
{0x02,0x04,0x08,0x10,0x20},/*"\",89*/
{0x41,0x41,0x7F,0x00,0x00},/*"]",89*/
{0x04,0x02,0x01,0x02,0x04},/*"^",89*/
{0x40,0x40,0x40,0x40,0x40},/*"_",89*/
{0x00,0x01,0x02,0x04,0x00},/*"`",89*/
{0x20,0x54,0x54,0x54,0x78},/*"a",89*/
{0x7F,0x48,0x44,0x44,0x38},/*"b",89*/
{0x38,0x44,0x44,0x44,0x20},/*"c",89*/
{0x38,0x44,0x44,0x48,0x7F},/*"d",89*/
{0x38,0x54,0x54,0x54,0x18},/*"e",89*/
{0x08,0x7E,0x09,0x01,0x02},/*"f",89*/
{0x08,0x14,0x54,0x54,0x3C},/*"g",89*/
{0x7F,0x08,0x04,0x04,0x78},/*"h",89*/
{0x00,0x44,0x7D,0x40,0x00},/*"i",89*/
{0x20,0x40,0x44,0x3D,0x00},/*"j",89*/
{0x00,0x7F,0x10,0x28,0x44},/*"k",89*/
{0x00,0x41,0x7F,0x40,0x00},/*"l",89*/
{0x7C,0x04,0x18,0x04,0x78},/*"m",89*/
{0x7C,0x08,0x04,0x04,0x78},/*"n",89*/
{0x38,0x44,0x44,0x44,0x38},/*"o",89*/
{0x7C,0x14,0x14,0x14,0x08},/*"p",89*/
{0x08,0x14,0x14,0x18,0x7C},/*"q",89*/
{0x7C,0x08,0x04,0x04,0x08},/*"r",89*/
{0x48,0x54,0x54,0x54,0x20},/*"s",89*/
{0x04,0x3F,0x44,0x40,0x20},/*"t",89*/
{0x3C,0x40,0x40,0x20,0x7C},/*"u",89*/
{0x1C,0x20,0x40,0x20,0x1C},/*"v",89*/
{0x3C,0x40,0x30,0x40,0x3C},/*"w",89*/
{0x44,0x28,0x10,0x28,0x44},/*"x",89*/
{0x0C,0x50,0x50,0x50,0x3C},/*"y",89*/
{0x44,0x64,0x54,0x4C,0x44},/*"z",90*/
{0x00,0x08,0x36,0x41,0x00},/*"{",91*/
{0x00,0x00,0x7F,0x00,0x00},/*"|",92*/
{0x00,0x41,0x36,0x08,0x00},/*"}",93*/
{0x02,0x01,0x02,0x04,0x02},/*"~",94*/
};                       


#endif