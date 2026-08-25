class JSONDecodeError(Exception):
    pass


def parse(text):
    parser = _Parser(text)
    parser._skip_ws()
    value = parser._parse_value()
    parser._skip_ws()
    if parser.i != len(parser.s):
        raise JSONDecodeError(f"Unexpected trailing data at position {parser.i}")
    return value


class _Parser:
    def __init__(self, text):
        self.s = text
        self.i = 0

    def _error(self, msg):
        raise JSONDecodeError(f"{msg} at position {self.i}")

    def _skip_ws(self):
        while self.i < len(self.s) and self.s[self.i] in " \t\n\r":
            self.i += 1

    def _parse_value(self):
        if self.i >= len(self.s):
            self._error("Unexpected end of input")
        ch = self.s[self.i]
        if ch == '{':
            return self._parse_object()
        if ch == '[':
            return self._parse_array()
        if ch == '"':
            return self._parse_string()
        if ch == 't':
            return self._parse_literal("true", True)
        if ch == 'f':
            return self._parse_literal("false", False)
        if ch == 'n':
            return self._parse_literal("null", None)
        if ch == '-' or ch.isdigit():
            return self._parse_number()
        self._error(f"Unexpected character '{ch}'")

    def _parse_literal(self, literal, value):
        if self.s[self.i:self.i + len(literal)] != literal:
            self._error(f"Invalid literal, expected '{literal}'")
        self.i += len(literal)
        return value

    def _parse_object(self):
        obj = {}
        self.i += 1  # skip '{'
        self._skip_ws()
        if self.i < len(self.s) and self.s[self.i] == '}':
            self.i += 1
            return obj
        while True:
            self._skip_ws()
            if self.i >= len(self.s) or self.s[self.i] != '"':
                self._error("Expected string key")
            key = self._parse_string()
            self._skip_ws()
            if self.i >= len(self.s) or self.s[self.i] != ':':
                self._error("Expected ':'")
            self.i += 1
            self._skip_ws()
            obj[key] = self._parse_value()
            self._skip_ws()
            if self.i >= len(self.s):
                self._error("Unexpected end of input in object")
            if self.s[self.i] == ',':
                self.i += 1
                continue
            if self.s[self.i] == '}':
                self.i += 1
                return obj
            self._error("Expected ',' or '}'")

    def _parse_array(self):
        arr = []
        self.i += 1  # skip '['
        self._skip_ws()
        if self.i < len(self.s) and self.s[self.i] == ']':
            self.i += 1
            return arr
        while True:
            self._skip_ws()
            arr.append(self._parse_value())
            self._skip_ws()
            if self.i >= len(self.s):
                self._error("Unexpected end of input in array")
            if self.s[self.i] == ',':
                self.i += 1
                continue
            if self.s[self.i] == ']':
                self.i += 1
                return arr
            self._error("Expected ',' or ']'")

    def _parse_string(self):
        self.i += 1  # skip opening quote
        result = []
        while True:
            if self.i >= len(self.s):
                self._error("Unterminated string")
            ch = self.s[self.i]
            if ch == '"':
                self.i += 1
                return "".join(result)
            if ch == '\\':
                self.i += 1
                if self.i >= len(self.s):
                    self._error("Unterminated escape sequence")
                esc = self.s[self.i]
                mapping = {'"': '"', '\\': '\\', '/': '/', 'b': '\b',
                           'f': '\f', 'n': '\n', 'r': '\r', 't': '\t'}
                if esc in mapping:
                    result.append(mapping[esc])
                    self.i += 1
                elif esc == 'u':
                    hex_digits = self.s[self.i + 1:self.i + 5]
                    if len(hex_digits) != 4:
                        self._error("Invalid unicode escape")
                    result.append(chr(int(hex_digits, 16)))
                    self.i += 5
                else:
                    self._error(f"Invalid escape character '{esc}'")
            else:
                result.append(ch)
                self.i += 1

    def _parse_number(self):
        start = self.i
        if self.s[self.i] == '-':
            self.i += 1
        if self.i >= len(self.s) or not self.s[self.i].isdigit():
            self._error("Invalid number")
        if self.s[self.i] == '0':
            self.i += 1
        else:
            while self.i < len(self.s) and self.s[self.i].isdigit():
                self.i += 1
        is_float = False
        if self.i < len(self.s) and self.s[self.i] == '.':
            is_float = True
            self.i += 1
            if self.i >= len(self.s) or not self.s[self.i].isdigit():
                self._error("Invalid number: expected digits after '.'")
            while self.i < len(self.s) and self.s[self.i].isdigit():
                self.i += 1
        if self.i < len(self.s) and self.s[self.i] in 'eE':
            is_float = True
            self.i += 1
            if self.i < len(self.s) and self.s[self.i] in '+-':
                self.i += 1
            if self.i >= len(self.s) or not self.s[self.i].isdigit():
                self._error("Invalid number: expected digits in exponent")
            while self.i < len(self.s) and self.s[self.i].isdigit():
                self.i += 1
        text = self.s[start:self.i]
        return float(text) if is_float else int(text)


if __name__ == "__main__":
    examples = [
        '{"name": "Alice", "age": 30, "active": true, "tags": ["a", "b"], "meta": null, "score": -1.5e2}',
        '[1, 2, 3.14, "hi", false, null, {"nested": [1, 2]}]',
    ]
    for e in examples:
        print(parse(e))
