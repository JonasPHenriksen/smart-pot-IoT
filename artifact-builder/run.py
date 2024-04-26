import os
import subprocess

def main():
    # Get the path to the batch file
    current_dir = os.path.dirname(os.path.realpath(__file__))
    batch_file_path = os.path.join(current_dir, "flash.bat")

    # Run the batch file
    subprocess.run(batch_file_path, shell=True)

if __name__ == "__main__":
    main()
