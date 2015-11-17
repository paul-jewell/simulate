#ifndef SIMULATE_H
#define SIMULATE_H

#include <string>
#include <list>

typedef std::list<Process*> ProcessList;

void err(char *msg);
void err(std::string str);

#endif
