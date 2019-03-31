/**
 Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne

 juan.cruzgomez@telecom-bretagne.eu 
 juandavidcruz@gmail.com

 Licensed under the EUPL, Version 1.2 or – as soon theywill be approved 
 by the European Commission - subsequent versions of the 
 EUPL (the "Licence");

 You may not use this work except in compliance with the Licence.
 You may obtain a copy of the Licence at:

    https://joinup.ec.europa.eu/software/page/eupl5
  
 Unless required by applicable law or agreed to inwriting, software 
 distributed under the Licence isdistributed on an *"AS IS"* basis,
 *WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND*, either express or implied.
 See the Licence for the specific language governing permissions and limitations 
 under the Licence.
*/


#ifndef EXECUTIONLOG_H
#define EXECUTIONLOG_H

#include <map>
#include <vector>
#include <string>
#include <string.h>
#include <inttypes.h>
#include <stdio.h>
#include <iostream>

#define ERROR_MSG	0
#define EVENT_MSG	1
#define TIME_LOG	2
#define LIST_LOG	3

#define BUFFER	128

using namespace std;

struct Event{
  bool valid;
  int type;
  char message[BUFFER];
  long time;
  vector<float> delta;
  explicit Event(){
      type = EVENT_MSG;
      memset(message,'\0',BUFFER);
      time = -1;
      valid = false;
  }
};

/**
 * The idea of this class is to allows the different components of the 
 * program to register different events and times. This could be used to
 * measure the performance of the algorithm and have some statistics.
 */
class ExecutionLog
{

public:
    ExecutionLog();
    virtual ~ExecutionLog();
    /**
     * 
     */
    void log_event( string event_name, void* event );
    /**
     * Adds an event to the event table
     */
    void create_event( string event_name, int type );
    /**
     * Prints all the events registered on the table
     */
    void print_events();
    
private:
  /**
   * The list of events logged
   */
  map<string, Event*> event_list;
  
  static string SELF_EVENT_LOG;
  
  static string SELF_ERROR_LOG;

};

#endif // EXECUTIONLOG_H
