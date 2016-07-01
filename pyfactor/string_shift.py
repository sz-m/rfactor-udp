static_i = 0
def string_shift(st):
    global static_i
    if(len(st) >= 16):
        st = ' '*16 + st +' '
        if(static_i > len(st)): static_i = 0
        else: static_i+=1
        return st[static_i:]

    else:
        return st


