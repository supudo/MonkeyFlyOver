// file automatically generated using katie!
// http://www.console-dev.de

#ifndef RESOURCEDATA_H
#define RESOURCEDATA_H

#ifdef __cplusplus
	extern "C"{
#endif

// ./gfx/splashscreen/splashscreen.pal
#define RES_SPLASHSCREEN_PAL	0
#define RES_SPLASHSCREEN_PAL_SIZE	512
#define RES_SPLASHSCREEN_PAL_SIZEPADDED	516
#define RES_SPLASHSCREEN_PAL_SIZE16	256
#define RES_SPLASHSCREEN_PAL_SIZE16PADDED	258
#define RES_SPLASHSCREEN_PAL_SIZE32	128
#define RES_SPLASHSCREEN_PAL_SIZE32PADDED	129

// ./gfx/splashscreen/splashscreen.raw
#define RES_SPLASHSCREEN_RAW	516
#define RES_SPLASHSCREEN_RAW_SIZE	38400
#define RES_SPLASHSCREEN_RAW_SIZEPADDED	38404
#define RES_SPLASHSCREEN_RAW_SIZE16	19200
#define RES_SPLASHSCREEN_RAW_SIZE16PADDED	19202
#define RES_SPLASHSCREEN_RAW_SIZE32	9600
#define RES_SPLASHSCREEN_RAW_SIZE32PADDED	9601


#define ResData(_identifier)	((const void*)&__ResourceData__[_identifier])
#define ResData8(_identifier)	((const unsigned char*)&__ResourceData__[_identifier])
#define ResData8X(_identifier, _index)	((const unsigned char*)&__ResourceData__[(_identifier)+(_index)])
#define ResData16(_identifier)	((const unsigned short*)&__ResourceData__[_identifier])
#define ResData16X(_identifier, _index)	((const unsigned short*)&__ResourceData__[(_identifier)+((_index)<<1)])
#define ResData32(_identifier)	((const unsigned long*)&__ResourceData__[_identifier])
#define ResData32X(_identifier, _index)	((const unsigned long*)&__ResourceData__[(_identifier)+((_index)<<2)])
#define ResDataType(_type, _identifier)	((const _type*)&__ResourceData__[_identifier])
#define ResDataTypeX(_type, _identifier, _index)	((const _type*)&__ResourceData__[(_identifier)+((_index)*sizeof(_type)])


extern const unsigned char __ResourceData__[];

#ifdef __cplusplus
	}
#endif

#endif // RESOURCEDATA_H

