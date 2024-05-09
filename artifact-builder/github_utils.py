import os
import requests
from zipfile import ZipFile
from utils import *

# Function to get the latest workflow run ID
def prompt_run_id(owner, repo, token):
  if prompt_yes_no("Use latest workflow run?"):
    url = f"https://api.github.com/repos/{owner}/{repo}/actions/runs"
    headers = { "Authorization": f"token {token}" }
    response = requests.get(url, headers=headers)
    
    if response.status_code != 200:
      print(f"Failed to fetch workflow runs. Status code: {response.status_code}")
      return

    workflow_runs = response.json()["workflow_runs"]
    if not workflow_runs:
      print("No workflow runs found.")
      return

    # Return the first run with a successful conclusion
    for i in range(len(workflow_runs)):
      run = workflow_runs[i]
      if (run["conclusion"] == "success"):
        return run["id"]
    
  elif prompt_yes_no("Use existing workflow run?"):
    return prompt_text("Workflow run id")
  
# Function to download GitHub workflow artifacts
def download_github_artifact(owner, repo, token, run_id, artifact_name):
  url = f"https://api.github.com/repos/{owner}/{repo}/actions/runs/{run_id}/artifacts"
  headers = { "Authorization": f"token {token}" }
  response = requests.get(url, headers=headers)

  if response.status_code != 200:
    print(f"[ERROR] Failed to fetch artifacts. Status code: {response.status_code}")
    return
  
  for artifact in response.json()["artifacts"]:
    if artifact["name"] != artifact_name:
      continue

    print(f"[LOADING] Downloading '{artifact_name}' artifact...")
    download_url = artifact["archive_download_url"]
    response = requests.get(download_url, headers=headers)
    if response.status_code != 200:
      print(f"[ERROR] Failed to download artifact '{artifact_name}'. Status code: {response.status_code}")
      return
    
    zip_file_path = f"{artifact_name}.zip"
    with open(zip_file_path, "wb") as file:
      file.write(response.content)

    with ZipFile(zip_file_path, "r") as file:
      file.extractall()

    print("\033[F\033[K", end=f"[SUCCESS] Downloaded '{artifact_name}' artifact.\n")
    # print(f"Artifact '{artifact_name}' downloaded and unzipped successfully.")
    os.remove(zip_file_path)
    return True
    
  print(f"Artifact '{artifact_name}' not found.")
