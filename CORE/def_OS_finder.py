import platform
import json

def OS_finder():
    #check the OS
    try:
        with open('DATA/path.json', 'r', encoding="utf-8") as f:
            path_data = json.load(f)
    except FileNotFoundError:
        print("Error: Path configuration file not found.")
        return None

    os_info = {
        "name": platform.system(),
        "version": platform.version(),
        "os": platform.platform(),
        "calcule_path": path_data.get("calcule").get(platform.system())
    }
    print(f"Name: {os_info.get("name")} | Version: {os_info.get("version")} | Completed infos: {os_info.get("os")}")
    return os_info