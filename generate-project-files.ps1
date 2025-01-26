$platforms = "x64"

if( Test-Path platform/platform_psvita.lua ) {
    $platforms += ",psvita"
}

if( (Test-Path platform/platform_3ds.lua) -and (Test-Path env:DEVKITARM) ) {
    $platforms += ",citra"
}

& "xmake" f --vs=2022
& "xmake" project -k vsxmake -y -m "Debug,Release,Package" -a $platforms ./build

if( $LASTEXITCODE -lt 0 )
{
    write-host "Press any key to continue..."
    [void][System.Console]::ReadKey($true)
}