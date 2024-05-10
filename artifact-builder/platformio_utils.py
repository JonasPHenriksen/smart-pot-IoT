import subprocess
import sys
from platformio.test.cli import cli
from io import StringIO


def run_tests():
  # Capture output when running tests in buffer
  # stderr is used since conclusion is printed here
  stdout_capture = StringIO()
  sys.stderr = stdout_capture

  # Run tests
  try:
    cli.main(["-e", "target_run"])
  except:
    pass
  
  # Reset to default buffer
  sys.stderr = sys.__stderr__

  result = stdout_capture.getvalue()

  if "test cases: 0 failed" in result:
    print("Tests passed. Flashing to avr...")
    return True

  print("Tests failed. Firmware will not be flashed.")

# Flash the firmware using AVRDUDE for Arduino devices
def flash_firmware(devices):
  # Set the baud rate (115200 for Arduino Mega 2560)
  BAUD_RATE = "115200"

  for port, description in devices:
    command = [
      "avrdude.exe",
      "-v", "-p", "atmega2560", "-c", "wiring",
      "-P", port, "-b", BAUD_RATE,
      "-D", "-U", "flash:w:firmware.hex:i"
    ]
    print(f"Flashing firmware to {port} at {BAUD_RATE} baud...")
    try:
      subprocess.run(command, check=True)
    except subprocess.CalledProcessError as e:
      print("error", e)

def install_platformio():
  pass
