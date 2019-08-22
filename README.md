# Hashfuzz

This repository contains the basic examples for targets of HashFuzz in ICSE 2020.

The folder targetExamples contains a target per program. To modify them, you can do it either manually modifying targetHash with 3 values for x1, x2 and x3 choosen uniformly at random with the restriction of 1 byte or automatically by applying the hashfuzz script as follows:

```
bash hashfuzz.bash ../targetExamples/woff2-2016-05-06/target.cc
```

These targets replace the targets from Google's Fuzz Test Suite. To apply the targets, just clone it:

```
git clone https://github.com/google/fuzzer-test-suite.git
```
Then, in each of the corresponding folder replace the target.cc with the new target and build it following the building intructions of the tutorial:

https://github.com/google/fuzzer-test-suite/blob/master/tutorial/libFuzzerTutorial.md

The seeds used for every library are the provided ones. When no seed is provided, we create a file containing a string "AAAAA" as the original seed.

For AFL and AFL-based, you can reuse the targets by using the AFL driver of LibFuzzer. Althought we provide the driver here, we recommend to get its last version from your AFL version.

You can find more information about the driver here:
https://github.com/llvm-mirror/compiler-rt/blob/master/lib/fuzzer/afl/afl_driver.cpp

Please remember to include the driver into the builds of Fuzz-test-suite and the corresponding flags (see URL).