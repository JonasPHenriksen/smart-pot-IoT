import subprocess

def run_tests():
  command = [
    "platformio",
    "test",
    "-e", "target_run"
  ]
  print("Running tests...")
  try:
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    print(result.stdout)

    # Check test result
    if "FAILED" in result.stdout or "ERRORED" in result.stdout:
      print("Tests failed. Firmware will not be flashed")
    elif "test cases: 0 failed" in result.stdout:
      print("Tests passed. Flashing to avr...")
      return True
    else:
      print("Unable to initialize test_env")
      
  except subprocess.CalledProcessError as e:
    print("error", e)

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
