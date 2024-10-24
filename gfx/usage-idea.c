

typedef struct GpuImage { int width, height; } GpuImage;
typedef struct GpuImageView GpuImageView;
typedef struct GpxTexture GpxTexture;
typedef struct GpxSprite GpxSprite;
typedef struct GpsSpriteBatch GpsSpriteBatch;
typedef struct GpxSpriteBatch GpxSpriteBatch;
typedef struct GpxCamera GpxCamera;

int FTR_IMAGE_FORMAT_RGBA8;






int main()
{
    /* gpu interface */
    void* pData;
    unsigned int dataSize;
    GpuImage* pImage = gpuCreateImage();
    gpuBufferImageData( pImage, pData, dataSize );

    GpuImageView* pImageView = gpuCreateImageView( pImage, pImage->width, pImage->height, FTR_IMAGE_FORMAT_RGBA8 );



    /* gpx interface */
    
    GpxCamera* pCamera;

    GpxTexture* pSpritesheet  = gpxLoadTexture( "player.png" );
    GpxSprite*  pPlayerSprite = gpxLoadSprite( pSpritesheet, 0, 0, 64, 64 );
    GpxSprite*  pEnemySprite  = gpxLoadSprite( pSpritesheet, 64, 0, 64, 64 );
    GpxSprite*  pHealthBarSprite;

    GpsSpriteBatch* pBackgroundSB = gpxSpriteBatchBegin();
    /* draw background sprites */
    gpxSpriteBatchEnd( pBackgroundSB );


    // layer 1
    GpxSpriteBatch* pEntitySB = gpxSpriteBatchBegin();
    gpxDrawSprite2D( pEntitySB, pPlayerSprite, 100, 100, 64, 64 );
    gpxDrawSprite2D( pEntitySB, pEnemySprite,  30,   80, 64, 64 );
    /* draw entity sprites */
    gpxSpriteBatchEnd( pEntitySB );


    GpxSpriteBatch* pForegroundSB = gpxSpriteBatchBeginEx( pCamera, 0, 0, 1.0f );
    gpxRasterSprite3D(  /* raster sprite in 3D space using 3D coordinates */
            pForegroundSB, 
            pHealthBarSprite, 
            0, 0, 0, /* top left */
            1, 0, 0, /* top right */
            1, 1, 0, /* bottom right */
            0, 1, 0  /* bottom left */ );
            
    /* draw foreground sprites */
    gpxSpriteBatchEnd( pForegroundSB );


    gpxClearScreen( 0.0f, 0.0f, 0.0f, 1.0f );
    gpxSpriteBatchSubmit( pBackgroundSB );
    gpxSpriteBatchSubmit( pEntitySB );
    gpxSpriteBatchSubmit( pForegroundSB );
    gpxDisplayScreen();
}













