#include <stdio.h>
#include <string.h>

const char* funcs =
"void|Test|int _x\n"
"int|TestOther|float _r, float _g, float _b\n";

#if _MSC_VER && !__INTEL_COMPILER
#define strtok_r strtok_s
#endif

void parseString( const char* _str )
{
	const char* lineDel = "\n";
	const char* tokenDel = "|";

	const char* nameSuffix = "gfx";
	const char* typeSuffix = "_t";

	char* end_str = 0;
	char* end_token = 0;
	
	for( char* line = strtok_r( _str, lineDel, &end_str ); line; line = strtok_r( NULL, lineDel, &end_str ) )
	{
		int tokenIdx = 0;

		char* ret = 0;
		char* name = 0;
		char* args = 0;

		for ( char* token = strtok_r( line, tokenDel, &end_token ); token; token = strtok_r( NULL, tokenDel, &end_token ) )
		{
			switch ( tokenIdx )
			{
			case 0: ret  = token; break;
			case 1: name = token; break;
			case 2: args = token; break;
			}
			
			tokenIdx++;
		}

		printf( "typedef %s ( *%s%s_t )( %s );\n", ret, nameSuffix, name, args );
		printf( "%s%s_t fp_%s%s;\n", nameSuffix, name, nameSuffix, name );
		printf( "#define %s%s fp_%s%s\n\n", nameSuffix, name, nameSuffix, name );
	}

}

int main()
{
	parseString( funcs );


	return 0;
}