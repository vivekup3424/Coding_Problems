symbols = '$¢£¥€¤'
print(symbols)
print(list(filter(lambda c: c > 127, map(ord,symbols))))