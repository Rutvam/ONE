import os
import subprocess
import sys
import importlib.util


def check_and_install(package):
    #Check if the modul is installed
    spec = importlib.util.find_spec(package)
    if spec is None:
        print(f"INFO:Installation for {package}...")
        subprocess.check_call ([sys.executable, "-m", "pip", "install", package])
    else:
        print(f"INFO:{package} is already installed.")

def clear(os_info, username, player):
    os.system("cls" if os.name == "nt" else "clear")
    print(f"{__string_color__}| Username: {__value_color__}{username}{__string_color__} | Language: {__value_color__}{player.get('P').get('langue')}{__string_color__} | OS name: {__value_color__}{os_info.get('name')}{__string_color__} | Version: {__value_color__}{os_info.get('version')}{__string_color__} | Completed infos: {__value_color__}{os_info.get('os')}{__reset_color__} |")
    print(f"{__string_color__}| Level English: {__number_color__}{player.get('Anglais').get('Level_Anglais')}{__string_color__} | Level Francais: {__number_color__}{player.get('Francais').get('Level_Francais')}{__string_color__} | {__string_color__}Level Deutsch: {__number_color__}{player.get("Deutsch").get("Level_Deutsch")}{__string_color__} | Level Mathe: {__number_color__}{player.get("Math").get("Level_Math")}{__string_color__} | {__string_color__}Level ScNat: {__number_color__}{player.get("ScNat").get("Level_ScNat")}{__string_color__} | {__string_color__}Level Geo: {__number_color__}{player.get("Geo").get("Level_Geo")}{__string_color__} | {__string_color__}Level Histo: {__number_color__}{player.get("Histo").get("Level_Histo")}{__string_color__} | Max XP {__number_color__}{int(player.get("Anglais").get("xp_Anglais")) + int(player.get("Francais").get("xp_Francais")) + int(player.get("Deutsch").get("xp_Deutsch")) + int(player.get("Math").get("xp_Math")) + int(player.get("ScNat").get("xp_ScNat")) + int(player.get("Geo").get("xp_Geo")) + int(player.get("Histo").get("xp_Histo")) if username != None else None}\n")   
    print(f"{__string_color__}============== ONE =============={__reset_color__}")

check_and_install("pwinput")
import pwinput
import random
import link as link
import ctypes
# helpers et singletons récupérés via getters pour éviter effets de bord à l'import
set_player = link.set_player
controller_int = link.controller_int
langue = link.langue

__warning_color__ = "\x1b[1;37;41m"
__number_color__ = "\x1b[1;33;41m"
__string_color__ = "\x1b[0;39;49m"
__input_color__ = "\x1b[0;3;36;49m"
__value_color__ = "\x1b[1;36;44m"
__reset_color__ = "\x1b[0m"
__false_color__ = "\x1b[1;31;49m"
__true_color__ = "\x1b[1;32;49m"

# instances fréquemment utilisées
s = link.get_sauvegarde()
couleurs = link.get_couleurs()
buttons = link.get_buttons()
ci = link.get_ci()
Data_Loader = link.get_data_loader()
ia = link.get_ia()

def main_program(test, info = {}):
    test = input(f"{__string_color__}Do you want to test ONE before create a acount? [{__true_color__}Y{__string_color__}/{__false_color__}N{__string_color__}]\n>>\t{__input_color__}").lower()
    if test in ["yes", "oui", "y", "ja"]:
        test = True
        print(f"{__string_color__}Testing mode is activate.{__reset_color__}")
    elif test in ["no", "non", "n", "nein"]:
        test = False
        print(f"{__string_color__}Testing mode isn't activate.{__reset_color__}")
    else:
        test = False
        print(f"{__warning_color__}WARNING: Sorry I don't understand.\nINFO: Test mode isn't activate.{__reset_color__}")
    os_info = link.OS_finder()
    lib = ctypes.CDLL(os.path.join(os.path.dirname(__file__), os_info.get("calcule_path")))
    lib.calculate_percentage.argtypes = [ctypes.c_int, ctypes.c_int]
    lib.calculate_percentage.restype = ctypes.c_double

    """Main program loop for ONE application console"""
    # ===============================
    #       MAIN PROGRAM
    # ===============================

    running = True
    connection = False

    if test == True:
        info = {
            "name": "Test",
            "key_word": "12345"
        }

    while running:

        data = s.charger_sauvegarde(None)

        # =================================
        #  LOGIN
        # =================================
        while not connection:
            username = None
            player = {
                "mot_de_passe": None,
                "best_score": None,
                "Francais": {
                    "parties_jouees_Francais": None,
                    "Level_Francais": None,
                    "xp_Francais": None,
                    "Max_xp_Francais": None
                },
                "Deutsch": {
                    "parties_jouees_Deutsch": None,
                    "Level_Deutsch": None,
                    "xp_Deutsch": None,
                    "Max_xp_Deutsch": None
                },
                "ScNat": {
                    "parties_jouees_ScNat": None,
                    "Level_ScNat": None,
                    "xp_ScNat": None,
                    "Max_xp_ScNat": None
                },
                "Anglais": {
                    "parties_jouees_Anglais": None,
                    "Level_Anglais": None,
                    "xp_Anglais": None,
                    "Max_xp_Anglais": None
                },
                "Math": {
                    "parties_jouees_Math": None,
                    "Level_Math": None,
                    "xp_Math": None,
                    "Max_xp_Math": None
                },
                "Geo": {
                    "parties_jouees_Geo": None,
                    "Level_Geo": None,
                    "xp_Geo": None,
                    "Max_xp_Geo": None
                },
                "Histo": {
                    "parties_jouees_Histo": None,
                    "Level_Histo": None,
                    "xp_Histo": None,
                    "Max_xp_Histo": None
                },
                "P": {
                    "langue": "EN"
                }
            }
            clear(os_info, username, player)
            if os_info.get("name") == "Windows":
                if os.path.exists("CORE\\DATA\\sauvegarde.json") or os.path.exists("DATA\\sauvegarde.json"):
                    choix = input(f"{__string_color__}Do you want to {__value_color__}(1) connect{__string_color__} or {__value_color__}(2) create a acount{__string_color__}?\n>>\t{__input_color__}")
                else:
                    choix = "2"
                    input(f"{__string_color__}Preparing to create the account...\nPress enter...{__reset_color__}")
            elif os_info.get("name") == "Linux":
                if os.path.exists("CORE/DATA/sauvegarde.json") or os.path.exists("DATA/sauvegarde.json"):
                    choix = input(f"{__string_color__}Do you want to {__value_color__}(1) connect{__string_color__} or {__value_color__}(2) create a acount{__string_color__}?\n>>\t{__input_color__}")
                else:
                    choix = "2"
                    input(f"{__string_color__}Preparing to create the account...\nPress enter...{__reset_color__}")
            elif os_info.get("name") == "Darwin":
                if os.path.exists("CORE/DATA/sauvegarde.json") or os.path.exists("DATA/sauvegarde.json"):
                    choix = input(f"{__string_color__}Do you want to {__value_color__}(1) connect{__string_color__} or {__value_color__}(2) create a acount{__string_color__}?\n>>\t{__input_color__}")
                else:
                    choix = "2"
                    input(f"{__string_color__}Preparing to create the account...\nPress enter...{__reset_color__}")
            if choix == "1":
                clear(os_info, username, player)
                password_state = False
                attempts = 5

                while password_state is False:
                    while username not in data["players"] or username == None:
                        if not test:
                            username = input(f"{__string_color__}Enter your username:\n>>\t{__input_color__}")
                        else:
                            username = info["name"]

                        if not username:
                            print(f"{__warning_color__}Username cannot be empty.{__reset_color__}")
                            input("Press ENTER to continue...")
                            continue

                    if not test:
                        password = pwinput.pwinput(prompt = f"{__string_color__}Enter your password:\n>>\t{__input_color__}", mask='#')
                    else:
                        password = info["key_word"]

                    if not password:
                        print(f"{__warning_color__}Password cannot be empty.{__reset_color__}")
                        input("Press ENTER to continue...")
                        continue

                    player, password_state = s.selectionner_joueur(data, username, password)
                    while password_state is False:
                        # Mot de passe incorrect
                        if link.verify_password(player["mot_de_passe"], password):
                            password_state = True
                        else:
                            print(f"{__warning_color__}Mot de passe incorrect.{__reset_color__}")
                            attempts -= 1
                            password = pwinput.pwinput(prompt = f"Enter your password:\n>>\t{__input_color__}", mask='#')

                        if attempts == 0:
                            exit()

            elif choix == "2":
                clear(os_info, username, player)
                username = input(f"{__string_color__}Enter a username:\n>>\t{__input_color__}")
                while username in data["players"]:
                    username = input(f"{__string_color__}Enter a {__warning_color__}different{__string_color__} username:\n>>\t{__input_color__}")

                password = pwinput.pwinput(prompt = f"{__string_color__}Enter your password:\n>>\t{__input_color__}", mask='#')
                while len(password) <= 7:
                    password = pwinput.pwinput(prompt = f"{__string_color__}Your password is {__warning_color__}too short{__string_color__}. Please choose another one:\n>>\t{__input_color__}", mask='#')


                while password != pwinput.pwinput(prompt = f"{__string_color__}Enter your password again:\n>>\t{__input_color__}", mask='#'):
                    print(f"{__warning_color__}INFO:False. Try again")
                    pwinput.pwinput(prompt = f"{__string_color__}Enter your password again:\n>>\t{__input_color__}", mask='#')
                    password = pwinput.pwinput(prompt = f"{__string_color__}Enter your password:\n>>\t{__input_color__}", mask='#')
                    while len(password) <= 7:
                        password = pwinput.pwinput(prompt = f"{__string_color__}Your password is {__warning_color__}too short{__string_color__}. Please choose another one:\n>>\t{__input_color__}", mask='#')
                    
                hached = link.hash_password(password)
                s.ajouter_joueur(data, username, hached)
                player = data["players"][username]
                s.sauvegarder_auto(data)
            connection = True
            set_player(player)

        # ===============================
        # | MAIN MENU
        # ===============================
        while True:
            clear(os_info, username, player)

            # ============================================================
            # | LANGUAGE
            # ============================================================
            # From this point on, avoid using print() with hardcoded text.
            # Always use the translation system:
            #     translated_text(key, langue)
            # the def is in the file CORE/CLASSE_SECONDAIRE/langue.py.
 
            language = player['P']['langue']
            from CORE.CLASSE_SECONDAIRE.langue import translate
            translate(__string_color__, "Welcome", language, "print", f"!{__reset_color__}")
            translate(__string_color__, "What would you like to do", language, "print", f"?{__reset_color__}")
            translate(f"{__value_color__}1.{__reset_color__} ", "Training", language, "print", ".")
            print(f"{__value_color__}2.{__reset_color__} INLL (Testing).")
            choice = translate(f"{__value_color__}2.{__reset_color__} ", "Setting", language, "input", f"\n>>\t{__input_color__}")

            # =============================================================================================================
            # | 1. Training                                                                                               |
            # =============================================================================================================
            # This section manages the training system and is divided into several steps.
            #
            # Step 1:
            # - Multiple buttons are displayed in the OFF state.
            #   This means their corresponding topics will NOT appear in the quiz.
            # - To activate a topic, type the code shown before the button name (e.g. "1", "1.1").
            # - Once you understand this system, you can select the topics you want.
            #
            # Step 2:
            # - Press ENTER to continue.
            # - Choose a game mode:
            #     • Infinite:
            #       Unlimited questions, but the session stops immediately after a mistake.
            #     • Normal:
            #       You define the number of questions.
            #       At the end, you receive your score and success percentage.
            if choice == "1":
                while True:
                    clear(os_info, username, player)
                    print(f"=========== {Lang['Setting'][player["P"]["langue"]]} ===========")

                    def show(btn, txt):
                        """Show button state"""
                        boole = "ON" if buttons.state[btn] else "OFF"
                        if boole == "ON":
                            state = ci.TEXT.text_editor("ON", police = "FAT", text_color = "GREEN", background_color = "DEFAULT")
                        else:
                            state = ci.TEXT.text_editor("OFF", police = "FAT", text_color = "RED", background_color = "DEFAULT")
                        print(f"({state}) {txt} ")
                        return boole

                    state = show("1", ("1 " + Lang['Language'][language]))
                    if state == "ON":
                        _ = show("1_1", ("1.1 " + Lang['Vocabulary'][language]))
                        _ = show("1_2", ("1.2 " + Lang['Conjugation'][language]))
                        _ = show("EN", ("EN) " + Lang["English"][language]))
                        _ = show("FR", ("FR) " + Lang["French"][language]))
                        _ = show("DE", ("DE) " + Lang["German"][language]))
                        print("")

                    state = show("2", ("2 " + Lang["Natural Sciences"][language]))
                    if state == "ON":
                        _ = show("2_1", ("\t2.1 " + Lang["Name of the elements"][language]))
                        _ = show("2_2", ("\t2.2 " + Lang["Atomic number"][language]))
                        print("")

                    state = show("3", ("3 " + Lang["Mathematics"][language]))
                    if state == "ON":
                        _ = show("3_1", ("\t3.1 " + Lang["The Basics (+ - x ÷)"][language]))
                        print("")

                    state = show("4", ("4 " + Lang["Geography"][language]))
                    if state == "ON":
                        _ = show("4_1", ("\t4.1 " + Lang["Plate tectonics theory"][language]))
                        print("")

                    state = show("5", ("5 " + Lang["History"][language]))
                    if state == "ON":
                        _ = show("5_1", ("\t5.1 " + Lang["Plate tectonics theory"][language]))
                        _ = show("5_2", ("\t5.2 " + Lang["Industrialization"][language]))
                        print("")

                    print("=" * 40)
                    action = input("\nq: Quit\nENTER to validate, or choose a button.\n>\t").strip()

                    mapping = {
                        "1": "1",
                        "1.1": "1_1",
                        "1.2": "1_2",
                        "EN": "EN",
                        "FR": "FR",
                        "DE": "DE",

                        "2": "2",
                        "2.1": "2_1",
                        "2.2": "2_2",

                        "3": "3",
                        "3.1": "3_1",

                        "4": "4",
                        "4.1": "4_1",

                        "5": "5",
                        "5.1": "5_1",
                        "5.2": "5_2",
                    }

                    if action in mapping:
                        buttons.toggle(mapping[action])
                    elif action == "":
                        break
                    elif action.lower() == "q" or action.lower() == "quit":
                        print("Goodbye!")
                        running = False
                        exit()
                    else:
                        print("Invalid choice.")
                        input("Press ENTER to continue...")

                # =======================================
                #         START GAMES
                # =======================================
                menu, langue_p, choices_langue, choices_scnat, choices_math, choices_geo, choices_histo = buttons.collect()

                if not menu:
                    print("No games selected in settings.")
                    input("Press ENTER to continue...")
                    continue
                
                mode_choice = input("Select mode:\n1: Infinite\n2: Normal\n>\t").strip().lower()

                # =====================================
                #           INFINITE MODE
                # =====================================
                if mode_choice in ["1", "infinite"]:
                    streak = True
                    ndq = 0

                    while streak == True:



                        ndq += 1
                        selected_game = random.choice(menu)
                        xp_gained = 0
                        score = False
                        if selected_game == "ScNat":
                            exercise_score, xp, streak = ci.matiere(link.get_scnat(), choices_scnat, player, ndq, score)
                        elif selected_game == "Language":
                            langue_choisi = random.choice(langue_p)
                            exercise_score, xp, streak = ci.matiere(link.get_langue(), langue_choisi, player, ndq, score)
                        elif selected_game == "Math":
                            exercise_score, xp, streak = ci.matiere(link.get_math(), choices_math, player, ndq, score)
                        elif selected_game == "Geo":
                            exercise_score, xp, streak = ci.matiere(link.get_geo(), choices_geo, player, ndq, score)
                        elif selected_game == "Histo":
                            exercise_score, xp, streak = ci.matiere(link.get_histo(), choices_histo, player, ndq, score)
                        else:
                            print("Game selection error.")
                            streak = False

                        if streak == True or streak == None:
                            streak = True
                        else:
                            streak = False

                        s.Level_up(player)
                        s.sauvegarder_auto(data)
                        clear(os_info, username, player)

                # =====================================
                #            NORMAL MODE
                # =====================================
                elif mode_choice in ["2", "normal"]:
                    streak = True
                    attempts = 5
                    max_attempts = attempts
                    score = 0
                    ndq = 0

                    ndq = controller_int(attempts, max_attempts, ndq, "How many questions do you want?")
                    total_questions = ndq

                    for i in range(ndq):
                        selected_game = random.choice(menu)

                        if selected_game == "ScNat":
                            exercise_score, xp, streak = ci.matiere(link.get_scnat(), choices_scnat, player, i, score)
                        elif selected_game == "Language":
                            langue_choisi = random.choice(langue_p)
                            exercise_score, xp, streak = ci.matiere(link.get_langue(), langue_choisi, player, ndq, score)
                        elif selected_game == "Math":
                            exercise_score, xp, streak = ci.matiere(link.get_math(), choices_math, player, i, score)
                        elif selected_game == "Geo":
                            exercise_score, xp, streak = ci.matiere(link.get_geo(), choices_geo, player, i, score)
                        elif selected_game == "Histo":
                            exercise_score, xp, streak = ci.matiere(link.get_histo(), choices_histo, player, i, score)
                        else:
                            print("Game selection error.")
                            streak = False

                        if streak == True or streak == None:
                            streak = True
                        else:
                            streak = False

                        s.Level_up(player)
                        s.sauvegarder_auto(data)
                        if i < ndq - 1:
                            input("Press ENTER to continue...")
                        clear(os_info, username, player)

                    percentage = lib.calculate_percentage(score, ndq)
                    input(f"Your result:\nScore: {score}\nSuccess percentage: {percentage}%\nPress ENTER to continue...")

            # =======================================
            #         INLL (AI Learning)
            # =======================================
            elif choice == "2":
                clear(os_info, username, player)
                print("=== INLL (Intelligent Natural Language Learning) ===")
                lang_choice = input(
                    "In which language do you want to write?\n"
                    "1. French\n"
                    "2. English\n"
                    "3. German\n> "
                ).strip()

                mapping = {
                    "1": ("FR", "Write your text in French:\n> "),
                    "2": ("EN", "Write your text in English:\n> "),
                    "3": ("DE", "Write your text in German:\n> ")
                }

                if lang_choice not in mapping:
                    print("Invalid choice. Returning to menu.")
                    continue
                
                lang_code, message = mapping[lang_choice]
                print("Hello! You can start writing your text. Type 'q' to quit.")

                while True:
                    text = input(message)

                    if text.lower() == "q":
                        break
                    
                    if text == "":
                        print("No text entered.")
                        continue
                    
                    # AI Learning
                    new_words = ia.learn_words(text, lang_code)

                    if new_words:
                        print("New words learned:")
                        print(f"{lang_code}: {new_words}")

                    answer = ia.answer_generation(text)
                    print(f"\n---\nAI Response: {answer}\n---\n")

            # =======================================
            #         SETTINGS (Player)
            # =======================================
            elif choice == "s" or choice == "p":
                clear(os_info, username, player)
                settings_choice = input("What do you want to do?\n1. Change language\n> ").strip()

                if settings_choice == "1":
                    lang_selected = input(
                        f"Select language:\n"
                        f"1. French ({'ON' if player['P'].get('langue', 'FR') == 'FR' else 'OFF'})\n"
                        f"2. English ({'ON' if player['P'].get('langue', 'FR') == 'EN' else 'OFF'})\n"
                        f"3. German ({'ON' if player['P'].get('langue', 'FR') == 'DE' else 'OFF'})\n> "
                    ).strip()

                    try:
                        if lang_selected == "1":
                            language = "FR"
                        elif lang_selected == "2":
                            language = "EN"
                        elif lang_selected == "3":
                            language = "DE"
                        else:
                            print("Invalid choice.")
                    except Exception as e:
                        print(f"Error: {e}")

                    input("Press ENTER to continue...")
                    s.sauvegarder_auto(data)

            # =======================================
            #         QUIT GAME
            # =======================================
            elif choice == "q":
                print("Goodbye!")
                running = False
                break

            else:
                print("Invalid choice.")
                input("Press ENTER to continue...")

if __name__ == "__main__":
    import sys
    import json
    if len(sys.argv) < 3:
        print("Usage: python main_def.py <test> <info_json>")
        sys.exit(1)
    test_str = sys.argv[1]
    info_json = sys.argv[2]
    test = test_str.lower() == "true"
    info = json.loads(info_json) if info_json else {}
    main_program(test, info)