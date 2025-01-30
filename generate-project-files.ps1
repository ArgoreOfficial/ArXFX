$platforms = "x64"

if( Test-Path xmake/psp2/xmake.lua ) {
    # $platforms += ",psp2"
}

if( (Test-Path xmake/arm_3ds/xmake.lua ) -and (Test-Path env:DEVKITARM) ) {
    # $platforms += ",arm_3ds"
}

& "xmake" f -c --vs=2022
& "xmake" project -k vsxmake -y -m "Debug,Release,Package" -a $platforms ./build

if( $LASTEXITCODE -lt 0 )
{
    write-host "Press any key to continue..."
    [void][System.Console]::ReadKey($true)
}