/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  Juan David Cruz Gomez <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
