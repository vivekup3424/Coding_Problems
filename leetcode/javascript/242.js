var isAnagram = function (s, t) {
  let obj = new Map();

  // Populate the first Map with characters from string s
  for (let i = 0; i < s.length; i++) {
    obj.set(s[i], (obj.get(s[i]) || 0) + 1);
  }
  //console.log(obj);

  let obj1 = new Map();

  // Populate the second Map with characters from string t
  for (let i = 0; i < t.length; i++) {
    obj1.set(t[i], (obj1.get(t[i]) || 0) + 1);
  }
  //console.log(obj1);

  // Compare the two Maps
  if (obj.size !== obj1.size) {
    return false;
  }

  for (let [key, value] of obj) {
    if (obj1.has(key) === false || obj1.get(key) !== value) {
      return false;
    }
  }

  return true;
};

function main() {
  console.log(isAnagram("anagram", "nagaram")); // Output: true
}

main();
