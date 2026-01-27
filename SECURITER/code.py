from link import DataLoader
def codage(text):
    mapping_1, mapping_2, mapping_3 = DataLoader.load_data("mapping")
    coded_1 = ""
    for char in text:
        coded_1 = coded_1 + mapping_1.get(char, "????????") + "&"
    
    coded_1 = coded_1.replace("&", "")

    coded_2 = ""
    ram = True
    for i in range(0, len(coded_1), 2):
        pair = coded_1[i:i+2]
        if ram:
            coded_2 = coded_2 + mapping_2.get(pair, "??")
            ram = False
        elif not ram:
            coded_2 = coded_2 + mapping_2.get(pair, "??") + "&"
            ram = True

    code = coded_2.replace("&", "")

    coded_3 = ""
    for i in range(0, len(code), 2):
        pair = code[i:i+2]
        coded_3 = coded_3 + mapping_3.get(pair, "??") + "&"
    
    coded = coded_3.replace("&", "")
    
    try:
        return coded, coded_2
    except:
        print("ERROR")
        return 0

def decodage(code):
    mapping_1, mapping_2, _ = DataLoader.load_data("mapping")

    dec_2 = {v: k for k, v in mapping_2.items()}
    dec_1 = {v: k for k, v in mapping_1.items()}

    code = code.replace("&", "")

    # couche 2 (base 4) → couche 1 (binaire)
    step1 = ""
    for i in code:
        step1 = step1 + dec_2.get(i, "??")


    if len(step1) % 8 != 0:
        return "?"

    # couche 1 → texte
    text = ""
    for i in range(0, len(step1), 8):
        byte = step1[i:i+8]
        text += dec_1.get(byte, "?")

    return text
