/**
 * Compile this with rpcgen
 */

struct CookieStruct
{
	int CanHaveCookie;
	int JudyOrTina;
};

program COOKIE_JAR
{
	version COOKIE_JAR_VERSION
	{
		int GET_ME_MY_COOKIE(struct CookieStruct) = 1;
	} = 1;
} = 0x84467008;
