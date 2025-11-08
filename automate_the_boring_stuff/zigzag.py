import sys, time
ident = 0
ident_increasing = True

while True:
    print(" "* ident, end= "")
    print("******")
    time.sleep(1/60)
    if ident_increasing:
        ident = ident + 1
        if ident == 20:
            ident_increasing = False
    else:
        ident = ident - 1
        if ident == 0:
            ident_increasing = True