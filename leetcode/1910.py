#remove occurences of a string t, from s
#using simulation
#iterate through the input string s and check if the substring part is present.
#O(n^2) time complexity

def removeOccurencesSimulation(s:str,t:str):
    while t in s:
        s = s.replace(t,'',1)
    return s