import serial.tools.list_ports
import os

def find_connected_devices():
  devices = [
    (p.device, p.description.split(':')[-1].strip())
    for p in serial.tools.list_ports.comports()
    if 'USB Serial Device' in p.description or 'Arduino Mega 2560' in p.description
  ]
  if not devices:
    print("No devices found.")
    exit(1)
  
  # Print all connected devices
  # print("Connected devices:")
  # for port, description in devices:     
  #   print(f"- {description}: {port}")
  return devices

def pio_penv_exists():
  user_profile = os.getenv("USERPROFILE")
  if user_profile:
    platformio_python = os.path.join(user_profile, ".platformio", "penv", "Scripts", "python.exe")
    return os.path.exists(platformio_python)

rgb = lambda r,g,b: f"\u001b[38;2;{r};{g};{b}m"
def yellow(text):
  return f"{rgb(255, 198, 51)}» {text}\u001b[0m"

def prompt_yes_no(message):
  while True:
    choice = input(yellow(f"{message} (Y/N): ")).strip().lower()
    if choice in ["y", "yes"]:
      return True
    elif choice in ["n", "no"]:
      return False
    else:
      print("\033[F\033[K", end="")

def prompt_text(message):
  return input(yellow(f"{message}: ")).strip()