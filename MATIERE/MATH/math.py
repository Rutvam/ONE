import random
import os
import ctypes

from CORE.exercise import Exercise
from CORE.dataloader import DataLoader
import link

# =========================
# Chargement librairie C
# =========================
use_c_lib = False
lib = None
# Error: Math base function not found. Returning a dummy function.
os_info = link.OS_finder()

try:
    if os_info and os_info.get("calcule_path"):
        BASE_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
        lib_path = os.path.join(BASE_DIR, os_info.get("calcule_path"))

        print("LIB PATH =", lib_path)
        print("EXISTS =", os.path.exists(lib_path))

        if os.path.exists(lib_path):
            lib = ctypes.CDLL(lib_path)

            if hasattr(lib, 'opperateur'):
                lib.opperateur.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_char]
                lib.opperateur.restype = ctypes.c_double
                use_c_lib = True
            else:
                print("[Math] 'opperateur' introuvable → fallback Python")
        else:
            print("[Math] Librairie introuvable → fallback Python")
    else:
        print("[Math] OS info invalide → fallback Python")

except Exception as e:
    print(f"[Math] Erreur chargement DLL : {e}")
    use_c_lib = False


# =========================
# Calcul opérateur
# =========================
def compute_op(a, b, op):
    if use_c_lib and lib is not None:
        try:
            return lib.opperateur(int(a), int(b), ctypes.c_char(op.encode('utf-8')))
        except Exception as e:
            print(f"[Math] Erreur appel DLL : {e}")

    # Fallback Python
    if op == "+":
        return a + b
    elif op == "-":
        return a - b
    elif op == "*":
        return a * b
    elif op == "/":
        if b == 0:
            return None
        return a // b if a % b == 0 else a / b
    elif op == "#":
        return a ** b

    raise ValueError(f"Unknown operator: {op}")


# =========================
# Classe principale
# =========================
class Math(Exercise):
    """Mathematics exercises"""

    def menu_math(self, choices, question_num):
        math_base = self.math_base
        player = link.player

        stats = {
            'xp': player.get('Math', {}).get('xp_Math', 0),
            'level': player.get('Math', {}).get('Level_Math', 1),
            'exercises': player.get('Math', {}).get('parties_jouees_Math', 0)
        }

        self.display_header(question_num, "Math", stats)

        max_val = 10 + stats['level'] * 5

        if not choices:
            print("❌ No choices provided for Math.")
            return self.score, self.xp, self.streak

        choice = random.choice(choices)

        if choice == "base":
            try:
                question, correct_answer = self.math_base(
                    i=["+", "-", "*", "/", "**"],
                    max_val=max_val
                )
            except Exception as e:
                print(f"Error executing math_base: {e}")
                question, correct_answer = "1 + 1 = ?", 2

            answer = input(question).strip()
            self.check_answer(answer, correct_answer)

        else:
            print(f"❌ Unknown Math choice: {choice}")

        return self.score, self.xp, self.streak

    # =========================
    # Génération nombres
    # =========================
    def choisir_un_nombre(self, min_val, max_val):
        return random.randint(min_val, max_val), random.randint(min_val, max_val)

    # =========================
    # Génération exercice
    # =========================
    def math_base(self, i, max_val):
        choix = random.choice(i)

        if choix in ["+", "-"]:
            a, b = self.choisir_un_nombre(-max_val, max_val)
            op = choix
            reponse_correct = compute_op(a, b, op)

        elif choix == "*":
            a, b = self.choisir_un_nombre(-20, 20)
            op = "*"
            reponse_correct = compute_op(a, b, op)

        elif choix == "/":
            b = 0
            while b == 0:
                _, b = self.choisir_un_nombre(-20, 20)

            quotient, _ = self.choisir_un_nombre(-20, 20)
            a = quotient * b
            op = "/"
            reponse_correct = quotient

        elif choix == "**":
            a, _ = self.choisir_un_nombre(-10, 10)
            _, b = self.choisir_un_nombre(-3, 3)
            op = "#"
            reponse_correct = compute_op(a, b, op)

            question = f"Calcul\n {a}^({b}) = ?\n>>"
            return question, int(reponse_correct)

        else:
            raise ValueError("Choix invalide")

        # Format affichage
        a_str = f"+{a}" if a > 0 else str(a)
        b_str = f"+{b}" if b > 0 else str(b)

        question = f"Calcul\n ({a_str}) {op} ({b_str}) = ?\n>>"

        try:
            return question, int(reponse_correct)
        except Exception:
            return question, reponse_correct