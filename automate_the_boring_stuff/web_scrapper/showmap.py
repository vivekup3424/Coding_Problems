#!/usr/bin/env python3

import webbrowser, sys
if len(sys.argv) > 1:
    address = ' '.join(sys.argv[1:])
    webbrowser.open(address)