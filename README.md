# cellular automata


This project has two dependencies [cxxopts](https://github.com/jarro2783/cxxopts.git) and [opencv](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html) 

Build the project by creating a build directory in the root directory of the project and using cmake

```bash

mkdir build && cd build
cmake ..
make

```

Once successfully built you can specify a rule between 0 and 254 for the  cellular automata

```bash
./ca.app --rule 30
```

The program will run and output a png file showing the output of the cellular automata, you can also build all rules with the —all flag

```bash
./ca.app --all
```


Cellular Automata ( CA ) are simple machines that work on a tape, they see a limited view of their tape and follow a few set rules.

They vary in breadth of vision and complexity but simple CA can create complex patterns.

An interesting subset of CA can see only three objects at a time, each object can have two states 1 or 0 and each state has an associated rule.

The task of the CA at each step along its tape is to assess its environment and make a decision, whether to assign its value 1 or 0.

![decision](https://nmcgblog-public.s3.amazonaws.com/ca/CABasicDecision.svg)

The CA’s decision is determined by the state of the objects in its view and its rule set, the objects in view each have two possible states so there are 2^3 unique combinations of state that these three object's can be in, giving 8 in total.

The rule set provides a 1 or 0 value for each of these 8 possible states, giving 2^8 possible sets of rules, 255 unique rules in total.

Each ruleset number's binary representation lays out the value to be assigned

![rule 1](https://nmcgblog-public.s3.amazonaws.com/ca/carule01.svg)

Rule 1 matches a 1 value only when all three cells in view have a value of 0, any cell with a 1 value will result in a 0 value being assigned, iterating this over rows viewed three cells at a time produces a pattern.


Some rulesets are more interesting than others, some produce regular patterns, some just look like white noise but others create patterns seemingly on the border between predictable structure and noise.

For example rule 126 produces a mixture of repeating motifs, not predictable but not entirely random either.

![rule 126](https://nmcgblog-public.s3.amazonaws.com/ca/carule126.svg)

![rule 126](https://nmcgblog-public.s3.amazonaws.com/ca/rule126.png)

