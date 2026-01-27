from SECURITER.code import codage, decodage
text = input(">> ")
code, code_and = codage(text)
print(f"secret code: {code}")
text = decodage(code_and)
print(text)