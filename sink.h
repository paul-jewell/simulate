#ifndef SINK_H
#define SINK_H

class Sink
{
 public:
  Sink(EventList *list) { eventlist = list; };
 private:
  EventList *eventlist;
};


#endif
