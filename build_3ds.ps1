& "xmake" f -c -p 3ds -a arm_3ds -m debug
& "xmake" -v

if( $LASTEXITCODE -lt 0 )
{
    write-host "Press any key to continue..."
    [void][System.Console]::ReadKey($true)
}