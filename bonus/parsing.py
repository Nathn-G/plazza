def parsing(file_name):
    p = ""
    fd = open(file_name, "r+")
    file_content = fd.read().replace("> ", "")
    if not "STATUS" in file_content:
        fd.close()
        return None, None
    if p != file_content:
        p = file_content
        fd.truncate(0)
    fd.close()
    p = p.split("\n")
    ki = 0
    kstates = {}
    ingredients = {}
    is_kitchen = False
    is_ingredient = False
    for i in p:
        if "KITCHEN" in i:
            is_kitchen = True
            is_ingredient = False
            ki = int(i.split(" ")[2])
            kstates[ki] = {
                "waiting": 0,
                "cooks": []
            }
            ingredients[ki] = {}
        elif "INGREDIENTS" in i:
            is_kitchen = False
            is_ingredient = True
        else:
            if "STATUS" in i:
                is_kitchen = False
                is_ingredient = False
            if is_kitchen:
                if "Waiting" in i:
                    kstates[ki]["waiting"] = int(i.split(" : ")[1])
                elif "Cook" in i:
                    s = i.split(" ")[-1]
                    kstates[ki]["cooks"].append(s)
            elif is_ingredient:
                w = i.split(" ")
                if len(w) == 3:
                    n,q = w[0], int(w[-1])
                    ingredients[ki][n] = q
    return kstates, ingredients
