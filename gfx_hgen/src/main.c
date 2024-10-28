#include <stdio.h>
#include <string.h>
#include <malloc.h>

#if _MSC_VER && !__INTEL_COMPILER
#define strtok_r strtok_s
#endif

void parseFunc( FILE* _pOutFile, const char* _str )
{
	const char* typeSuffix = "_t";

	char* end_str = 0;
	
	char* ret  = strtok_r( _str, " ", &end_str);
	char* name = strtok_r( NULL, "(", &end_str );
	char* args = strtok_r( NULL, ")", &end_str );
	
	char l1[ 200 ];
	char l2[ 200 ];
	char l3[ 200 ];

	sprintf( l1, "typedef %s (*%s%s)(%s);", ret, name, typeSuffix, args );
	sprintf( l2, "%s%s fp_%s;", name, typeSuffix, name );
	sprintf( l3, "#define %s fp_%s", name, name );

	if ( _pOutFile )
		fprintf( _pOutFile, "%s\n%s\n%s\n\n", l1, l2, l3 );
	else
		printf( "%s\n%s\n%s\n\n", l1, l2, l3 );

}

void parseFile( FILE* _pInputFile, FILE* _pOutFile )
{
	fseek( _pInputFile, 0, SEEK_END );
	size_t fileSize = ftell( _pInputFile );
	rewind( _pInputFile );

	if ( fileSize == 0 )
		return 1;

	char* inputStr = malloc( fileSize );
	if ( inputStr == 0 )
		return;

	fread( inputStr, sizeof( char ), fileSize, _pInputFile );

	char* endStr = 0;

	char* prepend = strtok_r( inputStr, "//", &endStr );
	fprintf( _pOutFile, prepend );
	
	char* line = strtok_r( NULL, "\n", &endStr );

	while ( line )
	{
		int length = strlen( line );
		if( line[ length-1 ] == ';' )
			parseFunc( _pOutFile, line );

		line = strtok_r( NULL, "\n", &endStr );
	}
}

int main( int argc, char* argv[] )
{
	/*
	if ( argc < 2 )
	{
		const char* testStr = "void gfxTest(int _a, int _b);";
		parseFunc( 0, testStr );
		
		return 0;
	}
	*/

	char* inPath  = argc > 1 ? argv[ 1 ] : "funcs.h";
	char* outPath = argc > 2 ? argv[ 2 ] : "out.h";

	FILE* pInput = fopen( inPath, "r" );
	if ( !pInput ) return 1;

	FILE* pOutput = fopen( outPath, "w" );
	if ( !pOutput ) return 1;

	parseFile( pInput, pOutput );

	fclose( pInput );
	fclose( pOutput );

	return 0;
}