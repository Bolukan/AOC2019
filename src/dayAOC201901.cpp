#include <dayAOC201901.h>
#define DELIMITERS "\r\n"

DayAOC201901::DayAOC201901(const char *inputfile)
    : _inputfile(inputfile),
      _helper(std::bind(&DayAOC201901::Process, this, std::placeholders::_1))
{
  // Process input
  _helper.SplitString(_inputfile, DELIMITERS);

  // Output statistics
  Serial.println("Statistics input file:");
  Serial.printf("# input lines: %d\n", _helper.InputCounter);
  Serial.printf("Sum of input (total mass): %d\n", _totalinputmass);
}

void DayAOC201901::Process(const char *input)
{
  int mass = atoi(input);
  _totalinputmass += mass;

  // Part 1
  int fuelmass = (mass < 9) ? 0 : (mass / 3) - 2;
  _totalfuel_part1 += fuelmass;
 
  // Part 2
  int fuelforthismass = 0;
  while (fuelmass > 0)
  {
    fuelforthismass += fuelmass;
    fuelmass = (fuelmass < 9) ? 0 : (fuelmass / 3) - 2;
  }
  _totalfuel_part2 += fuelforthismass;
}

void DayAOC201901::Part1()
{
  Serial.println("Part 1: What is the sum of the fuel requirements?");
  Serial.printf("Answer: %d\n", _totalfuel_part1);
}

void DayAOC201901::Part2()
{
  Serial.println("Part 2: What is the sum of the fuel requirements?");
  Serial.printf("Answer: %d\n", _totalfuel_part2);
}