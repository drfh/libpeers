
#ifndef libpeers_ip_h
#define libpeers_ip_h

#ifdef __cplusplus
extern "C" {
#endif


int ParseIPv4OrIPv6 ( const char** ppszText,unsigned char* abyAddr, int* pnPort, int* pbIsIPv6);


//simple version if we want don't care about knowing how much we ate
int ParseIPv4OrIPv6_2 ( const char* pszText,unsigned char* abyAddr, int* pnPort, int* pbIsIPv6);



#ifdef __cplusplus
}
#endif

#endif	// libpeers_ip_h
