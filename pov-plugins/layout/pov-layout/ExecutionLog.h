/**
 The MIT License (MIT)

 Copyright (c) 2013 Juan David Cruz Gómez and Telecom - Bretagne 
 juan.cruzgomez@telecom-bretagne.eu

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
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
