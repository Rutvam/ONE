import random
import link as link
from CORE.exercise import Exercise
from CORE.dataloader import DataLoader
# pas d'import circulaire : les sous-choix de langue seront récupérés dynamiquement

# player sera récupéré dynamiquement depuis CORE.link pour éviter import circulaire

class Language(Exercise):
    """French exercises"""

    def menu_langue(self, choices, question_num):
        """Main menu for exercises"""
        player = link.player
        if choices == "French":
            stats = {
                'xp': player.get('Francais', {}).get('xp_Francais', 0),
                'level': player.get('Francais', {}).get('Level_Francais', 1),
                'exercises': player.get('Francais', {}).get('parties_jouees_Francais', 0)
            }
            vocabulary, persons, agreement, verb_data = DataLoader.load_data("langue")
            self.display_header(question_num, "French", stats)
        elif choices == "German":
            stats = {
                'xp': player.get('Deutsch', {}).get('xp_Deutsch', 0),
                'level': player.get('Deutsch', {}).get('Level_Deutsch', 1),
                'exercises': player.get('Deutsch', {}).get('parties_jouees_Deutsch', 0)
            }
            vocabulary, persons, agreement, verb_data = DataLoader.load_data("langue")
            self.display_header(question_num, "German", stats)
        else:
            stats = {
                'xp': player.get('Anglais', {}).get('xp_Anglais', 0),
                'level': player.get('Anglais', {}).get('Level_Anglais', 1),
                'exercises': player.get('Anglais', {}).get('parties_jouees_Anglais', 0)
            }
            vocabulary, persons, agreement, verb_data = DataLoader.load_data("langue")
            self.display_header(question_num, "English", stats)
        
        if not choices:
            print(f"[Lang] Aucune langue sélectionnée.")
            return self.score, self.xp, self.streak

        # récupérer les types d'exercice (vocabulaire / conjugaison) depuis les boutons
        _, _, choices_langue, _, _, _, _ = link.get_buttons().collect()
        if not choices_langue:
            print("[Lang] Aucun type d'exercice de langue activé dans les parametres.")
            return self.score, self.xp, self.streak
        choice_ex = random.choice(choices_langue)

        if choice_ex == "Vocabulary":
            self._exercise_vocabulary(vocabulary, choices)
        elif choice_ex == "Conjugation":
            self._exercise_verbs(verb_data, persons)
        else:
            print(f"❌ Unknown French choice: {choice_ex}")

        return self.score, self.xp, self.streak

    def _exercise_vocabulary(self, vocabulary, choices):
        """vocabulary exercise"""
        if not vocabulary:
            print("❌ No vocabulary data available.")
            return

        translation, word = random.choice(list(vocabulary.items()))
        answer = input(f"How do you say '{word}' in {choices}?\n>> ").strip()
        
        self.check_answer(answer, translation)

    def _exercise_verbs(self, verb_data, persons):
        """verb conjugation exercise"""
        if not verb_data.get("verbs", {}).get("list") or not persons:
            print("❌ No verb or person data available.")
            return

        verb = random.choice(verb_data["verbs"]["list"])
        answer, correct_answer = self._conjugate_verb(verb, persons, verb_data)
        
        self.check_answer(answer, correct_answer)

    def _conjugate_verb(self, verb, persons, verb_data):
        """Conjugate a verb"""
        subject = random.choice(persons)
        tense = random.choice(["présent", "passé composé", "imparfait", "plus-que-parfait"])
        answer = input(f"Conjugate '{verb}' at {tense}:\n> {subject} ").strip()
        verbs_root = verb_data.get("verbs", {})
        verb_entry = verbs_root.get(verb, {})
        correct_answer = ""

        try:
            if tense == "présent":
                correct_answer = verb_entry.get("présent", {}).get(subject, "")
            elif tense == "passé composé":
                aux_present = verb_entry.get("présent", {}).get(subject)
                part = verb_entry.get("participe passé")
                if aux_present and part:
                    correct_answer = f"{aux_present} {part}"
            elif tense == "imparfait":
                correct_answer = verb_entry.get("imparfait", {}).get(subject, "")
            elif tense == "plus-que-parfait":
                imp = verb_entry.get("imparfait", {}).get(subject)
                part = verb_entry.get("participe passé")
                if imp and part:
                    correct_answer = f"{imp} {part}"
        except Exception as e:
            print(f"Error during conjugation: {e}")
            correct_answer = ""

        return answer, correct_answer
