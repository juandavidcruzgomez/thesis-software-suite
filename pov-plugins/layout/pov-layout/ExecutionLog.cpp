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


#include "ExecutionLog.h"

string ExecutionLog::SELF_EVENT_LOG = "SELF_EVENT_LOG";

string ExecutionLog::SELF_ERROR_LOG = "SELF_ERROR_LOG";

ExecutionLog::ExecutionLog()
{
    event_list.insert(pair<string, Event*>(SELF_EVENT_LOG, new Event()) );
    char msg[BUFFER];
    sprintf( msg, "Log has started %ld", time(NULL)  );
    log_event( SELF_EVENT_LOG, (void*)msg );
    event_list.insert(pair<string, Event*>(SELF_ERROR_LOG, new Event() ));
    event_list[SELF_ERROR_LOG]->type = ERROR_MSG;
}

ExecutionLog::~ExecutionLog()
{

}

void ExecutionLog::log_event( string event_name, void* event ) {
    if ( event_list.count(event_name) > 0 ) {
        event_list[event_name]->valid = true;
        if ( event_list[event_name]->type == LIST_LOG ) {
            event_list[event_name]->delta.push_back(*static_cast<float*>(event));
        } else if ( event_list[event_name]->type == EVENT_MSG || event_list[event_name]->type == ERROR_MSG ) {
            char* msg = static_cast<char*>(event);
            snprintf( event_list[event_name]->message, BUFFER, msg );// The idea here is to store BUFFER bytes only
        } else {
            event_list[event_name]->time = (long)event;
        }
    } else {
        sprintf( event_list[SELF_ERROR_LOG]->message, "ERROR: Event %s does not exist", event_name.c_str() );
    }
}

void ExecutionLog::create_event( string event_name, int type ) {
    if ( event_list.count(event_name) == 0 ) {
        event_list.insert(pair<string, Event*>(event_name, new Event() ));
        event_list[event_name]->type = type;
    } else {
        sprintf( event_list[SELF_ERROR_LOG]->message, "ERROR: Event %s already exists", event_name.c_str() );
    }
}

void ExecutionLog::print_events() {
    map<string, Event*>::iterator event_iter;
    for ( event_iter = event_list.begin(); event_iter != event_list.end(); ++event_iter ) {
        if ( (*event_iter).second->valid ) {
            if ( (*event_iter).second->type == ERROR_MSG ) {
                cout << "EE\t";
            } else {
                cout << "--\t";
            }
            cout << (*event_iter).first.c_str() << ": [Message=>" << (*event_iter).second->message << ", Time=>" << (*event_iter).second->time <<
                 ", Delta=>(list " << (*event_iter).second->delta.size() << " elements)]" << endl;
        }
    }
}
