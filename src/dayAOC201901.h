#ifndef DAYAOC201901_H
#define DAYAOC201901_H

#include <Arduino.h>
#include <helper.h>

class DayAOC201901
{
public:
  DayAOC201901(const char *inputfile);
  void Process(const char *input);
  void Part1();
  void Part2();

private:
  const char *_inputfile;
  Helper _helper;
  int _totalinputmass = 0;

  int _totalfuel_part1 = 0;
  int _totalfuel_part2 = 0;
};

#endif