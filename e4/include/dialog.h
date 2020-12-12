#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "map.h"
class Dialog
{
    Map map;
    void query_bus();
    void query_path();
    void query_stop();
public:
    Dialog(const char* file_name);
    Dialog(const Map& map);
    void begin_dialog();
};

#endif // _DIALOG_H_