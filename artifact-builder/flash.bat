@echo off

REM Detect the COM port of the Arduino Mega 2560 using WMIC
for /f "skip=1 tokens=2 delims=," %%A in ('wmic path Win32_SerialPort get DeviceID^,PNPDeviceID^,Description /format:csv') do (
    for /f "tokens=2 delims= " %%B in ("%%~A") do (
        for /f "tokens=2 delims==" %%C in ("%%~B") do (
            for /f "tokens=2 delims= " %%D in ("%%~A") do (
                if "%%~D"=="Arduino" set COM_PORT=%%~C
            )
        )
    )
)

REM Check if COM port was detected
if not defined COM_PORT (
    echo Arduino not found.
    exit /b
)

REM Set the baud rate (usually 115200 for Arduino Mega 2560)
set "BAUD_RATE=115200"

REM Flash the firmware using AVRDUDE
avrdude.exe -v -p atmega2560 -c wiring -P %COM_PORT% -b %BAUD_RATE% -D -U flash:w:firmware.hex:i
