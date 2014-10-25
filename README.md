MU-Game
=======

This program is based on a puzzle proposed by Douglas Hofstadter in his book, Godel, Escher, Bach.  
The puzzle is simple, you start with the string "MI," and attempt to reach the string "MU."  
You can change the string with 4 simple rules:
  1. If the string ends in I, you can add a U to the end. e.g. "MUI" --> "MUIU"
  2. You can double the string after an M s.t. Mx becomes Mxx. e.g. "MUI" --> "MUIUI"
  3. You can replace any III with a U. e.g. "MUIII" --> "MUU"
  4. You can remove any UU patterns. e.g. "MUUI" --> "MI"
  
This program uses these 4 rules to generate as many valid string as possible (by valid I mean  
strings that can be reached with the starting point of "MI"). 
