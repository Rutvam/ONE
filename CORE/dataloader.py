import os
import json

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

class DataLoader:
    """Class for loading data from JSON files"""

    ENCODING = "utf-8"

    @staticmethod
    def get_path(relative_path):
        """Get absolute path from relative path"""
        return os.path.join(BASE_DIR, relative_path)

    @staticmethod
    def load_data(subject):
        try:
            with open(DataLoader.get_path('DATA/path.json'), 'r', encoding=DataLoader.ENCODING) as f:
                path = json.load(f)
        except FileNotFoundError:
            print("Error: Path configuration file not found.")
            return None
        """Load data according to the specified subject"""
        if subject == "EN":
            return DataLoader._load_language(path["language"])
        elif subject == "FR":
            return DataLoader._load_language(path["language"])
        elif subject == "DE":
            return DataLoader._load_language(path["language"])
        elif subject == "ScNat":
            return DataLoader._load_scnat(path["scnat"])
        elif subject == "Geo":
            return DataLoader._load_geography(path["geo"])
        elif subject == "Histo":
            return DataLoader._load_histo(path["histo"])
        elif subject == "COLOR":
            return DataLoader._load_color(path["police"])
        elif subject == "mapping":
            return DataLoader._load_mapping(path["mapping"])

    @staticmethod
    def _load_mapping(mapping_path):
        """Load mathematics data"""
        try:
            file_path = DataLoader.get_path(mapping_path["mapping_1"])
            with open(file_path, "r", encoding=DataLoader.ENCODING) as f:
                data = json.load(f)
                mapping_1 = data
            file_path = DataLoader.get_path(mapping_path["mapping_2"])
        except ImportError:
            print("Error: Mapping 1 files not found") 
        try:
            with open(file_path, "r", encoding=DataLoader.ENCODING) as f:
                data = json.load(f)
                mapping_2 = data
            file_path = DataLoader.get_path(mapping_path["mapping_3"])
        except ImportError:
            print("Error: Mapping 2 files not found") 
        try:
            with open(file_path, "r", encoding=DataLoader.ENCODING) as f:
                data = json.load(f)
                mapping_3 = data
        except ImportError:
            print("Error: Mapping 3 files not found")    
        return mapping_1, mapping_2, mapping_3

    @staticmethod
    def _load_language(language_path):
        """Load French vocabulary and verb data"""
        vocabulary = {}
        persons = []
        agreement = {}
        verb_data = {}

        try:
            file_path = DataLoader.get_path(language_path["voc"])
            with open(file_path, 'r', encoding=DataLoader.ENCODING) as f:
                data = json.load(f)
                vocabulary = data.get("voc", {})
        except FileNotFoundError:
            print("Error: French vocabulary file not found.")
        except json.JSONDecodeError:
            print("Error: Invalid JSON format in French vocabulary file.")

        try:
            file_path = DataLoader.get_path(language_path["verbs"])
            with open(file_path, 'r', encoding=DataLoader.ENCODING) as f:
                verb_data = json.load(f)
                persons = verb_data.get("verbs", {}).get("personnes", [])
                agreement = verb_data.get("verbs", {}).get("accord", {})
        except FileNotFoundError:
            print("Error: French verb file not found.")
        except json.JSONDecodeError:
            print("Error: Invalid JSON format in French verb file.")

        return vocabulary, persons, agreement, verb_data

    @staticmethod
    def _load_scnat(scnat_path):
        """Load natural sciences data"""
        elements = {}
        atomic_numbers = {}
        try:
            file_path = DataLoader.get_path(scnat_path)
            with open(file_path, 'r', encoding=DataLoader.ENCODING) as f:
                data = json.load(f)
                elements = data.get("elements", {})
                atomic_numbers = data.get("ordnungszahl_von_elementen", {})
        except FileNotFoundError:
            print("Error: Natural Sciences data file not found.")
        except json.JSONDecodeError:
            print("Error: Invalid JSON format in Natural Sciences data file.")

        return elements, atomic_numbers

    @staticmethod
    def _load_geography(geo_path):
        """Load geography data"""
        try:
            file_path = DataLoader.get_path(geo_path)
            with open(file_path, 'r', encoding=DataLoader.ENCODING) as f:
                return json.load(f)
        except FileNotFoundError:
            print("Error: Geography data file not found.")
            return {}
        except json.JSONDecodeError:
            print("Error: Invalid JSON format in Geography data file.")
            return {}
        
    def _load_histo(histo_path):
        try:
            file_path = DataLoader.get_path(histo_path)
            with open(file_path, 'r', encoding=DataLoader.ENCODING) as f:
                return json.load(f)
        except FileNotFoundError:
            print("Error: History data file not found.")
            return {}
        except json.JSONDecodeError:
            print("Error: Invalid JSON format in History data file.")
            return {}
        
    def _load_color(color_path):
        try:
            file_path = DataLoader.get_path(color_path)
            with open(file_path, 'r', encoding=DataLoader.ENCODING) as f:
                return json.load(f)
        except FileNotFoundError:
            print("Error: COLOR data file not found.")
            return {}
        except json.JSONDecodeError:
            print("Error: Invalid JSON format in COLOR data file.")
            return {}
