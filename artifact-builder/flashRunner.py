from platformio_utils import *
from github_utils import *

if __name__ == "__main__":
  os.system("cls")
  print("""
  ╭────────────────────────────╮
  │ SMART POT FIRMWARE FLASHER │
  ╰────────────────────────────╯
  """)

  # Provide GitHub repository information to retrieve workflow ID
  GITHUB_OWNER = "JonasPHenriksen"
  GITHUB_REPO = "smart-pot-IoT"
  GITHUB_TOKEN = "INSERT_GITHUB_TOKEN" 

  # Get connected serial devices
  connected_devices = find_connected_devices()
  
  # Get latest workflow run id or custom run id
  run_id = prompt_run_id(GITHUB_OWNER, GITHUB_REPO, GITHUB_TOKEN)

  # Get firmware with run id
  if run_id:
    if not download_github_artifact(GITHUB_OWNER, GITHUB_REPO, GITHUB_TOKEN, run_id, "firmware"):
      exit(1)

  # Setup test environment and run tests
  if prompt_yes_no("Run tests before flashing?"):
    if run_id:
      if not download_github_artifact(GITHUB_OWNER, GITHUB_REPO, GITHUB_TOKEN, run_id, "test-env"):
        exit(1)
    if not pio_penv_exists():
      install_platformio()
    if not run_tests():
      exit(1)

  flash_firmware(connected_devices)
  os.system('pause')